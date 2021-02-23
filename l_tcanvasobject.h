#ifndef L_TCANVASOBJECT_H
#define L_TCANVASOBJECT_H

#include <QTimer>
#include <QMetaObject>
#include "l_canvasobject.h"

class LCANVAS_EXPORT L_TCanvasObject : public L_CanvasObject
{
    Q_OBJECT
public:
    L_TCanvasObject();

    void start(void(L_TCanvasObject::*function)());
    void stop();
private:
    QTimer m_timer;

    static const int interval = 50;
};

#endif // L_TCANVASOBJECT_H
