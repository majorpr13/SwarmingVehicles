#include "swarmcontroller_gui.h"
#include "ui_swarmcontroller_gui.h"


SwarmController_GUI::SwarmController_GUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SwarmController_GUI)
{
    ui->setupUi(this);

    initialization();

    m_MapVehicleWidgets.clear();

    m_HeartBeatTimer = new HeartBeatTimer();

    m_JoystickHandler = new USBJoy_Handler();

    m_CommandHelper = new Command_Helper();

    m_Conversions = new Conversions();


    connect(m_HeartBeatTimer,SIGNAL(elapsedUpdate(int,int)),this,SLOT(updateElapsedHearbeat(int,int)));

    JoystickCalibrate = false;
    JoystickEnabled = false;

    listVehicles.clear();

#ifdef ROS_LIBS
    m_ROSParser = new ROSParse(10);
    connect(m_ROSParser,SIGNAL(newVehicleHeartbeat(mavlink_common::HEARTBEAT)),this,SLOT(updateVehicleHeartbeat(mavlink_common::HEARTBEAT)));
    connect(m_ROSParser,SIGNAL(newVehicleAttitude(mavlink_common::ATTITUDE)), this, SLOT(updateVehicleAttitude(mavlink_common::ATTITUDE)));
    connect(m_ROSParser,SIGNAL(newVehicleStatus(mavlink_common::SYS_STATUS)), this, SLOT(updateVehicleSysStatus(mavlink_common::SYS_STATUS)));
    connect(m_ROSParser,SIGNAL(newVehiclePositionRaw(mavlink_common::GPS_RAW_INT)), this, SLOT(updateVehiclePositionRaw(mavlink_common::GPS_RAW_INT)));
    connect(m_ROSParser,SIGNAL(newVehiclePositionScaled(mavlink_common::GLOBAL_POSITION_INT)), this, SLOT(updateVehiclePositionScaled(mavlink_common::GLOBAL_POSITION_INT)));
    connect(m_ROSParser,SIGNAL(newRCValues(mavlink_common::RC_CHANNELS_RAW)),this, SLOT(updateRadioValues(mavlink_common::RC_CHANNELS_RAW)));
    connect(m_ROSParser,SIGNAL(newVehicleParam(mavlink_common::PARAM_VALUE)),this,SLOT(updateVehicleParams(mavlink_common::PARAM_VALUE)));
    connect(m_ROSParser,SIGNAL(newJoystickValues(sensor_msgs::Joy)),this, SLOT(USBJoystick(sensor_msgs::Joy)));

    //m_ROSParser->initiate(10);

#endif
}

void SwarmController_GUI::initialization()
{
    ui->pushButton_ImportHome->setDisabled(true);
    ui->pushButton_ExportHome->setDisabled(false);
    ui->pushButton_USBCalibrate->setDisabled(true);
}

void SwarmController_GUI::updateButtons()
{
    if(m_MapVehicleWidgets.size() > 0)
    {
        ui->pushButton_ImportHome->setDisabled(false);
        ui->pushButton_ExportHome->setDisabled(false);
    }
    else
    {
        ui->pushButton_ImportHome->setDisabled(true);
        ui->pushButton_ExportHome->setDisabled(true);
    }
}

SwarmController_GUI::~SwarmController_GUI()
{
    delete ui;

#ifdef ROS_LIBS
    delete m_ROSParser;
#endif
}

void SwarmController_GUI::on_addVehicleID_clicked()
{
    int VehicleID = ui->comboBox_VehicleID->currentText().toInt();
    bool add_Vehicle;

    add_Vehicle = ui->tableView_VehicleInformation->addEntry(VehicleID);

    if(add_Vehicle == true)
    {
        RC_Handler *newRCHandler = new RC_Handler();
        m_MapRC.insert(VehicleID,newRCHandler);

        m_HeartBeatTimer->addVehicle(VehicleID);

        VehicleDataDisplay *newWidget = new VehicleDataDisplay(ui->TabVehicleInfo);

        // If this is the first vehicle being added, delete the placeholder tab
        if(m_MapVehicleWidgets.isEmpty())
            ui->tabWidget_Vehicles->removeTab(0);

        ui->tabWidget_Vehicles->addTab(newWidget,QString::number(VehicleID));


        m_MapVehicleWidgets.insert(VehicleID,newWidget);
        m_MapVehicleWidgets[VehicleID]->addVehicle(VehicleID);

        ui->comboBox_VehicleHome->addItem(QString::number(VehicleID));

        connect(m_MapVehicleWidgets[VehicleID],SIGNAL(requestRCParams(int)),this,SLOT(requestRCParams(int)));
        connect(m_MapVehicleWidgets[VehicleID],SIGNAL(requestWPParams(int)),this,SLOT(requestWPParams(int)));
        connect(m_MapVehicleWidgets[VehicleID],SIGNAL(transmitWPParams(int,QString,double)),m_ROSParser,SLOT(publishParamSet(int,QString,double)));

        connect(m_MapVehicleWidgets[VehicleID],SIGNAL(signalJoystickOverride(int,RC_Handler::FlightChannel,bool)),this,SLOT(updateRCOverrides(int,RC_Handler::FlightChannel,bool)));
        connect(m_MapVehicleWidgets[VehicleID],SIGNAL(signalJoystickReverse(int,RC_Handler::FlightChannel,bool)),this,SLOT(updateRCReverse(int,RC_Handler::FlightChannel,bool)));

#ifdef ROS_LIBS
        m_ROSParser->addVehicle(VehicleID);

        connect(m_MapVehicleWidgets[VehicleID],SIGNAL(requestStream(int,int,int)),m_ROSParser,SLOT(publishDataStreamRequest(int,int,int)));
        connect(m_MapVehicleWidgets[VehicleID],SIGNAL(desiredFlightMode(int,int)),m_ROSParser,SLOT(publishDesiredFlightMode(int,int)));
        connect(m_MapVehicleWidgets[VehicleID],SIGNAL(armRequest(int,bool)),m_ROSParser,SLOT(publishArmDisarm(int,bool)));

#endif

        updateButtons();
    }

}

void SwarmController_GUI::updateElapsedHearbeat(const int VehicleID, const int elapsedTime)
{
    ui->tableView_VehicleInformation->updateElapsedTime(VehicleID,elapsedTime);
}

void SwarmController_GUI::on_removeVehicleID_clicked()
{
    int VehicleID = ui->comboBox_VehicleID->currentText().toInt();
    m_HeartBeatTimer->removeVehicle(VehicleID);

    int StreamModes [9] = {0,1,2,3,4,6,10,11,12};  //This segment will tell the vehicle to stop streaming
    for(int i = 0; i < 9; i++)   //when disconnecting so that it does not take up BW of swarm
    {
        m_ROSParser->publishDataStreamRequest(VehicleID,StreamModes[i],0);
    }

#ifdef ROS_LIBS
    m_ROSParser->removeVehicle(VehicleID);
#endif

    // Remove the tab
    for(int i = 0; i <= ui->tabWidget_Vehicles->count(); i++)
    {
        QString temp;
        temp = ui->tabWidget_Vehicles->tabText(i);
        if(temp == QString::number(VehicleID))
        {
            ui->tabWidget_Vehicles->removeTab(i);
        }
    }

    ui->tableView_VehicleInformation->removeEntry(VehicleID);
    ui->TabVehicleInfo->removeTab(ui->TabVehicleInfo->indexOf(m_MapVehicleWidgets.value(VehicleID)));

    //dont know how to remove this pointer
    //delete(m_MapVehicleWidgets[VehicleID]->VehicleDataDisplay.ui);
    m_MapVehicleWidgets.remove(VehicleID);
    m_MapRC.remove(VehicleID);

    ui->comboBox_VehicleHome->removeItem(ui->comboBox_VehicleHome->findText(QString::number(VehicleID)));

    updateButtons();
}

void SwarmController_GUI::requestRCParams(const int &VehicleID)
{
    QList<QString> listRC = m_MapRC[VehicleID]->parameterList_RC();
    for(int i = 0; i < listRC.length(); i++)
    {
#ifdef ROS_LIBS
        m_ROSParser->publishParameterRequest(VehicleID,listRC.at(i));
#endif
    }
}

void SwarmController_GUI::requestWPParams(const int &VehicleID)
{
    QList<QString> listRC = m_Conversions->parameterList_WP();
    for(int i = 0; i < listRC.length(); i++)
    {
#ifdef ROS_LIBS
        m_ROSParser->publishParameterRequest(VehicleID,listRC.at(i));
#endif
    }

}

void SwarmController_GUI::on_pushButton_USBCalibrate_clicked()
{
    JoystickCalibrate = !JoystickCalibrate;
    if(JoystickCalibrate == true)
        ui->pushButton_USBCalibrate->setText("Done");
    else
    {
        ui->pushButton_USBCalibrate->setText("Calibrate");
        QMapIterator<int, VehicleDataDisplay*> i(m_MapVehicleWidgets);
        while(i.hasNext())
        {
            i.next();
            m_MapVehicleWidgets[i.key()]->USBcalibrationCompleted();
        }
    }
}

void SwarmController_GUI::updateRCOverrides(const int &VehicleID, const RC_Handler::FlightChannel &FlightChannel, const bool &boolOverride)
{
    RC_Handler::cmd_Value updateOverride = m_MapRC[VehicleID]->updateRCOverrides(FlightChannel,boolOverride);

#ifdef ROS_LIBS
    m_ROSParser->publishJoystickOverride_single(VehicleID , updateOverride);
#endif
}

void SwarmController_GUI::updateRCReverse(const int &VehicleID, const RC_Handler::FlightChannel &FlightChannel, const bool &boolReverse)
{
    if(FlightChannel == RC_Handler::ROLL)
        m_MapRC[VehicleID]->setbool_Reverse(RC_Handler::ROLL,boolReverse);
    else if(FlightChannel == RC_Handler::PITCH)
        m_MapRC[VehicleID]->setbool_Reverse(RC_Handler::PITCH,boolReverse);
    else if(FlightChannel == RC_Handler::YAW)
        m_MapRC[VehicleID]->setbool_Reverse(RC_Handler::YAW,boolReverse);
    else if(FlightChannel == RC_Handler::THROTTLE)
        m_MapRC[VehicleID]->setbool_Reverse(RC_Handler::THROTTLE,boolReverse);
}

void SwarmController_GUI::on_pushButton_USBJOY_Enable_clicked()
{
    JoystickEnabled = !JoystickEnabled;
    if(JoystickEnabled == true)
    {
        ui->pushButton_USBCalibrate->setDisabled(false);
        ui->pushButton_USBJOY_Enable->setText("Disable");
    }
    else
    {
        ui->pushButton_USBCalibrate->setDisabled(true);
        ui->pushButton_USBJOY_Enable->setText("Enable");

        QMapIterator<int, RC_Handler*> i(m_MapRC);
        while(i.hasNext())
        {
            i.next();
            m_MapRC[i.key()]->setbool_Override(RC_Handler::ALL,false);
            RC_Handler::cmd_Value override_command;
            m_ROSParser->publishJoystickOverride_single(i.key(),override_command);
        }
    }

#ifdef ROS_LIBS
    m_ROSParser->joystickMode(JoystickEnabled);
#endif
}

void SwarmController_GUI::on_pushButton_ImportHome_clicked()
{
    GPS_Position HomePosition;
    QString string_VehicleID = ui->comboBox_VehicleHome->currentText();
    if(string_VehicleID != "ALL")
    {
        HomePosition = m_MapVehicleWidgets[string_VehicleID.toInt()]->requestPosition();

        ui->doubleSpinBox_LatHome->setValue(HomePosition.Latitude);
        ui->doubleSpinBox_LonHome->setValue(HomePosition.Longitude);
        ui->doubleSpinBox_AltHome->setValue(HomePosition.Altitude);
    }
}

void SwarmController_GUI::on_pushButton_ExportHome_clicked()
{
    QVector<double> homePositionVector(7);

    int numVehicles = m_MapVehicleWidgets.size();
    double degreeSeperation = 360.0 / (double)numVehicles;
    double distance = ui->spinBox_LandingRadius->value();

    double bearing = 0.0;
    int counter = 0;

    GPS_Position swarmHome;
    GPS_Position VehicleHome;

    swarmHome.Latitude = ui->doubleSpinBox_LatHome->value();
    swarmHome.Longitude = ui->doubleSpinBox_LonHome->value();
    swarmHome.Altitude = ui->doubleSpinBox_AltHome->value();

    QString string_VehicleID = ui->comboBox_VehicleHome->currentText();

    if(string_VehicleID == "ALL")
    {
        QMapIterator<int, VehicleDataDisplay*> i(m_MapVehicleWidgets);
        while(i.hasNext())
        {
            i.next();
            bearing = (double)counter * degreeSeperation;

            VehicleHome = swarmHome.Final(bearing,distance);
            m_MapVehicleWidgets[i.key()]->updateHomeCoordinate(VehicleHome);
            homePositionVector = m_CommandHelper->convert_setHome(0,VehicleHome);

            counter = counter + 1;

#ifdef ROS_LIBS
            m_ROSParser->publishMAVcommand(i.key(),mavCmdNum->setHome,0,homePositionVector);
#endif
        }
    }
    else
    {
        VehicleHome = swarmHome.Final(bearing,distance);

        m_MapVehicleWidgets[string_VehicleID.toInt()]->updateHomeCoordinate(VehicleHome);

        homePositionVector = m_CommandHelper->convert_setHome(0,VehicleHome);
#ifdef ROS_LIBS
        m_ROSParser->publishMAVcommand(string_VehicleID.toInt(),mavCmdNum->setHome,0,homePositionVector);
#endif
    }
}


#ifdef ROS_LIBS
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

    if(listVehicles.contains(QString::number(VehicleID)) == false)
    {
        listVehicles.append(QString::number(VehicleID));
        ui->comboBox_VehicleID->addItem(QString::number(VehicleID));
    }

    if(m_MapVehicleWidgets.contains(VehicleID))
    {
        m_MapVehicleWidgets[VehicleID]->updateVehicleType((EnumerationDefinitions::Vehicle_Type)VehicleHeartbeat.type);

        m_HeartBeatTimer->restartTimer(VehicleID);
        if(VehicleHeartbeat.base_mode == 81)
        {
            ui->tableView_VehicleInformation->ChangeArmed(VehicleID, false);
            m_MapVehicleWidgets[VehicleID]->updateArmStatus(false);
        }
        else
        {
            ui->tableView_VehicleInformation->ChangeArmed(VehicleID, true);
            m_MapVehicleWidgets[VehicleID]->updateArmStatus(true);
        }
        m_MapVehicleWidgets[VehicleID]->updateFlightMode(VehicleHeartbeat);
    }
}

void SwarmController_GUI::updateVehicleParams(const mavlink_common::PARAM_VALUE &VehicleParamValue)
{
    m_MapVehicleWidgets[VehicleParamValue.sysid]->updateVehicleParams(VehicleParamValue);
}

void SwarmController_GUI::updateRadioValues(const mavlink_common::RC_CHANNELS_RAW &VehicleRCValues)
{
    m_MapVehicleWidgets[VehicleRCValues.sysid]->updateRCValues(VehicleRCValues);
}

void::SwarmController_GUI::USBJoystick(const sensor_msgs::Joy &JoystickValues)
{
    updateUSBButtons(JoystickValues); //This will update the buttons and perform any associated actions

    if(JoystickCalibrate == true)
    {
        m_JoystickHandler->USBJoystickCalibration(JoystickValues);
        RC_Handler::USBJoystick USBHL = m_JoystickHandler->getUSBJoystickCalibration();

        ui->lineEdit_RollLow->setText(QString::number(USBHL.USB_RL));
        ui->lineEdit_RollHigh->setText(QString::number(USBHL.USB_RH));
        ui->lineEdit_PitchLow->setText(QString::number(USBHL.USB_PL));
        ui->lineEdit_PitchHigh->setText(QString::number(USBHL.USB_PH));
        ui->lineEdit_YawLow->setText(QString::number(USBHL.USB_YL));
        ui->lineEdit_YawHigh->setText(QString::number(USBHL.USB_YH));
        ui->lineEdit_ThrottleLow->setText(QString::number(USBHL.USB_TL));
        ui->lineEdit_ThrottleHigh->setText(QString::number(USBHL.USB_TH));

        QMapIterator<int, RC_Handler*> i(m_MapRC);
        while(i.hasNext())
        {
            i.next();
            m_MapRC[i.key()]->setJS_HL(USBHL);
        }
    }

    else
    {
        RC_Handler::usb_Value usbValue;
        usbValue.roll_value = JoystickValues.axes.at(0);
        usbValue.pitch_value = JoystickValues.axes.at(1);
        usbValue.yaw_value = JoystickValues.axes.at(4);
        usbValue.throttle_value = JoystickValues.axes.at(2);

        QMap<int,RC_Handler::cmd_Value> mapCommand;

        QMapIterator<int, RC_Handler*> i(m_MapRC);
        while(i.hasNext())
        {
            i.next();
            if(i.value()->overrideDesired == true)
            {
                RC_Handler::cmd_Value cmdValue = m_MapRC[i.key()]->computeOverride(usbValue);
                mapCommand.insert(i.key(),cmdValue);
                m_MapVehicleWidgets[i.key()]->updateUSBOverride(cmdValue);
            }
        }
        m_ROSParser->publishJoystickOverride(mapCommand);
    }
}

void SwarmController_GUI::updateUSBButtons(const sensor_msgs::Joy &JoystickValues)
{
    if(m_USBButtons.Button1 != JoystickValues.buttons.at(0))
    {
        m_USBButtons.Button1 = JoystickValues.buttons.at(0);
    }
    if(m_USBButtons.Button2 != JoystickValues.buttons.at(1))
    {
        m_USBButtons.Button2 = JoystickValues.buttons.at(1);
    }
    if(m_USBButtons.Button3 != JoystickValues.buttons.at(2))
    {
        m_USBButtons.Button3 = JoystickValues.buttons.at(2);
    }
    if(m_USBButtons.Button4 != JoystickValues.buttons.at(3))
    {
        m_USBButtons.Button4 = JoystickValues.buttons.at(3);
    }
    if(m_USBButtons.Button5 != JoystickValues.buttons.at(4))
    {
        m_USBButtons.Button5 = JoystickValues.buttons.at(4);
    }
}

#endif
