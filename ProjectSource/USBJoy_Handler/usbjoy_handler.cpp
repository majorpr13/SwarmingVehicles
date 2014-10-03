#include "usbjoy_handler.h"


USBJoy_Handler::USBJoy_Handler()
{
    m_joystickCalib.USB_PH = 0.0;
    m_joystickCalib.USB_PL = 0.0;

    m_joystickCalib.USB_RH = 0.0;
    m_joystickCalib.USB_RL = 0.0;

    m_joystickCalib.USB_YH = 0.0;
    m_joystickCalib.USB_YL = 0.0;

    m_joystickCalib.USB_TH = 0.0;
    m_joystickCalib.USB_TL = 0.0;

    calibrationCalled = false;

}

void USBJoy_Handler::USBJoystickCalibration(const sensor_msgs::Joy &JoystickValues)
{
    calibrationCalled = true;

    double roll = JoystickValues.axes.at(0);
    double pitch = JoystickValues.axes.at(1);
    double yaw = JoystickValues.axes.at(4);
    double throttle = JoystickValues.axes.at(2);

    if(roll < m_joystickCalib.USB_RL)
    {
        m_joystickCalib.USB_RL = roll;
    }
    else if(roll > m_joystickCalib.USB_RH)
    {
        m_joystickCalib.USB_RH = roll;
    }

    if(pitch < m_joystickCalib.USB_PL)
    {
        m_joystickCalib.USB_PL = pitch;
    }
    else if(pitch > m_joystickCalib.USB_PH)
    {
        m_joystickCalib.USB_PH = pitch;
    }

    if(yaw < m_joystickCalib.USB_YL)
    {
        m_joystickCalib.USB_YL = yaw;
    }
    else if(yaw > m_joystickCalib.USB_YH)
    {
        m_joystickCalib.USB_YH = yaw;
    }

    if(throttle < m_joystickCalib.USB_TL)
    {
        m_joystickCalib.USB_TL = throttle;
    }
    else if(throttle > m_joystickCalib.USB_TH)
    {
        m_joystickCalib.USB_TH = throttle;
    }
}

RC_Handler::USBJoystick USBJoy_Handler::getUSBJoystickCalibration()
{
    RC_Handler::USBJoystick returnJoystick;
    returnJoystick.USB_RH = m_joystickCalib.USB_RH;
    returnJoystick.USB_RL = m_joystickCalib.USB_RL;

    returnJoystick.USB_PH = m_joystickCalib.USB_PH;
    returnJoystick.USB_PL = m_joystickCalib.USB_PL;

    returnJoystick.USB_YH = m_joystickCalib.USB_YH;
    returnJoystick.USB_YL = m_joystickCalib.USB_YL;

    returnJoystick.USB_TH = m_joystickCalib.USB_TH;
    returnJoystick.USB_TL= m_joystickCalib.USB_TL;

    return(returnJoystick);
}
