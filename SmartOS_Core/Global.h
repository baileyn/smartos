#ifndef GLOBAL_H
#define GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SMARTOS_CORE_LIBRARY)
#  define SMARTOS_CORESHARED_EXPORT Q_DECL_EXPORT
#else
#  define SMARTOS_CORESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // GLOBAL_H
