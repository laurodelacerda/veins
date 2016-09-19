#include "veins/modules/waveApplication/applications/ApplicationManager.h"

void ApplicationManager::insert(BaseApplication* message,
        Message_Behaviour behaviour) {
    messageComponents.insert(
            std::pair<BaseApplication*, Message_Behaviour>(message, behaviour));
}

void ApplicationManager::erase(BaseApplication* message) {
    messageComponents.erase(message);
}

std::list<WaveShortMessage*> ApplicationManager::prepareMessage(WaveShortMessage* baseWsm) {
    std::map<BaseApplication*, Message_Behaviour>::iterator it;
    std::list<WaveShortMessage*> wsms;
    for (it = messageComponents.begin(); it != messageComponents.end(); ++it) {
        if (it->second == Message_Behaviour::CREATOR) { //if it's a creator, prepares message to be sent:
            wsms.push_back(it->first->prepareMessage(baseWsm));
        }
    }
    return wsms;
}

std::list<WaveShortMessage*> ApplicationManager::executeWsm(WaveShortMessage* receivedWsm) {
    std::map<BaseApplication*, Message_Behaviour>::iterator it;
    std::list<WaveShortMessage*> wsms;

    if (std::find(wsmCache.begin(), wsmCache.end(), receivedWsm->getWsmData()) == wsmCache.end()) { //if not found in cache

        for (it = messageComponents.begin(); it != messageComponents.end(); ++it) {
            if (it->second == Message_Behaviour::RECEIVER || it->second == Message_Behaviour::REPLICATOR) { //if it's a receiver (or replicator), prepare to act
                if (it->first->validPsid(receivedWsm->getPsid())) {
                    WaveShortMessage* replicate = new WaveShortMessage(*it->first->execute(receivedWsm));
                    if (it->second == Message_Behaviour::REPLICATOR) {
                        if (it->first->isReplicable()) { wsms.push_back(replicate); }
                    }
                }
            }
        }
        if (wsmCache.size() < wsmCacheSize) {
            wsmCache.push_back(receivedWsm->getWsmData());
        }
        else {
            wsmCache.pop_front();
            wsmCache.push_back(receivedWsm->getWsmData());
        }
    }
    return wsms; //DOUBT retornar lista msm? aqui SEMPRE vai ser UMA wsm (ou nenhuma) apenas
}

std::list<WaveShortMessage*> ApplicationManager::prepareMessage(WaveShortMessage* baseWsm, BaseDriver* driver, BaseGPS* gps) { //, std::string data) {
    std::map<BaseApplication*, Message_Behaviour>::iterator it;
    std::list<WaveShortMessage*> wsms;
    for (it = messageComponents.begin(); it != messageComponents.end(); ++it) {
        if (it->second == Message_Behaviour::CREATOR) { //if it's a creator, prepares message to be sent:
            wsms.push_back(it->first->prepareMessage(baseWsm, driver, gps));
        }
    }
    return wsms;
}

std::list<WaveShortMessage*> ApplicationManager::executeWsm(WaveShortMessage* receivedWsm, BaseDriver* driver, BaseGPS* gps) {
    std::map<BaseApplication*, Message_Behaviour>::iterator it;
    std::list<WaveShortMessage*> wsms;

    if (std::find(wsmCache.begin(), wsmCache.end(), receivedWsm->getWsmData()) == wsmCache.end()) { //if not found in cache
        for (it = messageComponents.begin(); it != messageComponents.end(); ++it) {
            if (it->second == Message_Behaviour::RECEIVER || it->second == Message_Behaviour::REPLICATOR) { //if it's a receiver (or replicator), prepare to act
                if (it->first->validPsid(receivedWsm->getPsid())) {
                    WaveShortMessage* replicate = new WaveShortMessage(*it->first->execute(receivedWsm, driver, gps));
                    if (it->second == Message_Behaviour::REPLICATOR) {
                        if (it->first->isReplicable()) {
                            wsms.push_back(replicate);
                        }
                    }
                }
            }
        }
        if (wsmCache.size() < wsmCacheSize) {
            wsmCache.push_back(receivedWsm->getWsmData());
        }
        else {
            wsmCache.pop_front();
            wsmCache.push_back(receivedWsm->getWsmData());
        }
    }
    return wsms; //DOUBT retornar lista msm? aqui SEMPRE vai ser UMA wsm (ou nenhuma) apenas
}
