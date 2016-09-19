#ifndef BaseCryptography_H_
#define BaseCryptography_H_

#include <string>

class BaseCryptography {

public:
    virtual std::string encrypt(std::string data) = 0;
    virtual std::string decrypt(std::string encryptedData) = 0;

};

#endif
