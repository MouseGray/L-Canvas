#include "l_tcanvasobject.h"

L_TCanvasObject::L_TCanvasObject() : L_CanvasObject()
{
    m_timer.setSingleShot(false);
}

void L_TCanvasObject::start(void (L_TCanvasObject::*function)())
{
    m_timer.start(interval);
    (this->*function)();
    connect(&m_timer, &QTimer::timeout, this, function, Qt::ConnectionType::DirectConnection);
}

void L_TCanvasObject::stop()
{
    m_timer.stop();
    m_timer.disconnect();
}


