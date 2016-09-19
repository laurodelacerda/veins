#include "veins/modules/waveApplication/waveDevice/BaseWaveDevice.h"
#include "veins/modules/waveApplication/applications/EmergencyApplication.h"

void BaseWaveDevice::initialize(int stage) { //todo BasciWaveApplLayer ve o PSID e chama aplicações DIFERENTES?
    BaseWaveApplicationLayer::initialize(stage);
    if (stage == 0) {
        applications = new ApplicationManager();

        std::vector<std::string> appls = vectorize(par("applications"));
        std::vector<std::string> types = vectorize(par("applCommunication"));

        numberOfRoads = par("roads");

        for (std::vector<std::string>::iterator itA = appls.begin(), itT =
                types.begin(); itA != appls.end() && itT != types.end();
                ++itA, ++itT) {
            applications->insert(getApplication(*itA), getType(*itT));
        }

    }
}

void BaseWaveDevice::sendMessage(WaveShortMessage* baseWsm) {
    std::list<WaveShortMessage*> wsms;
    wsms = applications->prepareMessage(baseWsm); //todo verificar se wsm está sendo mudada
    std::list<WaveShortMessage*>::iterator it;
    for (it = wsms.begin(); it != wsms.end(); ++it)
        BaseWaveApplicationLayer::sendWSM(*it);
}

void BaseWaveDevice::receiveMessage(WaveShortMessage* wsm) {
    findHost()->getDisplayString().updateWith("r=16,green");
    std::list<WaveShortMessage*> wsms;
    wsms = applications->executeWsm(wsm);
    std::list<WaveShortMessage*>::iterator it;
    for (it = wsms.begin(); it != wsms.end(); ++it) {
        BaseWaveApplicationLayer::sendWSM(*it);
    }
}

BaseApplication* BaseWaveDevice::getApplication(std::string name) {

    if (name == "emergency")
        return new EmergencyApplication(numberOfRoads);
    //Add new applications here
    else
        throw cRuntimeError(
                "ERROR BaseWaveDevice::getApplication(name). Application not found");
}

Message_Behaviour BaseWaveDevice::getType(std::string name) {

    //TODO Melhorar lógica
    if (name == "replicator")
        return Message_Behaviour::REPLICATOR;
    else if (name == "creator")
        return Message_Behaviour::CREATOR;
    else if (name == "receiver")
        return Message_Behaviour::RECEIVER;
    else
        throw cRuntimeError("ERROR BaseWaveDevice::getType(name). Type not found");
}

std::vector<std::string> BaseWaveDevice::vectorize(std::string values) {
    std::string token = " ";
    std::string::size_type i = 0;
    std::string::size_type j = values.find(token);

    std::vector<std::string> valuesList;

    if (j == std::string::npos) {
        valuesList.push_back(values);
    } else {
        while (j != std::string::npos) {
            valuesList.push_back(values.substr(i, j - i));
            i = ++j;
            j = values.find(token, j);

            if (j == std::string::npos) {
                valuesList.push_back(values.substr(i, values.length()));
            }
        }
    }
    return valuesList;
}
