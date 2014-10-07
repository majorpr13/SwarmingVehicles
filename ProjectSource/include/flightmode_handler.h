#ifndef FLIGHTMODE_HANDLER_H
#define FLIGHTMODE_HANDLER_H

#include <QString>

#include "FlightMode_Handler_global.h"

class FLIGHTMODE_HANDLERSHARED_EXPORT FlightMode_Handler {
public:
    struct FlightModes
    {
         uint Stabilize;
         uint AltHold;
         uint Loiter;
         uint RTL;
         uint Auto;
         uint Acro;
         uint Sport;
         uint Drift;
         uint Guided;
         uint CircleFM;
         uint Position;
         uint Land;
         uint TakeOff;
         //int FollowMe;
         //int Simple;
         //int SuperSimple;
    };

    enum enum_FlightModes
    {
        Stabilize,
        AltHold,
        Loiter,
        RTL,
        Auto,
        Acro,
        Sport,
        Drift,
        Guided,
        CircleFM,
        Position,
        Land,
        TakeOff,
        //int FollowMe;
        //int Simple;
        //int SuperSimple;
        FlightMode_Length
    };

public:
    FlightMode_Handler();

    int FlightMode_StringtoEnum(const QString &QFlightMode);

    QString FlightMode_EnumtoString(const uint &FlightMode);

    enum_FlightModes getFlightMode(const uint &FlightMode);

    FlightModes m_FlightMode;
};

#endif // FLIGHTMODE_HANDLER_H
