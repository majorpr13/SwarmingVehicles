#ifndef VEHICLEDATADISPLAY_H
#define VEHICLEDATADISPLAY_H

#include <QWidget>

#include "WidgetPFD.h"
#include "qfi_PFD.h"

#include "initialization.h"
#include "conversions.h"
#include "Definitions.h"


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

    void updateHomeCoordinate(const StructureDefinitions::GPS_Params &homeValue);

    void updateVehicleType(const EnumerationDefinitions::Vehicle_Type &vehicleType);

    void USBcalibrationCompleted();

    void updateRCParam(const EnumerationDefinitions::Vehicle_Params &Parameter, const double value);

    void updateVehicleParams(const mavlink_common::PARAM_VALUE &parameter);

    StructureDefinitions::GPS_Params requestPosition();

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

    void requestRCConfiguration(const int &vehicleID);
    void signalJoystickOverride(const int &VehicleID, const EnumerationDefinitions::FlightMethods &FlightMode, const bool &boolOverride);
    void signalJoystickReverse(const int &VehicleID, const EnumerationDefinitions::FlightMethods &FlightMode, const bool &boolReverse);

private slots:

    void on_comboBox_DesiredFlightMode_activated(const QString &arg1);

    void on_pushButton_STREAM_clicked();

    void on_pushButton_Cal_released();

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

private:

    void checkRCParams();

    void updateOverrideCheckbox();

    void initialization();

    Ui::VehicleDataDisplay *ui;

    StructureDefinitions::VehicleRCHL m_RCCalibration;
    StructureDefinitions::HomeDefinition m_HomeCoordinate;
    StructureDefinitions::VehicleStateV m_VehicleState;


    bool boolUSBCalibraiton;
    bool boolRCCalibration;

    bool firstTimeLoad;

    int m_currentVehicleID;

    Conversions *m_Conversion;
    Initialization *m_Initialization;

};

#endif // VEHICLEDATADISPLAY_H
