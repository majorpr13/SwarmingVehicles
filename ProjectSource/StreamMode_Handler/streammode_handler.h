#ifndef STREAMMODE_HANDLER_H
#define STREAMMODE_HANDLER_H

#include <QString>

#include "StreamMode_Handler_global.h"

class STREAMMODE_HANDLERSHARED_EXPORT StreamMode_Handler {
public:
    struct StreamModes
    {
         uint StreamAll;
         uint SRawSensors;
         uint SExtendedStatus;
         uint SRCChannels;
         uint SRawController;
         uint SPosition;
         uint SExtra1;
         uint SExtra2;
         uint SExtra3;
    };

    enum enum_StreamModes
    {
        StreamAll,
        SRawSensors,
        SExtendedStatus,
        SRCChannels,
        SRawController,
        SPosition,
        SExtra1,
        SExtra2,
        SExtra3
    };

public:
    StreamMode_Handler();

    QString StreamMode_EnumtoString(const int &StreamMode);
    int StreamMode_StringtoEnum(const QString &StreamMode);

    StreamModes m_StreamModes;
};

#endif // STREAMMODE_HANDLER_H
