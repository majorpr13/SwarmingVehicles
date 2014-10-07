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


QVector<Command_Helper::defaultCMD_Structure> Command_Helper::getcmdstructure_TakeOff(const GPS_Position &currentGPS)
{
    QVector<defaultCMD_Structure> returnVector;

    defaultCMD_Structure defaultReturn;

    defaultReturn.parameterName = "Takeoff Pitch";

    returnVector.insert(0 , defaultReturn);

    defaultReturn.parameterName = "";
    defaultReturn.enabled = false;

    returnVector.insert(1 , defaultReturn);
    returnVector.insert(2 , defaultReturn);
    returnVector.insert(3 , defaultReturn);

    defaultReturn.enabled = true;

    defaultReturn.defaultValue = currentGPS.Latitude;
    defaultReturn.parameterName = "Latitude";
    returnVector.insert(4 , defaultReturn);

    defaultReturn.defaultValue = currentGPS.Longitude;
    defaultReturn.parameterName = "Longitude";
    returnVector.insert(5 , defaultReturn);

    defaultReturn.defaultValue = 5.0;
    defaultReturn.parameterName = "Altitude (m)";
    returnVector.insert(6 , defaultReturn);

    return(returnVector);

}


QVector<Command_Helper::defaultCMD_Structure> Command_Helper::getcmdstructure_SwarmTakeOff()
{
    QVector<defaultCMD_Structure> returnVector;

    defaultCMD_Structure defaultReturn;

    defaultReturn.parameterName = "";
    defaultReturn.enabled = false;

    returnVector.insert(0 , defaultReturn);
    returnVector.insert(1 , defaultReturn);
    returnVector.insert(2 , defaultReturn);
    returnVector.insert(3 , defaultReturn);
    returnVector.insert(4 , defaultReturn);
    returnVector.insert(5 , defaultReturn);

    defaultReturn.enabled = true;
    defaultReturn.defaultValue = 5.0;
    defaultReturn.parameterName = "Altitude (m)";
    returnVector.insert(6 , defaultReturn);

    return(returnVector);

}
