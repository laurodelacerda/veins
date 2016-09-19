
#include "veins/modules/waveApplication/applications/BaseApplication.h"

bool BaseApplication::validPsid(int psid) {
    if (myPsid == psid)
        return true;
    return false;
}

bool BaseApplication::isReplicable() {
    return replicate;
}
