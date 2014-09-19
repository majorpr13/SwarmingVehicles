#ifndef VEHICLESTATE_H
#define VEHICLESTATE_H

#include <QMap>

#include <ros/ros.h>
#include "Definitions.h"

#include <mavlink_common/HEARTBEAT.h>
#include <mavlink_common/ATTITUDE.h>
#include <mavlink_common/GLOBAL_POSITION_INT.h>

class VehicleState
{
public:
    VehicleState();
    void addVehicle(const int &VehicleID);
    void removeVehicle(const int &VehicleID);
    void updateAttitude(const mavlink_common::ATTITUDE &msg);
    void updatePosition(const mavlink_common::GLOBAL_POSITION_INT &msg);
    void updateGoal();

private:
    QMap<int, StructureDefinitions::VehicleStateV*> m_MapVehicleState;
};

#endif // VEHICLESTATE_H
