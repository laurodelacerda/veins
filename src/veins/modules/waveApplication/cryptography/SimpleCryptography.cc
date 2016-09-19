
#include "veins/modules/waveApplication/cryptography/SimpleCryptography.h"

std::string SimpleCryptography::encrypt(std::string data){

    std::string encryptedData = "{" + data + "}";

    return encryptedData;
}

std::string SimpleCryptography::decrypt(std::string encryptedData){

    std::string decryptedData = encryptedData;

    decryptedData.erase(decryptedData.begin());
    decryptedData.erase(decryptedData.end()-1);

    return decryptedData;
}
