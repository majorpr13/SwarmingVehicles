#ifndef RC_HANDLER_H
#define RC_HANDLER_H

#include <QList>
#include <QString>

#include "RC_Handler_global.h"

class RC_HANDLERSHARED_EXPORT RC_Handler {
public:

    enum FlightChannel
    {
        ROLL,
        PITCH,
        YAW,
        THROTTLE,
        ALL
    };

    enum Vehicle_Params{
        RC1_Min,
        RC1_Max,
        RC2_Min,
        RC2_Max,
        RC3_Min,
        RC3_Max,
        RC4_Min,
        RC4_Max,
        RC5_Min,
        RC5_Max,
        RC6_Min,
        RC6_Max,
        RC7_Min,
        RC7_Max,
        RC8_Min,
        RC8_Max,
        RC9_Min,
        RC9_Max,
        RC10_Min,
        RC10_Max,
        RC11_Min,
        RC11_Max,
        RC12_Min,
        RC12_Max,
        RC13_Min,
        RC13_Max,
        RC14_Min,
        RC14_Max,
        RC_Length
    };

    struct RCJoystick
    {
        int RC_TL;
        int RC_TH;
        bool RC_TR;
        bool RC_TO;

        int RC_RL;
        int RC_RH;
        bool RC_RR;
        bool RC_RO;

        int RC_PL;
        int RC_PH;
        bool RC_PR;
        bool RC_PO;

        int RC_YL;
        int RC_YH;
        bool RC_YR;
        bool RC_YO;
    };

    struct USBJoystick
    {
        double USB_TL;
        double USB_TH;
        double USB_RL;
        double USB_RH;
        double USB_PL;
        double USB_PH;
        double USB_YL;
        double USB_YH;
    };

    struct cmd_Value
    {
        cmd_Value() : roll_override(0),pitch_override(0),yaw_override(0),throttle_override(0){}
        int roll_override;
        int pitch_override;
        int yaw_override;
        int throttle_override;
    };

    struct usb_Value
    {
        usb_Value() : roll_value(0),pitch_value(0),yaw_value(0),throttle_value(0){}
        double roll_value;
        double pitch_value;
        double yaw_value;
        double throttle_value;
    };

    struct int_CalibValue
    {
        int calibRollH;
        int calibPitchH;
        int calibYawH;
        int calibThrottleH;

        int calibRollL;
        int calibPitchL;
        int calibYawL;
        int calibThrottleL;
    };

public:
    RC_Handler();

    bool overrideDesired;

    void setRC_HL(const int_CalibValue &value);
    void setJS_HL(const  USBJoystick &value);
    void setbool_Override(const FlightChannel &channel, const bool value);
    void setbool_Reverse(const FlightChannel &channel, const bool value);

    cmd_Value updateRCOverrides(const FlightChannel &FlightMode, const bool &boolOverrride);

    cmd_Value computeOverride(const usb_Value &usbCommand);

    QList<QString> parameterList_RC();
    QString RC_EnumtoString(const int &Parameter);
    Vehicle_Params RC_StringtoEnum(const QString &Parameter);

private:
    void checkOverride();

private:
    USBJoystick store_USB;
    RCJoystick store_RC;
};

#endif // RC_HANDLER_H
