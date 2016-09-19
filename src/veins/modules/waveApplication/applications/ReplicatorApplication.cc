#include "veins/modules/waveApplication/applications/ReplicatorApplication.h"
#include "veins/modules/waveApplication/cryptography/SimpleCryptography.h"

ReplicatorApplication::ReplicatorApplication() {
    myPsid = NULL_PSID;
    replicate = true;
    cryptography = 0;
}

WaveShortMessage* ReplicatorApplication::prepareMessage(
        WaveShortMessage* baseWsm, BaseDriver* driver, BaseGPS* gps) {
    throw cRuntimeError(
                "Function \"ReplicatorApplication::prepareMessage()\" should not be called");
}

WaveShortMessage* ReplicatorApplication::execute(WaveShortMessage* receivedWsm,
        BaseDriver* driver, BaseGPS* gps) {
    WaveShortMessage* wsm = new WaveShortMessage(*receivedWsm); //todo check if it has a new sender (or is copying the same)
    return wsm;

}

WaveShortMessage* ReplicatorApplication::prepareMessage(
        WaveShortMessage* baseWsm) {

    throw cRuntimeError(
            "Function \"ReplicatorApplication::prepareMessage()\" should have driver and gps: ReplicatorApplication::prepareMessage(wsm, driver, gps)");
}

WaveShortMessage* ReplicatorApplication::execute(WaveShortMessage* receivedWsm) {

    WaveShortMessage* wsm = new WaveShortMessage(*receivedWsm); //TODO check if it has a new sender (or is copying the same)
    return wsm;

}
