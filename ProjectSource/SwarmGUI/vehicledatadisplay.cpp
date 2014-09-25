#include "vehicledatadisplay.h"
#include "ui_vehicledatadisplay.h"
#include <stdio.h>
VehicleDataDisplay::VehicleDataDisplay(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VehicleDataDisplay)
{
    ui->setupUi(this);
    m_Conversion = new Conversions();
    m_Initialization = new Initialization();

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
    int DFM = m_Conversion->FlightMode_StringtoEnum(arg1);
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
    int streamTypeInt;
    QString streamString = ui->comboBox_StreamType->currentText();
    int streamRate = ui->spinBox_StreamRate->value();
    streamTypeInt = m_Conversion->StreamMode_StringtoEnum(streamString);
    emit(requestStream(m_currentVehicleID,streamTypeInt,streamRate));
}

void VehicleDataDisplay::on_pushButton_Cal_released()
{
    //boolean_Calibration = !boolean_Calibration;
    //emit(radioCalibrate(m_currentVehicleID , m_Initialization->m_StreamModeV.RCChannels , boolean_Calibration));
}


void VehicleDataDisplay::on_pushButton_ARM_clicked()
{
    emit(armRequest(m_currentVehicleID,true));
}

void VehicleDataDisplay::on_pushButton_DISARM_clicked()
{
    emit(armRequest(m_currentVehicleID,false));
}

void VehicleDataDisplay::updateHomeCoordinate(const StructureDefinitions::GPS_Params &homeValue)
{
        m_HomeCoordinate.HLatitude = homeValue.Lat;
        m_HomeCoordinate.HLongitude = homeValue.Lon;
        m_HomeCoordinate.HAltitude = homeValue.Alt;
}

void VehicleDataDisplay::on_checkBox_RollOverride_clicked(bool checked)
{
    emit(signalJoystickOverride(m_currentVehicleID,EnumerationDefinitions::Roll,checked));
}

void VehicleDataDisplay::on_checkBox_PitchOverride_clicked(bool checked)
{
    emit(signalJoystickOverride(m_currentVehicleID,EnumerationDefinitions::Pitch,checked));
}

void VehicleDataDisplay::on_checkBox_YawOverride_clicked(bool checked)
{
    emit(signalJoystickOverride(m_currentVehicleID,EnumerationDefinitions::Yaw,checked));
}

void VehicleDataDisplay::on_checkBox_ThrottleOverride_clicked(bool checked)
{
    emit(signalJoystickOverride(m_currentVehicleID,EnumerationDefinitions::Throttle,checked));
}

void VehicleDataDisplay::on_checkBox_RollRev_clicked(bool checked)
{
    emit(signalJoystickReverse(m_currentVehicleID,EnumerationDefinitions::Roll,checked));
}

void VehicleDataDisplay::on_checkBox_PitchRev_clicked(bool checked)
{
    emit(signalJoystickReverse(m_currentVehicleID,EnumerationDefinitions::Pitch,checked));
}

void VehicleDataDisplay::on_checkBox_YawRev_clicked(bool checked)
{
    emit(signalJoystickReverse(m_currentVehicleID,EnumerationDefinitions::Yaw,checked));
}

void VehicleDataDisplay::on_checkBox_ThrottleRev_clicked(bool checked)
{
    emit(signalJoystickReverse(m_currentVehicleID,EnumerationDefinitions::Throttle,checked));
}


StructureDefinitions::GPS_Params VehicleDataDisplay::requestPosition()
{
    StructureDefinitions::GPS_Params returnGPS;
    returnGPS.Lat = m_VehicleState.Cur_Lat;
    returnGPS.Lon = m_VehicleState.Cur_Lon;
    returnGPS.Alt = m_VehicleState.Cur_Altitude;
    return(returnGPS);
}

void VehicleDataDisplay::on_pushButton_RCRequestParameters_clicked()
{
    emit(requestRCConfiguration(m_currentVehicleID));
}

void VehicleDataDisplay::USBcalibrationCompleted()
{
    boolUSBCalibraiton = true;
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
    EnumerationDefinitions::Vehicle_Params VP = m_Conversion->VehicleParam_StringtoEnum(newString);
    if(VP < EnumerationDefinitions::RC_Length)
    {
        updateRCParam(VP,parameter.param_value);
    }
}

void VehicleDataDisplay::updateRCParam(const EnumerationDefinitions::Vehicle_Params &Parameter, const double value)
{
    switch(Parameter)
    {
    case(EnumerationDefinitions::RC1_Min):
        m_RCCalibration.roll_low = (int)value;
        ui->lineEdit_RollLow->setText(QString::number(m_RCCalibration.roll_low));
        break;
    case(EnumerationDefinitions::RC1_Max):
        m_RCCalibration.roll_high = (int)value;
        ui->lineEdit_RollHigh->setText(QString::number(m_RCCalibration.roll_high));
        break;
    case(EnumerationDefinitions::RC2_Min):
        m_RCCalibration.pitch_low = (int)value;
        ui->lineEdit_PitchLow->setText(QString::number(m_RCCalibration.pitch_low));
        break;
    case(EnumerationDefinitions::RC2_Max):
        m_RCCalibration.pitch_high = (int)value;
        ui->lineEdit_PitchHigh->setText(QString::number(m_RCCalibration.pitch_high));
        break;
    case(EnumerationDefinitions::RC3_Min):
        m_RCCalibration.throttle_low = (int)value;
        ui->lineEdit_ThrottleLow->setText(QString::number(m_RCCalibration.throttle_low));
        break;
    case(EnumerationDefinitions::RC3_Max):
        m_RCCalibration.throttle_high = (int)value;
        ui->lineEdit_ThrottleHigh->setText(QString::number(m_RCCalibration.throttle_high));
        break;
    case(EnumerationDefinitions::RC4_Min):
        m_RCCalibration.yaw_low = (int)value;
        ui->lineEdit_YawLow->setText(QString::number(m_RCCalibration.yaw_low));
        break;
    case(EnumerationDefinitions::RC4_Max):
        m_RCCalibration.yaw_high = (int)value;
        ui->lineEdit_YawHigh->setText(QString::number(m_RCCalibration.yaw_high));
        break;
    default:
        break;
    }


}

void VehicleDataDisplay::checkRCParams()
{
    if(m_RCCalibration.pitch_high != 0)
        if(m_RCCalibration.pitch_low != 0)
            if(m_RCCalibration.roll_high != 0)
                if(m_RCCalibration.roll_low != 0)
                    if(m_RCCalibration.throttle_high != 0)
                        if(m_RCCalibration.throttle_low != 0)
                            if(m_RCCalibration.yaw_high != 0)
                                if(m_RCCalibration.yaw_low != 0)
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
    StructureDefinitions::GPS_Params New;
    StructureDefinitions::GPS_Params Home;
    Home.Lat = m_HomeCoordinate.HLatitude;
    Home.Lon = m_HomeCoordinate.HLongitude;
    Home.Alt = m_HomeCoordinate.HAltitude;

    New.Lat = (double)VehiclePositionGPS.lat / GPSdivisor;
    New.Lon = (double)VehiclePositionGPS.lon / GPSdivisor;

    double distance = m_Conversion->DistanceGPS(Home,New);
    double bearing_degrees = m_Conversion->BearingGPS(Home,New);
    double bearing_radians = m_Conversion->DegreestoRadians(bearing_degrees);

    ui->lineEdit_CurrentX->setText(QString::number(distance * cos(bearing_radians)));
    ui->lineEdit_CurrentY->setText(QString::number(distance * sin(bearing_radians)));

    ui->lineEdit_relativeAlt->setText(QString::number(VehiclePositionGPS.relative_alt / 1000.0));
    m_VehicleState.Cur_Altitude = VehiclePositionGPS.relative_alt / 1000.0;

    ui->lineEdit_Latitude->setText(QString::number(New.Lat));
    m_VehicleState.Cur_Lat = VehiclePositionGPS.lat / GPSdivisor;

    ui->lineEdit_Longitude->setText(QString::number(New.Lon));
    m_VehicleState.Cur_Lon = VehiclePositionGPS.lon / GPSdivisor;

    ui->widget_MainFlightInstrument->setHeading(VehiclePositionGPS.hdg / 100.0);
}

void VehicleDataDisplay::updateFlightMode(const mavlink_common::HEARTBEAT &VehicleHeartbeat)
{
    if(VehicleHeartbeat.custom_mode != m_Conversion->FlightMode_StringtoEnum(ui->lineEdit_FlightMode->text()))
    {
        if(VehicleHeartbeat.custom_mode == m_Initialization->m_FlightModeV.Stabilize)
        {
            ui->lineEdit_FlightMode->setText("Stabilize");
        }
        else if(VehicleHeartbeat.custom_mode == m_Initialization->m_FlightModeV.Acro)
        {
            ui->lineEdit_FlightMode->setText("Acro");
        }
        else if(VehicleHeartbeat.custom_mode == m_Initialization->m_FlightModeV.AltHold)
        {
            ui->lineEdit_FlightMode->setText("AltHold");
        }
        else if(VehicleHeartbeat.custom_mode == m_Initialization->m_FlightModeV.Auto)
        {
            ui->lineEdit_FlightMode->setText("Auto");
        }
        else if(VehicleHeartbeat.custom_mode == m_Initialization->m_FlightModeV.Guided)
        {
            ui->lineEdit_FlightMode->setText("Guided");
        }
        else if(VehicleHeartbeat.custom_mode == m_Initialization->m_FlightModeV.Loiter)
        {
            ui->lineEdit_FlightMode->setText("Loiter");
        }
        else if(VehicleHeartbeat.custom_mode == m_Initialization->m_FlightModeV.RTL)
        {
            ui->lineEdit_FlightMode->setText("RTL");
        }
        else if(VehicleHeartbeat.custom_mode == m_Initialization->m_FlightModeV.CircleFM)
        {
            ui->lineEdit_FlightMode->setText("Circle");
        }
        else if(VehicleHeartbeat.custom_mode == m_Initialization->m_FlightModeV.Land)
        {
            ui->lineEdit_FlightMode->setText("Land");
        }
        else if(VehicleHeartbeat.custom_mode == m_Initialization->m_FlightModeV.Drift)
        {
            ui->lineEdit_FlightMode->setText("Drift");
        }
        else if(VehicleHeartbeat.custom_mode == m_Initialization->m_FlightModeV.Sport)
        {
            ui->lineEdit_FlightMode->setText("Sport");
        }
        ui->comboBox_DesiredFlightMode->setCurrentIndex(ui->comboBox_DesiredFlightMode->findText(ui->lineEdit_FlightMode->text()));
    }
}
#endif
