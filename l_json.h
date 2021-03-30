#ifndef L_JSON_H
#define L_JSON_H

#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>

#include <stdexcept>

#include "L_Canvas_global.h"

namespace ljson {

    enum class importance : bool {
        required,
        optional
    };

    template <typename T>
    constexpr QJsonValue::Type typeToJsonType();

    template <>
    constexpr QJsonValue::Type typeToJsonType<bool>() {
        return QJsonValue::Bool;
    }

    template <>
    constexpr QJsonValue::Type typeToJsonType<int>() {
        return QJsonValue::Double;
    }

    template <>
    constexpr QJsonValue::Type typeToJsonType<double>() {
        return QJsonValue::Double;
    }

    template <>
    constexpr QJsonValue::Type typeToJsonType<QString>() {
        return QJsonValue::String;
    }

    template <>
    constexpr QJsonValue::Type typeToJsonType<QJsonObject>() {
        return QJsonValue::Object;
    }

    template <>
    constexpr QJsonValue::Type typeToJsonType<QJsonArray>() {
        return QJsonValue::Array;
    }

    template <typename T>
    T jsonToValue_(const QJsonValue&);

    template <>
    LCANVAS_EXPORT bool jsonToValue_<bool>(const QJsonValue& json);

    template <>
    LCANVAS_EXPORT int jsonToValue_<int>(const QJsonValue& json);

    template <>
    LCANVAS_EXPORT double jsonToValue_<double>(const QJsonValue& json);

    template <>
    LCANVAS_EXPORT QString jsonToValue_<QString>(const QJsonValue& json);

    template <>
    LCANVAS_EXPORT QJsonObject jsonToValue_<QJsonObject>(const QJsonValue& json);

    template <>
    LCANVAS_EXPORT QJsonArray jsonToValue_<QJsonArray>(const QJsonValue& json);

    template <typename T>
    T jsonToValue(const QJsonValue& json) {
        if (json.type() != typeToJsonType<T>()) {
            throw std::invalid_argument("Incorrect json value.");
        }
        return jsonToValue_<T>(json);
    }

    template <importance I = importance::required, typename T>
    bool jsonToValue(T& value, const QJsonValue& json) {
        if (json.type() != typeToJsonType<T>()) {
            if constexpr (I == importance::required)
                throw std::invalid_argument("Incorrect json value.");
            else
                return false;
        }
        value = jsonToValue_<T>(json);
        return true;
    }
}

#endif // L_JSON_H
