#include "command_helper.h"


Command_Helper::Command_Helper()
{
}

QVector<double> Command_Helper::convert_setHome(const int &useCurrent,const GPS_Position &Position)
{
    QVector<double> returnVector(7);
    returnVector.insert(0 , (double)useCurrent);
    returnVector.insert(1 , 0.0);
    returnVector.insert(2 , 0.0);
    returnVector.insert(3 , 0.0);
    returnVector.insert(4 , Position.Latitude);
    returnVector.insert(5 , Position.Longitude);
    returnVector.insert(6 , Position.Altitude);

    return(returnVector);
}

QVector<double> Command_Helper::convert_takeOff(const GPS_Position &Position)
{
    QVector<double> returnVector(7);
    returnVector.insert(0 , 0.0);
    returnVector.insert(1 , 0.0);
    returnVector.insert(2 , 0.0);
    returnVector.insert(3 , 0.0);
    returnVector.insert(4 , Position.Latitude);
    returnVector.insert(5 , Position.Longitude);
    returnVector.insert(6 , Position.Altitude);

    return(returnVector);
}

