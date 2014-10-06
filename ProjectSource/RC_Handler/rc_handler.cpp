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

    overrideDesired = false;
}

void RC_Handler::checkOverride()
{
    if(store_RC.RC_PO == true)
        if(store_RC.RC_RO == true)
            if(store_RC.RC_YO == true)
                if(store_RC.RC_TO == true)
                    overrideDesired == true;
    else
                    overrideDesired == false;
}

void RC_Handler::setJS_HL(const USBJoystick &value)
{
    store_USB.USB_RL = value.USB_RL;
    store_USB.USB_RH = value.USB_RH;

    store_USB.USB_PL = value.USB_PL;
    store_USB.USB_PH = value.USB_PH;

    store_USB.USB_YL = value.USB_YL;
    store_USB.USB_YH = value.USB_YH;

    store_USB.USB_TL = value.USB_TL;
    store_USB.USB_TH = value.USB_TH;
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
    case (ALL):
        store_RC.RC_RO = value;
        store_RC.RC_PO = value;
        store_RC.RC_YO = value;
        store_RC.RC_TO = value;
        break;
    default:
        break;
    }

    checkOverride();
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

RC_Handler::cmd_Value RC_Handler::updateRCOverrides(const RC_Handler::FlightChannel &FlightMode, const bool &boolOverrride)
{
    RC_Handler::cmd_Value override_command;

    override_command.roll_override = 65535;
    override_command.pitch_override = 65535;
    override_command.yaw_override = 65535;
    override_command.throttle_override = 65535;

    if(FlightMode == RC_Handler::ROLL)
    {
        store_RC.RC_RO = boolOverrride;
        if(boolOverrride == false)
            override_command.roll_override = 0;
    }
    else if(FlightMode == RC_Handler::PITCH)
    {
       store_RC.RC_PO = boolOverrride;
        if(boolOverrride == false)
            override_command.pitch_override = 0;
    }
    else if(FlightMode == RC_Handler::YAW)
    {
        store_RC.RC_YO = boolOverrride;
        if(boolOverrride == false)
            override_command.yaw_override = 0;
    }
    else if(FlightMode == RC_Handler::THROTTLE)
    {
        store_RC.RC_TO = boolOverrride;
        if(boolOverrride == false)
            override_command.throttle_override = 0;
    }

    return(override_command);
}

QList<QString> RC_Handler::parameterList_RC()
{
    QList<QString> returnList;
    returnList.append(RC_EnumtoString(RC1_Max));
    returnList.append(RC_EnumtoString(RC2_Max));
    returnList.append(RC_EnumtoString(RC3_Max));
    returnList.append(RC_EnumtoString(RC4_Max));

    returnList.append(RC_EnumtoString(RC1_Min));
    returnList.append(RC_EnumtoString(RC2_Min));
    returnList.append(RC_EnumtoString(RC3_Min));
    returnList.append(RC_EnumtoString(RC4_Min));
    return(returnList);
}

QString RC_Handler::RC_EnumtoString(const int &Parameter)
{
    QString string_return = "";
    switch(Parameter)
    {
    case(RC1_Min):
        string_return = "RC1_Min";
        break;
    case(RC1_Max):
        string_return = "RC1_Max";
        break;
    case(RC2_Min):
        string_return = "RC2_Min";
        break;
    case(RC2_Max):
        string_return = "RC2_Max";
        break;
    case(RC3_Min):
        string_return = "RC3_Min";
        break;
    case(RC3_Max):
        string_return = "RC3_Max";
        break;
    case(RC4_Min):
        string_return = "RC4_Min";
        break;
    case(RC4_Max):
        string_return = "RC4_Max";
        break;

    case(RC5_Min):
        string_return = "RC5_Min";
        break;
    case(RC5_Max):
        string_return = "RC5_Max";
        break;
    case(RC6_Min):
        string_return = "RC6_Min";
        break;
    case(RC6_Max):
        string_return = "RC6_Max";
        break;
    case(RC7_Min):
        string_return = "RC7_Min";
        break;
    case(RC7_Max):
        string_return = "RC7_Max";
        break;
    case(RC8_Min):
        string_return = "RC8_Min";
        break;
    case(RC8_Max):
        string_return = "RC8_Max";
        break;

    case(RC9_Min):
        string_return = "RC9_Min";
        break;
    case(RC9_Max):
        string_return = "RC9_Max";
        break;
    case(RC10_Min):
        string_return = "RC10_Min";
        break;
    case(RC10_Max):
        string_return = "RC10_Max";
        break;
    case(RC11_Min):
        string_return = "RC11_Min";
        break;
    case(RC11_Max):
        string_return = "RC11_Max";
        break;
    case(RC12_Min):
        string_return = "RC12_Min";
        break;
    case(RC12_Max):
        string_return = "RC12_Max";
        break;

    case(RC13_Min):
        string_return = "RC13_Min";
        break;
    case(RC13_Max):
        string_return = "RC13_Max";
        break;
    case(RC14_Min):
        string_return = "RC14_Min";
        break;
    case(RC14_Max):
        string_return = "RC14_Max";
        break;

    default:
        string_return = "";
    }
    return(string_return);
}

RC_Handler::Vehicle_Params RC_Handler::RC_StringtoEnum(const QString &Parameter)
{
    RC_Handler::Vehicle_Params return_int;

    if(Parameter == "RC1_Min")
        return_int = RC_Handler::RC1_Min;
    else if(Parameter == "RC1_Max")
        return_int = RC_Handler::RC1_Max;
    else if(Parameter == "RC2_Min")
        return_int = RC_Handler::RC2_Min;
    else if(Parameter == "RC2_Max")
        return_int = RC_Handler::RC2_Max;
    else if(Parameter == "RC3_Min")
        return_int = RC_Handler::RC3_Min;
    else if(Parameter == "RC3_Max")
        return_int = RC_Handler::RC3_Max;
    else if(Parameter == "RC4_Min")
        return_int = RC_Handler::RC4_Min;
    else if(Parameter == "RC4_Max")
        return_int = RC_Handler::RC4_Max;

    else if(Parameter == "RC5_Min")
        return_int = RC_Handler::RC5_Min;
    else if(Parameter == "RC5_Max")
        return_int = RC_Handler::RC5_Max;
    else if(Parameter == "RC6_Min")
        return_int = RC_Handler::RC6_Min;
    else if(Parameter == "RC6_Max")
        return_int = RC_Handler::RC6_Max;
    else if(Parameter == "RC7_Min")
        return_int = RC_Handler::RC7_Min;
    else if(Parameter == "RC7_Max")
        return_int = RC_Handler::RC7_Max;
    else if(Parameter == "RC8_Min")
        return_int = RC_Handler::RC8_Min;
    else if(Parameter == "RC8_Max")
        return_int = RC_Handler::RC8_Max;

    else if(Parameter == "RC9_Min")
        return_int = RC_Handler::RC9_Min;
    else if(Parameter == "RC9_Max")
        return_int = RC_Handler::RC9_Max;
    else if(Parameter == "RC10_Min")
        return_int = RC_Handler::RC10_Min;
    else if(Parameter == "RC10_Max")
        return_int = RC_Handler::RC10_Max;
    else if(Parameter == "RC11_Min")
        return_int = RC_Handler::RC11_Min;
    else if(Parameter == "RC11_Max")
        return_int = RC_Handler::RC11_Max;
    else if(Parameter == "RC12_Min")
        return_int = RC_Handler::RC12_Min;
    else if(Parameter == "RC12_Max")
        return_int = RC_Handler::RC12_Max;

    else if(Parameter == "RC13_Min")
        return_int = RC_Handler::RC13_Min;
    else if(Parameter == "RC13_Max")
        return_int = RC_Handler::RC13_Max;
    else if(Parameter == "RC14_Min")
        return_int = RC_Handler::RC14_Min;
    else if(Parameter == "RC14_Max")
        return_int = RC_Handler::RC14_Max;
    else
        return_int = RC_Handler::RC_Length;

    return(return_int);

}

