#ifndef L_CONTAINER_H
#define L_CONTAINER_H

#include <QVector>
#include "l_taskobject.h"

class LCANVAS_EXPORT L_Container : public QObject
{
    Q_OBJECT
public:
    L_Container();

    L_TaskObject& operator[](int n);

    void fill(QVector<L_TaskObject*>&& ptr);

    void next();
    void previous();

    int size() const { return m_data.size(); }
    int current() const { return m_current; }

    L_TaskObject& currentObj() { return *m_data[m_current]; }
signals:
    void changed();
private:
    int m_current = 0;
    QVector<L_TaskObject*> m_data;
};

#endif // L_CONTAINER_H
