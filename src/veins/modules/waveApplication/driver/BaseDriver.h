
#ifndef BaseDriver_H
#define BaseDriver_H

#include "veins/modules/mobility/traci/TraCICommandInterface.h"

using Veins::TraCICommandInterface;

class BaseDriver {

protected:
    TraCICommandInterface::Vehicle* traciVehicle;

public:
    virtual void changeLane() = 0;

};

#endif
