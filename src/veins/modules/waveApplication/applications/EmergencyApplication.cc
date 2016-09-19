#include "veins/modules/waveApplication/applications/EmergencyApplication.h"
#include "veins/modules/waveApplication/cryptography/SimpleCryptography.h"

EmergencyApplication::EmergencyApplication(int roads) {
    myPsid = t_psid::EMERGENCY_WARNING;
    replicate = true;
    cryptography = new SimpleCryptography();
    numberOfRoads = roads;
}

WaveShortMessage* EmergencyApplication::prepareMessage(
        WaveShortMessage* baseWsm, BaseDriver* driver, BaseGPS* gps) {
    WaveShortMessage* wsm = new WaveShortMessage(*baseWsm);
    std::string data = gps->getCourse(numberOfRoads);
//    std::cout << "(" << simTime() << ") " << data << std::endl; //FIXME get course fixo aqui
    std::string encryptedData = cryptography->encrypt(data);
    wsm->setWsmData(encryptedData.c_str());

    wsm->setPsid(myPsid);
    wsm->setChannelNumber(Channels::CCH);
    wsm->addByteLength(encryptedData.size());

    return wsm;
}

WaveShortMessage* EmergencyApplication::execute(WaveShortMessage* receivedWsm,
        BaseDriver* driver, BaseGPS* gps) {

    std::string encryptedData = receivedWsm->getWsmData();
    std::string data = cryptography->decrypt(encryptedData);

    if (gps->onRoute(data)) {
        driver->changeLane();
    }

    WaveShortMessage* wsm = new WaveShortMessage(*receivedWsm); //todo check if it has a new sender (or is copying the same)
    return wsm;

}

WaveShortMessage* EmergencyApplication::prepareMessage(
        WaveShortMessage* baseWsm) {

    throw cRuntimeError(
            "Function \"EmergencyApplication::prepareMessage()\" should have driver and gps: EmergencyApplication::prepareMessage(wsm, driver, gps)");
}

WaveShortMessage* EmergencyApplication::execute(WaveShortMessage* receivedWsm) {

    WaveShortMessage* wsm = new WaveShortMessage(*receivedWsm); //TODO check if it has a new sender (or is copying the same)
    return wsm;

}
