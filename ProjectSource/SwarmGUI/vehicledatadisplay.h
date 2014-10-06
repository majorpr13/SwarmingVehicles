#ifndef VEHICLEDATADISPLAY_H
#define VEHICLEDATADISPLAY_H

#include <QWidget>

#include "WidgetPFD.h"
#include "qfi_PFD.h"

#include "cmdconversions.h"

#include "initialization.h"
#include "conversions.h"
#include "Definitions.h"

#include "rc_handler.h"
#include "gps_position.h"

#ifdef ROS_LIBS
#include <mavlink_common/ATTITUDE.h>
#include <mavlink_common/GPS_RAW_INT.h>
#include <mavlink_common/HEARTBEAT.h>
#include <mavlink_common/GLOBAL_POSITION_INT.h>
#include <mavlink_common/RC_CHANNELS_RAW.h>
#include <mavlink_common/PARAM_VALUE.h>
#endif

namespace Ui {
class VehicleDataDisplay;

}

class VehicleDataDisplay : public QWidget
{
    Q_OBJECT

public:
    explicit VehicleDataDisplay(QWidget *parent = 0);
    ~VehicleDataDisplay();

    void addVehicle(const int &VehicleID);

    void updateHomeCoordinate(const GPS_Position &homeValue);

    void updateVehicleType(const EnumerationDefinitions::Vehicle_Type &vehicleType);

    void USBcalibrationCompleted();

    void updateVehicleParams(const mavlink_common::PARAM_VALUE &parameter);

    void updateUSBOverride(const RC_Handler::cmd_Value &cmdValue);

    GPS_Position requestPosition();



#ifdef ROS_LIBS
    void updateRCValues(const mavlink_common::RC_CHANNELS_RAW &RCValues);
#endif

public slots:

    void updateArmStatus(const bool &Armed);

#ifdef ROS_LIBS
    void updateAttitude(const mavlink_common::ATTITUDE &VehicleAttitude);
    void updatePositioning(const mavlink_common::GLOBAL_POSITION_INT &VehiclePositionGPS);
    void updateFlightMode(const mavlink_common::HEARTBEAT &VehicleHeartbeat);
#endif

signals:

    void desiredFlightMode(const int &VehicleID, const int &FlightMode);
    void requestStream(const int &VehicleID, const int &StreamMessage, const int &StreamRate);
    void armRequest(const int &VehicleID, const bool &armValue);

    void requestRCParams(const int &vehicleID);
    void requestWPParams(const int &vehicleID);
    void transmitWPParams(const int &VehicleID, const QString &msgString, const double &value);

    void signalJoystickOverride(const int &VehicleID, const RC_Handler::FlightChannel &FlightChannel, const bool &boolOverride);
    void signalJoystickReverse(const int &VehicleID, const RC_Handler::FlightChannel &FlightChannel, const bool &boolReverse);

private slots:

    void on_comboBox_DesiredFlightMode_activated(const QString &arg1);

    void on_pushButton_STREAM_clicked();

    void on_pushButton_ARM_clicked();

    void on_pushButton_DISARM_clicked();

    void on_checkBox_RollOverride_clicked(bool checked);

    void on_checkBox_PitchOverride_clicked(bool checked);

    void on_checkBox_YawOverride_clicked(bool checked);

    void on_checkBox_ThrottleOverride_clicked(bool checked);

    void on_checkBox_RollRev_clicked(bool checked);

    void on_checkBox_PitchRev_clicked(bool checked);

    void on_checkBox_YawRev_clicked(bool checked);

    void on_checkBox_ThrottleRev_clicked(bool checked);

    void on_pushButton_RCRequestParameters_clicked();

    void on_pushButton_reqWPParams_clicked();

    void on_pushButton_trWPParams_clicked();

    void on_pushButton_DisableOverride_clicked();

private:

    void updateRCParam(const RC_Handler::Vehicle_Params &Parameter, const double value);

    void updateWPParam(const EnumerationDefinitions::Vehicle_Params &Parameter, const double value);

    void updateOverrideCheckbox();

    void checkRCParams();

    void initialization();

    Ui::VehicleDataDisplay *ui;

    RC_Handler::RCJoystick m_RCCalibration;

    GPS_Position m_HomeCoordinate;

    StructureDefinitions::VehicleStateV m_VehicleState;


    bool boolUSBCalibraiton;
    bool boolRCCalibration;

    bool firstTimeLoad;

    int m_currentVehicleID;

    Conversions *m_Conversion;
    Initialization *m_Initialization;

};

#endif // VEHICLEDATADISPLAY_H
