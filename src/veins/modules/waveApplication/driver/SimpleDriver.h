#ifndef SimpleDriver_H
#define SimpleDriver_H

#include "veins/modules/waveApplication/driver/BaseDriver.h"

class SimpleDriver: public BaseDriver {

public:
    SimpleDriver(TraCICommandInterface::Vehicle*);

public:
    void changeLane();

};

#endif
