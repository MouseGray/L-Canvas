#include "l_canvasobject.h"

int L_CanvasObject::rotateStep = 3;
int L_CanvasObject::resizeStep = 2;
int L_CanvasObject::moveStep = 2;

void L_CanvasObject::rotateRight()
{
    m_angle = (m_angle + rotateStep) % 360;
    emit changed();
}

void L_CanvasObject::rotateLeft()
{
    m_angle = (m_angle - rotateStep + 360) % 360;
    emit changed();
}

void L_CanvasObject::increaseWidth()
{
    m_size.setWidth(qMin(m_size.width() + resizeStep, maxSize));
    emit changed();
}

void L_CanvasObject::decreaseWidth()
{
    m_size.setWidth(qMax(m_size.width() - resizeStep, minSize));
    emit changed();
}

void L_CanvasObject::increaseHeight()
{
    m_size.setHeight(qMin(m_size.height() + resizeStep, maxSize));
    emit changed();
}

void L_CanvasObject::decreaseHeight()
{
    m_size.setHeight(qMax(m_size.height() - resizeStep, minSize));
    emit changed();
}

void L_CanvasObject::moveUp()
{
    m_position.setY(qMin(m_position.y() + moveStep, maxPos));
    emit changed();
}

void L_CanvasObject::moveDown()
{
    m_position.setY(qMax(m_position.y() - moveStep, minPos));
    emit changed();
}

void L_CanvasObject::moveRight()
{
    m_position.setX(qMin(m_position.x() + moveStep, maxPos));
    emit changed();
}

void L_CanvasObject::moveLeft()
{
    m_position.setX(qMax(m_position.x() - moveStep, minPos));
    emit changed();
}

L_CanvasObject::L_CanvasObject(L_CanvasObjType type, QColor color, int angle, QPoint pos, QSize size)
{
    m_type = type;
    m_color = color;
    m_angle = angle;
    m_position = pos;
    m_size = size;
}

void L_CanvasObject::paint(QColor color)
{
    m_color = color;
    emit changed();
}

void L_CanvasObject::setSize(QSize size)
{
    m_size = size;
    emit changed();
}

void L_CanvasObject::setPos(QPoint pos)
{
    m_position = pos;
    emit changed();
}

void L_CanvasObject::setSize(QPoint rPos)
{
    m_size = QSize(rPos.x() - m_position.x(), rPos.y() - m_position.y());
    emit changed();
}

void L_CanvasObject::setType(L_CanvasObjType type)
{
    m_type = type;
}

L_CanvasObjType L_CanvasObject::type() const
{
    return m_type;
}

void L_CanvasObject::toJSON(QJsonObject &json)
{
    json.insert("type", getTypeName(m_type));

    if(m_type == L_CanvasObjType::null) return;

    QJsonObject color;
    color.insert("r", m_color.red  ());
    color.insert("g", m_color.green());
    color.insert("b", m_color.blue ());

    QJsonObject position;
    position.insert("x", m_position.x());
    position.insert("y", m_position.y());

    QJsonObject size;
    size.insert("width",  m_size.width ());
    size.insert("height", m_size.height());

    json.insert("color",    color   );
    json.insert("angle",    m_angle );
    json.insert("position", position);
    json.insert("size",     size    );
}

bool L_CanvasObject::fromJSON(QJsonObject &json)
{
    QJsonValue value = json["type"];
    if(!value.isString()) return false;
    m_type = getType(value.toString());

    if(m_type == L_CanvasObjType::null) return true;

    value = json["color"];
    if(!value.isObject()) return false;

    QJsonObject obj = value.toObject();
    value = obj["r"];
    if(!value.isDouble()) return false;
    m_color.setRed(value.toInt());
    value = obj["g"];
    if(!value.isDouble()) return false;
    m_color.setGreen(value.toInt());
    value = obj["b"];
    if(!value.isDouble()) return false;
    m_color.setBlue(value.toInt());

    value = json["angle"];
    if(!value.isDouble()) return false;
    m_angle = value.toInt();

    value = json["position"];
    if(!value.isObject()) return false;

    obj = value.toObject();
    value = obj["x"];
    if(!value.isDouble()) return false;
    m_position.setX(value.toInt());
    value = obj["y"];
    if(!value.isDouble()) return false;
    m_position.setY(value.toInt());

    value = json["size"];
    if(!value.isObject()) return false;

    obj = value.toObject();
    value = obj["width"];
    if(!value.isDouble()) return false;
    m_size.setWidth(value.toInt());
    value = obj["height"];
    if(!value.isDouble()) return false;
    m_size.setHeight(value.toInt());

    return true;
}

void L_CanvasObject::create(L_CanvasObjType type)
{
    m_type = type;
    m_angle = 0;
    if(type != L_CanvasObjType::point){
        m_position = QPoint(-15, 15);
        m_size = QSize(30, 30);
        m_color = QColor(255, 255, 255);
    }
    else {
        m_position = QPoint(1, -1);
        m_size = QSize(3, 3);
        m_color = QColor(0, 0, 0);
    }
    emit changed();
}

void L_CanvasObject::remove()
{
    m_type = L_CanvasObjType::null;
    emit changed();
}

L_CanvasObjType L_CanvasObject::getType(QString name)
{
    if(name == "null")      return L_CanvasObjType::null;
    if(name == "point")     return L_CanvasObjType::point;
    if(name == "line")      return L_CanvasObjType::line;
    if(name == "triangle")  return L_CanvasObjType::triangle;
    if(name == "rect")      return L_CanvasObjType::rect;
    if(name == "ellipse")   return L_CanvasObjType::ellipse;
    return L_CanvasObjType::null;
}

QString L_CanvasObject::getTypeName(L_CanvasObjType type)
{
    switch (type) {
    case L_CanvasObjType::null:     return "null";
    case L_CanvasObjType::point:    return "point";
    case L_CanvasObjType::line:     return "line";
    case L_CanvasObjType::triangle: return "triangle";
    case L_CanvasObjType::rect:     return "rect";
    case L_CanvasObjType::ellipse:  return "ellipse";
    }
    return "null";
}

void L_CanvasObject::draw(QPainter &painter, QPoint &&startPoint, L_CanvasObjSelect select)
{
    auto&& pos = QPoint(startPoint.x() + m_position.x(), startPoint.y() - m_position.y());

    if(m_type == L_CanvasObjType::null) return;

    painter.save();

    painter.setBrush(m_color);

    auto&& mid = QPoint(m_size.width() >> 1, m_size.height() >> 1);
    auto&& center = pos + mid;

    painter.translate(center);
    painter.rotate   (m_angle);

    if(select == L_CanvasObjSelect::null) painter.setPen(QColor(0, 0, 0));
    else painter.setPen(QColor(255, 0, 0));

    switch (m_type)
    {
    case L_CanvasObjType::null:
        break;
    case L_CanvasObjType::point:
        painter.drawEllipse(-mid, m_size.width(), m_size.height());
        break;
    case L_CanvasObjType::line:
        painter.drawLine(-mid, QPoint(m_size.width(), m_size.height()));
        break;
    case L_CanvasObjType::triangle: {
        QPoint polygon[3];
        polygon[0] = QPoint(-mid.x(),  mid.y());
        polygon[1] = QPoint( mid.x(),  mid.y());
        polygon[2] = QPoint(0       , -mid.y());
        painter.drawPolygon(polygon, 3);
        break;
    }
    case L_CanvasObjType::rect:
        painter.drawRect(-mid.x(), -mid.y(), m_size.width(), m_size.height());
        break;
    case L_CanvasObjType::ellipse:
        painter.drawEllipse(-mid.x(), -mid.y(), m_size.width(), m_size.height());
        break;
    }

    painter.resetTransform();

    painter.restore();
}

