#ifndef L_TASK_H
#define L_TASK_H

#include <QObject>
#include <QVector>
#include <QDebug>

#include "l_container.h"

class LCANVAS_EXPORT L_Task : public QObject
{
    Q_OBJECT
public:
    explicit L_Task(QObject *parent = nullptr);
    ~L_Task();

    bool initialize(QJsonObject &json);

    void toJSON  (QJsonObject& json);
    bool fromJSON(QJsonObject& json);

    inline QString title() const { return m_title; }
    inline QString text()  const { return m_text;  }

    inline L_Container& container() { return m_container; }
signals:
    void changed();
public slots:
    void changed_slot();
private:
    void _clear();

    QString m_title;
    QString m_text;

    QVector<L_TaskObject*> m_objects;

    L_Container m_container;
};

#endif // L_TASK_H
