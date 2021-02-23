#include "l_taskobject.h"

L_TaskObject::L_TaskObject()
{

}

void L_TaskObject::toJSON(QJsonObject &json)
{
    json.insert("name", m_name);
    QJsonObject obj;
    m_canvasObject.toJSON(obj);
    json.insert("object", obj);

    if(!m_subTaskObjects.isEmpty()) {
        QJsonArray array;
        for(auto a: m_subTaskObjects){
            QJsonObject obj;
            a->toJSON(obj);
            array.push_back(obj);
        }
        json.insert("sub", array);
    }
}

bool L_TaskObject::fromJSON(QJsonObject &json)
{
    QJsonValue value = json["name"];
    if(!value.isString()) return false;
    m_name = value.toString();

    value = json["object"];
    if(!value.isObject()) return false;
    QJsonObject obj = value.toObject();
    if(!m_canvasObject.fromJSON(obj)) return false;

    value = json["sub"];
    if(value.isArray())
    {
        QJsonArray array = value.toArray();
        for(auto a: array){
            L_TaskObject* tobj = new L_TaskObject();
            QJsonObject obj = a.toObject();
            tobj->fromJSON(obj);
            m_subTaskObjects.push_back(tobj);
        }
    }
    return true;
}

QString L_TaskObject::name()
{
    return m_name;
}

L_TCanvasObject &L_TaskObject::object()
{
    return m_canvasObject;
}

void L_TaskObject::getTape(QVector<L_TaskObject *> &dist)
{
    dist.append(this);
    for(auto a: m_subTaskObjects) a->getTape(dist);
}
