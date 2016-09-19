#include "veins/modules/waveApplication/waveDevice/obu/BaseOBUDevice.h"
#include "veins/modules/waveApplication/gps/SimpleGPS.h"
#include "veins/modules/waveApplication/driver/SimpleDriver.h"

Define_Module(BaseOBUDevice);

using Veins::TraCIMobilityAccess;

void BaseOBUDevice::initialize(int stage) {

    BaseWaveDevice::initialize(stage);

    if (stage == 0) {

        mobility = TraCIMobilityAccess().get(getParentModule());
        traciVehicle = mobility->getVehicleCommandInterface();

        myGPS = new SimpleGPS(traciVehicle);
//        myDriver = new SimpleDriver(traciVehicle);

    }
}

//void BaseOBUDevice::sendMessage(WaveShortMessage* baseWsm) {
//    std::list<WaveShortMessage*> wsms;
//    wsms = applications->prepareMessage(baseWsm, myDriver, myGPS);
//    std::list<WaveShortMessage*>::iterator it;
//    for (it = wsms.begin(); it != wsms.end(); ++it)
//        BaseWaveApplicationLayer::sendWSM(*it);
//}
//
//void BaseOBUDevice::receiveMessage(WaveShortMessage* wsm) {
//    std::list<WaveShortMessage*> wsms;
//    wsms = applications->executeWsm(wsm, myDriver, myGPS);
//    std::list<WaveShortMessage*>::iterator it;
//    for (it = wsms.begin(); it != wsms.end(); ++it) {
//        BaseWaveApplicationLayer::sendWSM(*it);
//    }
//}
