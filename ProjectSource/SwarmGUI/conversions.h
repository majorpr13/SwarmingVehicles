#ifndef CONVERSIONS_H
#define CONVERSIONS_H
#include "Definitions.h"
#include "initialization.h"
#include "math.h"

class Conversions
{
public:
    Conversions();
    int FlightMode_StringtoEnum(const QString &FlightMode);
    int StreamMode_StringtoEnum(const QString &StreamMode);
    int VehicleParam_StringtoEnum(const QString &Parameter);

    QString FlightMode_EnumtoString(const int &FlightMode);
    QString StreamMode_EnumtoString(const int &StreamMode);
    QString VehicleParam_EnumtoString(const int &Parameter);

    double USBtoPercent(const StructureDefinitions::JoystickHL &USBRange, const EnumerationDefinitions::FlightMethods &FlightAxis, const double &USBRCValue);
    int PercenttoRC(const StructureDefinitions::VehicleRCHL &RCRange, const EnumerationDefinitions::FlightMethods &FlightAxis, const double &Percentage);

    double DistanceGPS(const StructureDefinitions::GPS_Params &Beg, const StructureDefinitions::GPS_Params &End);
    double BearingGPS(const StructureDefinitions::GPS_Params &Beg, const StructureDefinitions::GPS_Params &End);
    StructureDefinitions::GPS_Params FinalGPS(const StructureDefinitions::GPS_Params &Beg, const double &bearing, const double &distance);

    double DegreestoRadians(const double &valueDegrees);

    double RadianstoDegrees(const double &valueRadians);

    Initialization *m_Initialization;

private:

    double PI;
};

#endif // CONVERSIONS_H
