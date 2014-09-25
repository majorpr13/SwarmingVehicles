#ifndef CMDCONVERSIONS_H
#define CMDCONVERSIONS_H

#include <QVector>

#include <Definitions.h>

class cmdConversions
{
public:
    cmdConversions();

    QVector<double> convert_setHome(mavCommandStructures::mavCMD_setHome &mavCMD);

};

#endif // CMDCONVERSIONS_H
