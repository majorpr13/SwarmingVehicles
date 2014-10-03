#ifndef USBJOY_HANDLER_H
#define USBJOY_HANDLER_H

#include "USBJoy_Handler_global.h"
#include <sensor_msgs/Joy.h>
#include "rc_handler.h"

class USBJOY_HANDLERSHARED_EXPORT USBJoy_Handler {
public:
    struct struct_USBJoystick
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
public:
    USBJoy_Handler();

    void USBJoystickCalibration(const sensor_msgs::Joy &JoystickValues);

    RC_Handler::USBJoystick getUSBJoystickCalibration();

private:
    struct_USBJoystick m_joystickCalib;

    bool calibrationCalled;
};

#endif // USBJOY_HANDLER_H
