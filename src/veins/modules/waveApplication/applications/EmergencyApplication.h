#ifndef EmergencyApplication_H_
#define EmergencyApplication_H_

#include "veins/modules/waveApplication/applications/BaseApplication.h"
#include "veins/modules/utility/Consts80211p.h"
#include "veins/modules/waveApplication/gps/BaseGPS.h"
#include "veins/modules/waveApplication/driver/BaseDriver.h"
#include "veins/modules/waveApplication/cryptography/BaseCryptography.h"

class EmergencyApplication: public BaseApplication {
public:
    EmergencyApplication(int roads);

    WaveShortMessage* execute(WaveShortMessage* receivedWsm, BaseDriver* driver, BaseGPS* gps);
    WaveShortMessage* prepareMessage(WaveShortMessage* baseWsm, BaseDriver* driver, BaseGPS* gps);
    WaveShortMessage* execute(WaveShortMessage* receivedWsm);
    WaveShortMessage* prepareMessage(WaveShortMessage* baseWsm);

private:
    BaseCryptography* cryptography;
    int numberOfRoads;

};

#endif
