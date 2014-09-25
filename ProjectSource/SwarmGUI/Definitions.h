#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <QString>
#include <QTime>

namespace mavCommandStructures{
struct mavCMD_numberList{
    mavCMD_numberList() : setHome(179){}
    int setHome;
};

struct mavCMD_setHome{
    mavCMD_setHome() : useCurrent(0),empty1(0.0),empty2(0.0),empty3(0.0),Latitude(0.0),Longitude(0.0),Altitude(0.0){}
    double useCurrent;
    double empty1;
    double empty2;
    double empty3;
    double Latitude;
    double Longitude;
    double Altitude;
};
}
namespace StructureDefinitions{
struct GCSDefinition
{
    GCSDefinition() : sysid(255),compid(190){}
    int sysid;
    int compid;
};

struct GPS_Params{
    double Lat;
    double Lon;
    double Alt;
};

struct HomeDefinition
{
    HomeDefinition() : HLatitude(0.0),HLongitude(0.0),HAltitude(0.0){}
    double HLatitude;
    double HLongitude;
    double HAltitude;
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

struct RCOverride
{
    RCOverride(): roll_override(0),pitch_override(0),yaw_override(0),throttle_override(0){}
    int roll_override;
    int pitch_override;
    int yaw_override;
    int throttle_override;
};

struct VehicleStateV
{
    VehicleStateV(): roll(0.0),rollrate(0.0),pitch(0.0),pitchrate(0.0),yaw(0.0),yawrate(0.0),climbrate(0.0),Cur_Lat(0.0),Cur_Lon(0.0),Cur_Heading(0.0),Cur_Altitude(0.0),Goal_Lat(0.0),Goal_Lon(0.0),Goal_Heading(0.0),Goal_Altitude(0.0){}
    double roll;
    double rollrate;
    double pitch;
    double pitchrate;
    double yaw;
    double yawrate;
    double climbrate;
    double Cur_Lat;
    double Cur_Lon;
    double Cur_Heading;
    double Cur_Altitude;
    double Goal_Lat;
    double Goal_Lon;
    double Goal_Heading;
    double Goal_Altitude;
};
struct VehicleRCHL
{
    VehicleRCHL(): throttle_low(1100),throttle_high(1900),throttle_or(false),yaw_low(1100),yaw_high(1900),yaw_or(false),pitch_low(1100),pitch_high(1900),pitch_or(false),roll_low(1100),roll_high(1900),roll_or(false),roll_reverse(false),pitch_reverse(false),yaw_reverse(false),throttle_reverse(false){}
    //VehicleRCHL(): throttle_low(1500),throttle_high(1500),throttle_or(false),yaw_low(1500),yaw_high(1500),yaw_or(false),pitch_low(1500),pitch_high(1500),pitch_or(false),roll_low(1500),roll_high(1500),roll_or(false),roll_reverse(false),pitch_reverse(false),yaw_reverse(false),throttle_reverse(false){}
    int throttle_low;
    int throttle_high;
    bool throttle_or;
    int yaw_low;
    int yaw_high;
    bool yaw_or;
    int pitch_low;
    int pitch_high;
    bool pitch_or;
    int roll_low;
    int roll_high;
    bool roll_or;
    bool roll_reverse;
    bool pitch_reverse;
    bool yaw_reverse;
    bool throttle_reverse;
};
struct JoystickHL
{
    JoystickHL(): throttle_low(0.0),throttle_high(0.0),yaw_low(0.0),yaw_high(0.0),pitch_low(0.0),pitch_high(0.0),roll_low(0.0),roll_high(0.0){}
    double throttle_low;
    double throttle_high;
    double yaw_low;
    double yaw_high;
    double pitch_low;
    double pitch_high;
    double roll_low;
    double roll_high;
};
}
namespace FlightModeStructure{
struct FlightModes
{
     uint Stabilize;
     uint AltHold;
     uint Loiter;
     uint RTL;
     uint Auto;
     uint Acro;
     uint Sport;
     uint Drift;
     uint Guided;
     uint CircleFM;
     uint Position;
     uint Land;
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

enum Vehicle_Type{
    Generic,
    Plane,
    Quadrotor,
    Coaxial,
    Helicopter,
    Antenna_Tracker,
    GCS,
    Airship,
    Balloon,
    Rocket,
    Rover,
    Boat,
    Submarine,
    Hexacopter,
    Octocopter,
    Tricopter,
    FlappingWing,
    Kite,
    Companion
};

enum GPS_Fix{
    Fix0D,
    Fix2D,
    Fix3D
};

enum GPS_Params{
    Lat,
    Lon,
    Alt
};

enum FlightMethods{
    Roll,
    Pitch,
    Yaw,
    Throttle
};

enum Vehicle_Params{
    RC1_Min,
    RC1_Max,
    RC2_Min,
    RC2_Max,
    RC3_Min,
    RC3_Max,
    RC4_Min,
    RC4_Max,
    RC5_Min,
    RC5_Max,
    RC6_Min,
    RC6_Max,
    RC7_Min,
    RC7_Max,
    RC8_Min,
    RC8_Max,
    RC9_Min,
    RC9_Max,
    RC10_Min,
    RC10_Max,
    RC11_Min,
    RC11_Max,
    RC12_Min,
    RC12_Max,
    RC13_Min,
    RC13_Max,
    RC14_Min,
    RC14_Max,
    RC_Length,
    WPNAV_SPEED,
    WPNAV_RADIUS,
    WPNAV_SPEED_UP,
    WPNAV_SPEED_DN,
    WPNAV_LOIT_SPEED,
    WPNAV_ACCEL,
    WPNAV_ACCEL_Z,
    WPNAV_LOIT_JERK,
    WP_Length
};
}
#endif // DEFINITIONS_H
