#ifndef USBJOY_HANDLER_GLOBAL_H
#define USBJOY_HANDLER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(USBJOY_HANDLER_LIBRARY)
#  define USBJOY_HANDLERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define USBJOY_HANDLERSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // USBJOY_HANDLER_GLOBAL_H
