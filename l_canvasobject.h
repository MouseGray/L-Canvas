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
    static int rotateStep;
    static int resizeStep;
    static int moveStep;

    L_CanvasObject() {};

    L_CanvasObject(L_CanvasObjType type, QColor color,
                   int angle, QPoint pos, QSize size);

    void paint (QColor color );

    void draw  (QPainter& painter, QPoint&& startPoint, L_CanvasObjSelect select = L_CanvasObjSelect::null);

    void setSize(QSize size);
    void setPos (QPoint pos);

    void setSize(QPoint rPos);

    void setType(L_CanvasObjType type);
    L_CanvasObjType type() const;

    void toJSON  (QJsonObject& json);
    bool fromJSON(QJsonObject& json);

    void create(L_CanvasObjType type);
    void remove();

    static L_CanvasObjType getType(QString name);
    static QString getTypeName(L_CanvasObjType type);
    QPoint getPosition() const;

public slots:
    void rotateRight();
    void rotateLeft ();

    void increaseWidth();
    void decreaseWidth();
    void increaseHeight();
    void decreaseHeight();

    void moveUp();
    void moveUp2(int r);
    void moveDown();
    void moveLeft();
    void moveRight();
signals:
    void changed();
protected:
    int    m_angle    = 0;

    QColor m_color       ;

    QPoint m_position    ;
    QSize  m_size        ;

    L_CanvasObjType m_type = L_CanvasObjType::null;

    static const int minSize = 3;
    static const int maxSize = 200;

    static const int minPos = -200;
    static const int maxPos = 200;
};

#endif // L_CANVASOBJECT_H
