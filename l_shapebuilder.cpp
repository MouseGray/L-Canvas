#include "l_shapebuilder.h"

L_ShapeBuilder::L_ShapeBuilder(const QJsonValue &jtype) :
    _type(L_CanvasObjType::null),
    _angle(0),
    _color(QColor(0, 0, 0)),
    _pos(QPoint(0, 0)),
    _size(QSize(0, 0))
{
    if (jtype.isString())
        _type = L_CanvasObject::getType(jtype.toString());
    else
        _invalid = true;
}

L_ShapeBuilder& L_ShapeBuilder::angle(const QJsonValue &jangle)
{
    if (jangle.isDouble())
        _angle = jangle.toInt();
    else
        _invalid = true;
    return *this;
}

L_ShapeBuilder& L_ShapeBuilder::color(const QJsonValue &jcolor)
{
    if (jcolor.isObject()) {
        auto obj = jcolor.toObject();

        auto jred = obj["red"];
        if (jred.isDouble())
            _color.setRed(jred.toInt());
        else
            _invalid = true;

        auto jgreen = obj["green"];
        if (jgreen.isDouble())
            _color.setGreen(jgreen.toInt());
        else
            _invalid = true;

        auto jblue = obj["blue"];
        if (jblue.isDouble())
            _color.setBlue(jblue.toInt());
        else
            _invalid = true;
    }
    else
        _invalid = true;
    return *this;
}

L_ShapeBuilder& L_ShapeBuilder::pos(const QJsonValue &jpos)
{
    if (jpos.isObject()) {
        auto obj = jpos.toObject();

        auto jx = obj["x"];
        if (jx.isDouble())
            _pos.setX(jx.toInt());
        else
            _invalid = true;

        auto jy = obj["y"];
        if (jy.isDouble())
            _pos.setX(jy.toInt());
        else
            _invalid = true;
    }
    else
        _invalid = true;
    return *this;
}

L_ShapeBuilder& L_ShapeBuilder::size(const QJsonValue &jsize)
{
    if (jsize.isObject()) {
        auto obj = jsize.toObject();

        auto jwidth = obj["width"];
        if (jwidth.isDouble())
            _size.setWidth(jwidth.toInt());
        else
            _invalid = true;

        auto jheight = obj["height"];
        if (jheight.isDouble())
            _size.setHeight(jheight.toInt());
        else
            _invalid = true;
    }
    else
        _invalid = true;
    return *this;
}

L_CanvasObject *L_ShapeBuilder::build(Build type, bool *status)
{
    if (status != nullptr) *status = !_invalid;
    if (type == Build::onlyValid && _invalid) return nullptr;
    return new (std::nothrow) L_CanvasObject(_type, _color,
                                        _angle, _pos, _size);
}

