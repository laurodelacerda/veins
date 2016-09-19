
#ifndef SimpleRSUApplication_H
#define SimpleRSUApplication_H

#include "veins/modules/waveApplication/waveDevice/BaseWaveDevice.h"
#include "veins/modules/waveApplication/driver/BaseDriver.h"

class RSUDevice : public BaseWaveDevice {

public:
    void initialize(int stage);

private:
    BaseMobility* mobi;
};

#endif
