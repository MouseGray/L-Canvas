#ifndef L_CANVASOBJECT_H
#define L_CANVASOBJECT_H

#include "L_Canvas_global.h"

#include <QObject>
#include <QPainter>
#include <QtMath>

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

enum class L_CanvasObjSelect
{
    null,
    selected
};

enum class L_CanvasObjType
{
    null,
    point,
    line,
    triangle,
    rect,
    ellipse
};

class LCANVAS_EXPORT L_CanvasObject : public QObject
{
    Q_OBJECT
public:
    static constexpr int FIELD_SIZE = 250;

    static int rotateStep;
    static int resizeStep;
    static int moveStep;

    static const L_CanvasObject null_object;

    L_CanvasObject() { qDebug() << "created object:" << "null"; };

    L_CanvasObject(L_CanvasObjType type, QColor color,
                   int angle, QPoint pos, QSize size);

    ~L_CanvasObject() { qDebug() << "deleted object:" << getTypeName(m_type); }



    void draw(QPainter& painter, const QPoint& startPoint, int UPP_X, int UPP_Y, L_CanvasObjSelect select = L_CanvasObjSelect::null);

    L_CanvasObjType type() const;

    QJsonObject toJSON();

    static L_CanvasObjType getType(QString name);
    static QString getTypeName(L_CanvasObjType type);
    QPoint getPosition() const;

public slots:
    bool rotate(int degree);
    bool resize(int width, int height);
    bool move(int x, int y);
    bool paint(QColor color);
protected:
    int    m_angle    = 0;

    QColor m_color       ;

    QPoint m_position    ;
    QSize  m_size        ;

    L_CanvasObjType m_type = L_CanvasObjType::null;

    static constexpr int MIN_SIZE = 3;
    static constexpr int MAX_SIZE = 100;
};

#endif // L_CANVASOBJECT_H
