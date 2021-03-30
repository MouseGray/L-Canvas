#include "l_taskobject.h"

#include <stdexcept>

L_TaskObject::L_TaskObject(const QString &name, L_CanvasObject *object, std::list<oneget_ptr<L_TaskObject> > &sub)
    : m_parentTaskObject(nullptr)
{
    m_name = name;
    m_canvasObject = object;
    for(auto& el: sub) {
        m_subTaskObjects.push_back(el.get());
        m_subTaskObjects.back()->m_parentTaskObject = this;
    }

    if (object != nullptr)
        emit objectPushed();
    qDebug() << "created tasobject:" << m_name;
}

L_TaskObject::~L_TaskObject()
{
    qDebug() << "deleted tasobject:" << m_name;

    delete m_canvasObject;
    for(auto& el: m_subTaskObjects) delete el;
}

QJsonObject L_TaskObject::toJSON() const noexcept
{
    auto json = QJsonObject();
    json.insert("name", m_name);

    if (m_canvasObject != nullptr)
        json.insert("object", m_canvasObject->toJSON());

    if(!m_subTaskObjects.empty()) {
        auto array = QJsonArray();
        for(auto a: m_subTaskObjects) {
            array.push_back(a->toJSON());
        }
        json.insert("sub", array);
    }

    return json;
}

void L_TaskObject::pushObject(L_CanvasObject* object)
{
    delete m_canvasObject;
    m_canvasObject = object;
    emit objectPushed();
}

void L_TaskObject::popObject()
{
    delete m_canvasObject;
    m_canvasObject = nullptr;
    emit objectPopped();
}

QString L_TaskObject::name() const
{
    return m_name;
}

L_CanvasObject *L_TaskObject::object()
{
    return m_canvasObject;
}

L_TaskObject *L_TaskObject::begin()
{
    if (m_subTaskObjects.empty()) return nullptr;
    return m_subTaskObjects.front();
}

L_TaskObject* L_TaskObject::next(L_TaskObject *object)
{
    if (object == nullptr) {
        if (m_subTaskObjects.empty())
            return safe_call_pfunction(m_parentTaskObject, &L_TaskObject::next, this);
        else
            return m_subTaskObjects.front();
    }

    auto res = std::find(m_subTaskObjects.begin(), m_subTaskObjects.end(), object);
    assert(res != m_subTaskObjects.end());

    if (++res == m_subTaskObjects.end())
        return safe_call_pfunction(m_parentTaskObject, &L_TaskObject::next, this);
    else
        return *res;
}

L_TaskObject* L_TaskObject::previous(L_TaskObject *object)
{
    if (object == nullptr)
        return safe_call_pfunction(m_parentTaskObject, &L_TaskObject::previous, this);

    auto res = std::find(m_subTaskObjects.begin(), m_subTaskObjects.end(), object);
    if (res == m_subTaskObjects.begin())
        return this;
    else
        return (*std::prev(res))->end();
}

L_TaskObject* L_TaskObject::end()
{
    if (m_subTaskObjects.empty()) return this;
    return m_subTaskObjects.back()->end();
}

