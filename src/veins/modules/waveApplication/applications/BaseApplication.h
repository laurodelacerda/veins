
#ifndef BaseApplication_H_
#define BaseApplication_H_

#include "veins/modules/messages/WaveShortMessage_m.h"
#include "veins/modules/waveApplication/PSIDList1609_12.h"
#include "veins/modules/waveApplication/driver/BaseDriver.h"
#include "veins/modules/waveApplication/gps/BaseGPS.h"
#include <list>

//todo rever strings e pensar na possibilidade de usar char*
//FIXME Esta classe aqui mesmo que PREPARE A WSM? Ele n deveria preparar apenas a msg em si? (pensando em como o modelo wave funciona na realidade)
    //  adicionar um Vistor pra resolver esse problema descrito acima?
    //TODO talvez usar TEMPLATE pra pegar o tipo da aplicacao! Nao sei, arrumar um jeito de verificar o leaf (resolucao bem bosta, se for resolver, usar visitor)

class BaseApplication {

public:

    //fixme realmente precisa repetir as duas funcoes?
    virtual WaveShortMessage* prepareMessage(WaveShortMessage* baseWsm) = 0; //FIXME  mudar nome (mesmo pra applManager e EmergAppl)
    virtual WaveShortMessage* execute(WaveShortMessage* receivedWsm) = 0;
    virtual WaveShortMessage* prepareMessage(WaveShortMessage* baseWsm, BaseDriver*, BaseGPS*) = 0; //FIXME  mudar nome
    virtual WaveShortMessage* execute(WaveShortMessage* receivedWsm, BaseDriver*, BaseGPS*) = 0;
    bool validPsid(int psid); //todo tentar colocar parametro do tipo t_psid
    bool isReplicable();

protected:
    t_psid myPsid;
    bool replicate;
};

#endif
