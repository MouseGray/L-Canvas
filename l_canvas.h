#ifndef LCANVAS_H
#define LCANVAS_H

#include "L_Canvas_global.h"

#include <QPainter>
#include <QtMath>
#include <QWidget>
#include <QMouseEvent>

#include "l_task.h"

class LCANVAS_EXPORT L_Canvas : public QWidget
{
    Q_OBJECT
public:
    explicit L_Canvas(QWidget *parent = nullptr);

    //void mousePressEvent  (QMouseEvent *event);
    //void mouseMoveEvent   (QMouseEvent *event);
    //void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent (QPaintEvent  *event) override;

    void resizeEvent(QResizeEvent *event) override;

    void setTask(L_Task* task);
private:
    L_Task* m_task = nullptr;

    float UPP_X = 1.0f;
    float UPP_Y = 1.0f;
};

#endif // LCANVAS_H
