#ifndef PSIDList_H
#define PSIDList_H

//TODO vai ser enum msm?
//TODO 2 implementa isso nas classe tudo ou faz um jeito de implementar num lugar só?
enum t_psid
    : int {
        NULL_PSID = 0x00,

    ELECTRONIC_FEE_COLLECTION = 0x01,
    FREIGHT_FLEET_MANAGEMENT = 0x02,
    PUBLIC_TRANSPORT = 0x03,
    TRAFFIC_TRAVELLER_INFORMATION = 0x04,
    TRAFFIC_CONTROL = 0x05,
    PARKING_MANAGEMENT = 0x06,
    GEOGRAPHIC_ROAD_DATABASE = 0x07,
    EMERGENCY_WARNING = 0x0c,
    AFTER_THEFT_SYSTEMS = 0x10,
    V2V_SAFETY = 0x20,
    WAVE_SEC_MANAGEMENT = 0x23,
    VULNERABLE_ROAD_USERS = 0x27,
    TESTING = 0x7F,
    INTERSECTION_SAFETY = 0x82,
    TRAVELLER_INFO_ROADSIDE_SIGNAGE = 0x83,
    WAVE_SERVICE_AD = 0x87,
    IPV6_ROUTING = 0x1020407E,
};

//enum t_message_behaviour {
enum class Message_Behaviour
    : int {
        CREATOR = 1, RECEIVER, REPLICATOR // replicator is also a receiver but not a creator
};

#endif
