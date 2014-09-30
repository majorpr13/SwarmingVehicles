#ifndef GPS_POSITION_H
#define GPS_POSITION_H

#include "GPS_Position_global.h"
#include "math.h"

class GPS_POSITIONSHARED_EXPORT GPS_Position {
public:

    enum GPS_Fix{
        Fix0D,
        Fix2D,
        Fix3D
    };

    float Latitude;
    float Longitude;
    float Altitude;
    float PI;

    GPS_Position();

    double Distance(const GPS_Position &End);

    double Bearing(const GPS_Position &End);

    GPS_Position Final(const double &bearing, const double &distance);

    GPS_Position DegTORad() const;

    GPS_Position RadTODeg() const;

    double DegTORad(const double value);

    double RadTODeg(const double value);
};

#endif // GPS_POSITION_H
