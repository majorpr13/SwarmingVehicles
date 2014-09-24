#ifndef VEHICLESTATE_H
#define VEHICLESTATE_H

#include <QMap>

#ifdef ROS_LIBS
#include <ros/ros.h>

#include <mavlink_common/HEARTBEAT.h>
#include <mavlink_common/ATTITUDE.h>
#include <mavlink_common/GLOBAL_POSITION_INT.h>
#endif

#include "Definitions.h"

class VehicleState
{
public:
    VehicleState();
    void addVehicle(const int &VehicleID);
    void removeVehicle(const int &VehicleID);

    void updateGoal();

#ifdef ROS_LIBS
    void updateAttitude(const mavlink_common::ATTITUDE &msg);
    void updatePosition(const mavlink_common::GLOBAL_POSITION_INT &msg);
#endif

private:
    QMap<int, StructureDefinitions::VehicleStateV*> m_MapVehicleState;
};

#endif // VEHICLESTATE_H
