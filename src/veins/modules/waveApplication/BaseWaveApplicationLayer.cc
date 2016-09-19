
#include "veins/modules/waveApplication/BaseWaveApplicationLayer.h"

const simsignalwrap_t BaseWaveApplicationLayer::mobilityStateChangedSignal =
        simsignalwrap_t(MIXIM_SIGNAL_MOBILITY_CHANGE_NAME);

void BaseWaveApplicationLayer::initialize(int stage) {
    BaseApplLayer::initialize(stage);

    if (stage == 0) {
        myMac = FindModule<WaveAppToMac1609_4Interface*>::findSubModule(
                getParentModule());
        assert(myMac);

        myId = getParentModule()->getIndex();

        headerLength = par("headerLength").longValue();
        double maxOffset = par("maxOffset").doubleValue();
        sendBeacons = par("sendBeacons").boolValue();
        beaconLengthBits = par("beaconLengthBits").longValue();
        beaconPriority = par("beaconPriority").longValue();

        scheduleMsg = par("scheduleMsg");

//        sendData = par("sendData").boolValue();
        dataPriority = par("dataPriority").longValue();

        sendBeaconEvt = new cMessage("beacon evt", SEND_BEACON_EVT);

        //simulate asynchronous channel access
        double offSet = dblrand() * (par("beaconInterval").doubleValue() / 2);
        offSet = offSet + floor(offSet / 0.050) * 0.050;
        individualOffset = dblrand() * maxOffset;

        findHost()->subscribe(mobilityStateChangedSignal, this);

        if (sendBeacons) {
            scheduleAt(simTime() + offSet, sendBeaconEvt);
        }

        //todo resolver isso \/
        wsmInterval = par("wsmInterval");
        emergencyMessage = new cMessage("Emergency Message",
                SEND_EMERGENCY_EVT);
        if (scheduleMsg){
            scheduleAt(simTime() + wsmInterval, emergencyMessage);
            //todo resolver isso
        }

    }
}

//TODO REVER BEACON, tipo add beaconlenghtbits etc
WaveShortMessage* BaseWaveApplicationLayer::prepareBeaconWSM(int beaconLengthBits,
        int priority, int rcvId, int serial) {
    WaveShortMessage* wsm = new WaveShortMessage("beacon");
    wsm->addBitLength(headerLength);
    wsm->setChannelNumber(Channels::CCH);
    DBG << "Creating Beacon with Priority " << priority << " at Applayer at "
               << wsm->getTimestamp() << std::endl;
    return wsm;
}

WaveShortMessage* BaseWaveApplicationLayer::createDataWSM(t_psid psid,
        Channels::ChannelNumber channel, int priority, int rcvId, int serial) {
    WaveShortMessage* wsm = new WaveShortMessage("data");
    wsm->addBitLength(headerLength); //TODO verificar o valor correto

    wsm->setChannelNumber(channel);
    wsm->setPsid(psid);

    wsm->setPriority(priority);
    wsm->setWsmVersion(3);
    wsm->setTimestamp(simTime());
    wsm->setSenderAddress(myId);
    wsm->setRecipientAddress(rcvId);
    wsm->setSenderPos(curPosition);
    wsm->setSerial(serial);

    DBG << "Creating Data with Priority " << priority << " at Applayer at "
               << wsm->getTimestamp() << std::endl;

    return wsm;
}

WaveShortMessage* BaseWaveApplicationLayer::createDataWSM(int priority, int rcvId, int serial) {
    WaveShortMessage* wsm = new WaveShortMessage("data");
    wsm->addBitLength(headerLength); //TODO verificar se é o valor correto

    wsm->setPriority(priority);
    wsm->setWsmVersion(3);
    wsm->setTimestamp(simTime());
    wsm->setSenderAddress(myId);
    wsm->setRecipientAddress(rcvId);
    wsm->setSenderPos(curPosition);
    wsm->setSerial(serial);

    DBG << "Creating Data with Priority " << priority << " at Applayer at "
               << wsm->getTimestamp() << std::endl;

    return wsm;
}

void BaseWaveApplicationLayer::receiveSignal(cComponent* source, simsignal_t signalID,
        cObject* obj, cObject* details) {
    Enter_Method_Silent
    ();
    if (signalID == mobilityStateChangedSignal) {
        handlePositionUpdate(obj);
    }
}

void BaseWaveApplicationLayer::onBeacon(WaveShortMessage* wsm) {
    //some code
}

void BaseWaveApplicationLayer::handlePositionUpdate(cObject* obj) {
    ChannelMobilityPtrType const mobility = check_and_cast<
            ChannelMobilityPtrType>(obj);
    curPosition = mobility->getCurrentPosition();
}

void BaseWaveApplicationLayer::onData(WaveShortMessage* wsm) {
    receiveMessage(wsm);
}

void BaseWaveApplicationLayer::handleLowerMsg(cMessage* msg) {

    WaveShortMessage* wsm = dynamic_cast<WaveShortMessage*>(msg);
    ASSERT(wsm);

    if (std::string(wsm->getName()) == "beacon") {
        onBeacon(wsm);
    } else if (std::string(wsm->getName()) == "data") {
        onData(wsm);
    } else {
        DBG << "unknown message (" << wsm->getName() << ")  received\n";
    }
    delete (msg);
}

void BaseWaveApplicationLayer::handleSelfMsg(cMessage* msg) {
    switch (msg->getKind()) {
    case SEND_BEACON_EVT: {
        WaveShortMessage* beacon = prepareBeaconWSM(beaconLengthBits, beaconPriority, 0, -1);
        sendWSM(beacon);
        scheduleAt(simTime() + par("beaconInterval").doubleValue(), sendBeaconEvt);
        break;
    }
    case SEND_EMERGENCY_EVT: {
        WaveShortMessage* baseWsm = createDataWSM(dataPriority, -1, 2);
        sendMessage(baseWsm);
        scheduleAt(simTime() + wsmInterval, emergencyMessage); //FIXME arrumar o agendamento da msg
        break;
    }
    default: {
        if (msg)
            DBG << "APP: Error: Got Self Message of unknown kind! Name: "
                       << msg->getName() << endl;
        break;
    }
    }
}

void BaseWaveApplicationLayer::sendWSM(WaveShortMessage* wsm) {
    sendDelayedDown(wsm, individualOffset);
}

void BaseWaveApplicationLayer::finish() {
    if (sendBeaconEvt->isScheduled()) {
        cancelAndDelete(sendBeaconEvt);
    } else {
        delete sendBeaconEvt;
    }

    findHost()->unsubscribe(mobilityStateChangedSignal, this);

}
