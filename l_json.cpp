#include "l_json.h"

template <>
bool ljson::jsonToValue_<bool>(const QJsonValue& json) {
    return json.toBool();
}

template <>
int ljson::jsonToValue_<int>(const QJsonValue& json) {
    return json.toInt();
}

template <>
double ljson::jsonToValue_<double>(const QJsonValue& json) {
    return json.toDouble();
}

template <>
QString ljson::jsonToValue_<QString>(const QJsonValue& json) {
    return json.toString();
}

template <>
QJsonObject ljson::jsonToValue_<QJsonObject>(const QJsonValue& json) {
    return json.toObject();
}

template <>
QJsonArray ljson::jsonToValue_<QJsonArray>(const QJsonValue& json) {
   return json.toArray();
}
