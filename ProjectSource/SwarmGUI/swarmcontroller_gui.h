#ifndef SWARMCONTROLLER_GUI_H
#define SWARMCONTROLLER_GUI_H

#include <QMainWindow>
#include <QMap>
#include <QDateTime>
#include <QTimer>

#include "Definitions.h"
#include "heartbeattimer.h"
#include "vehicledatadisplay.h"
#include "rosparse.h"

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

    void updateVehicleAttitude(const mavlink_common::ATTITUDE &VehicleAttitude);

    void updateVehicleHeartbeat(const mavlink_common::HEARTBEAT &VehicleHeartbeat);

    void updateVehiclePositionRaw(const mavlink_common::GPS_RAW_INT &VehiclePosition);

    void updateVehiclePositionScaled(const mavlink_common::GLOBAL_POSITION_INT &VehiclePosition);

    void updateVehicleSysStatus(const mavlink_common::SYS_STATUS &VehicleSysStatus);

    void updateElapsedHearbeat(const int VehicleID, const int elapsedTime);

    void updateWarningString(const QString &warningString);

    void updateStreamRequest(const int &VehicleID, const int &StreamType, const int &StreamRate);

    void updateDesiredFlightMode(const int &VehicleID, const int &DesiredFlightMode);

    void radioCalibration(const int &VehicleID, const int &MessageStream, const bool &boolStream);

    void updateRadioValues(const mavlink_common::RC_CHANNELS_RAW &VehicleRCValues);

    void armRequest(const int &VehicleID, const bool &armValue);


private:
    QTimer *m_Timer;
    Ui::SwarmController_GUI *ui;

    ROSParse *m_ROSParser;

    HeartBeatTimer *m_HeartBeatTimer;

    QMap<int, VehicleDataDisplay*> m_MapVehicleWidgets;
    QMap<int, StructureDefinitions::VehicleRCHL> m_MapVehicleRC;

    int warningCounter;

    double roll_counter;

    double pitch_counter;
};

#endif // SWARMCONTROLLER_GUI_H
