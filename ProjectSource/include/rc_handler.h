#ifndef RC_HANDLER_H
#define RC_HANDLER_H

#include "RC_Handler_global.h"

class RC_HANDLERSHARED_EXPORT RC_Handler {
public:

    enum FlightChannel
    {
        ROLL,
        PITCH,
        YAW,
        THROTTLE
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
        int roll_override;
        int pitch_override;
        int yaw_override;
        int throttle_override;
    };

    struct usb_Value
    {
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

    void setRC_HL(const int_CalibValue &value);
    void setJS_HL(const int_CalibValue &value);
    void setbool_Override(const FlightChannel &channel, const bool value);
    void setbool_Reverse(const FlightChannel &channel, const bool value);

    cmd_Value computeOverride(const usb_Value &usbCommand);
private:
    USBJoystick store_USB;
    RCJoystick store_RC;
};

#endif // RC_HANDLER_H
