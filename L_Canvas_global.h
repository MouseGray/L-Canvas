#ifndef LCANVAS_GLOBAL_H
#define LCANVAS_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LCANVAS_LIBRARY)
#  define LCANVAS_EXPORT Q_DECL_EXPORT
#else
#  define LCANVAS_EXPORT Q_DECL_IMPORT
#endif

#endif // LCANVAS_GLOBAL_H
