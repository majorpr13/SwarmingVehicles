#ifndef COMMAND_HELPER_H
#define COMMAND_HELPER_H

#include "Command_Helper_global.h"

#include <QVector>

class COMMAND_HELPERSHARED_EXPORT Command_Helper {
public:
    Command_Helper();

    QVector<double> convert_setHome();
};

#endif // COMMAND_HELPER_H
