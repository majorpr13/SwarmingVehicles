#include "conversions.h"
#include <iostream>
Conversions::Conversions()
{
    m_Initialization = new Initialization();
    PI = 3.14159265358979;
}

//uint Conversions::FlightMode_StringtoEnum(const QString &FlightMode)
//{
//    if(FlightMode == "Acro")
//        return m_Initialization->m_FlightModeV.Acro;
//    else if(FlightMode == "AltHold")
//        return m_Initialization->m_FlightModeV.AltHold;
//    else if(FlightMode == "Auto")
//        return m_Initialization->m_FlightModeV.Auto;
//    else if(FlightMode == "Circle")
//        return m_Initialization->m_FlightModeV.CircleFM;
//    else if(FlightMode == "Drift")
//        return m_Initialization->m_FlightModeV.Drift;
//    //else if(FlightMode == "Follow Me")
//        //return m_Initialization->m_FlightModeV.FollowMe;
//    else if(FlightMode == "Guided")
//        return m_Initialization->m_FlightModeV.Guided;
//    else if(FlightMode == "Land")
//        return m_Initialization->m_FlightModeV.Land;
//    else if(FlightMode == "Loiter")
//        return m_Initialization->m_FlightModeV.Loiter;
//    else if(FlightMode == "Position")
//        return m_Initialization->m_FlightModeV.Position;
//    else if(FlightMode == "RTL")
//        return m_Initialization->m_FlightModeV.RTL;
//    //else if(FlightMode == "Simple")
//        //return m_Initialization->m_FlightModeV.Simple;
//    else if(FlightMode == "Sport")
//        return m_Initialization->m_FlightModeV.Sport;
//    else if(FlightMode == "Stabilize")
//        return m_Initialization->m_FlightModeV.Stabilize;
//    //else if(FlightMode == "Super Simple")
//        //return m_Initialization->m_FlightModeV.SuperSimple;
//    else
//        return -1;
//}

//QString Conversions::FlightMode_EnumtoString(const uint &FlightMode)
//{
//    if(FlightMode == m_Initialization->m_FlightModeV.Acro)
//        return "Acro";
//    else if(FlightMode == m_Initialization->m_FlightModeV.AltHold)
//        return "AltHold";
//    else if(FlightMode == m_Initialization->m_FlightModeV.Auto)
//        return "Auto";
//    else if(FlightMode == m_Initialization->m_FlightModeV.CircleFM)
//        return "Circle";
//    else if(m_Initialization->m_FlightModeV.Drift)
//        return "Drift";
//    //else if(FlightMode == m_Initialization->m_FlightModeV.FollowMe)
//        //return "Follow Me";
//    else if(FlightMode == m_Initialization->m_FlightModeV.Guided)
//        return "Guided";
//    else if(FlightMode == m_Initialization->m_FlightModeV.Land)
//        return "Land";
//    else if(FlightMode == m_Initialization->m_FlightModeV.Loiter)
//        return "Loiter";
//    else if(FlightMode == m_Initialization->m_FlightModeV.Position)
//        return "Position";
//    else if(FlightMode == m_Initialization->m_FlightModeV.RTL)
//        return "RTL";
//    //else if(FlightMode == m_Initialization->m_FlightModeV.Simple)
//        //return "Simple";
//    else if(FlightMode == m_Initialization->m_FlightModeV.Sport)
//        return "Sport";
//    else if(FlightMode == m_Initialization->m_FlightModeV.Stabilize)
//        return "Stabilize";
//    //else if(FlightMode == m_Initialization->m_FlightModeV.SuperSimple)
//        //return "Super Simple";
//    else
//        return "";
//}





//QString Conversions::VehicleParam_EnumtoString(const int &Parameter)
//{
//    QString string_return = "";
//    switch(Parameter)
//    {
//    case(EnumerationDefinitions::RC1_Min):
//        string_return = "RC1_Min";
//        break;
//    case(EnumerationDefinitions::RC1_Max):
//        string_return = "RC1_Max";
//        break;
//    case(EnumerationDefinitions::RC2_Min):
//        string_return = "RC2_Min";
//        break;
//    case(EnumerationDefinitions::RC2_Max):
//        string_return = "RC2_Max";
//        break;
//    case(EnumerationDefinitions::RC3_Min):
//        string_return = "RC3_Min";
//        break;
//    case(EnumerationDefinitions::RC3_Max):
//        string_return = "RC3_Max";
//        break;
//    case(EnumerationDefinitions::RC4_Min):
//        string_return = "RC4_Min";
//        break;
//    case(EnumerationDefinitions::RC4_Max):
//        string_return = "RC4_Max";
//        break;

//    case(EnumerationDefinitions::RC5_Min):
//        string_return = "RC5_Min";
//        break;
//    case(EnumerationDefinitions::RC5_Max):
//        string_return = "RC5_Max";
//        break;
//    case(EnumerationDefinitions::RC6_Min):
//        string_return = "RC6_Min";
//        break;
//    case(EnumerationDefinitions::RC6_Max):
//        string_return = "RC6_Max";
//        break;
//    case(EnumerationDefinitions::RC7_Min):
//        string_return = "RC7_Min";
//        break;
//    case(EnumerationDefinitions::RC7_Max):
//        string_return = "RC7_Max";
//        break;
//    case(EnumerationDefinitions::RC8_Min):
//        string_return = "RC8_Min";
//        break;
//    case(EnumerationDefinitions::RC8_Max):
//        string_return = "RC8_Max";
//        break;

//    case(EnumerationDefinitions::RC9_Min):
//        string_return = "RC9_Min";
//        break;
//    case(EnumerationDefinitions::RC9_Max):
//        string_return = "RC9_Max";
//        break;
//    case(EnumerationDefinitions::RC10_Min):
//        string_return = "RC10_Min";
//        break;
//    case(EnumerationDefinitions::RC10_Max):
//        string_return = "RC10_Max";
//        break;
//    case(EnumerationDefinitions::RC11_Min):
//        string_return = "RC11_Min";
//        break;
//    case(EnumerationDefinitions::RC11_Max):
//        string_return = "RC11_Max";
//        break;
//    case(EnumerationDefinitions::RC12_Min):
//        string_return = "RC12_Min";
//        break;
//    case(EnumerationDefinitions::RC12_Max):
//        string_return = "RC12_Max";
//        break;

//    case(EnumerationDefinitions::RC13_Min):
//        string_return = "RC13_Min";
//        break;
//    case(EnumerationDefinitions::RC13_Max):
//        string_return = "RC13_Max";
//        break;
//    case(EnumerationDefinitions::RC14_Min):
//        string_return = "RC14_Min";
//        break;
//    case(EnumerationDefinitions::RC14_Max):
//        string_return = "RC14_Max";
//        break;

//    case(EnumerationDefinitions::WPNAV_ACCEL):
//        string_return = "WPNAV_ACCEL";
//        break;
//    case(EnumerationDefinitions::WPNAV_ACCEL_Z):
//        string_return = "WPNAV_ACCEL_Z";
//        break;
//    case(EnumerationDefinitions::WPNAV_LOIT_JERK):
//        string_return = "WPNAV_LOIT_JERK";
//        break;
//    case(EnumerationDefinitions::WPNAV_LOIT_SPEED):
//        string_return = "WPNAV_LOIT_SPEED";
//        break;
//    case(EnumerationDefinitions::WPNAV_RADIUS):
//        string_return = "WPNAV_RADIUS";
//        break;
//    case(EnumerationDefinitions::WPNAV_SPEED):
//        string_return = "WPNAV_SPEED";
//        break;
//    case(EnumerationDefinitions::WPNAV_SPEED_DN):
//        string_return = "WPNAV_SPEED_DN";
//        break;
//    case(EnumerationDefinitions::WPNAV_SPEED_UP):
//        string_return = "WPNAV_SPEED_UP";
//        break;

//    default:
//        string_return = "";
//    }
//    return(string_return);
//}



QList<QString> Conversions::parameterList_WP()
{
    QList<QString> returnList;
//    returnList.append(VehicleParam_EnumtoString(EnumerationDefinitions::WPNAV_ACCEL));
//    returnList.append(VehicleParam_EnumtoString(EnumerationDefinitions::WPNAV_ACCEL_Z));
//    returnList.append(VehicleParam_EnumtoString(EnumerationDefinitions::WPNAV_LOIT_JERK));
//    returnList.append(VehicleParam_EnumtoString(EnumerationDefinitions::WPNAV_LOIT_SPEED));

//    returnList.append(VehicleParam_EnumtoString(EnumerationDefinitions::WPNAV_RADIUS));
//    returnList.append(VehicleParam_EnumtoString(EnumerationDefinitions::WPNAV_SPEED));
//    returnList.append(VehicleParam_EnumtoString(EnumerationDefinitions::WPNAV_SPEED_DN));
//    returnList.append(VehicleParam_EnumtoString(EnumerationDefinitions::WPNAV_SPEED_UP));
    return(returnList);
}
