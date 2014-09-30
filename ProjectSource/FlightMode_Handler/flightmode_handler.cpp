#include "flightmode_handler.h"


FlightMode_Handler::FlightMode_Handler()
{

    m_FlightMode.Acro = 1;//
    m_FlightMode.AltHold = 2;//
    m_FlightMode.Auto = 3; //
    m_FlightMode.CircleFM = 7;
    m_FlightMode.Drift = 11;//
    //m_FlightMode.FollowMe = 0;
    m_FlightMode.Guided = 4; //
    m_FlightMode.Land = 9;//
    m_FlightMode.Loiter = 5;//
    m_FlightMode.Position = 0;
    m_FlightMode.RTL = 6;//
    //m_FlightMode.Simple = 0;
    m_FlightMode.Sport = 13;
    m_FlightMode.Stabilize = 0;//
   // m_FlightMode.SuperSimple = 0;
}


uint FlightMode_Handler::FlightMode_StringtoEnum(const QString &QFlightMode)
{
    if(QFlightMode == "Acro")
        return m_FlightMode.Acro;
    else if(QFlightMode == "AltHold")
        return m_FlightMode.AltHold;
    else if(QFlightMode == "Auto")
        return m_FlightMode.Auto;
    else if(QFlightMode == "Circle")
        return m_FlightMode.CircleFM;
    else if(QFlightMode == "Drift")
        return m_FlightMode.Drift;
    //else if(QFlightMode == "Follow Me")
        //return m_FlightMode.FollowMe;
    else if(QFlightMode == "Guided")
        return m_FlightMode.Guided;
    else if(QFlightMode == "Land")
        return m_FlightMode.Land;
    else if(QFlightMode == "Loiter")
        return m_FlightMode.Loiter;
    else if(QFlightMode == "Position")
        return m_FlightMode.Position;
    else if(QFlightMode == "RTL")
        return m_FlightMode.RTL;
    //else if(QFlightMode == "Simple")
        //return m_FlightMode.Simple;
    else if(QFlightMode == "Sport")
        return m_FlightMode.Sport;
    else if(QFlightMode == "Stabilize")
        return m_FlightMode.Stabilize;
    //else if(QFlightMode == "Super Simple")
        //return m_FlightMode.SuperSimple;
    else
        return -1;
}

QString FlightMode_Handler::FlightMode_EnumtoString(const uint &FlightMode)
{
    if(FlightMode == m_FlightMode.Acro)
        return "Acro";
    else if(FlightMode == m_FlightMode.AltHold)
        return "AltHold";
    else if(FlightMode == m_FlightMode.Auto)
        return "Auto";
    else if(FlightMode == m_FlightMode.CircleFM)
        return "Circle";
    else if(m_FlightMode.Drift)
        return "Drift";
    //else if(FlightMode == m_FlightMode.FollowMe)
        //return "Follow Me";
    else if(FlightMode == m_FlightMode.Guided)
        return "Guided";
    else if(FlightMode == m_FlightMode.Land)
        return "Land";
    else if(FlightMode == m_FlightMode.Loiter)
        return "Loiter";
    else if(FlightMode == m_FlightMode.Position)
        return "Position";
    else if(FlightMode == m_FlightMode.RTL)
        return "RTL";
    //else if(FlightMode == m_FlightMode.Simple)
        //return "Simple";
    else if(FlightMode == m_FlightMode.Sport)
        return "Sport";
    else if(FlightMode == m_FlightMode.Stabilize)
        return "Stabilize";
    //else if(FlightMode == m_FlightMode.SuperSimple)
        //return "Super Simple";
    else
        return "";
}

FlightMode_Handler::enum_FlightModes FlightMode_Handler::getFlightMode(const uint &FlightMode)
{
    if(FlightMode == m_FlightMode.Acro)
        return FlightMode_Handler::Acro;
    else if(FlightMode == m_FlightMode.AltHold)
        return FlightMode_Handler::AltHold;
    else if(FlightMode == m_FlightMode.Auto)
        return FlightMode_Handler::Auto;
    else if(FlightMode == m_FlightMode.CircleFM)
        return FlightMode_Handler::CircleFM;
    else if(m_FlightMode.Drift)
        return FlightMode_Handler::Drift;
    //else if(FlightMode == m_FlightMode.FollowMe)
        //return "Follow Me";
    else if(FlightMode == m_FlightMode.Guided)
        return FlightMode_Handler::Guided;
    else if(FlightMode == m_FlightMode.Land)
        return FlightMode_Handler::Land;
    else if(FlightMode == m_FlightMode.Loiter)
        return FlightMode_Handler::Loiter;
    else if(FlightMode == m_FlightMode.Position)
        return FlightMode_Handler::Position;
    else if(FlightMode == m_FlightMode.RTL)
        return FlightMode_Handler::RTL;
    //else if(FlightMode == m_FlightMode.Simple)
        //return "Simple";
    else if(FlightMode == m_FlightMode.Sport)
        return FlightMode_Handler::Sport;
    else if(FlightMode == m_FlightMode.Stabilize)
        return FlightMode_Handler::Stabilize;
    //else if(FlightMode == m_FlightMode.SuperSimple)
        //return "Super Simple";
    else
        return FlightMode_Handler::FlightMode_Length;
}
