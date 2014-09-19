#include "vehiclestate.h"

VehicleState::VehicleState()
{
    m_MapVehicleState.clear();
}

void VehicleState::addVehicle(const int &VehicleID)
{
    StructureDefinitions::VehicleStateV *newState = new StructureDefinitions::VehicleStateV();
    m_MapVehicleState.insert(VehicleID,newState);
}

void VehicleState::removeVehicle(const int &VehicleID)
{
    m_MapVehicleState.remove(VehicleID);
}

void VehicleState::updateAttitude(const mavlink_common::ATTITUDE &msg)
{
    m_MapVehicleState[msg.sysid]->roll = msg.roll;
    m_MapVehicleState[msg.sysid]->rollrate = msg.rollspeed;

    m_MapVehicleState[msg.sysid]->pitch = msg.pitch;
    m_MapVehicleState[msg.sysid]->pitchrate = msg.pitchspeed;

    m_MapVehicleState[msg.sysid]->yaw = msg.yaw;
    m_MapVehicleState[msg.sysid]->yawrate = msg.yawspeed;
}

void VehicleState::updatePosition(const mavlink_common::GLOBAL_POSITION_INT &msg)
{
    double GPSdivisor = 10000000.0;
    m_MapVehicleState[msg.sysid]->Cur_Lat = msg.lat / GPSdivisor;
    m_MapVehicleState[msg.sysid]->Cur_Lon = msg.lon / GPSdivisor;
}

void VehicleState::updateGoal()
{

}
