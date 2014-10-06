#ifndef COMMAND_HELPER_H
#define COMMAND_HELPER_H

#include "Command_Helper_global.h"
#include "gps_position.h"
#include <QString>
#include <QVector>

class COMMAND_HELPERSHARED_EXPORT Command_Helper {
public:

    struct mavCMD_numberList{
        mavCMD_numberList() : setHome(179), takeOff(22){}
        int setHome;
        int takeOff;
    };

    struct defaultCMD_Structure
    {
        defaultCMD_Structure() : parameterName(""), defaultValue(0.0), enabled(true){}
        QString parameterName;
        float defaultValue;
        bool enabled;
    };

public:
    Command_Helper();

    QVector<double> convert_setHome(const int &useCurrent, const GPS_Position &Position);

    QVector<double> convert_takeOff(const GPS_Position &Position);


};

#endif // COMMAND_HELPER_H
