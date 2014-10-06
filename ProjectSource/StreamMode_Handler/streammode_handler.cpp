#include "streammode_handler.h"


StreamMode_Handler::StreamMode_Handler()
{    
        m_StreamModes.StreamAll = 0;
        m_StreamModes.SRawSensors = 1;
        m_StreamModes.SExtendedStatus = 2;
        m_StreamModes.SRCChannels = 3;
        m_StreamModes.SRawController = 4;
        m_StreamModes.SPosition = 6;
        m_StreamModes.SExtra1 = 10;
        m_StreamModes.SExtra2 = 11;
        m_StreamModes.SExtra3 = 12;
}


int StreamMode_Handler::StreamMode_StringtoEnum(const QString &StreamMode)
{
    if(StreamMode == "Stream All")
        return m_StreamModes.StreamAll;
    else if(StreamMode == "Raw Sensors")
        return m_StreamModes.SRawSensors;
    else if(StreamMode == "Extended Status")
        return m_StreamModes.SExtendedStatus;
    else if(StreamMode == "RC Channels")
        return m_StreamModes.SRCChannels;
    else if(StreamMode == "Raw Controller")
        return m_StreamModes.SRawController;
    else if(StreamMode == "Position")
        return m_StreamModes.SPosition;
    else if(StreamMode == "Extra 1")
        return m_StreamModes.SExtra1;
    else if(StreamMode == "Extra 2")
        return m_StreamModes.SExtra2;
    else if(StreamMode == "Extra 3")
        return m_StreamModes.SExtra3;
    else
        return -1;
}

QString StreamMode_Handler::StreamMode_EnumtoString(const int &StreamMode)
{
    if(StreamMode == m_StreamModes.StreamAll)
        return "Stream All";
    else if(StreamMode == m_StreamModes.SRawSensors)
        return "Raw Sensors";
    else if(StreamMode == m_StreamModes.SExtendedStatus)
        return "Extended Status";
    else if(StreamMode == m_StreamModes.SRCChannels)
        return "RC Channels";
    else if(StreamMode == m_StreamModes.SRawController)
        return "Raw Controller";
    else if(StreamMode == m_StreamModes.SPosition)
        return "Position";
    else if(StreamMode == m_StreamModes.SExtra1)
        return "Extra 1";
    else if(StreamMode == m_StreamModes.SExtra2)
        return "Extra 2";
    else if(StreamMode == m_StreamModes.SExtra3)
        return "Extra 3";
    else
        return "";
}
