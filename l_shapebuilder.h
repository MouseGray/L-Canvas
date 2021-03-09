#ifndef L_SHAPEBUILDER_H
#define L_SHAPEBUILDER_H

#include <QColor>
#include <QPoint>
#include <QSize>
#include <QJsonValue>

#include "l_canvasobject.h"

class L_ShapeBuilder
{
public:
    enum class Build {
        always,
        onlyValid
    };
    L_ShapeBuilder(const QJsonValue &jtype);

    L_ShapeBuilder& angle(const QJsonValue &jangle);

    L_ShapeBuilder& color(const QJsonValue &jcolor);

    L_ShapeBuilder& pos(const QJsonValue &jpos);

    L_ShapeBuilder& size(const QJsonValue &jsize);

    L_CanvasObject* build(Build type, bool* status = nullptr);

private:
    L_CanvasObjType _type;
    int _angle;
    QColor _color;
    QPoint _pos;
    QSize _size;

    bool _invalid;
};

#endif // L_SHAPEBUILDER_H
