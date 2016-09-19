#ifndef VehicleDevice_H
#define VehicleDevice_H

#include "veins/modules/mobility/traci/TraCIMobility.h"
#include "veins/modules/mobility/traci/TraCICommandInterface.h"
#include "veins/modules/waveApplication/waveDevice/BaseWaveDevice.h"
#include "veins/modules/waveApplication/driver/BaseDriver.h"
#include "veins/modules/waveApplication/gps/BaseGPS.h"
#include "veins/modules/waveApplication/waveDevice/obu/BaseOBUDevice.h"

using Veins::TraCIMobility;
using Veins::TraCICommandInterface;

class VehicleDevice: public BaseOBUDevice {

public:
    void initialize(int stage);

private:
//    BaseGPS* myGPS;
    BaseDriver* myDriver;
//    TraCIMobility* mobility; //DOUBT precisa do mobility msm?
//    TraCICommandInterface::Vehicle* traciVehicle;

private:

    void sendMessage(WaveShortMessage* baseWsm);
    void receiveMessage(WaveShortMessage* wsm);

};

#endif
