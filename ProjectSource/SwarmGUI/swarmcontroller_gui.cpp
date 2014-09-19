#include "swarmcontroller_gui.h"
#include "ui_swarmcontroller_gui.h"


SwarmController_GUI::SwarmController_GUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SwarmController_GUI)
{
    ui->setupUi(this);

    m_ROSParser = new ROSParse(10);
    m_MapVehicleWidgets.clear();
    m_HeartBeatTimer = new HeartBeatTimer();
    warningCounter = 0;

    connect(m_HeartBeatTimer,SIGNAL(elapsedUpdate(int,int)),this,SLOT(updateElapsedHearbeat(int,int)));
    connect(m_ROSParser,SIGNAL(newVehicleHeartbeat(mavlink_common::HEARTBEAT)),this,SLOT(updateVehicleHeartbeat(mavlink_common::HEARTBEAT)));
    connect(m_ROSParser,SIGNAL(newVehicleAttitude(mavlink_common::ATTITUDE)), this, SLOT(updateVehicleAttitude(mavlink_common::ATTITUDE)));
    connect(m_ROSParser,SIGNAL(newVehicleStatus(mavlink_common::SYS_STATUS)), this, SLOT(updateVehicleSysStatus(mavlink_common::SYS_STATUS)));
    connect(m_ROSParser,SIGNAL(newVehiclePositionRaw(mavlink_common::GPS_RAW_INT)), this, SLOT(updateVehiclePositionRaw(mavlink_common::GPS_RAW_INT)));
    connect(m_ROSParser,SIGNAL(newVehiclePositionScaled(mavlink_common::GLOBAL_POSITION_INT)), this, SLOT(updateVehiclePositionScaled(mavlink_common::GLOBAL_POSITION_INT)));
    roll_counter = 0.0;
    pitch_counter = 0.0;
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
        connect(m_MapVehicleWidgets[VehicleID],SIGNAL(requestStream(int,int,int)),this,SLOT(updateStreamRequest(int,int,int)));
        connect(m_MapVehicleWidgets[VehicleID],SIGNAL(desiredFlightMode(int,int)),this,SLOT(updateDesiredFlightMode(int,int)));
        connect(m_MapVehicleWidgets[VehicleID],SIGNAL(),this,SLOT();
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
    //if the vehicle is armed
    if(VehicleHeartbeat.system_status == 4)
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
    m_ROSParser->publishDataStreamRequest(VehicleID,MessageStream,10);
}
