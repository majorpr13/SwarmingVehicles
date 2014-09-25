#include "rosparse.h"
#include <QString>
#include <QDebug>



#ifdef ROS_LIBS
ROSParse::ROSParse(){

}

ROSParse::ROSParse(const int &GCSID)
{
    m_GCSID = GCSID;

        ros::NodeHandle node_handler;

        arduSub_Heartbeat = node_handler.subscribe("/from_mav_heartbeat", 10, &ROSParse::UAVHeartbeat,this);
        arduSub_Attitude = node_handler.subscribe("/from_mav_attitude", 10, &ROSParse::UAVAttitude,this);
        arduSub_GPSPositionRaw = node_handler.subscribe("/from_mav_gps_raw_int", 10, &ROSParse::UAVPositionRaw,this);
        arduSub_GPSPositionScaled = node_handler.subscribe("/from_mav_global_position_int",10, &ROSParse::UAVPositionScaled,this);
        arduSub_SysStatus = node_handler.subscribe("/from_mav_sys_status", 10, &ROSParse::UAVSysStatus,this);
        arduSub_RCRawValue = node_handler.subscribe("/from_mav_rc_channels_raw", 10, &ROSParse::UAVRCValue,this);
        arduSub_ParamReq = node_handler.subscribe("/from_mav_param_value",10,&ROSParse::UAVParam,this);

        arduPub_desiredFlightMode = node_handler.advertise<mavlink_common::SET_MODE>("to_mav_set_mode",10);
        arduPub_requestDataStreams = node_handler.advertise<mavlink_common::REQUEST_DATA_STREAM>("to_mav_request_data_stream",10);
        arduPub_armRequest = node_handler.advertise<mavlink_common::COMMAND_LONG>("to_mav_command_long",10);
        arduPub_rcOverride = node_handler.advertise<mavlink_common::RC_CHANNELS_OVERRIDE>("to_mav_rc_channels_override",10);
        arduPub_paramReq = node_handler.advertise<mavlink_common::PARAM_REQUEST_READ>("to_mav_param_request_read",20);
        arduPub_cmdReq = node_handler.advertise<mavlink_common::COMMAND_LONG>("to_mav_command_long",10);

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

void ROSParse::UAVRCValue(const mavlink_common::RC_CHANNELS_RAW &msg)
{
    if(m_MapVehicleIDs.contains(msg.sysid))
    {
        emit(newRCValues(msg));
    }
}

void ROSParse::UAVParam(const mavlink_common::PARAM_VALUE &msg)
{
    if(m_MapVehicleIDs.contains(msg.sysid))
    {
        emit(newVehicleParam(msg));
    }
}

void ROSParse::publishParamSet(const int &VehicleID, const QString &msgString, const double &value)
{
    StructureDefinitions::GCSDefinition GCSParameters;
    mavlink_common::PARAM_SET msg;

    msg.sysid = GCSParameters.sysid;
    msg.compid = GCSParameters.compid;

    msg.target_system = VehicleID;
    msg.target_component = 0;

    boost::array<u_int8_t, 16> stringArray;
    std::fill(stringArray.begin(), stringArray.end(), 0 );
    QByteArray ba = msgString.toLocal8Bit();

    for(int i = 0; i < ba.length(); i++)
    {
        stringArray[i] = ba.at(i);
    }

    msg.param_id = stringArray;
    msg.param_value = value;

    arduPub_paramSet.publish(msg);
}

void ROSParse::publishMAVcommand(const int &VehicleID, const int &idCMD, const int &confirmation, const QVector<double> &msgVector)
{
    if(msgVector.size() == 7)
    {
        StructureDefinitions::GCSDefinition GCSParameters;
        mavlink_common::COMMAND_LONG msg;

        msg.sysid = GCSParameters.sysid;
        msg.compid = GCSParameters.compid;

        msg.target_system = VehicleID;
        msg.target_component = 0;

        msg.command = idCMD;

        msg.confirmation = confirmation;

        msg.param1 = msgVector.at(0);
        msg.param2 = msgVector.at(1);
        msg.param3 = msgVector.at(2);
        msg.param4 = msgVector.at(3);
        msg.param5 = msgVector.at(4);
        msg.param6 = msgVector.at(5);
        msg.param7 = msgVector.at(6);

        arduPub_cmdReq.publish(msg);
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

void ROSParse::publishParameterRequest(const int &VehicleID, const QString &msgString)
{
    StructureDefinitions::GCSDefinition GCSParameters;
    mavlink_common::PARAM_REQUEST_READ msg;

    msg.sysid = GCSParameters.sysid;
    msg.compid = GCSParameters.compid;

    msg.target_system = VehicleID;
    msg.target_component = 0;

    boost::array<u_int8_t, 16> stringArray;
    std::fill(stringArray.begin(), stringArray.end(), 0 );
    QByteArray ba = msgString.toLocal8Bit();

    for(int i = 0; i < ba.length(); i++)
    {
        stringArray[i] = ba.at(i);
    }

    msg.param_id = stringArray;
    msg.param_index = -1;

    arduPub_paramReq.publish(msg);

}

void ROSParse::publishDataStreamRequest(const int &VehicleID, const int &StreamMessage, const int &StreamRate)
{
    StructureDefinitions::GCSDefinition GCSParameters;
    mavlink_common::REQUEST_DATA_STREAM msg;

    msg.sysid = GCSParameters.sysid;
    msg.compid = GCSParameters.compid;

    msg.target_system = VehicleID;
    msg.target_component = 01;
    msg.req_stream_id = StreamMessage;
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
    arduPub_desiredFlightMode.publish(msg);
    arduPub_desiredFlightMode.publish(msg);
}

void ROSParse::publishArmDisarm(const int &VehicleID, const bool &ArmStatus)
{
    StructureDefinitions::GCSDefinition GCSParameters;
    mavlink_common::COMMAND_LONG msg;
    msg.sysid = GCSParameters.sysid;
    msg.compid = GCSParameters.compid;

    msg.target_system = VehicleID;
    msg.target_component = 250;
    msg.command = 400;
    msg.confirmation = 00;

    if(ArmStatus == false)
        msg.param1 = 00;
    else
        msg.param1 = 01;

    arduPub_armRequest.publish(msg);
}

void ROSParse::publishJoystickOverride(const int &VehicleID, const StructureDefinitions::RCOverride &RCOverride)
{
    StructureDefinitions::GCSDefinition GCSParameters;
    mavlink_common::RC_CHANNELS_OVERRIDE msg;
    msg.sysid = GCSParameters.sysid;
    msg.compid = GCSParameters.compid;

    msg.target_system = VehicleID;
    msg.target_component = 0; // check that this value is correct
    msg.chan1_raw = RCOverride.roll_override;
    msg.chan2_raw = RCOverride.pitch_override;
    msg.chan3_raw = RCOverride.throttle_override;
    msg.chan4_raw = RCOverride.yaw_override;
    msg.chan5_raw = 0;
    msg.chan6_raw = 0;
    msg.chan7_raw = 0;
    msg.chan8_raw = 0;
    arduPub_armRequest.publish(msg);
}

void ROSParse::JoystickValues(const sensor_msgs::Joy &msg)
{
    emit(newJoystickValues(msg));
}

void ROSParse::joystickMode(const bool &joystickOperations)
{
    ros::NodeHandle node_handler;

    if(joystickOperations == true)
        joySub_Value = node_handler.subscribe("/joy", 2, &ROSParse::JoystickValues, this);
    else
        joySub_Value.shutdown();
}


#endif
