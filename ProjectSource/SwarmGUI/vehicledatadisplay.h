#ifndef VEHICLEDATADISPLAY_H
#define VEHICLEDATADISPLAY_H

#include <QWidget>
#include <mavlink_common/ATTITUDE.h>
#include <mavlink_common/GPS_RAW_INT.h>
#include <mavlink_common/HEARTBEAT.h>
#include <mavlink_common/GLOBAL_POSITION_INT.h>
#include <mavlink_common/RC_CHANNELS_RAW.h>

#include "WidgetPFD.h"
#include "qfi_PFD.h"

#include "initialization.h"
#include "conversions.h"
#include "Definitions.h"

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

    void updateRCValues(const mavlink_common::RC_CHANNELS_RAW &RCValues);

    void updateHomeCoordinate(const EnumerationDefinitions::GPS_Params GPS_Method, const double value);

    StructureDefinitions::GPS_Params requestPosition();

public slots:

    void updateAttitude(const mavlink_common::ATTITUDE &VehicleAttitude);
    void updatePositioning(const mavlink_common::GLOBAL_POSITION_INT &VehiclePositionGPS);
    void updateFlightMode(const mavlink_common::HEARTBEAT &VehicleHeartbeat);
    void updateArmStatus(const bool &Armed);

signals:

    void desiredFlightMode(const int &VehicleID, const int &FlightMode);
    void requestStream(const int &VehicleID, const int &StreamType, const int &StreamRate);
    void radioCalibrate(const int &VehicleID, const int &StreamID, const bool &boolStream);
    void armRequest(const int &VehicleID, const bool &armValue);
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

private:
    Ui::VehicleDataDisplay *ui;

    StructureDefinitions::VehicleRCHL m_RCCalibration;
    StructureDefinitions::HomeDefinition m_HomeCoordinate;
    StructureDefinitions::VehicleStateV m_VehicleState;


    bool boolean_Calibration;

    int m_currentVehicleID;

    Conversions *m_Conversion;
    Initialization *m_Initialization;

};

#endif // VEHICLEDATADISPLAY_H
