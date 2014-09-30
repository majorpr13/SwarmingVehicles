#ifndef COMMAND_HELPER_GLOBAL_H
#define COMMAND_HELPER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(COMMAND_HELPER_LIBRARY)
#  define COMMAND_HELPERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define COMMAND_HELPERSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // COMMAND_HELPER_GLOBAL_H
