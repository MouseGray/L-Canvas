#include "l_canvasobject.h"

int L_CanvasObject::rotateStep = 3;
int L_CanvasObject::resizeStep = 2;
int L_CanvasObject::moveStep = 2;

L_CanvasObject::L_CanvasObject(L_CanvasObjType type, QColor color, int angle, QPoint pos, QSize size)
{
    m_type     = type;
    m_color    = color;
    m_angle    = angle;
    m_position = pos;
    m_size     = size;

    qDebug() << "created object:" << getTypeName(type);
}

QPoint L_CanvasObject::getPosition() const
{
    return m_position;
}

bool L_CanvasObject::rotate(int degree)
{
    auto r = degree % 360;
    m_angle = (m_angle + r) % 360;
    return r != 0;
}

bool L_CanvasObject::resize(int width, int height)
{
    auto oldPoint = m_size;
    m_size.setWidth(std::clamp(m_size.width()  + width,  MIN_SIZE, MAX_SIZE));
    m_size.setHeight(std::clamp(m_size.height() + height, MIN_SIZE, MAX_SIZE));
    return m_size != oldPoint;
}

bool L_CanvasObject::move(int x, int y)
{
    auto oldPoint = m_position;
    m_position.setX(std::clamp(m_position.x() + x, -FIELD_SIZE, FIELD_SIZE));
    m_position.setY(std::clamp(m_position.y() + y, -FIELD_SIZE, FIELD_SIZE));
    return m_position != oldPoint;
}

bool L_CanvasObject::paint(QColor color)
{
    m_color = color;
    return true;
}

L_CanvasObjType L_CanvasObject::type() const
{
    return m_type;
}

QJsonObject L_CanvasObject::toJSON()
{
    auto json = QJsonObject();
    json.insert("type", getTypeName(m_type));

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

    return json;
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

void L_CanvasObject::draw(QPainter &painter, const QPoint &startPoint, int UPP_X, int UPP_Y, L_CanvasObjSelect select)
{
    if(m_type == L_CanvasObjType::null) return;

    auto center = QPointF(startPoint.x() + m_position.x()*UPP_X, startPoint.y() - m_position.y()*UPP_Y);

    painter.save();

    painter.setBrush(m_color);

    auto half = QPointF((m_size.width() >> 1)*UPP_X, (m_size.height() >> 1)*UPP_Y);

    painter.translate(center);
    painter.rotate   (m_angle);

    if(select == L_CanvasObjSelect::null) painter.setPen(QColor(0, 0, 0));
    else painter.setPen(QColor(255, 0, 0));

    switch (m_type)
    {
    case L_CanvasObjType::null:
        break;
    case L_CanvasObjType::point:
        painter.drawEllipse(QPoint(0, 0), m_size.width(), m_size.height());
        break;
    case L_CanvasObjType::line:
        painter.drawLine(QPoint(-half.x(), 0), QPoint(half.x(), 0));
        break;
    case L_CanvasObjType::triangle: {
        QPoint polygon[3];
        polygon[0] = QPoint(-half.x(),  half.y());
        polygon[1] = QPoint( half.x(),  half.y());
        polygon[2] = QPoint(        0, -half.y());
        painter.drawPolygon(polygon, 3);
        break;
    }
    case L_CanvasObjType::rect:
        painter.drawRect(-half.x(), -half.y(), m_size.width(), m_size.height());
        break;
    case L_CanvasObjType::ellipse:
        painter.drawEllipse(QPointF(0.0f, 0.0f), half.x(), half.y());
        break;
    }

    painter.resetTransform();

    painter.restore();
}

