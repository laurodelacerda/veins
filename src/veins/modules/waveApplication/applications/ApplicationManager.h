
#ifndef ApplicationManager_H_
#define ApplicationManager_H_

#include <map>
#include <algorithm>
#include "veins/modules/waveApplication/applications/BaseApplication.h"

class BaseWaveDevice;

class ApplicationManager {

public:

    void insert(BaseApplication*, Message_Behaviour);
    void erase(BaseApplication*);

    std::list<WaveShortMessage*> prepareMessage(WaveShortMessage* baseWsm);
    std::list<WaveShortMessage*> executeWsm(WaveShortMessage* receivedWsm);

    std::list<WaveShortMessage*> prepareMessage(WaveShortMessage* baseWsm, BaseDriver*, BaseGPS*);
    std::list<WaveShortMessage*> executeWsm(WaveShortMessage* receivedWsm, BaseDriver*, BaseGPS*);

private:

    std::map<BaseApplication*, Message_Behaviour> messageComponents;
    std::list<std::string> wsmCache;
    unsigned int wsmCacheSize = 5; //todo tentar implementar no ned

};

#endif
