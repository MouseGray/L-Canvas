#ifndef L_TASKOBJECTBUILDER_H
#define L_TASKOBJECTBUILDER_H

#include "l_canvasobject.h"
#include "l_taskobject.h"
#include "l_shapebuilder.h"

#include <QString>
#include <list>
#include <memory>

class L_TaskObjectBuilder
{
public:
    enum class Build {
        always,
        onlyValid
    };

    L_TaskObjectBuilder();

    L_TaskObjectBuilder& name(const QJsonValue &jname);

    L_TaskObjectBuilder& object(const QJsonValue &jobject);

    L_TaskObjectBuilder& sub(const QJsonValue &jarray);

    L_TaskObject* build();
private:
    QString _name;

    oneget_ptr<L_CanvasObject> _object;

    std::list<oneget_ptr<L_TaskObject>> _subNodes;
};

#endif // L_TASKOBJECTBUILDER_H
