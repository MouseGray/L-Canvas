#ifndef L_TASK_H
#define L_TASK_H

#include "L_Canvas_global.h"

#include <QObject>
#include <QVector>
#include <QDebug>

#include "l_taskobject.h"

class LCANVAS_EXPORT L_Task : public QObject
{
    Q_OBJECT
public:
    explicit L_Task(QObject *parent = nullptr);

    QJsonObject toJSON();

    // throws std::invalid_argument, std::bad_alloc
    void fromJSON(const QJsonObject& json) noexcept(false);

    inline QString title() const noexcept { return m_title; }
    inline QString text()  const noexcept { return m_text;  }
    inline QString name()  const { return m_data->name(); }

    inline bool hasValidData() const noexcept { return m_data != nullptr; };

    L_TaskObject* data() const;

    void next();
    void previous();

    L_TaskObject *current() const;

    void push(L_CanvasObject* obj);
    void pop();

    void rotate(int degree);
    void move(int x, int y);
    void resize(int width, int height);
    void paint(QColor color);
signals:
    void changed();
public slots:
    void changed_slot();
private:
    QString m_title;
    QString m_text;

    L_TaskObject* m_data = nullptr;

    L_TaskObject* m_current = nullptr;
};

#endif // L_TASK_H
