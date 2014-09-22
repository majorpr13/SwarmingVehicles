#include "swarmcontroller_gui.h"
#include "ui_swarmcontroller_gui.h"


SwarmController_GUI::SwarmController_GUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SwarmController_GUI)
{
    ui->setupUi(this);

    m_ROSParser = new ROSParse(10);
    m_MapVehicleWidgets.clear();
    m_MapVehicleRC.clear();
    m_HeartBeatTimer = new HeartBeatTimer();
    warningCounter = 0;

    connect(m_HeartBeatTimer,SIGNAL(elapsedUpdate(int,int)),this,SLOT(updateElapsedHearbeat(int,int)));
    connect(m_ROSParser,SIGNAL(newVehicleHeartbeat(mavlink_common::HEARTBEAT)),this,SLOT(updateVehicleHeartbeat(mavlink_common::HEARTBEAT)));
    connect(m_ROSParser,SIGNAL(newVehicleAttitude(mavlink_common::ATTITUDE)), this, SLOT(updateVehicleAttitude(mavlink_common::ATTITUDE)));
    connect(m_ROSParser,SIGNAL(newVehicleStatus(mavlink_common::SYS_STATUS)), this, SLOT(updateVehicleSysStatus(mavlink_common::SYS_STATUS)));
    connect(m_ROSParser,SIGNAL(newVehiclePositionRaw(mavlink_common::GPS_RAW_INT)), this, SLOT(updateVehiclePositionRaw(mavlink_common::GPS_RAW_INT)));
    connect(m_ROSParser,SIGNAL(newVehiclePositionScaled(mavlink_common::GLOBAL_POSITION_INT)), this, SLOT(updateVehiclePositionScaled(mavlink_common::GLOBAL_POSITION_INT)));
    connect(m_ROSParser,SIGNAL(newRCValues(mavlink_common::RC_CHANNELS_RAW)),this, SLOT(updateRadioValues(mavlink_common::RC_CHANNELS_RAW)));
    connect(m_ROSParser,SIGNAL(newJoystickValues(sensor_msgs::Joy)),this, SLOT(USBJoystick(sensor_msgs::Joy)));
    roll_counter = 0.0;
    pitch_counter = 0.0;
    JoystickCalibrate = false;
}

//SwarmController_GUI::SwarmController_GUI()
//{
//    //the empty constructor
//}

SwarmController_GUI::~SwarmController_GUI()
{
    delete ui;

    delete m_ROSParser;
}

void SwarmController_GUI::on_addVehicleID_clicked()
{

//    int VehicleID = ui->spinBoxVehicleID->value();
//    bool add_Vehicle;

//    add_Vehicle = ui->tableView_VehicleInformation->addEntry(VehicleID);

//    if(add_Vehicle == true)
//    {
//        VehicleDataDisplay *newWidget = new VehicleDataDisplay(ui->TabVehicleInfo);
//        ui->TabVehicleInfo->addTab(newWidget,QString::number(VehicleID));
//        m_MapVehicleWidgets.insert(VehicleID,newWidget);
//        m_ROSParser->addVehicle(VehicleID);
//    }

    int VehicleID = ui->spinBoxVehicleID->value();
    bool add_Vehicle;

    add_Vehicle = ui->tableView_VehicleInformation->addEntry(VehicleID);

    if(add_Vehicle == true)
    {
        m_HeartBeatTimer->addVehicle(VehicleID);

        VehicleDataDisplay *newWidget = new VehicleDataDisplay(ui->TabVehicleInfo);
        ui->TabVehicleInfo->addTab(newWidget,QString::number(VehicleID));

        m_MapVehicleWidgets.insert(VehicleID,newWidget);
        m_MapVehicleWidgets[VehicleID]->addVehicle(VehicleID);

        StructureDefinitions::VehicleRCHL default_value;
        m_MapVehicleRC.insert(VehicleID,default_value);

        connect(m_MapVehicleWidgets[VehicleID],SIGNAL(requestStream(int,int,int)),this,SLOT(updateStreamRequest(int,int,int)));
        connect(m_MapVehicleWidgets[VehicleID],SIGNAL(desiredFlightMode(int,int)),this,SLOT(updateDesiredFlightMode(int,int)));
        connect(m_MapVehicleWidgets[VehicleID],SIGNAL(armRequest(int,bool)),this,SLOT(armRequest(int,bool)));
        connect(m_MapVehicleWidgets[VehicleID],SIGNAL(radioCalibrate(int,int,bool)),this,SLOT(radioCalibration(int,int,bool)));
        connect(m_MapVehicleWidgets[VehicleID],SIGNAL(signalJoystickOverride(int,EnumerationDefinitions::FlightMethods,bool)),this,SLOT(updateRCOverrides(int,EnumerationDefinitions::FlightMethods,bool)));
        m_ROSParser->addVehicle(VehicleID);
    }

}

void SwarmController_GUI::updateVehiclePositionRaw(const mavlink_common::GPS_RAW_INT &VehiclePosition)
{
    ui->tableView_VehicleInformation->ChangeSatellite(VehiclePosition);
    //m_MapVehicleWidgets[VehiclePosition.sysid]->updatePositioning(VehiclePosition);
}

void SwarmController_GUI::updateVehiclePositionScaled(const mavlink_common::GLOBAL_POSITION_INT &VehiclePosition)
{
    m_MapVehicleWidgets[VehiclePosition.sysid]->updatePositioning(VehiclePosition);
}

void SwarmController_GUI::updateVehicleAttitude(const mavlink_common::ATTITUDE &VehicleAttitude)
{
    m_MapVehicleWidgets[VehicleAttitude.sysid]->updateAttitude(VehicleAttitude);
}

void SwarmController_GUI::updateVehicleSysStatus(const mavlink_common::SYS_STATUS &VehicleSysStatus)
{
    ui->tableView_VehicleInformation->ChangeBatteryVoltage(VehicleSysStatus);
}

void SwarmController_GUI::updateVehicleHeartbeat(const mavlink_common::HEARTBEAT &VehicleHeartbeat)
{
    int VehicleID = VehicleHeartbeat.sysid;
    m_HeartBeatTimer->restartTimer(VehicleID);

    if(VehicleHeartbeat.base_mode == 209)
    {
        ui->tableView_VehicleInformation->ChangeArmed(VehicleID, true);
        m_MapVehicleWidgets[VehicleID]->updateArmStatus(true);
    }
    else
    {
        ui->tableView_VehicleInformation->ChangeArmed(VehicleID, false);
        m_MapVehicleWidgets[VehicleID]->updateArmStatus(false);
    }
    m_MapVehicleWidgets[VehicleID]->updateFlightMode(VehicleHeartbeat);
}

void SwarmController_GUI::updateElapsedHearbeat(const int VehicleID, const int elapsedTime)
{
    ui->tableView_VehicleInformation->updateElapsedTime(VehicleID,elapsedTime);
}

void SwarmController_GUI::on_removeVehicleID_clicked()
{
    int VehicleID = ui->spinBoxVehicleID->value();
    m_HeartBeatTimer->removeVehicle(VehicleID);
    m_ROSParser->removeVehicle(VehicleID);
    ui->tableView_VehicleInformation->removeEntry(VehicleID);
    ui->TabVehicleInfo->removeTab(ui->TabVehicleInfo->indexOf(m_MapVehicleWidgets.value(VehicleID)));
    //dont know how to remove this pointer
    //delete(m_MapVehicleWidgets[VehicleID]->VehicleDataDisplay.ui);
    m_MapVehicleWidgets.remove(VehicleID);
}

void SwarmController_GUI::updateWarningString(const QString &warningString)
{
    //ui->textBrowser_Warnings->append(warningString);
}

void SwarmController_GUI::updateStreamRequest(const int &VehicleID, const int &StreamType, const int &StreamRate)
{
    m_ROSParser->publishDataStreamRequest(VehicleID,StreamType,StreamRate);
}

void SwarmController_GUI::updateDesiredFlightMode(const int &VehicleID, const int &DesiredFlightMode)
{
    m_ROSParser->publishDesiredFlightMode(VehicleID,DesiredFlightMode);
}

void SwarmController_GUI::radioCalibration(const int &VehicleID, const int &MessageStream, const bool &boolStream)
{
    //m_ROSParser->publishDataStreamRequest(VehicleID,MessageStream,10);
}

void SwarmController_GUI::updateRadioValues(const mavlink_common::RC_CHANNELS_RAW &VehicleRCValues)
{
    m_MapVehicleWidgets[VehicleRCValues.sysid]->updateRCValues(VehicleRCValues);
}

void SwarmController_GUI::armRequest(const int &VehicleID, const bool &armValue)
{
    m_ROSParser->publishArmDisarm(VehicleID,armValue);
}

void::SwarmController_GUI::USBJoystick(const sensor_msgs::Joy &JoystickValues)
{
    double roll = JoystickValues.axes.at(0);
    ui->lineEdit_RollCurrent->setText(QString::number(roll));

    double pitch = JoystickValues.axes.at(1);
    ui->lineEdit_PitchCurrent->setText(QString::number(pitch));

    double yaw = JoystickValues.axes.at(4);
    ui->lineEdit_YawCurrent->setText(QString::number(yaw));

    double throttle = JoystickValues.axes.at(2);
    ui->lineEdit_ThrottleCurrent->setText(QString::number(throttle));

    if(JoystickCalibrate == true)
    {
        if(roll < m_USBJoystickHL.roll_low)
        {
            m_USBJoystickHL.roll_low = roll;
            ui->lineEdit_RollLow->setText(QString::number(m_USBJoystickHL.roll_low));
        }
        else if(roll > m_USBJoystickHL.roll_high)
        {
            m_USBJoystickHL.roll_high = roll;
            ui->lineEdit_RollHigh->setText(QString::number(m_USBJoystickHL.roll_high));
        }

        if(pitch < m_USBJoystickHL.pitch_low)
        {
            m_USBJoystickHL.pitch_low = pitch;
            ui->lineEdit_PitchLow->setText(QString::number(m_USBJoystickHL.pitch_low));
        }
        else if(pitch > m_USBJoystickHL.pitch_high)
        {
            m_USBJoystickHL.pitch_high = pitch;
            ui->lineEdit_PitchHigh->setText(QString::number(m_USBJoystickHL.pitch_high));
        }

        if(yaw < m_USBJoystickHL.yaw_low)
        {
            m_USBJoystickHL.yaw_low = yaw;
            ui->lineEdit_YawLow->setText(QString::number(m_USBJoystickHL.yaw_low));
        }
        else if(yaw > m_USBJoystickHL.yaw_high)
        {
            m_USBJoystickHL.yaw_high = yaw;
            ui->lineEdit_YawHigh->setText(QString::number(m_USBJoystickHL.yaw_high));
        }

        if(throttle < m_USBJoystickHL.throttle_low)
        {
            m_USBJoystickHL.throttle_low = throttle;
            ui->lineEdit_ThrottleLow->setText(QString::number(m_USBJoystickHL.throttle_low));
        }
        else if(throttle > m_USBJoystickHL.throttle_high)
        {
            m_USBJoystickHL.throttle_high = throttle;
            ui->lineEdit_ThrottleHigh->setText(QString::number(m_USBJoystickHL.throttle_high));
        }
    }

    else
    {
        QMapIterator<int, VehicleDataDisplay*> i(m_MapVehicleRC);
        while(i.hasNext())
        {
            i.next();
            if(m_MapVehicleRC[i.key()].roll_or == true)
            {

            }
            if(m_MapVehicleRC[i.key()].pitch_or == true)
            {

            }
            if(m_MapVehicleRC[i.key()].yaw_or == true)
            {

            }
            if(m_MapVehicleRC[i.key()].throttle_or == true)
            {

            }
        }

    }
}

void SwarmController_GUI::on_pushButton_USBCalibrate_clicked()
{
    JoystickCalibrate = !JoystickCalibrate;
    if(JoystickCalibrate == true)
        ui->pushButton_USBCalibrate->setText("DONE");
    else
        ui->pushButton_USBCalibrate->setText("CALIBRATE");
}

void SwarmController_GUI::updateRCOverrides(const int &VehicleID, const EnumerationDefinitions::FlightMethods &FlightMode, const bool &boolOverrride)
{
    if(FlightMode == EnumerationDefinitions::Roll)
        m_MapVehicleRC[VehicleID].roll_or = boolOverrride;
    else if(FlightMode == EnumerationDefinitions::Pitch)
        m_MapVehicleRC[VehicleID].pitch_or = boolOverrride;
    else if(FlightMode == EnumerationDefinitions::Yaw)
        m_MapVehicleRC[VehicleID].yaw_or = boolOverrride;
    else if(FlightMode == EnumerationDefinitions::Throttle)
        m_MapVehicleRC[VehicleID].throttle_or = boolOverrride;

}

void SwarmController_GUI::on_doubleSpinBox_LatHome_valueChanged(double arg1)
{
    QMapIterator<int, VehicleDataDisplay*> i(m_MapVehicleWidgets);
    while(i.hasNext())
    {
        i.next();
        m_MapVehicleWidgets[i.key()]->updateHomeCoordinate(EnumerationDefinitions::Lat,arg1);
    }
}

void SwarmController_GUI::on_doubleSpinBox_LonHome_valueChanged(double arg1)
{
    QMapIterator<int, VehicleDataDisplay*> i(m_MapVehicleWidgets);
    while(i.hasNext())
    {
        i.next();
        m_MapVehicleWidgets[i.key()]->updateHomeCoordinate(EnumerationDefinitions::Lon,arg1);
    }
}

void SwarmController_GUI::on_doubleSpinBox_AltHome_valueChanged(double arg1)
{
    QMapIterator<int, VehicleDataDisplay*> i(m_MapVehicleWidgets);
    while(i.hasNext())
    {
        i.next();
        m_MapVehicleWidgets[i.key()]->updateHomeCoordinate(EnumerationDefinitions::Alt,arg1);
    }
}
