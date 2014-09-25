#ifndef CONVERSIONS_H
#define CONVERSIONS_H
#include "Definitions.h"
#include "initialization.h"
#include "math.h"

#include <QList>


class Conversions
{
public:
    Conversions();

    uint FlightMode_StringtoEnum(const QString &FlightMode);
    QString FlightMode_EnumtoString(const uint &FlightMode);

    int StreamMode_StringtoEnum(const QString &StreamMode);
    QString StreamMode_EnumtoString(const int &StreamMode);

    EnumerationDefinitions::Vehicle_Params VehicleParam_StringtoEnum(const QString &Parameter);
    QString VehicleParam_EnumtoString(const int &Parameter);

    double USBtoPercent(const StructureDefinitions::JoystickHL &USBRange, const EnumerationDefinitions::FlightMethods &FlightAxis, const double &USBRCValue);
    int PercenttoRC(const StructureDefinitions::VehicleRCHL &RCRange, const EnumerationDefinitions::FlightMethods &FlightAxis, const double &Percentage);

    double DistanceGPS(const StructureDefinitions::GPS_Params &Beg, const StructureDefinitions::GPS_Params &End);
    double BearingGPS(const StructureDefinitions::GPS_Params &Beg, const StructureDefinitions::GPS_Params &End);
    StructureDefinitions::GPS_Params FinalGPS(const StructureDefinitions::GPS_Params &Beg, const double &bearing, const double &distance);

    double DegreestoRadians(const double &valueDegrees);

    double RadianstoDegrees(const double &valueRadians);

    QList<QString> parameterList_RC();

    QList<QString> parameterList_WP();

    Initialization *m_Initialization;

private:

    double PI;
};

#endif // CONVERSIONS_H
