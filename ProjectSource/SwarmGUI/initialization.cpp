#include "initialization.h"

Initialization::Initialization()
{
    initFlightModes();
    initStreamModes();
}

void Initialization::initFlightModes()
{
    m_FlightModeV.Acro = 1;//
    m_FlightModeV.AltHold = 2;//
    m_FlightModeV.Auto = 3; //
    m_FlightModeV.CircleFM = 7;
    m_FlightModeV.Drift = 11;//
    //m_FlightModeV.FollowMe = 0;
    m_FlightModeV.Guided = 4; //
    m_FlightModeV.Land = 9;//
    m_FlightModeV.Loiter = 5;//
    m_FlightModeV.Position = 0;
    m_FlightModeV.RTL = 6;//
    //m_FlightModeV.Simple = 0;
    m_FlightModeV.Sport = 13;
    m_FlightModeV.Stabilize = 0;//
   // m_FlightModeV.SuperSimple = 0;

}

void Initialization::initStreamModes()
{
    m_StreamModeV.StreamAll = 0;
    m_StreamModeV.RawSensors = 1; //Enable IMU_RAW, GPS_RAW, GPS_STATUS
    m_StreamModeV.ExtendedStatus = 2; //Enable GPS_STATUS, CONTROL_STATUS, AUX_STATUS
    m_StreamModeV.RCChannels = 3; //Enable RC_CHANNELS_SCALED, RC_CHANNELS_RAW, RAW_SERVO_OUTPUT
    m_StreamModeV.RawController = 4; //Enable ATTITUDE_CONTROLLER_OUTPUT, POSITION_CONTROLLER_OUTPUT, NAV_CONTROLLER_OUPUT
    m_StreamModeV.Position = 6; //Enable LOCAL_POSITION, GLOBAL_POSITION, GLOBAL_POSITION_INT
    m_StreamModeV.Extra1 = 10;
    m_StreamModeV.Extra2 = 11;
    m_StreamModeV.Extra3 = 12;

}
