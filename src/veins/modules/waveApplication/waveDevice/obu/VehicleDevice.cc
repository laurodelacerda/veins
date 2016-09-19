#include "veins/modules/waveApplication/waveDevice/obu/VehicleDevice.h"
#include "veins/modules/waveApplication/gps/SimpleGPS.h"
#include "veins/modules/waveApplication/driver/SimpleDriver.h"

Define_Module(VehicleDevice);

using Veins::TraCIMobilityAccess;

void VehicleDevice::initialize(int stage) {

    BaseOBUDevice::initialize(stage);

    if (stage == 0) {

//        mobility = TraCIMobilityAccess().get(getParentModule());
//        traciVehicle = mobility->getVehicleCommandInterface();
//
//        myGPS = new SimpleGPS(traciVehicle);
        myDriver = new SimpleDriver(traciVehicle);

    }
}

void VehicleDevice::sendMessage(WaveShortMessage* baseWsm) {
    std::list<WaveShortMessage*> wsms;
    wsms = applications->prepareMessage(baseWsm, myDriver, myGPS);
    std::list<WaveShortMessage*>::iterator it;
    for (it = wsms.begin(); it != wsms.end(); ++it)
        BaseWaveApplicationLayer::sendWSM(*it);
}

void VehicleDevice::receiveMessage(WaveShortMessage* wsm) {
    findHost()->getDisplayString().updateWith("r=6,green");
    std::list<WaveShortMessage*> wsms;
    wsms = applications->executeWsm(wsm, myDriver, myGPS);
    std::list<WaveShortMessage*>::iterator it;
    for (it = wsms.begin(); it != wsms.end(); ++it) {
        BaseWaveApplicationLayer::sendWSM(*it);
    }
}
