#include "heartbeattimer.h"
#include <iostream>
HeartBeatTimer::HeartBeatTimer()
{
    m_Timer = new QTimer();
    m_Timer->setInterval(200);
    connect(m_Timer,SIGNAL(timeout()),this,SLOT(updateElapsedTime()));
    m_Timer->start();
}

void HeartBeatTimer::updateElapsedTime()
{
    QMapIterator<int,QTime*> i(m_HeartbeatMap);
    while(i.hasNext())
    {
        i.next();
        emit(elapsedUpdate(i.key(),m_HeartbeatMap[i.key()]->elapsed()));
    }
}

void HeartBeatTimer::addVehicle(const int &VehicleID)
{
    QTime *newTimer = new QTime;
    newTimer->start();
    m_HeartbeatMap.insert(VehicleID,newTimer);
}

void HeartBeatTimer::removeVehicle(const int &VehicleID)
{
    delete(m_HeartbeatMap[VehicleID]);
    m_HeartbeatMap.remove(VehicleID);
}

void HeartBeatTimer::restartTimer(const int &VehicleID)
{
    m_HeartbeatMap[VehicleID]->restart();
}

int HeartBeatTimer::timeElapsed(const int &VehicleID)
{
    int sinceLastBeat = m_HeartbeatMap[VehicleID]->elapsed();
    return sinceLastBeat;
}
