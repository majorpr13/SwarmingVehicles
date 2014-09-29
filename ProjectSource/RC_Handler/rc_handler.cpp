#include "rc_handler.h"


RC_Handler::RC_Handler()
{
    store_USB.USB_TL = 0.0;
    store_USB.USB_TH = 0.0;
    store_USB.USB_RL = 0.0;
    store_USB.USB_RH = 0.0;
    store_USB.USB_PL = 0.0;
    store_USB.USB_PH = 0.0;
    store_USB.USB_YL = 0.0;
    store_USB.USB_YH = 0.0;


    store_RC.RC_TL = 0;
    store_RC.RC_TH = 0;
    store_RC.RC_TR = false;
    store_RC.RC_TO = false;

    store_RC.RC_RL = 0;
    store_RC.RC_RH = 0;
    store_RC.RC_RR = false;
    store_RC.RC_RO = false;

    store_RC.RC_PL = 0;
    store_RC.RC_PH = 0;
    store_RC.RC_PR = false;
    store_RC.RC_PO = false;

    store_RC.RC_PL = 0;
    store_RC.RC_PH = 0;
    store_RC.RC_PR = false;
    store_RC.RC_PO = false;
}

void RC_Handler::setJS_HL(const int_CalibValue &value)
{
    store_USB.USB_RL = value.calibRollL;
    store_USB.USB_RH = value.calibRollH;

    store_USB.USB_PL = value.calibPitchL;
    store_USB.USB_PH = value.calibPitchH;

    store_USB.USB_YL = value.calibYawL;
    store_USB.USB_YH = value.calibYawH;

    store_USB.USB_TL = value.calibThrottleL;
    store_USB.USB_TH = value.calibThrottleH;
}

void RC_Handler::setRC_HL(const int_CalibValue &value)
{
    store_RC.RC_RL = value.calibRollL;
    store_RC.RC_RH = value.calibRollH;

    store_USB.USB_PL = value.calibPitchL;
    store_RC.RC_PH = value.calibPitchH;

    store_RC.RC_YL = value.calibYawL;
    store_RC.RC_YH = value.calibYawH;

    store_RC.RC_TL = value.calibThrottleL;
    store_RC.RC_TH = value.calibThrottleH;
}

void RC_Handler::setbool_Override(const FlightChannel &channel, const bool value)
{
    switch(channel)
    {
    case (ROLL):
        store_RC.RC_RO = value;
        break;
    case (PITCH):
        store_RC.RC_PO = value;
        break;
    case (YAW):
        store_RC.RC_YO = value;
        break;
    case (THROTTLE):
        store_RC.RC_TO = value;
        break;
    default:
        break;
    }
}

void RC_Handler::setbool_Reverse(const FlightChannel &channel, const bool value)
{
    switch(channel)
    {
    case (ROLL):
        store_RC.RC_RR = value;
        break;
    case (PITCH):
        store_RC.RC_PR = value;
        break;
    case (YAW):
        store_RC.RC_YR = value;
        break;
    case (THROTTLE):
        store_RC.RC_TR = value;
        break;
    default:
        break;
    }
}

RC_Handler::cmd_Value RC_Handler::computeOverride(const RC_Handler::usb_Value &usbCommand)
{
    RC_Handler::cmd_Value overrideValue;

    int RC_Value = 0;
    double result = 0.0;

    //________________________________________ROLL OVERRIDE COMPUTATION________________________________
    if(store_RC.RC_RO == true)
    {
        result = (usbCommand.roll_value - store_USB.USB_RL) / (store_USB.USB_RH - store_USB.USB_RL);

        if(this->store_RC.RC_RR == false)
            result = ((double)(store_RC.RC_RH - store_RC.RC_RL) * result) + (double)store_RC.RC_RL;
        else
            result = (double)store_RC.RC_RH - ((double)(store_RC.RC_RH - store_RC.RC_RL) * result);

        result = result + 0.5; //This is performed so that the type cast to int rounds correctly
        RC_Value = (int)result;

        if(RC_Value > store_RC.RC_RH)
            RC_Value = store_RC.RC_RH;
        else if(RC_Value < store_RC.RC_RL)
            RC_Value = store_RC.RC_RL;
    }
    else
        RC_Value = 65535;

    overrideValue.roll_override = RC_Value;
    //________________________________________ROLL OVERRIDE COMPUTATION________________________________

    //________________________________________PITCH OVERRIDE COMPUTATION________________________________
    if(store_RC.RC_PO == true)
    {
        result = (usbCommand.pitch_value - store_USB.USB_PL) / (store_USB.USB_PH - store_USB.USB_PL);

        if(this->store_RC.RC_RR == false)
            result = ((double)(store_RC.RC_PH - store_RC.RC_PL) * result) + (double)store_RC.RC_PL;
        else
            result = (double)store_RC.RC_PH - ((double)(store_RC.RC_PH - store_RC.RC_PL) * result);

        result = result + 0.5; //This is performed so that the type cast to int rounds correctly
        RC_Value = (int)result;

        if(RC_Value > store_RC.RC_PH)
            RC_Value = store_RC.RC_PH;
        else if(RC_Value < store_RC.RC_PL)
            RC_Value = store_RC.RC_PL;
    }
    else
        RC_Value = 65535;

    overrideValue.pitch_override = RC_Value;
    //________________________________________PITCH OVERRIDE COMPUTATION________________________________

    //________________________________________YAW OVERRIDE COMPUTATION________________________________
    if(store_RC.RC_YO == true)
    {
        result = (usbCommand.yaw_value - store_USB.USB_YL) / (store_USB.USB_YH - store_USB.USB_YL);

        if(this->store_RC.RC_RR == false)
            result = ((double)(store_RC.RC_YH - store_RC.RC_YL) * result) + (double)store_RC.RC_YL;
        else
            result = (double)store_RC.RC_YH - ((double)(store_RC.RC_YH - store_RC.RC_YL) * result);

        result = result + 0.5; //This is performed so that the type cast to int rounds correctly
        RC_Value = (int)result;

        if(RC_Value > store_RC.RC_YH)
            RC_Value = store_RC.RC_YH;
        else if(RC_Value < store_RC.RC_YL)
            RC_Value = store_RC.RC_YL;
    }
    else
        RC_Value = 65535;

    overrideValue.yaw_override = RC_Value;
    //________________________________________YAW OVERRIDE COMPUTATION________________________________

    //________________________________________THROTTLE OVERRIDE COMPUTATION________________________________
    if(store_RC.RC_TO == true)
    {
        result = (usbCommand.throttle_value - store_USB.USB_TL) / (store_USB.USB_TH - store_USB.USB_TL);

        if(this->store_RC.RC_RR == false)
            result = ((double)(store_RC.RC_TH - store_RC.RC_TL) * result) + (double)store_RC.RC_TL;
        else
            result = (double)store_RC.RC_TH - ((double)(store_RC.RC_TH - store_RC.RC_TL) * result);

        result = result + 0.5; //This is performed so that the type cast to int rounds correctly
        RC_Value = (int)result;

        if(RC_Value > store_RC.RC_TH)
            RC_Value = store_RC.RC_TH;
        else if(RC_Value < store_RC.RC_TL)
            RC_Value = store_RC.RC_TL;
    }
    else
        RC_Value = 65535;

    overrideValue.throttle_override = RC_Value;
    //________________________________________THROTTLE OVERRIDE COMPUTATION________________________________

    return(overrideValue);
}

