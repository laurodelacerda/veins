
#include "veins/modules/waveApplication/waveDevice/rsu/RSUDevice.h"

Define_Module(RSUDevice);

void RSUDevice::initialize(int stage) {

    BaseWaveDevice::initialize(stage);

    if (stage == 0) {

        mobi = dynamic_cast<BaseMobility*> (getParentModule()->getSubmodule("mobility"));
        ASSERT(mobi);

    }
}
