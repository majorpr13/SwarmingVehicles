#include "conversions.h"
#include <iostream>
Conversions::Conversions()
{
    m_Initialization = new Initialization();
    PI = 3.14159265358979;
}

uint Conversions::FlightMode_StringtoEnum(const QString &FlightMode)
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

QString Conversions::FlightMode_EnumtoString(const uint &FlightMode)
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

EnumerationDefinitions::Vehicle_Params Conversions::VehicleParam_StringtoEnum(const QString &Parameter)
{
    EnumerationDefinitions::Vehicle_Params return_int;

    if(Parameter == "RC1_Min")
        return_int = EnumerationDefinitions::RC1_Min;
    else if(Parameter == "RC1_Max")
        return_int = EnumerationDefinitions::RC1_Max;
    else if(Parameter == "RC2_Min")
        return_int = EnumerationDefinitions::RC2_Min;
    else if(Parameter == "RC2_Max")
        return_int = EnumerationDefinitions::RC2_Max;
    else if(Parameter == "RC3_Min")
        return_int = EnumerationDefinitions::RC3_Min;
    else if(Parameter == "RC3_Max")
        return_int = EnumerationDefinitions::RC3_Max;
    else if(Parameter == "RC4_Min")
        return_int = EnumerationDefinitions::RC4_Min;
    else if(Parameter == "RC4_Max")
        return_int = EnumerationDefinitions::RC4_Max;

    else if(Parameter == "RC5_Min")
        return_int = EnumerationDefinitions::RC5_Min;
    else if(Parameter == "RC5_Max")
        return_int = EnumerationDefinitions::RC5_Max;
    else if(Parameter == "RC6_Min")
        return_int = EnumerationDefinitions::RC6_Min;
    else if(Parameter == "RC6_Max")
        return_int = EnumerationDefinitions::RC6_Max;
    else if(Parameter == "RC7_Min")
        return_int = EnumerationDefinitions::RC7_Min;
    else if(Parameter == "RC7_Max")
        return_int = EnumerationDefinitions::RC7_Max;
    else if(Parameter == "RC8_Min")
        return_int = EnumerationDefinitions::RC8_Min;
    else if(Parameter == "RC8_Max")
        return_int = EnumerationDefinitions::RC8_Max;

    else if(Parameter == "RC9_Min")
        return_int = EnumerationDefinitions::RC9_Min;
    else if(Parameter == "RC9_Max")
        return_int = EnumerationDefinitions::RC9_Max;
    else if(Parameter == "RC10_Min")
        return_int = EnumerationDefinitions::RC10_Min;
    else if(Parameter == "RC10_Max")
        return_int = EnumerationDefinitions::RC10_Max;
    else if(Parameter == "RC11_Min")
        return_int = EnumerationDefinitions::RC11_Min;
    else if(Parameter == "RC11_Max")
        return_int = EnumerationDefinitions::RC11_Max;
    else if(Parameter == "RC12_Min")
        return_int = EnumerationDefinitions::RC12_Min;
    else if(Parameter == "RC12_Max")
        return_int = EnumerationDefinitions::RC12_Max;

    else if(Parameter == "RC13_Min")
        return_int = EnumerationDefinitions::RC13_Min;
    else if(Parameter == "RC13_Max")
        return_int = EnumerationDefinitions::RC13_Max;
    else if(Parameter == "RC14_Min")
        return_int = EnumerationDefinitions::RC14_Min;
    else if(Parameter == "RC14_Max")
        return_int = EnumerationDefinitions::RC14_Max;

    else if(Parameter == "WPNAV_SPEED")
        return_int = EnumerationDefinitions::WPNAV_SPEED;
    else if(Parameter == "WPNAV_RADIUS")
        return_int = EnumerationDefinitions::WPNAV_RADIUS;
    else if(Parameter == "WPNAV_SPEED_UP")
        return_int = EnumerationDefinitions::WPNAV_SPEED_UP;
    else if(Parameter == "WPNAV_SPEED_DN")
        return_int = EnumerationDefinitions::WPNAV_SPEED_DN;
    else if(Parameter == "WPNAV_LOIT_SPEED")
        return_int = EnumerationDefinitions::WPNAV_LOIT_SPEED;
    else if(Parameter == "WPNAV_ACCEL")
        return_int = EnumerationDefinitions::WPNAV_ACCEL;
    else if(Parameter == "WPNAV_ACCEL_Z")
        return_int = EnumerationDefinitions::WPNAV_ACCEL_Z;
    else if(Parameter == "WPNAV_LOIT_JERK")
        return_int = EnumerationDefinitions::WPNAV_LOIT_JERK;

    else
        return_int = EnumerationDefinitions::RC_Length;
    return(return_int);

}

QString Conversions::VehicleParam_EnumtoString(const int &Parameter)
{
    QString string_return = "";
    switch(Parameter)
    {
    case(EnumerationDefinitions::RC1_Min):
        string_return = "RC1_Min";
        break;
    case(EnumerationDefinitions::RC1_Max):
        string_return = "RC1_Max";
        break;
    case(EnumerationDefinitions::RC2_Min):
        string_return = "RC2_Min";
        break;
    case(EnumerationDefinitions::RC2_Max):
        string_return = "RC2_Max";
        break;
    case(EnumerationDefinitions::RC3_Min):
        string_return = "RC3_Min";
        break;
    case(EnumerationDefinitions::RC3_Max):
        string_return = "RC3_Max";
        break;
    case(EnumerationDefinitions::RC4_Min):
        string_return = "RC4_Min";
        break;
    case(EnumerationDefinitions::RC4_Max):
        string_return = "RC4_Max";
        break;

    case(EnumerationDefinitions::RC5_Min):
        string_return = "RC5_Min";
        break;
    case(EnumerationDefinitions::RC5_Max):
        string_return = "RC5_Max";
        break;
    case(EnumerationDefinitions::RC6_Min):
        string_return = "RC6_Min";
        break;
    case(EnumerationDefinitions::RC6_Max):
        string_return = "RC6_Max";
        break;
    case(EnumerationDefinitions::RC7_Min):
        string_return = "RC7_Min";
        break;
    case(EnumerationDefinitions::RC7_Max):
        string_return = "RC7_Max";
        break;
    case(EnumerationDefinitions::RC8_Min):
        string_return = "RC8_Min";
        break;
    case(EnumerationDefinitions::RC8_Max):
        string_return = "RC8_Max";
        break;

    case(EnumerationDefinitions::RC9_Min):
        string_return = "RC9_Min";
        break;
    case(EnumerationDefinitions::RC9_Max):
        string_return = "RC9_Max";
        break;
    case(EnumerationDefinitions::RC10_Min):
        string_return = "RC10_Min";
        break;
    case(EnumerationDefinitions::RC10_Max):
        string_return = "RC10_Max";
        break;
    case(EnumerationDefinitions::RC11_Min):
        string_return = "RC11_Min";
        break;
    case(EnumerationDefinitions::RC11_Max):
        string_return = "RC11_Max";
        break;
    case(EnumerationDefinitions::RC12_Min):
        string_return = "RC12_Min";
        break;
    case(EnumerationDefinitions::RC12_Max):
        string_return = "RC12_Max";
        break;

    case(EnumerationDefinitions::RC13_Min):
        string_return = "RC13_Min";
        break;
    case(EnumerationDefinitions::RC13_Max):
        string_return = "RC13_Max";
        break;
    case(EnumerationDefinitions::RC14_Min):
        string_return = "RC14_Min";
        break;
    case(EnumerationDefinitions::RC14_Max):
        string_return = "RC14_Max";
        break;

    case(EnumerationDefinitions::WPNAV_ACCEL):
        string_return = "WPNAV_ACCEL";
        break;
    case(EnumerationDefinitions::WPNAV_ACCEL_Z):
        string_return = "WPNAV_ACCEL_Z";
        break;
    case(EnumerationDefinitions::WPNAV_LOIT_JERK):
        string_return = "WPNAV_LOIT_JERK";
        break;
    case(EnumerationDefinitions::WPNAV_LOIT_SPEED):
        string_return = "WPNAV_LOIT_SPEED";
        break;
    case(EnumerationDefinitions::WPNAV_RADIUS):
        string_return = "WPNAV_RADIUS";
        break;
    case(EnumerationDefinitions::WPNAV_SPEED):
        string_return = "WPNAV_SPEED";
        break;
    case(EnumerationDefinitions::WPNAV_SPEED_DN):
        string_return = "WPNAV_SPEED_DN";
        break;
    case(EnumerationDefinitions::WPNAV_SPEED_UP):
        string_return = "WPNAV_SPEED_UP";
        break;

    default:
        string_return = "";
    }
    return(string_return);
}


double Conversions::DegreestoRadians(const double &valueDegrees)
{
    return(valueDegrees * (PI/180.0));
}

double Conversions::RadianstoDegrees(const double &valueRadians)
{
    return(valueRadians * (180.0/PI));
}

QList<QString> Conversions::parameterList_RC()
{
    QList<QString> returnList;
    returnList.append(VehicleParam_EnumtoString(EnumerationDefinitions::RC1_Max));
    returnList.append(VehicleParam_EnumtoString(EnumerationDefinitions::RC2_Max));
    returnList.append(VehicleParam_EnumtoString(EnumerationDefinitions::RC3_Max));
    returnList.append(VehicleParam_EnumtoString(EnumerationDefinitions::RC4_Max));

    returnList.append(VehicleParam_EnumtoString(EnumerationDefinitions::RC1_Min));
    returnList.append(VehicleParam_EnumtoString(EnumerationDefinitions::RC2_Min));
    returnList.append(VehicleParam_EnumtoString(EnumerationDefinitions::RC3_Min));
    returnList.append(VehicleParam_EnumtoString(EnumerationDefinitions::RC4_Min));
    return(returnList);
}

QList<QString> Conversions::parameterList_WP()
{
    QList<QString> returnList;
    returnList.append(VehicleParam_EnumtoString(EnumerationDefinitions::WPNAV_ACCEL));
    returnList.append(VehicleParam_EnumtoString(EnumerationDefinitions::WPNAV_ACCEL_Z));
    returnList.append(VehicleParam_EnumtoString(EnumerationDefinitions::WPNAV_LOIT_JERK));
    returnList.append(VehicleParam_EnumtoString(EnumerationDefinitions::WPNAV_LOIT_SPEED));

    returnList.append(VehicleParam_EnumtoString(EnumerationDefinitions::WPNAV_RADIUS));
    returnList.append(VehicleParam_EnumtoString(EnumerationDefinitions::WPNAV_SPEED));
    returnList.append(VehicleParam_EnumtoString(EnumerationDefinitions::WPNAV_SPEED_DN));
    returnList.append(VehicleParam_EnumtoString(EnumerationDefinitions::WPNAV_SPEED_UP));
    return(returnList);
}
