#include "l_task.h"
#include "l_taskobjectbuilder.h"

L_Task::L_Task(QObject *parent) : QObject(parent) { }

QJsonObject L_Task::toJSON()
{
    assert(m_data);

    auto json = QJsonObject();
    json.insert("title", m_title);
    json.insert("text",  m_text);
    json.insert("data",  m_data->toJSON());
    return json;
}

void L_Task::fromJSON(const QJsonObject &json) noexcept(false)
{
    auto title = ljson::jsonToValue<QString>(json["title"]);
    auto text  = ljson::jsonToValue<QString>(json["text"]);

    auto jobject = ljson::jsonToValue<QJsonObject>(json["data"]);
    auto data = L_TaskObjectBuilder()
            .name   (jobject.value("name"))
            .object (jobject.value("object"))
            .sub    (jobject.value("sub"))
            .build  ();

    auto current = data->begin();
    if (current == nullptr) throw std::invalid_argument("Data does not contain elements.");

    delete m_data;
    m_data = nullptr;

    m_title   = title;
    m_text    = text;
    m_data    = data;
    m_current = current;
}

L_TaskObject* L_Task::data() const
{
    return m_data;
}

void L_Task::next()
{
    if (m_current == nullptr) return;
    m_current = m_current->next();
    if (m_current == nullptr) m_current = m_data->begin();
}

void L_Task::previous()
{
    if (m_current == nullptr) return;
    m_current = m_current->previous();
    if (m_current == nullptr) m_current = m_data->end();
}

void L_Task::changed_slot()
{
    emit changed();
}

L_TaskObject *L_Task::current() const
{
    return m_current;
}

void L_Task::push(L_CanvasObject *obj)
{
    if (m_current == nullptr) return;
    m_current->pushObject(obj);
    emit changed();
}

void L_Task::pop()
{
    if (m_current == nullptr) return;
    m_current->popObject();
    emit changed();
}

void L_Task::rotate(int degree)
{
    if (m_current == nullptr) return;
    if (m_current->object()->rotate(degree)) emit changed();
}

void L_Task::move(int x, int y)
{
    if (m_current == nullptr) return;
    if (m_current->object()->move(x, y)) emit changed();
}

void L_Task::resize(int width, int height)
{
    if (m_current == nullptr) return;
    if (m_current->object()->resize(width, height)) emit changed();
}

void L_Task::paint(QColor color)
{
    if (m_current == nullptr) return;
    m_current->object()->paint(color);
    emit changed();
}
