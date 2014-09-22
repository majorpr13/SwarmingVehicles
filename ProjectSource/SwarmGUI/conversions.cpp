#include "conversions.h"
#include <iostream>
Conversions::Conversions()
{
    m_Initialization = new Initialization();
}

int Conversions::FlightMode_StringtoEnum(const QString &FlightMode)
{
    if(FlightMode == "Acro")
        return m_Initialization->m_FlightModeV.Acro;
    else if(FlightMode == "AltHold")
        return m_Initialization->m_FlightModeV.AltHold;
    else if(FlightMode == "Auto")
        return m_Initialization->m_FlightModeV.Auto;
    else if(FlightMode == "Circle")
        return m_Initialization->m_FlightModeV.CircleFM;
    else if(FlightMode == "Drift")
        return m_Initialization->m_FlightModeV.Drift;
    //else if(FlightMode == "Follow Me")
        //return m_Initialization->m_FlightModeV.FollowMe;
    else if(FlightMode == "Guided")
        return m_Initialization->m_FlightModeV.Guided;
    else if(FlightMode == "Land")
        return m_Initialization->m_FlightModeV.Land;
    else if(FlightMode == "Loiter")
        return m_Initialization->m_FlightModeV.Loiter;
    else if(FlightMode == "Position")
        return m_Initialization->m_FlightModeV.Position;
    else if(FlightMode == "RTL")
        return m_Initialization->m_FlightModeV.RTL;
    //else if(FlightMode == "Simple")
        //return m_Initialization->m_FlightModeV.Simple;
    else if(FlightMode == "Sport")
        return m_Initialization->m_FlightModeV.Sport;
    else if(FlightMode == "Stabilize")
        return m_Initialization->m_FlightModeV.Stabilize;
    //else if(FlightMode == "Super Simple")
        //return m_Initialization->m_FlightModeV.SuperSimple;
    else
        return -1;
}

QString Conversions::FlightMode_EnumtoString(const int &FlightMode)
{
    if(FlightMode == m_Initialization->m_FlightModeV.Acro)
        return "Acro";
    else if(FlightMode == m_Initialization->m_FlightModeV.AltHold)
        return "AltHold";
    else if(FlightMode == m_Initialization->m_FlightModeV.Auto)
        return "Auto";
    else if(FlightMode == m_Initialization->m_FlightModeV.CircleFM)
        return "Circle";
    else if(m_Initialization->m_FlightModeV.Drift)
        return "Drift";
    //else if(FlightMode == m_Initialization->m_FlightModeV.FollowMe)
        //return "Follow Me";
    else if(FlightMode == m_Initialization->m_FlightModeV.Guided)
        return "Guided";
    else if(FlightMode == m_Initialization->m_FlightModeV.Land)
        return "Land";
    else if(FlightMode == m_Initialization->m_FlightModeV.Loiter)
        return "Loiter";
    else if(FlightMode == m_Initialization->m_FlightModeV.Position)
        return "Position";
    else if(FlightMode == m_Initialization->m_FlightModeV.RTL)
        return "RTL";
    //else if(FlightMode == m_Initialization->m_FlightModeV.Simple)
        //return "Simple";
    else if(FlightMode == m_Initialization->m_FlightModeV.Sport)
        return "Sport";
    else if(FlightMode == m_Initialization->m_FlightModeV.Stabilize)
        return "Stabilize";
    //else if(FlightMode == m_Initialization->m_FlightModeV.SuperSimple)
        //return "Super Simple";
    else
        return "";
}

int Conversions::StreamMode_StringtoEnum(const QString &StreamMode)
{
    if(StreamMode == "Stream All")
        return m_Initialization->m_StreamModeV.StreamAll;
    else if(StreamMode == "Raw Sensors")
        return m_Initialization->m_StreamModeV.RawSensors;
    else if(StreamMode == "Extended Status")
        return m_Initialization->m_StreamModeV.ExtendedStatus;
    else if(StreamMode == "RC Channels")
        return m_Initialization->m_StreamModeV.RCChannels;
    else if(StreamMode == "Raw Controller")
        return m_Initialization->m_StreamModeV.RawController;
    else if(StreamMode == "Position")
        return m_Initialization->m_StreamModeV.Position;
    else if(StreamMode == "Extra 1")
        return m_Initialization->m_StreamModeV.Extra1;
    else if(StreamMode == "Extra 2")
        return m_Initialization->m_StreamModeV.Extra2;
    else if(StreamMode == "Extra 3")
        return m_Initialization->m_StreamModeV.Extra3;
    else
        return -1;
}

QString Conversions::StreamMode_EnumtoString(const int &StreamMode)
{
    if(StreamMode == m_Initialization->m_StreamModeV.StreamAll)
        return "Stream All";
    else if(StreamMode == m_Initialization->m_StreamModeV.RawSensors)
        return "Raw Sensors";
    else if(StreamMode == m_Initialization->m_StreamModeV.ExtendedStatus)
        return "Extended Status";
    else if(StreamMode == m_Initialization->m_StreamModeV.RCChannels)
        return "RC Channels";
    else if(StreamMode == m_Initialization->m_StreamModeV.RawController)
        return "Raw Controller";
    else if(StreamMode == m_Initialization->m_StreamModeV.Position)
        return "Position";
    else if(StreamMode == m_Initialization->m_StreamModeV.Extra1)
        return "Extra 1";
    else if(StreamMode == m_Initialization->m_StreamModeV.Extra2)
        return "Extra 2";
    else if(StreamMode == m_Initialization->m_StreamModeV.Extra3)
        return "Extra 3";
    else
        return "";
}


