#ifndef COMMAND_HELPER_H
#define COMMAND_HELPER_H

#include "Command_Helper_global.h"
#include "gps_position.h"

#include <QVector>

class COMMAND_HELPERSHARED_EXPORT Command_Helper {
public:

    struct mavCMD_numberList{
        mavCMD_numberList() : setHome(179){}
        int setHome;
    };

public:
    Command_Helper();

    QVector<double> convert_setHome(const int &useCurrent, const GPS_Position &Position);
};

#endif // COMMAND_HELPER_H
