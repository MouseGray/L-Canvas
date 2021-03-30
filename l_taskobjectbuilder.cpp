#include "l_taskobjectbuilder.h"

L_TaskObjectBuilder::L_TaskObjectBuilder() { }

L_TaskObjectBuilder &L_TaskObjectBuilder::name(const QJsonValue &jname)
{
    ljson::jsonToValue(_name, jname);
    return *this;
}

L_TaskObjectBuilder &L_TaskObjectBuilder::object(const QJsonValue &jobject)
{
    if (jobject.isObject()) {
        auto object = jobject.toObject();
        _object = L_ShapeBuilder()
                .type (object.value("type"))
                .angle(object.value("angle"))
                .color(object.value("color"))
                .pos  (object.value("position"))
                .size (object.value("size"))
                .build(L_ShapeBuilder::Build::onlyValid);
    }
    return *this;
}

L_TaskObjectBuilder &L_TaskObjectBuilder::sub(const QJsonValue &jarray)
{
    auto array = QJsonArray();
    if (ljson::jsonToValue<ljson::importance::optional>(array, jarray)) {
        for(const auto& a: array){
            auto jobject = a.toObject();
            _subNodes.emplace_back(L_TaskObjectBuilder()
                                .name  (jobject.value("name"))
                                .object(jobject.value("object"))
                                .sub   (jobject.value("sub"))
                                .build());
        }
    }
    return *this;
}

L_TaskObject *L_TaskObjectBuilder::build()
{
    return new L_TaskObject(_name, _object.get(), _subNodes);
}
