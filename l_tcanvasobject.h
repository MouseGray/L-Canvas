#ifndef L_TCANVASOBJECT_H
#define L_TCANVASOBJECT_H

#include <QTimer>
#include <QMetaObject>
#include "l_canvasobject.h"

#include <functional>
#include <tr1/functional>

class LCANVAS_EXPORT L_TCanvasObject : public QObject
{
    Q_OBJECT
public:
    L_TCanvasObject();

    template<typename ...Args>
    void start(L_CanvasObject *obj, void(L_CanvasObject::*function)(Args...), Args... args) {
        m_timer.start(interval);
        auto binded = std::bind(function, obj, args...);
        connect(&m_timer, &QTimer::timeout, binded);
    }

    void stop();
private:
    QTimer m_timer;

    static const int interval = 50;
};

#endif // L_TCANVASOBJECT_H
