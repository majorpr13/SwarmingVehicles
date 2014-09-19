#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <QString>
#include <QTime>

namespace StructureDefinitions{
struct GCSDefinition
{
    GCSDefinition() : sysid(255),compid(190){}
    int sysid;
    int compid;
};

struct TableDefinition
{
    TableDefinition(): VehicleID(0),Connection_Status(0),Vehicle_Armed(false),GPS_Sat(0),GPSFix(0),Battery_V(0.0),Cell_Count(3),Battery_A(0.0),Battery_AH(100.0){}
    int VehicleID;
    int Connection_Status;
    bool Vehicle_Armed;
    int GPS_Sat;
    int GPSFix;
    double Battery_V;
    int Cell_Count;
    double Battery_A;
    double Battery_AH;
};

struct VehicleStateV
{
    VehicleStateV(): roll(0.0),rollrate(0.0),pitch(0.0),pitchrate(0.0),yaw(0.0),yawrate(0.0),Cur_Lat(0.0),Cur_Lon(0.0),Cur_Heading(0.0),Cur_Altitude(0.0),Goal_Lat(0.0),Goal_Lon(0.0),Goal_Heading(0.0),Goal_Altitude(0.0){}
    double roll;
    double rollrate;
    double pitch;
    double pitchrate;
    double yaw;
    double yawrate;
    double Cur_Lat;
    double Cur_Lon;
    double Cur_Heading;
    double Cur_Altitude;
    double Goal_Lat;
    double Goal_Lon;
    double Goal_Heading;
    double Goal_Altitude;
};
}
namespace FlightModeStructure{
struct FlightModes
{
     int Stabilize;
     int AltHold;
     int Loiter;
     int RTL;
     int Auto;
     int Acro;
     int Sport;
     int Drift;
     int Guided;
     int CircleFM;
     int Position;
     int Land;
     //int FollowMe;
     //int Simple;
     //int SuperSimple;
};
}

namespace StreamModeStructure{
struct StreamModes
{
    int StreamAll;
    int RawSensors;
    int ExtendedStatus;
    int RCChannels;
    int RawController;
    int Position;
    int Extra1;
    int Extra2;
    int Extra3;
};
}
namespace EnumerationDefinitions{

enum GPS_Fix{
    Fix0D,
    Fix2D,
    Fix3D
};

}
#endif // DEFINITIONS_H
