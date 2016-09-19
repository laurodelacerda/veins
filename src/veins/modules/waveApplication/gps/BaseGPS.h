#ifndef BASEGPS_H_
#define BASEGPS_H_

#include "veins/modules/mobility/traci/TraCICommandInterface.h"

using Veins::TraCICommandInterface;

class BaseGPS {

public:
    virtual std::string getCourse(int maxNumberOfRoads) = 0;
    virtual bool onRoute(std::string course) = 0;

protected:
    TraCICommandInterface::Vehicle* traciVehicle;
};

#endif
