QT += gui core widgets

TEMPLATE = lib
DEFINES += LCANVAS_LIBRARY

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    l_canvas.cpp \
    l_canvasobject.cpp \
    l_container.cpp \
    l_task.cpp \
    l_taskobject.cpp \
    l_tcanvasobject.cpp

HEADERS += \
    L_Canvas_global.h \
    l_canvas.h \
    l_canvasobject.h \
    l_container.h \
    l_task.h \
    l_taskobject.h \
    l_tcanvasobject.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
