#ifndef IWaveApplication_H_
#define IWaveApplication_H_

#include "veins/modules/waveApplication/BaseWaveApplicationLayer.h"
#include "veins/modules/waveApplication/applications/ApplicationManager.h"

class BaseWaveDevice: public BaseWaveApplicationLayer {

public:
    virtual void initialize(int stage);

protected:

    ApplicationManager* applications;

protected:

    virtual void sendMessage(WaveShortMessage* baseWsm);
    virtual void receiveMessage(WaveShortMessage* wsm);

private:

    BaseApplication* getApplication(std::string name);
    Message_Behaviour getType(std::string name);
    std::vector<std::string> vectorize(std::string values);
    int numberOfRoads;

};

#endif
