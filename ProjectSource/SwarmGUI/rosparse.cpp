#include "rosparse.h"
#include <QString>
#include <QDebug>
ROSParse::ROSParse(){

}

ROSParse::ROSParse(const int &GCSID)
{
    m_GCSID = GCSID;

        ros::NodeHandle node_handler;

        arduSub_Heartbeat = node_handler.subscribe("/from_mav_heartbeat",10,&ROSParse::UAVHeartbeat,this);
        arduSub_Attitude = node_handler.subscribe("/from_mav_attitude",10,&ROSParse::UAVAttitude,this);
        arduSub_GPSPositionRaw = node_handler.subscribe("/from_mav_gps_raw_int",10,&ROSParse::UAVPositionRaw,this);
        arduSub_GPSPositionScaled = node_handler.subscribe("/from_mav_global_position_int",10, &ROSParse::UAVPositionScaled,this);
        arduSub_SysStatus = node_handler.subscribe("/from_mav_sys_status",10,&ROSParse::UAVSysStatus,this);

        arduPub_desiredFlightMode = node_handler.advertise<mavlink_common::SET_MODE>("to_mav_set_mode",10);
        arduPub_requestDataStreams = node_handler.advertise<mavlink_common::REQUEST_DATA_STREAM>("to_mav_request_data_stream",10);
        //arduPub_gcsHeartbeat = node_handler.advertise<mavlink_common::HEARTBEAT>("to_mav_heartbeat",2);

        //connect(m_TimerHeartbeat,SIGNAL(timeout()),this,SLOT(publishGCSHeartbeat()));
        rosspinner = new ros::AsyncSpinner(0);
        rosspinner->start();
}

ROSParse::~ROSParse()
{

}


void ROSParse::addVehicle(const int &VehicleID)
{
    m_MapVehicleIDs.insert(VehicleID,true);
}

void ROSParse::removeVehicle(const int &VehicleID)
{
    m_MapVehicleIDs.remove(VehicleID);
}


void ROSParse::UAVHeartbeat(const mavlink_common::HEARTBEAT &msg)
{
    if(m_MapVehicleIDs.contains(msg.sysid))
    {
        emit(newVehicleHeartbeat(msg));
    }
    else
        return;
}

void ROSParse::UAVAttitude(const mavlink_common::ATTITUDE &msg)
{
    if(m_MapVehicleIDs.contains(msg.sysid))
    {
        //m_VehicleState->updateAttitude(msg);
        emit(newVehicleAttitude(msg));
    }
    else
        return;
}

void ROSParse::UAVPositionRaw(const mavlink_common::GPS_RAW_INT &msg)
{
    if(m_MapVehicleIDs.contains(msg.sysid))
    {
        emit(newVehiclePositionRaw(msg));
    }
}

void ROSParse::UAVPositionScaled(const mavlink_common::GLOBAL_POSITION_INT &msg)
{
    if(m_MapVehicleIDs.contains(msg.sysid))
    {
        emit(newVehiclePositionScaled(msg));
    }
}
void ROSParse::UAVSysStatus(const mavlink_common::SYS_STATUS &msg)
{
    if(m_MapVehicleIDs.contains(msg.sysid))
    {
        emit(newVehicleStatus(msg));
    }
}

void ROSParse::publishGCSHeartbeat()
{
    StructureDefinitions::GCSDefinition GCSParameters;
    mavlink_common::HEARTBEAT msg;
    msg.sysid = GCSParameters.sysid;
    msg.compid = GCSParameters.compid;
    msg.type = 0;
    msg.autopilot = 0;
    msg.base_mode = 0;
    msg.custom_mode = 395264;
    msg.system_status = 0;
    msg.mavlink_version = 3;

    arduPub_gcsHeartbeat.publish(msg);
}

void ROSParse::publishDataStreamRequest(const int &VehicleID, const int &StreamType, const int &StreamRate)
{
    StructureDefinitions::GCSDefinition GCSParameters;
    mavlink_common::REQUEST_DATA_STREAM msg;

    msg.sysid = GCSParameters.sysid;
    msg.compid = GCSParameters.compid;

    msg.target_system = VehicleID;
    msg.target_component = 0;
    msg.req_stream_id = StreamType;
    msg.req_message_rate = StreamRate;

    if(StreamRate == 0)
        msg.start_stop = 0;
    else
        msg.start_stop = 1;
    arduPub_requestDataStreams.publish(msg);
    arduPub_requestDataStreams.publish(msg);
}

void ROSParse::publishDesiredFlightMode(const int &VehicleID, const int &FlightMode)
{
    StructureDefinitions::GCSDefinition GCSParameters;
    mavlink_common::SET_MODE msg;

    msg.sysid = GCSParameters.sysid;
    msg.compid = GCSParameters.compid;

    msg.target_system = VehicleID;
    msg.base_mode = 01;
    msg.custom_mode = FlightMode;

}
