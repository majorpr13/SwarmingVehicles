#include "swarmcontroller_gui.h"
#include "ui_swarmcontroller_gui.h"


SwarmController_GUI::SwarmController_GUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SwarmController_GUI)
{
    ui->setupUi(this);

    initialization();

    m_MapVehicleWidgets.clear();
    m_MapVehicleRC.clear();

    m_HeartBeatTimer = new HeartBeatTimer();


    m_Conversions = new Conversions();
    m_cmdConversions = new cmdConversions();

    warningCounter = 0;


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
    ui->pushButton_ExportHome->setDisabled(true);
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

//SwarmController_GUI::SwarmController_GUI()
//{
//    //the empty constructor
//}

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
        m_HeartBeatTimer->addVehicle(VehicleID);

        VehicleDataDisplay *newWidget = new VehicleDataDisplay(ui->TabVehicleInfo);
        // If this is the first vehicle being added, delete the placeholder tab
        if(m_MapVehicleWidgets.isEmpty())
            ui->tabWidget_Vehicles->removeTab(0);

        ui->tabWidget_Vehicles->addTab(newWidget,QString::number(VehicleID));

        m_MapVehicleWidgets.insert(VehicleID,newWidget);
        m_MapVehicleWidgets[VehicleID]->addVehicle(VehicleID);

        ui->comboBox_VehicleHome->addItem(QString::number(VehicleID));

        StructureDefinitions::VehicleRCHL default_value;
        m_MapVehicleRC.insert(VehicleID,default_value);

        connect(m_MapVehicleWidgets[VehicleID],SIGNAL(requestRCParams(int)),this,SLOT(requestRCParams(int)));
        connect(m_MapVehicleWidgets[VehicleID],SIGNAL(requestWPParams(int)),this,SLOT(requestWPParams(int)));
        connect(m_MapVehicleWidgets[VehicleID],SIGNAL(transmitWPParams(int,QString,double)),m_ROSParser,SLOT(publishParamSet(int,QString,double)));

        connect(m_MapVehicleWidgets[VehicleID],SIGNAL(signalJoystickOverride(int,EnumerationDefinitions::FlightMethods,bool)),this,SLOT(updateRCOverrides(int,EnumerationDefinitions::FlightMethods,bool)));
        connect(m_MapVehicleWidgets[VehicleID],SIGNAL(signalJoystickReverse(int,EnumerationDefinitions::FlightMethods,bool)),this,SLOT(updateRCReverse(int,EnumerationDefinitions::FlightMethods,bool)));

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
    m_MapVehicleRC.remove(VehicleID);

    ui->comboBox_VehicleHome->removeItem(ui->comboBox_VehicleHome->findText(QString::number(VehicleID)));

    updateButtons();
}

void SwarmController_GUI::requestRCParams(const int &VehicleID)
{
    QList<QString> listRC = m_Conversions->parameterList_RC();
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

void SwarmController_GUI::updateRCOverrides(const int &VehicleID, const EnumerationDefinitions::FlightMethods &FlightMode, const bool &boolOverrride)
{
    StructureDefinitions::RCOverride override_command;

    if(FlightMode == EnumerationDefinitions::Roll)
    {
        m_MapVehicleRC[VehicleID].roll_or = boolOverrride;
        if(boolOverrride == false)
            override_command.roll_override = 0;
        else
            override_command.roll_override = 65535;
    }
    else if(FlightMode == EnumerationDefinitions::Pitch)
    {
        m_MapVehicleRC[VehicleID].pitch_or = boolOverrride;
        if(boolOverrride == false)
            override_command.pitch_override = 0;
        else
            override_command.pitch_override = 65535;
    }
    else if(FlightMode == EnumerationDefinitions::Yaw)
    {
        m_MapVehicleRC[VehicleID].yaw_or = boolOverrride;
        if(boolOverrride == false)
            override_command.yaw_override = 0;
        else
            override_command.yaw_override = 65535;
    }
    else if(FlightMode == EnumerationDefinitions::Throttle)
    {
        m_MapVehicleRC[VehicleID].throttle_or = boolOverrride;
        if(boolOverrride == false)
            override_command.throttle_override = 0;
        else
            override_command.throttle_override = 65535;
    }

#ifdef ROS_LIBS
    m_ROSParser->publishJoystickOverride(VehicleID , override_command);
#endif
}

void SwarmController_GUI::updateRCReverse(const int &VehicleID, const EnumerationDefinitions::FlightMethods &FlightMode, const bool &boolReverse)
{
    if(FlightMode == EnumerationDefinitions::Roll)
        m_MapVehicleRC[VehicleID].roll_reverse = boolReverse;
    else if(FlightMode == EnumerationDefinitions::Pitch)
        m_MapVehicleRC[VehicleID].pitch_reverse = boolReverse;
    else if(FlightMode == EnumerationDefinitions::Yaw)
        m_MapVehicleRC[VehicleID].yaw_reverse = boolReverse;
    else if(FlightMode == EnumerationDefinitions::Throttle)
        m_MapVehicleRC[VehicleID].throttle_reverse = boolReverse;

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
        QMapIterator<int, StructureDefinitions::VehicleRCHL> i(m_MapVehicleRC);
        bool sendOverride = false;
        while(i.hasNext())
        {
            i.next();
            StructureDefinitions::RCOverride override_command;
            m_ROSParser->publishJoystickOverride(i.key(),override_command);
        }
    }

#ifdef ROS_LIBS
    m_ROSParser->joystickMode(JoystickEnabled);
#endif
}

void SwarmController_GUI::on_pushButton_ImportHome_clicked()
{
    StructureDefinitions::GPS_Params HomePosition;
    QString string_VehicleID = ui->comboBox_VehicleHome->currentText();
    if(string_VehicleID != "ALL")
    {
        HomePosition = m_MapVehicleWidgets[string_VehicleID.toInt()]->requestPosition();

        ui->doubleSpinBox_LatHome->setValue(HomePosition.Lat);
        ui->doubleSpinBox_LonHome->setValue(HomePosition.Lon);
        ui->doubleSpinBox_AltHome->setValue(HomePosition.Alt);
    }
}

void SwarmController_GUI::on_pushButton_ExportHome_clicked()
{
    QVector<double> homePositionVector(7);

    int numVehicles = m_MapVehicleWidgets.size();
    double degreeSeperation = 360.0 / (double)numVehicles;
    double start = 0.0;
    double distance = ui->spinBox_LandingRadius->value();

    StructureDefinitions::GPS_Params swarmHome;
    StructureDefinitions::GPS_Params VehicleHome;
    swarmHome.Lat = ui->doubleSpinBox_LatHome->value();
    swarmHome.Lon = ui->doubleSpinBox_LonHome->value();
    swarmHome.Alt = ui->doubleSpinBox_AltHome->value();

    QString string_VehicleID = ui->comboBox_VehicleHome->currentText();
    if(string_VehicleID == "ALL")
    {
        QMapIterator<int, VehicleDataDisplay*> i(m_MapVehicleWidgets);
        while(i.hasNext())
        {
            i.next();
            VehicleHome = m_Conversions->FinalGPS(swarmHome,start,distance);
            m_MapVehicleWidgets[i.key()]->updateHomeCoordinate(VehicleHome);
            mavCommandStructures::mavCMD_setHome mavCmd;
            mavCmd.Latitude = VehicleHome.Lat;
            mavCmd.Longitude = VehicleHome.Lon;
            mavCmd.Altitude = VehicleHome.Alt;
            homePositionVector = m_cmdConversions->convert_setHome(mavCmd);
            m_ROSParser->publishMAVcommand(i.key(),mavCmdNum.setHome,0,homePositionVector);
            start = start + degreeSeperation;
        }
    }
    else
        m_MapVehicleWidgets[string_VehicleID.toInt()]->updateHomeCoordinate(swarmHome);
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
        QMapIterator<int, StructureDefinitions::VehicleRCHL> i(m_MapVehicleRC);
        bool sendOverride = false;
        while(i.hasNext())
        {
            i.next();
            StructureDefinitions::RCOverride override_command;
            if(i.value().roll_or== true)
            {
                double roll_percentage = m_Conversions->USBtoPercent(m_USBJoystickHL,EnumerationDefinitions::Roll,roll);
                override_command.roll_override = m_Conversions->PercenttoRC(i.value(),EnumerationDefinitions::Roll,roll_percentage);
                sendOverride = true;
            }
            else
                override_command.roll_override = 0;

            if(i.value().pitch_or == true)
            {
                double pitch_percentage = m_Conversions->USBtoPercent(m_USBJoystickHL,EnumerationDefinitions::Pitch,pitch);
                override_command.pitch_override = m_Conversions->PercenttoRC(i.value(),EnumerationDefinitions::Pitch,pitch_percentage);
                sendOverride = true;
            }
            else
                override_command.pitch_override = 0;

            if(i.value().yaw_or == true)
            {
                double yaw_percentage = m_Conversions->USBtoPercent(m_USBJoystickHL,EnumerationDefinitions::Yaw,yaw);
                override_command.yaw_override = m_Conversions->PercenttoRC(i.value(),EnumerationDefinitions::Yaw,yaw_percentage);
                sendOverride = true;
            }
            else
                override_command.yaw_override = 0;

            if(i.value().throttle_or == true)
            {
                double throttle_percentage = m_Conversions->USBtoPercent(m_USBJoystickHL,EnumerationDefinitions::Throttle,throttle);
                override_command.throttle_override = m_Conversions->PercenttoRC(i.value(),EnumerationDefinitions::Roll,throttle_percentage);
                sendOverride = true;
            }
            else
                override_command.throttle_override = 0;

            if(sendOverride == true)
                m_ROSParser->publishJoystickOverride(i.key() , override_command);

            m_MapVehicleWidgets[i.key()]->updateUSBOverride(override_command.roll_override,override_command.pitch_override,override_command.yaw_override,override_command.throttle_override);

        }
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
