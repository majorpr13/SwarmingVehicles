#ifndef CONVERSIONS_H
#define CONVERSIONS_H
#include "Definitions.h"
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

    QString VehicleParam_EnumtoString(const int &Parameter);

    QList<QString> parameterList_WP();

private:

    double PI;
};

#endif // CONVERSIONS_H
