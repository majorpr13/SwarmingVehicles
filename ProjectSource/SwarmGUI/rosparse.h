#ifndef ROSPARSE_H
#define ROSPARSE_H

#include <QList>
#include <QMap>
#include <QHash>
#include <QTimer>
#include <QObject>
#include <QCoreApplication>
#include <QThread>

#include <ros/ros.h>
#include "Definitions.h"

#include <mavlink_common/HEARTBEAT.h>
#include <mavlink_common/ATTITUDE.h>
#include <mavlink_common/GPS_RAW_INT.h>
#include <mavlink_common/SYS_STATUS.h>
#include <mavlink_common/GLOBAL_POSITION_INT.h>

#include <mavlink_common/SET_MODE.h>
#include <mavlink_common/REQUEST_DATA_STREAM.h>
#include <mavlink_common/E_MAV_DATA_STREAM.h>
#include <mavlink_common/E_MAV_CMD.h>

class ROSParse : public QThread
{
    Q_OBJECT
public:
    ROSParse(const int &GCSID);

    ROSParse();

    ~ROSParse();

    void addVehicle(const int &VehicleID);

    void removeVehicle(const int &VehicleID);

    void publishDataStreamRequest(const int &VehicleID, const int &StreamType, const int &StreamRate);

    void publishDesiredFlightMode(const int &VehicleID, const int &FlightMode);

signals:

    void newVehicleAttitude(mavlink_common::ATTITUDE msg);
    void newVehicleHeartbeat(mavlink_common::HEARTBEAT msg);
    void newVehiclePositionRaw(mavlink_common::GPS_RAW_INT msg);
    void newVehiclePositionScaled(mavlink_common::GLOBAL_POSITION_INT msg);
    void newVehicleStatus(mavlink_common::SYS_STATUS msg);

public slots:

    //void publishDesiredFlightMode(const int &VehicleID, const int &FlightMode);



private slots:
    void UAVHeartbeat(const mavlink_common::HEARTBEAT &msg);
    void UAVAttitude(const mavlink_common::ATTITUDE &msg);
    void UAVPositionRaw(const mavlink_common::GPS_RAW_INT &msg);
    void UAVPositionScaled(const mavlink_common::GLOBAL_POSITION_INT &msg);
    void UAVSysStatus(const mavlink_common::SYS_STATUS &msg);

    void publishGCSHeartbeat();

private:

    QMap<int,bool> m_MapVehicleIDs;

    ros::Publisher arduPub_gcsHeartbeat;

    ros::Publisher arduPub_requestDataStreams;
    ros::Publisher arduPub_desiredFlightMode;

    ros::Subscriber arduSub_Heartbeat;
    ros::Subscriber arduSub_Attitude;
    ros::Subscriber arduSub_GPSPositionRaw;
    ros::Subscriber arduSub_GPSPositionScaled;
    ros::Subscriber arduSub_SysStatus;

    ros::AsyncSpinner* rosspinner;

    int m_GCSID;



};

#endif // ROSPARSE_H
