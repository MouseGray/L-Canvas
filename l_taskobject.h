#ifndef L_TASKOBJECT_H
#define L_TASKOBJECT_H

#include "l_tcanvasobject.h"

#define SUCCESS(exp) ((exp) != -1)

class LCANVAS_EXPORT L_TaskObject
{
public:
    L_TaskObject();

    void toJSON  (QJsonObject& json);
    bool fromJSON(QJsonObject& json);

    QString name();

    L_CanvasObject& object();

    void getTape(QVector<L_TaskObject*>& dist);
private:
    QString m_name;
    L_CanvasObject m_canvasObject;

    QVector<L_TaskObject*> m_subTaskObjects;
};

#endif // L_TASKOBJECT_H
