#include "gps_position.h"

GPS_Position::GPS_Position()
{
    this->Latitude = 0.0;
    this->Longitude = 0.0;
    this->Altitude = 0.0;
    this->PI = 3.14159265358979;
}


double GPS_Position::Distance(const GPS_Position &End)
{
    GPS_Position Beg;
    GPS_Position EndN;

    Beg = this->DegTORad();
    EndN = End.DegTORad();

    double deltaLat = EndN.Latitude - Beg.Latitude;
    double deltaLon = EndN.Longitude - Beg.Longitude;

    double a = sin(deltaLat/2.0)*sin(deltaLat/2.0) + cos(Beg.Latitude)*cos(EndN.Latitude)*sin(deltaLon/2.0)*sin(deltaLon/2.0);
    double c = 2 * atan2(sqrt(a),sqrt(1-a));
    return (6371000 * c);
}

double GPS_Position::Bearing(const GPS_Position &End)
{
    double bearing = 0.0;

    GPS_Position Beg;
    GPS_Position EndN;

    Beg = this->DegTORad();
    EndN = End.DegTORad();

    double deltaLon = EndN.Longitude - Beg.Longitude;

    double y = sin(deltaLon)*cos(EndN.Latitude);
    double x = cos(Beg.Latitude)*sin(EndN.Latitude) - sin(Beg.Latitude)*cos(EndN.Latitude)*cos(deltaLon);
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
            bearing = RadTODeg(atan(y/x));
        else if(x < 0)
            bearing = 180.0 - RadTODeg(atan(-y/x));
        else
            bearing = 90.0;
    }
    else if(y < 0.0)
    {
        if (x > 0.0)
            bearing = -RadTODeg(atan(-y/x));
        else if(x < 0)
            bearing = RadTODeg(atan(y/x)) - 180.0;
        else
            bearing = 270.0;
    }
    return bearing;
}


GPS_Position GPS_Position::Final(const double &bearing, const double &distance)
{
    GPS_Position rad_GPSH;
    GPS_Position GPSF;

    double heading = 0.0;

    rad_GPSH = this->DegTORad();
    heading = bearing * (PI / 180.0);

    GPSF.Latitude = asin(sin(rad_GPSH.Latitude) * cos(distance/(6371.0 * 1000)) + cos(rad_GPSH.Latitude) * sin(distance/(6371.0 * 1000)) * cos(heading));
    GPSF.Longitude = rad_GPSH.Longitude + atan2((sin(heading) * sin(distance/(6371.0 * 1000)) * cos(rad_GPSH.Latitude)) , (cos(distance/(6371.0 * 1000)) - sin(rad_GPSH.Latitude) * sin(GPSF.Latitude)));

    GPSF.RadTODeg();
    GPSF.Altitude = this->Altitude;

    return (GPSF);
}

GPS_Position GPS_Position::DegTORad() const
{
    GPS_Position radianPosition;
    radianPosition.Latitude = this->Latitude * (PI / 180.0);
    radianPosition.Longitude = this->Longitude * (PI / 180.0);
    return radianPosition;
}


GPS_Position GPS_Position::RadTODeg() const
{
    GPS_Position radianPosition;
    radianPosition.Latitude = this->Latitude * (180.0 / PI);
    radianPosition.Longitude = this->Longitude * (180.0 / PI);
    return radianPosition;
}


double GPS_Position::DegTORad(const double value)
{
    return (value * (PI / 180.0));
}


double GPS_Position::RadTODeg(const double value)
{
    return (value * (180.0 / PI));
}
