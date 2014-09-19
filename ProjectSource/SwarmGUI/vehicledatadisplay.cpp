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
    boolean_Calibration = false;
}

VehicleDataDisplay::~VehicleDataDisplay()
{
    delete ui;
}

void VehicleDataDisplay::addVehicle(const int &VehicleID)
{
    m_currentVehicleID = VehicleID;
}

void VehicleDataDisplay::updateAttitude(const mavlink_common::ATTITUDE &VehicleAttitude)
{
    ui->widget_MainFlightInstrument->setRoll(VehicleAttitude.roll * (180.0/3.14159265));
    ui->widget_MainFlightInstrument->setPitch(VehicleAttitude.pitch * (180.0/3.14159265));
    ui->widget_MainFlightInstrument->update();
}

void VehicleDataDisplay::updatePositioning(const mavlink_common::GLOBAL_POSITION_INT &VehiclePositionGPS)
{
    double GPSdivisor = 10000000.0;
    ui->lcdNumber_Alt->display(VehiclePositionGPS.alt / 1000.0);
    ui->lcdNumber_Lat->display(VehiclePositionGPS.lat / GPSdivisor);
    ui->lcdNumber_Lon->display(VehiclePositionGPS.lon / GPSdivisor);
    ui->widget_MainFlightInstrument->setHeading(VehiclePositionGPS.hdg / 100.0);
}

void VehicleDataDisplay::updateFlightMode(const mavlink_common::HEARTBEAT &VehicleHeartbeat)
{
    if(VehicleHeartbeat.custom_mode != m_Conversion->FlightMode_StringtoEnum(ui->lineEdit_FlightMode->text()))
    {
        ui->comboBox_DesiredFlightMode->setCurrentIndex(ui->comboBox_DesiredFlightMode->findText(ui->lineEdit_FlightMode->text()));

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
    }
}


void VehicleDataDisplay::on_comboBox_DesiredFlightMode_activated(const QString &arg1)
{
    int DFM = m_Conversion->FlightMode_StringtoEnum(arg1);
    std::cout<<"The new desired flight mode has fired."<<std::endl;
    //emit(desiredFlightMode(m_currentVehicleID,DFM));
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
    boolean_Calibration = !boolean_Calibration;
    emit(radioCalibrate(m_currentVehicleID , m_Initialization->m_StreamModeV.RCChannels , boolean_Calibration));
}
