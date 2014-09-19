#ifndef VEHICLEDATADISPLAY_H
#define VEHICLEDATADISPLAY_H

#include <QWidget>
#include <mavlink_common/ATTITUDE.h>
#include <mavlink_common/GPS_RAW_INT.h>
#include <mavlink_common/HEARTBEAT.h>
#include <mavlink_common/GLOBAL_POSITION_INT.h>
#include "WidgetPFD.h"
#include "qfi_PFD.h"

#include "initialization.h"
#include "conversions.h"

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

public slots:

    void updateAttitude(const mavlink_common::ATTITUDE &VehicleAttitude);
    void updatePositioning(const mavlink_common::GLOBAL_POSITION_INT &VehiclePositionGPS);
    void updateFlightMode(const mavlink_common::HEARTBEAT &VehicleHeartbeat);
    void updateArmStatus(const bool &Armed);

signals:

    void desiredFlightMode(const int &VehicleID, const int &FlightMode);
    void requestStream(const int &VehicleID, const int &StreamType, const int &StreamRate);
    void radioCalibrate(const int &VehicleID, const int &StreamID, const bool &boolStream);

private slots:

    void on_comboBox_DesiredFlightMode_activated(const QString &arg1);

    void on_pushButton_STREAM_clicked();

    void on_pushButton_Cal_released();

private:
    Ui::VehicleDataDisplay *ui;

    bool boolean_Calibration;

    int m_currentVehicleID;

    Conversions *m_Conversion;
    Initialization *m_Initialization;


};

#endif // VEHICLEDATADISPLAY_H
