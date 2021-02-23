#include "l_canvas.h"

L_Canvas::L_Canvas(QWidget *parent) : QWidget(parent) {}

//void L_Canvas::mousePressEvent(QMouseEvent *event)
//{
//    Q_UNUSED(event);
//}

//void L_Canvas::mouseMoveEvent(QMouseEvent *event)
//{
//    Q_UNUSED(event);
//}

//void L_Canvas::mouseReleaseEvent(QMouseEvent *event)
//{
//    Q_UNUSED(event);
//}

void L_Canvas::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    auto& container = m_task->container();
    for(int i = 0; i < container.size(); i++){
        container[i].object().draw(painter, QPoint(width() >> 1, height() >> 1), i == container.current() ? L_CanvasObjSelect::selected:L_CanvasObjSelect::null);
    }
}

void L_Canvas::setTask(L_Task* task)
{
    m_task = task;
    connect(m_task, SIGNAL(changed()), this, SLOT(update()));
}
