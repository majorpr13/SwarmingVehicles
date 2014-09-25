#include "cmdconversions.h"

cmdConversions::cmdConversions()
{
}

QVector<double> cmdConversions::convert_setHome(mavCommandStructures::mavCMD_setHome &mavCMD)
{
    QVector<double> returnVector(7);
    returnVector.insert(0 , mavCMD.useCurrent);
    returnVector.insert(1 , mavCMD.empty1);
    returnVector.insert(2 , mavCMD.empty2);
    returnVector.insert(3 , mavCMD.empty3);
    returnVector.insert(4 , mavCMD.Latitude);
    returnVector.insert(5 , mavCMD.Longitude);
    returnVector.insert(6 , mavCMD.Altitude);

    return(returnVector);
}
