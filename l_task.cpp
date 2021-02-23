#include "l_task.h"

L_Task::L_Task(QObject *parent) : QObject(parent)
{
    connect(&m_container, SIGNAL(changed()), this, SLOT(changed_slot()));
}

L_Task::~L_Task()
{
    _clear();
}

bool L_Task::initialize(QJsonObject &json)
{

    if(!fromJSON(json)) return false;
    m_container.fill(std::move(m_objects));
    for(int i = 0; i < m_container.size(); i++){
        connect(&m_container[i].object(), SIGNAL(changed()), this, SLOT(changed_slot()));
    }
    return true;
}

void L_Task::toJSON(QJsonObject &json)
{
    json.insert("title", m_title);
    json.insert("text",  m_text);

    if(m_objects.isEmpty()) return;

    auto&& arr = QJsonArray();
    for(auto&& a: m_objects){
        auto&& obj = QJsonObject();
        a->toJSON(obj);
        arr.append(obj);
    }
    json.insert("data", arr);
}

bool L_Task::fromJSON(QJsonObject &json)
{
    QJsonValue value = json["title"];
    if(!value.isString()) return false;
    m_title = value.toString();

    value = json["text"];
    if(!value.isString()) return false;
    m_text = value.toString();

    value = json["data"];
    _clear();
    if(value.isArray())
    {
        auto&& arr = value.toArray();
        for(auto&& a: arr){
            auto&& obj = a.toObject();
            m_objects.append(new L_TaskObject());
            m_objects.back()->fromJSON(obj);
        }
    }
    return true;
}

void L_Task::changed_slot()
{
    emit changed();
}

void L_Task::_clear()
{
    for(auto&& a: m_objects) delete a;
    m_objects.clear();
}
