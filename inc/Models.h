#ifndef __MODELS_H__
#define __MODELS_H__

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include "Utils.h"

class VentReq {
public:
    std::string vnetId;
    std::string region;

    bool Construct(const std::map<std::string, std::string>& jsonMap);
    VentReq(const std::map<std::string, std::string>& jsonMap);
    bool isVnetIdValid();
    bool isValid() const;
    void Display();
    std::string Process();
};

class MappingReq {
public:
    std::string vnetId;
    std::string cAddr;
    std::string cMac;
    std::string pAddr;
    std::string pMac;

    // Construct all variables from jsonMap
    bool Construct(const std::map<std::string, std::string>& jsonMap);
    MappingReq(const std::map<std::string, std::string>& jsonMap);
    std::string Process();
    void display() const;
    bool isValid() const;
};

#endif
