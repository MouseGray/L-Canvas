#ifndef L_TASKOBJECT_H
#define L_TASKOBJECT_H

#include "l_tcanvasobject.h"
#include "l_shapebuilder.h"
#include "l_oneget_ptr.h"
#include "l_json.h"

#define SUCCESS(exp) ((exp) != -1)

class LCANVAS_EXPORT L_TaskObject : public QObject
{
    Q_OBJECT
public:
    L_TaskObject(const QString& name, L_CanvasObject* object, std::list<oneget_ptr<L_TaskObject>>& sub);

    L_TaskObject(const L_TaskObject&) = delete;
    L_TaskObject(const L_TaskObject&&) = delete;

    L_TaskObject& operator=(const L_TaskObject&) = delete;
    L_TaskObject& operator=(const L_TaskObject&&) = delete;

    ~L_TaskObject();

    QJsonObject toJSON() const noexcept;

    QString name() const;

    inline bool hasObject() const noexcept { return m_canvasObject != nullptr; };

    L_CanvasObject* object();

    void pushObject(L_CanvasObject* obj);
    void popObject();

    L_TaskObject* begin();
    L_TaskObject* next(L_TaskObject* object = nullptr);
    L_TaskObject* previous(L_TaskObject* object = nullptr);
    L_TaskObject* end();
signals:
    void objectPushed();
    void objectPopped();
private:
    QString m_name;
    L_CanvasObject* m_canvasObject;

    L_TaskObject* m_parentTaskObject;
    std::vector<L_TaskObject*> m_subTaskObjects;
};

#endif // L_TASKOBJECT_H
