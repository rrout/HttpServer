#include "Utils.h"
#include "Models.h"

// Construct all variables from jsonMap
bool VentReq::Construct(const std::map<std::string, std::string>& jsonMap) {
    std::cout << "Constructing  [ VentReq ] from JSON" << std::endl;
    if (jsonMap.find("vnetId") != jsonMap.end()) vnetId = jsonMap.at("vnetId");
    if (jsonMap.find("region") != jsonMap.end()) region = jsonMap.at("region");
    return true;
}
VentReq::VentReq(const std::map<std::string, std::string>& jsonMap) {
    Construct(jsonMap);
}

bool VentReq::isVnetIdValid() {
    return Utils::isValidGUID(vnetId);
}
// Validate that all required fields are populated
bool VentReq::isValid() const {
    std::cout << "Validating  [ VentReq ] authenticity" << std::endl;
    return !vnetId.empty() && !region.empty();
}
void VentReq::Display() {
    std::cout << "Vnet: " << vnetId << std::endl;
    std::cout << "region: " << region << std::endl;
}
std::string VentReq::Dump() {
    Display();
    return "Vent Request  Dumping filtered content \n";
}
std::string VentReq::Process() {
    help();
    return "Processed";
}
std::string VentReq::help() {
    std::string helpStr = "Example Payload : {\"vnetId\":\"01234567-89ab-cdef-0123-456789abcdef\",\n \"region\":\"India\"}";
    return helpStr;
}



bool MappingReq::Construct(const std::map<std::string, std::string>& jsonMap) {
      std::cout << "Constructing [ MappingReq ] from JSON" << std::endl;
      if (jsonMap.find("vnetId") != jsonMap.end()) vnetId = jsonMap.at("vnetId");
      if (jsonMap.find("cAddr") != jsonMap.end()) cAddr = jsonMap.at("cAddr");
      if (jsonMap.find("cMac") != jsonMap.end()) cMac = jsonMap.at("cMac");
      if (jsonMap.find("pAddr") != jsonMap.end()) pAddr = jsonMap.at("pAddr");
      if (jsonMap.find("pMac") != jsonMap.end()) pMac = jsonMap.at("pMac");
      return true;
}
MappingReq::MappingReq(const std::map<std::string, std::string>& jsonMap) {
  Construct(jsonMap);
}

std::string MappingReq::Process() {
  std::cout << "Processing [ MappingReq ] " << std::endl;
  if (isValid()) {
      return "MappingReq Processing Success\n";
  } else {
      return "Invalid Request : " + help();
      display();
  }
  return help();
}
// Display all variables
void MappingReq::display() const {
  std::cout << "vnetId: " << vnetId << "\n";
  std::cout << "cAddr: " << cAddr << "\n";
  std::cout << "cMac: " << cMac << "\n";
  std::cout << "pAddr: " << pAddr << "\n";
  std::cout << "pMac: " << pMac << "\n";
}
std::string MappingReq::Dump() {
    display();
    return  " MappingReq Dumping Filtered content \n";
}

// Validate that all required fields are populated
bool MappingReq::isValid() const {
  std::cout << "Validating [ MappingReq ] authenticity ....." << std::endl;
  return !vnetId.empty() && !cAddr.empty() && !cMac.empty() && !pAddr.empty() && !pMac.empty();
}

std::string MappingReq::help() {
    std::string helpStr = "Example Payload : {\"vnetId\":\"01234567-89ab-cdef-0123-456789abcdef\",\n \"cAddr\":\"1.1.1.1\", \"cMac\":\"1.1.1.1\", \"pAddr\":\"1.1.1.1\", \"pMac\":\"1.1.1.1\"}";
    return helpStr;
}

bool ConfigReq::Construct(const std::map<std::string, std::string>& jsonMap) {
    std::cout << "Not Implimented: " << "\n";
    return true;
}

ConfigReq::ConfigReq(const std::map<std::string, std::string>& jsonMap) {
  Construct(jsonMap);
}

std::string ConfigReq::Process() {
  std::cout << "Processing [ MappingReq ] " << std::endl;
  if (isValid()) {
      return "ConfigReq Processing Success\n";
  } else {
      return "Invalid Request : " + help();
      display();
  }
  return help();
}

void ConfigReq::display() const {
  std::cout << "Not Implimented: " << "\n";
}
std::string ConfigReq::Dump() {
    display();
    return  " ConfigReq Dumping Filtered content \n";
}

// Validate that all required fields are populated
bool ConfigReq::isValid() const {
  std::cout << "Validating [ ConfigReq ] authenticity ....." << std::endl;
  return false;
}

std::string ConfigReq::help() {
    std::string helpStr = "Example Payload : {\"vnetId\":\"01234567-89ab-cdef-0123-456789abcdef\",\n \"cAddr\":\"1.1.1.1\", \"cMac\":\"1.1.1.1\", \"pAddr\":\"1.1.1.1\", \"pMac\":\"1.1.1.1\"}";
    return helpStr;
}