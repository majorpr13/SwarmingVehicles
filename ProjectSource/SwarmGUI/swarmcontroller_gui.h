#ifndef SWARMCONTROLLER_GUI_H
#define SWARMCONTROLLER_GUI_H

#include <QMainWindow>
#include <QMap>
#include <QDateTime>
#include <QTimer>
#include <QMapIterator>

#include "Definitions.h"
#include "heartbeattimer.h"
#include "vehicledatadisplay.h"

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
    //SwarmController_GUI();

    ~SwarmController_GUI();

public slots:

private slots:
    void on_addVehicleID_clicked();

    void on_removeVehicleID_clicked();

    void updateElapsedHearbeat(const int VehicleID, const int elapsedTime);

    void radioCalibration(const int &VehicleID);

    void updateRCOverrides(const int &VehicleID, const EnumerationDefinitions::FlightMethods &FlightMode, const bool &boolOverrride);

    void updateRCReverse(const int &VehicleID, const EnumerationDefinitions::FlightMethods &FlightMode, const bool &boolReverse);

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
    void USBJoystick(const sensor_msgs::Joy &JoystickValues);
#endif

private:
    void initialization();
    void updateButtons();

private:

    QTimer *m_Timer;
    Ui::SwarmController_GUI *ui;    

    HeartBeatTimer *m_HeartBeatTimer;

    Conversions *m_Conversions;

    QMap<int, VehicleDataDisplay*> m_MapVehicleWidgets;
    QMap<int, StructureDefinitions::VehicleRCHL> m_MapVehicleRC;

    StructureDefinitions::JoystickHL m_USBJoystickHL;
    StructureDefinitions::HomeDefinition m_GlobalHome;

    bool JoystickCalibrate;
    bool JoystickEnabled;

    int warningCounter;

#ifdef ROS_LIBS
    ROSParse *m_ROSParser;
#endif
};

#endif // SWARMCONTROLLER_GUI_H
