#ifndef SimpleGPS_H
#define SimpleGPS_H

#include "veins/modules/waveApplication/gps/BaseGPS.h"

class SimpleGPS: public BaseGPS {

public:
    SimpleGPS(TraCICommandInterface::Vehicle*);

    std::string getCourse(int maxNumberOfRoads);
    bool onRoute(std::string course);

private:
    std::string formatRoad(std::string road);
    std::string formatLane(int lane);
};

#endif
