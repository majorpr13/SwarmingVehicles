#include "vehicledatadisplay.h"
#include "ui_vehicledatadisplay.h"
#include <stdio.h>
VehicleDataDisplay::VehicleDataDisplay(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VehicleDataDisplay)
{
    ui->setupUi(this);
    m_Conversion = new Conversions();

    boolUSBCalibraiton = false;
    boolRCCalibration = false;
    firstTimeLoad = true;

    ui->checkBox_RollOverride->setDisabled(true);
    ui->checkBox_PitchOverride->setDisabled(true);
    ui->checkBox_YawOverride->setDisabled(true);
    ui->checkBox_ThrottleOverride->setDisabled(true);

    initialization();
}

VehicleDataDisplay::~VehicleDataDisplay()
{
    delete ui;
}

void VehicleDataDisplay::initialization()
{

}

void VehicleDataDisplay::addVehicle(const int &VehicleID)
{
    m_currentVehicleID = VehicleID;
}

void VehicleDataDisplay::updateVehicleType(const EnumerationDefinitions::Vehicle_Type &vehicleType)
{
    if(firstTimeLoad == true)
    {
        firstTimeLoad = false;
    }
}

void VehicleDataDisplay::on_comboBox_DesiredFlightMode_activated(const QString &arg1)
{
    int DFM = m_FlightModes.FlightMode_StringtoEnum(arg1);
    emit(desiredFlightMode(m_currentVehicleID,DFM));
}

void VehicleDataDisplay::updateArmStatus(const bool &Armed)
{
    if(Armed == true)
    {
        ui->pushButton_ARM->setDisabled(true);
        ui->pushButton_DISARM->setDisabled(false);
    }
    else
    {
        ui->pushButton_ARM->setDisabled(false);
        ui->pushButton_DISARM->setDisabled(true);
    }
}


void VehicleDataDisplay::on_pushButton_STREAM_clicked()
{
//    int streamTypeInt;
//    QString streamString = ui->comboBox_StreamType->currentText();
//    int streamRate = ui->spinBox_StreamRate->value();
//    streamTypeInt = m_Conversion->StreamMode_StringtoEnum(streamString);
//    emit(requestStream(m_currentVehicleID,streamTypeInt,streamRate));
}

void VehicleDataDisplay::on_pushButton_ARM_clicked()
{
    emit(armRequest(m_currentVehicleID,true));
}

void VehicleDataDisplay::on_pushButton_DISARM_clicked()
{
    emit(armRequest(m_currentVehicleID,false));
}

void VehicleDataDisplay::updateHomeCoordinate(const GPS_Position &homeValue)
{
        m_HomeCoordinate.Latitude = homeValue.Latitude;
        m_HomeCoordinate.Longitude = homeValue.Longitude;
        m_HomeCoordinate.Altitude = homeValue.Altitude;
}

void VehicleDataDisplay::on_checkBox_RollOverride_clicked(bool checked)
{
    emit(signalJoystickOverride(m_currentVehicleID,RC_Handler::ROLL,checked));
}

void VehicleDataDisplay::on_checkBox_PitchOverride_clicked(bool checked)
{
    emit(signalJoystickOverride(m_currentVehicleID,RC_Handler::PITCH,checked));
}

void VehicleDataDisplay::on_checkBox_YawOverride_clicked(bool checked)
{
    emit(signalJoystickOverride(m_currentVehicleID,RC_Handler::YAW,checked));
}

void VehicleDataDisplay::on_checkBox_ThrottleOverride_clicked(bool checked)
{
    emit(signalJoystickOverride(m_currentVehicleID,RC_Handler::THROTTLE,checked));
}

void VehicleDataDisplay::on_checkBox_RollRev_clicked(bool checked)
{
    emit(signalJoystickReverse(m_currentVehicleID,RC_Handler::ROLL,checked));
}

void VehicleDataDisplay::on_checkBox_PitchRev_clicked(bool checked)
{
    emit(signalJoystickReverse(m_currentVehicleID,RC_Handler::PITCH,checked));
}

void VehicleDataDisplay::on_checkBox_YawRev_clicked(bool checked)
{
    emit(signalJoystickReverse(m_currentVehicleID,RC_Handler::YAW,checked));
}

void VehicleDataDisplay::on_checkBox_ThrottleRev_clicked(bool checked)
{
    emit(signalJoystickReverse(m_currentVehicleID,RC_Handler::THROTTLE,checked));
}


GPS_Position VehicleDataDisplay::requestPosition()
{
    GPS_Position returnGPS;
    returnGPS.Latitude = m_VehicleState.Cur_Lat;
    returnGPS.Longitude = m_VehicleState.Cur_Lon;
    returnGPS.Altitude = m_VehicleState.Cur_Altitude;
    return(returnGPS);
}

void VehicleDataDisplay::on_pushButton_RCRequestParameters_clicked()
{
    emit(requestRCParams(m_currentVehicleID));
}

void VehicleDataDisplay::USBcalibrationCompleted()
{
    boolUSBCalibraiton = true;
    updateOverrideCheckbox();
}

void VehicleDataDisplay::updateOverrideCheckbox()
{
    if((boolUSBCalibraiton == true) && (boolRCCalibration == true))
    {
        ui->checkBox_RollOverride->setDisabled(false);
        ui->checkBox_PitchOverride->setDisabled(false);
        ui->checkBox_YawOverride->setDisabled(false);
        ui->checkBox_ThrottleOverride->setDisabled(false);
    }
}

void VehicleDataDisplay::updateVehicleParams(const mavlink_common::PARAM_VALUE &parameter)
{
    QByteArray ba;
    for(uint i = 0; i < parameter.param_id.size(); i++)
    {
        ba[i] = parameter.param_id.at(i);
    }
    QString newString(ba);
    RC_Handler::Vehicle_Params VP = m_RCHandler.RC_StringtoEnum(newString);

    if(VP != RC_Handler::RC_Length)
    {
        updateRCParam(VP,parameter.param_value);
    }
    //if RC_Length was returned this means it was not one of the RC parameters lets continue to check
//    else if((VP > EnumerationDefinitions::RC_Length) && (VP< EnumerationDefinitions::WP_Length))
//    {
//        updateWPParam(VP,parameter.param_value);
//    }
}

void VehicleDataDisplay::updateWPParam(const EnumerationDefinitions::Vehicle_Params &Parameter, const double value)
{
    switch(Parameter)
    {
    case(EnumerationDefinitions::WPNAV_ACCEL):
        break;
    case(EnumerationDefinitions::WPNAV_ACCEL_Z):
        break;
    case(EnumerationDefinitions::WPNAV_LOIT_JERK):
        break;
    case(EnumerationDefinitions::WPNAV_LOIT_SPEED):
        break;
    case(EnumerationDefinitions::WPNAV_RADIUS):
        ui->spinBox_WPRadius->setValue(value);
        break;
    case(EnumerationDefinitions::WPNAV_SPEED):
        ui->spinBox_WPSpeed->setValue(value);
        break;
    case(EnumerationDefinitions::WPNAV_SPEED_DN):
        ui->spinBox_WPDescent->setValue(value);
        break;
    case(EnumerationDefinitions::WPNAV_SPEED_UP):
        ui->spinBox_WPAscent->setValue(value);
        break;
    default:
        break;

    }
}

void VehicleDataDisplay::updateRCParam(const RC_Handler::Vehicle_Params &Parameter, const double value)
{
    switch(Parameter)
    {
    case(RC_Handler::RC1_Min):
        m_RCCalibration.RC_RL = (int)value;
        ui->lineEdit_RollLow->setText(QString::number(m_RCCalibration.RC_RL));
        break;
    case(RC_Handler::RC1_Max):
        m_RCCalibration.RC_RH = (int)value;
        ui->lineEdit_RollHigh->setText(QString::number(m_RCCalibration.RC_RH));
        break;
    case(RC_Handler::RC2_Min):
        m_RCCalibration.RC_PL = (int)value;
        ui->lineEdit_PitchLow->setText(QString::number(m_RCCalibration.RC_PL));
        break;
    case(RC_Handler::RC2_Max):
        m_RCCalibration.RC_PH = (int)value;
        ui->lineEdit_PitchHigh->setText(QString::number(m_RCCalibration.RC_PH));
        break;
    case(RC_Handler::RC3_Min):
        m_RCCalibration.RC_TL = (int)value;
        ui->lineEdit_ThrottleLow->setText(QString::number(m_RCCalibration.RC_TL));
        break;
    case(RC_Handler::RC3_Max):
        m_RCCalibration.RC_TH = (int)value;
        ui->lineEdit_ThrottleHigh->setText(QString::number(m_RCCalibration.RC_TH));
        break;
    case(RC_Handler::RC4_Min):
        m_RCCalibration.RC_YL = (int)value;
        ui->lineEdit_YawLow->setText(QString::number(m_RCCalibration.RC_YL));
        break;
    case(RC_Handler::RC4_Max):
        m_RCCalibration.RC_YH = (int)value;
        ui->lineEdit_YawHigh->setText(QString::number(m_RCCalibration.RC_YH));
        break;
    default:
        break;
    }

    checkRCParams();

}

void VehicleDataDisplay::checkRCParams()
{
    if(m_RCCalibration.RC_PH != 0)
        if(m_RCCalibration.RC_PL != 0)
            if(m_RCCalibration.RC_RH != 0)
                if(m_RCCalibration.RC_RL != 0)
                    if(m_RCCalibration.RC_TH != 0)
                        if(m_RCCalibration.RC_TL != 0)
                            if(m_RCCalibration.RC_YH != 0)
                                if(m_RCCalibration.RC_YL != 0)
                                {
                                    boolRCCalibration = true;
                                    updateOverrideCheckbox();
                                }
    else
                                    return;


}


#ifdef ROS_LIBS
void VehicleDataDisplay::updateRCValues(const mavlink_common::RC_CHANNELS_RAW &RCValues)
{
    ui->lineEdit_PitchCurrent->setText(QString::number(RCValues.chan2_raw));
    ui->lineEdit_RollCurrent->setText(QString::number(RCValues.chan1_raw));
    ui->lineEdit_ThrottleCurrent->setText(QString::number(RCValues.chan3_raw));
    ui->lineEdit_YawCurrent->setText(QString::number(RCValues.chan4_raw));
}


void VehicleDataDisplay::updateAttitude(const mavlink_common::ATTITUDE &VehicleAttitude)
{
    ui->widget_MainFlightInstrument->setRoll(VehicleAttitude.roll * (180.0/3.14159265));
    m_VehicleState.roll = VehicleAttitude.roll;
    m_VehicleState.rollrate = VehicleAttitude.rollspeed;

    ui->widget_MainFlightInstrument->setPitch(VehicleAttitude.pitch * (180.0/3.14159265));
    m_VehicleState.pitch = VehicleAttitude.pitch;
    m_VehicleState.pitchrate = VehicleAttitude.pitchspeed;

    ui->widget_MainFlightInstrument->update();
}

void VehicleDataDisplay::updatePositioning(const mavlink_common::GLOBAL_POSITION_INT &VehiclePositionGPS)
{
    double GPSdivisor = 10000000.00000;

    GPS_Position positionUpdate;
//    StructureDefinitions::GPS_Params Home;

//    Home.Lat = m_HomeCoordinate.HLatitude;
//    Home.Lon = m_HomeCoordinate.HLongitude;
//    Home.Alt = m_HomeCoordinate.HAltitude;

    positionUpdate.Latitude = (double)VehiclePositionGPS.lat / GPSdivisor;
    positionUpdate.Longitude = (double)VehiclePositionGPS.lon / GPSdivisor;

    double distance = m_HomeCoordinate.Distance(positionUpdate);
    double bearing_degrees = m_HomeCoordinate.Bearing(positionUpdate);
    double bearing_radians = bearing_degrees * (3.14 / 180.0);

    ui->lineEdit_CurrentX->setText(QString::number(distance * cos(bearing_radians)));
    ui->lineEdit_CurrentY->setText(QString::number(distance * sin(bearing_radians)));

    ui->lineEdit_relativeAlt->setText(QString::number(VehiclePositionGPS.relative_alt / 1000.0));
    m_VehicleState.Cur_Altitude = VehiclePositionGPS.relative_alt / 1000.0;
    ui->widget_MainFlightInstrument->setAltitude(m_VehicleState.Cur_Altitude);

    ui->lineEdit_Latitude->setText(QString::number(positionUpdate.Latitude));
    m_VehicleState.Cur_Lat = positionUpdate.Latitude;

    ui->lineEdit_Longitude->setText(QString::number(positionUpdate.Longitude));
    m_VehicleState.Cur_Lon = positionUpdate.Longitude;

    ui->widget_MainFlightInstrument->setHeading(VehiclePositionGPS.hdg / 100.0);

    ui->widget_MainFlightInstrument->update();
}

void VehicleDataDisplay::updateFlightMode(const mavlink_common::HEARTBEAT &VehicleHeartbeat)
{
    if(VehicleHeartbeat.custom_mode != m_FlightModes.FlightMode_StringtoEnum(ui->lineEdit_FlightMode->text()))
    {
        QString setString = m_FlightModes.FlightMode_EnumtoString(VehicleHeartbeat.custom_mode);
        ui->lineEdit_FlightMode->setText(setString);
        ui->comboBox_DesiredFlightMode->setCurrentIndex(ui->comboBox_DesiredFlightMode->findText(ui->lineEdit_FlightMode->text()));
    }
}
#endif

void VehicleDataDisplay::on_pushButton_reqWPParams_clicked()
{
    emit(requestWPParams(m_currentVehicleID));
}

void VehicleDataDisplay::updateUSBOverride(const RC_Handler::cmd_Value &cmdValue)
{
    ui->lineEdit_RollOR->setText(QString::number(cmdValue.roll_override));
    ui->lineEdit_PitchOR->setText(QString::number(cmdValue.pitch_override));
    ui->lineEdit_YawOR->setText(QString::number(cmdValue.yaw_override));
    ui->lineEdit_ThrottleOR->setText(QString::number(cmdValue.throttle_override));

}

void VehicleDataDisplay::on_pushButton_trWPParams_clicked()
{
//    double value = 0.0;
//    QString msgString = "";

//    value = ui->spinBox_WPSpeed->value();
//    msgString = m_Conversion->VehicleParam_EnumtoString(EnumerationDefinitions::WPNAV_SPEED);
//    emit(transmitWPParams(m_currentVehicleID,msgString,value));

//    value = ui->spinBox_WPRadius->value();
//    msgString = m_Conversion->VehicleParam_EnumtoString(EnumerationDefinitions::WPNAV_RADIUS);
//    emit(transmitWPParams(m_currentVehicleID,msgString,value));

//    value = ui->spinBox_WPAscent->value();
//    msgString = m_Conversion->VehicleParam_EnumtoString(EnumerationDefinitions::WPNAV_SPEED_UP);
//    emit(transmitWPParams(m_currentVehicleID,msgString,value));

//    value = ui->spinBox_WPDescent->value();
//    msgString = m_Conversion->VehicleParam_EnumtoString(EnumerationDefinitions::WPNAV_SPEED_DN);
//    emit(transmitWPParams(m_currentVehicleID,msgString,value));
}

void VehicleDataDisplay::on_pushButton_DisableOverride_clicked()
{

    ui->checkBox_RollOverride->setChecked(false);
    ui->checkBox_PitchOverride->setChecked(false);
    ui->checkBox_YawOverride->setChecked(false);
    ui->checkBox_ThrottleOverride->setChecked(false);

    emit(signalJoystickOverride(m_currentVehicleID,RC_Handler::ROLL,false));
    emit(signalJoystickOverride(m_currentVehicleID,RC_Handler::PITCH,false));
    emit(signalJoystickOverride(m_currentVehicleID,RC_Handler::YAW,false));
    emit(signalJoystickOverride(m_currentVehicleID,RC_Handler::THROTTLE,false));
}
