
#include "veins/modules/waveApplication/driver/SimpleDriver.h"

SimpleDriver::SimpleDriver(TraCICommandInterface::Vehicle* vehicle) {
    traciVehicle = vehicle;
}

void SimpleDriver::changeLane() {
    if (traciVehicle->getLaneIndex() > 0) {
        traciVehicle->changeLane(traciVehicle->getLaneIndex()-1, 0);
    }
}
