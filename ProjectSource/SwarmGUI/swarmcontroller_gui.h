#ifndef SWARMCONTROLLER_GUI_H
#define SWARMCONTROLLER_GUI_H

#include <QMainWindow>
#include <QMap>
#include <QDateTime>
#include <QTimer>
#include <QMapIterator>

#include "cmdconversions.h"

#include "Definitions.h"
#include "heartbeattimer.h"
#include "vehicledatadisplay.h"


#include "usbjoy_handler.h"
#include "gps_position.h"
#include "rc_handler.h"
#include "command_helper.h"

#ifdef ROS_LIBS
#include "rosparse.h"
#endif

namespace Ui {
class SwarmController_GUI;
}

class SwarmController_GUI : public QMainWindow
{
    Q_OBJECT

public:

    SwarmController_GUI(QWidget *parent = 0);

    ~SwarmController_GUI();

public slots:

private slots:
    void on_addVehicleID_clicked();

    void on_removeVehicleID_clicked();

    void updateElapsedHearbeat(const int VehicleID, const int elapsedTime);

    void requestRCParams(const int &VehicleID);

    void updateRCOverrides(const int &VehicleID, const RC_Handler::FlightChannel &FlightChannel, const bool &boolOverride);

    void updateRCReverse(const int &VehicleID, const RC_Handler::FlightChannel &FlightChannel, const bool &boolReverse);

    void requestWPParams(const int &VehicleID);

    void on_pushButton_USBCalibrate_clicked();

    void on_pushButton_USBJOY_Enable_clicked();

    void on_pushButton_ImportHome_clicked();

    void on_pushButton_ExportHome_clicked();

#ifdef ROS_LIBS
    void updateVehicleAttitude(const mavlink_common::ATTITUDE &VehicleAttitude);
    void updateVehicleHeartbeat(const mavlink_common::HEARTBEAT &VehicleHeartbeat);
    void updateVehiclePositionRaw(const mavlink_common::GPS_RAW_INT &VehiclePosition);
    void updateVehiclePositionScaled(const mavlink_common::GLOBAL_POSITION_INT &VehiclePosition);
    void updateVehicleSysStatus(const mavlink_common::SYS_STATUS &VehicleSysStatus);
    void updateRadioValues(const mavlink_common::RC_CHANNELS_RAW &VehicleRCValues);
    void updateVehicleParams(const mavlink_common::PARAM_VALUE &VehicleParamValue);

    void USBJoystick(const sensor_msgs::Joy &JoystickValues);

#endif

private:
    void initialization();
    void updateButtons();
    void updateUSBButtons(const sensor_msgs::Joy &JoystickValues);

private:

    USBJoy_Handler *m_JoystickHandler;
    QMap<int, RC_Handler*> m_MapRC;

    Ui::SwarmController_GUI *ui;    
    HeartBeatTimer *m_HeartBeatTimer;
    HeartBeatTimer *m_GCSHeartbeat;

    Conversions *m_Conversions;
    Command_Helper *m_CommandHelper;

    mavCommandStructures::mavCMD_numberList *mavCmdNum;

    QMap<int, VehicleDataDisplay*> m_MapVehicleWidgets;

    QList<QString> listVehicles;

    StructureDefinitions::USB_Buttons m_USBButtons;

    bool JoystickCalibrate;
    bool JoystickEnabled;

#ifdef ROS_LIBS
    ROSParse *m_ROSParser;
#endif
};

#endif // SWARMCONTROLLER_GUI_H
