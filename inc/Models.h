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

  // Construct all variables from jsonMap
    bool Construct(const std::map<std::string, std::string>& jsonMap) {
        std::cout << "Constructing  [ VentReq ] from JSON" << std::endl;
        if (jsonMap.find("vnetId") != jsonMap.end()) vnetId = jsonMap.at("vnetId");
        if (jsonMap.find("region") != jsonMap.end()) region = jsonMap.at("region");
        return true;
    }
    VentReq(const std::map<std::string, std::string>& jsonMap) {
        Construct(jsonMap);
    }

  bool isVnetIdValid() {
    return Utils::isValidGUID(vnetId);
  }
  // Validate that all required fields are populated
  bool isValid() const {
      std::cout << "Validating  [ VentReq ] authenticity" << std::endl;
      return !vnetId.empty() && !region.empty();
  }
  void Display() {
    std::cout << "Vnet: " << vnetId << std::endl;
    std::cout << "region: " << region << std::endl;
  }
  std::string Process() {
    return "Processed";
  }
};

class MappingReq {
public:
    std::string vnetId;
    std::string cAddr;
    std::string cMac;
    std::string pAddr;
    std::string pMac;

    // Construct all variables from jsonMap
    bool Construct(const std::map<std::string, std::string>& jsonMap) {
        std::cout << "Constructing [ MappingReq ] from JSON" << std::endl;
        if (jsonMap.find("vnetId") != jsonMap.end()) vnetId = jsonMap.at("vnetId");
        if (jsonMap.find("cAddr") != jsonMap.end()) cAddr = jsonMap.at("cAddr");
        if (jsonMap.find("cMac") != jsonMap.end()) cMac = jsonMap.at("cMac");
        if (jsonMap.find("pAddr") != jsonMap.end()) pAddr = jsonMap.at("pAddr");
        if (jsonMap.find("pMac") != jsonMap.end()) pMac = jsonMap.at("pMac");
        return true;
    }
    MappingReq(const std::map<std::string, std::string>& jsonMap) {
        Construct(jsonMap);
    }

    std::string Process() {
        std::cout << "Processing [ MappingReq ] " << std::endl;
        if (isValid()) {
            return "MappingReq Processing Success\n";
        } else {
            return "Invalid Request";
            display();
        }
        return "Request processing failed";
    }
    // Display all variables
    void display() const {
        std::cout << "vnetId: " << vnetId << "\n";
        std::cout << "cAddr: " << cAddr << "\n";
        std::cout << "cMac: " << cMac << "\n";
        std::cout << "pAddr: " << pAddr << "\n";
        std::cout << "pMac: " << pMac << "\n";
    }

    // Validate that all required fields are populated
    bool isValid() const {
        std::cout << "Validating [ MappingReq ] authenticity ....." << std::endl;
        return !vnetId.empty() && !cAddr.empty() && !cMac.empty() && !pAddr.empty() && !pMac.empty();
    }
};

#endif
