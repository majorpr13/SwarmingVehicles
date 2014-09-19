#ifndef HEARTBEATTIMER_H
#define HEARTBEATTIMER_H

#include <QObject>
#include <QTime>
#include <QTimer>
#include <QMap>

class HeartBeatTimer : public QObject
{
    Q_OBJECT

public:
    explicit HeartBeatTimer();

    void addVehicle(const int &VehicleID);

    int timeElapsed(const int &VehicleID);

    void restartTimer(const int &VehicleID);

    void removeVehicle(const int &VehicleID);

signals:

    void elapsedUpdate(int VehicleID, int time);

private slots:
        void updateElapsedTime();

private:

    QMap<int,QTime*> m_HeartbeatMap;

    QTime *m_Time;

    QTimer *m_Timer;


};

#endif // HEARTBEATTIMER_H
