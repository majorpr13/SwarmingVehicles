#ifndef CONVERSIONS_H
#define CONVERSIONS_H
#include "Definitions.h"
#include "initialization.h"

class Conversions
{
public:
    Conversions();
    int FlightMode_StringtoEnum(const QString &FlightMode);
    int StreamMode_StringtoEnum(const QString &StreamMode);
    QString FlightMode_EnumtoString(const int &FlightMode);
    QString StreamMode_EnumtoString(const int &StreamMode);
    Initialization *m_Initialization;

private:

};

#endif // CONVERSIONS_H
