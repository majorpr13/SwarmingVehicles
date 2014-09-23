#include "conversions.h"
#include <iostream>
Conversions::Conversions()
{
    m_Initialization = new Initialization();
    PI = 3.14159265358979;
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

double Conversions::USBtoPercent(const StructureDefinitions::JoystickHL &USBRange, const EnumerationDefinitions::FlightMethods &FlightAxis, const double &USBRCValue)
{
    double percentage = 0.0;

    switch(FlightAxis)
    {
    case(EnumerationDefinitions::Roll):
        percentage = (USBRCValue - USBRange.roll_low) / (USBRange.roll_high - USBRange.roll_low);
        break;
    case(EnumerationDefinitions::Pitch):
        percentage = (USBRCValue - USBRange.pitch_low) / (USBRange.pitch_high - USBRange.pitch_low);
        break;
    case(EnumerationDefinitions::Yaw):
        percentage = (USBRCValue - USBRange.yaw_low) / (USBRange.yaw_high - USBRange.yaw_low);
        break;
    case(EnumerationDefinitions::Throttle):
        percentage = (USBRCValue - USBRange.throttle_low) / (USBRange.throttle_high - USBRange.throttle_low);
        break;
    default:
        percentage = 0.5;
        break;
    }

    return(percentage);
}

int Conversions::PercenttoRC(const StructureDefinitions::VehicleRCHL &RCRange, const EnumerationDefinitions::FlightMethods &FlightAxis, const double &Percentage)
{
    int RC_Value = 0;
    double result = 0.0;
    switch(FlightAxis)
    {
    case(EnumerationDefinitions::Roll):
        if(RCRange.roll_reverse == false)
            result = ((double)(RCRange.roll_high - RCRange.roll_low) * Percentage) + (double)RCRange.roll_low;
        else
            result = (double)RCRange.roll_high - ((double)(RCRange.roll_high - RCRange.roll_low) * Percentage);
        break;
    case(EnumerationDefinitions::Pitch):
        if(RCRange.pitch_reverse == false)
            result = ((double)(RCRange.pitch_high - RCRange.pitch_low) * Percentage) + (double)RCRange.pitch_low;
        else
            result = (double)RCRange.pitch_high - ((double)(RCRange.pitch_high - RCRange.pitch_low) * Percentage);
        break;
    case(EnumerationDefinitions::Yaw):
        if(RCRange.yaw_reverse == false)
            result = ((double)(RCRange.yaw_high - RCRange.yaw_low) * Percentage) + (double)RCRange.yaw_low;
        else
            result = (double)RCRange.yaw_high - ((double)(RCRange.yaw_high - RCRange.yaw_low) * Percentage);
        break;
    case(EnumerationDefinitions::Throttle):
        if(RCRange.throttle_reverse == false)
            result = ((double)(RCRange.throttle_high - RCRange.throttle_low) * Percentage) + (double)RCRange.throttle_low;
        else
            result = (double)RCRange.throttle_high - ((double)(RCRange.throttle_high - RCRange.throttle_low) * Percentage);
        break;
    default:
        result = 1500;
        break;
    }

     result = result + 0.5; //This is performed so that the type cast to int rounds correctly
     RC_Value = (int)result;
     return(RC_Value);
}

int Conversions::VehicleParam_StringtoEnum(const QString &Parameter)
{
    int return_int = -1;
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
    else
        return_int = -1;
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

    default:
        string_return = "";
    }
    return(string_return);
}

double Conversions::DistanceGPS(const StructureDefinitions::GPS_Params &Beg, const StructureDefinitions::GPS_Params &End)
{
    StructureDefinitions::GPS_Params GPS1;
    StructureDefinitions::GPS_Params GPS2;

    GPS1.Lat = DegreestoRadians(Beg.Lat);
    GPS1.Lon = DegreestoRadians(Beg.Lon);
    GPS2.Lat = DegreestoRadians(End.Lat);
    GPS2.Lon = DegreestoRadians(End.Lon);

    double deltaLat = GPS2.Lat - GPS1.Lat;
    double deltaLon = GPS2.Lon - GPS1.Lon;

    double a = sin(deltaLat/2.0)*sin(deltaLat/2.0) + cos(GPS1.Lat)*cos(GPS2.Lat)*sin(deltaLon/2.0)*sin(deltaLon/2.0);
    double c = 2 * atan2(sqrt(a),sqrt(1-a));
    return (6371.0 * c);
}

double Conversions::BearingGPS(const StructureDefinitions::GPS_Params &Beg, const StructureDefinitions::GPS_Params &End)
{
    double bearing = 0.0;

    StructureDefinitions::GPS_Params GPS1;
    StructureDefinitions::GPS_Params GPS2;

    GPS1.Lat = DegreestoRadians(Beg.Lat);
    GPS1.Lon = DegreestoRadians(Beg.Lon);
    GPS2.Lat = DegreestoRadians(End.Lat);
    GPS2.Lon = DegreestoRadians(End.Lon);

    double deltaLon = GPS2.Lon - GPS1.Lon;

    double y = sin(deltaLon)*cos(GPS2.Lat);
    double x = cos(GPS1.Lat)*sin(GPS2.Lat) - sin(GPS1.Lat)*cos(GPS2.Lat)*cos(deltaLon);
    if(y == 0.0)
    {
        if (x > 0.0)
            bearing = 0.0;
        else if(x < 0)
            bearing = 180.0;
        else
            bearing = 0.0;
    }
    else if(y > 0.0)
    {
        if (x > 0.0)
            bearing = RadianstoDegrees(atan(y/x));
        else if(x < 0)
            bearing = 180.0 - RadianstoDegrees(atan(-y/x));
        else
            bearing = 90.0;
    }
    else if(y < 0.0)
    {
        if (x > 0.0)
            bearing = -RadianstoDegrees(atan(-y/x));
        else if(x < 0)
            bearing = RadianstoDegrees(atan(y/x)) - 180.0;
        else
            bearing = 270.0;
    }
    return bearing;
}

StructureDefinitions::GPS_Params Conversions::FinalGPS(const StructureDefinitions::GPS_Params &Beg, const double &bearing, const double &distance)
{
    StructureDefinitions::GPS_Params GPS1;
    StructureDefinitions::GPS_Params GPS2;
    double heading = 0.0;

    GPS1.Lat = DegreestoRadians(Beg.Lat);
    GPS1.Lon = DegreestoRadians(Beg.Lon);
    heading = DegreestoRadians(bearing);

    GPS2.Lat = asin(sin(GPS1.Lat) * cos(distance/(6371.0 * 1000)) + cos(GPS1.Lat) * sin(distance/(6371.0 * 1000)) * cos(heading));
    GPS2.Lon = GPS1.Lon + atan2((sin(heading) * sin(distance/(6371.0 * 1000)) * cos(GPS1.Lat)) , (cos(distance/(6371.0 * 1000)) - sin(GPS1.Lat) * sin(GPS2.Lat)));

    GPS2.Lat = RadianstoDegrees(GPS2.Lat);
    GPS2.Lon = RadianstoDegrees(GPS2.Lon);
    GPS2.Alt = Beg.Alt;

    return (GPS2);
}

double Conversions::DegreestoRadians(const double &valueDegrees)
{
    return(valueDegrees * (PI/180.0));
}

double Conversions::RadianstoDegrees(const double &valueRadians)
{
    return(valueRadians * (180.0/PI));
}
