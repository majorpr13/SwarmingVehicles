#ifndef INITIALIZATION_H
#define INITIALIZATION_H
#include "Definitions.h"

class Initialization
{
public:
    Initialization();
    FlightModeStructure::FlightModes m_FlightModeV;
    StreamModeStructure::StreamModes m_StreamModeV;
private:
    void initFlightModes();
    void initStreamModes();
};

#endif // INITIALIZATION_H
