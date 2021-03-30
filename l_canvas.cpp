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
    assert(m_task != nullptr);

    QPainter painter(this);   
    if (m_task->data() == nullptr) {
        painter.drawText(QRect(0, 0, width(), height()), Qt::AlignCenter, "No data");
        return;
    }
    for (auto cur = m_task->data()->begin(); cur != nullptr; cur = cur->next()) {
        if (cur->object() == nullptr) continue;
        cur->object()->draw(painter, QPoint(width() >> 1, height() >> 1), UPP_X, UPP_Y, cur == m_task->current() ? L_CanvasObjSelect::selected:L_CanvasObjSelect::null);
    }
}

void L_Canvas::setTask(L_Task* task)
{
    m_task = task;
    connect(m_task, SIGNAL(changed()), this, SLOT(update()));
}


void L_Canvas::resizeEvent(QResizeEvent *event)
{
    UPP_X = event->size().width()/L_CanvasObject::FIELD_SIZE;
    UPP_Y = event->size().height()/L_CanvasObject::FIELD_SIZE;
}
