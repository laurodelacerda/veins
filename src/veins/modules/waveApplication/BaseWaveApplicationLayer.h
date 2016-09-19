#ifndef BaseWaveApplicationLayer_H_
#define BaseWaveApplicationLayer_H_

#include <map>
#include "veins/base/modules/BaseApplLayer.h"
#include "veins/modules/utility/Consts80211p.h"
#include "veins/modules/messages/WaveShortMessage_m.h"
#include "veins/base/connectionManager/ChannelAccess.h"
#include "veins/modules/mac/ieee80211p/WaveAppToMac1609_4Interface.h"
#include "veins/modules/waveApplication/PSIDList1609_12.h"

#ifndef DBG
#define DBG EV
#endif

class BaseWaveApplicationLayer: public BaseApplLayer {

public:
//    ~BaseWaveApplicationLayer();
    virtual void initialize(int stage);
    virtual void finish();

    virtual void receiveSignal(cComponent* source, simsignal_t signalID,
            cObject* obj, cObject* details);
    void handleSelfMsg(cMessage *msg);

    enum WaveApplMessageKinds {
        SERVICE_PROVIDER = LAST_BASE_APPL_MESSAGE_KIND,
        SEND_BEACON_EVT,
        SEND_EMERGENCY_EVT //FIXME arrumar o agendamento de mensagens
    };

protected:
    int dataPriority;

private:
//    TraCIMobility* mobility;
//    bool changedLane;
    double wsmInterval; //FIXME parametrizar no emergencymessage
    cMessage* emergencyMessage;
    cMessage* sendBeaconEvt;

    int beaconLengthBits;
    int beaconPriority;
//    bool sendData; //TODO TIRA OU DEIXA? SE DEIXAR PODE CONFUNDIR
    bool sendBeacons;
//    bool receiveMessage;
    simtime_t individualOffset;
    Coord curPosition;
    int myId;

    WaveAppToMac1609_4Interface* myMac;

    bool scheduleMsg;

protected:
    WaveShortMessage* createDataWSM(t_psid psid,
            Channels::ChannelNumber channel, int priority, int rcvId,
            int serial = 0); //TODO acho q n to usando isso, verificar
    WaveShortMessage* createDataWSM(int priority, int rcvId,
            int serial = 0);
    void sendWSM(WaveShortMessage* wsm);
    virtual void sendMessage(WaveShortMessage* baseWsm) = 0;
    virtual void receiveMessage(WaveShortMessage* wsm) = 0;

private:
    static const simsignalwrap_t mobilityStateChangedSignal;

    /** @brief handle messages from below */
    void handleLowerMsg(cMessage* msg);
    /** @brief handle self messages */
//		virtual void handleSelfMsg(cMessage* msg);
    WaveShortMessage* prepareBeaconWSM(int beaconLengthBits, int priority,
            int rcvId, int serial = 0);
    void onBeacon(WaveShortMessage* wsm);
    void onData(WaveShortMessage* wsm);

    void handlePositionUpdate(cObject* obj);

};

#endif /* BASEWAVEAPPLLAYER_H_ */
