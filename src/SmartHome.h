#ifndef SMARTHOME_H
#define SMARTHOME_H

#include <string>
#include "Room.h"
#include "Automation.h"
#include "EnergyLog.h"
#include "UserAuthentication.h"

class SmartDevice;
using namespace std;
class SmartHome
{
private:
  Room *rooms[20];
  int roomCount;
  Automation *automations[50];
  int automationCount;
  EnergyLog *energyLog;
  UserAuthentication *auth;
  int nextDeviceId;

public:
  SmartHome();
  ~SmartHome();

  bool createRoom(const string &roomName);
  bool deleteRoom(const string &roomName);
  Room *findRoom(const string &roomName) const;
  void displayRooms() const;
  void displayAllDevices() const;
  SmartDevice *findDeviceById(int deviceId) const;
  bool registerDevice(SmartDevice *device, const string &roomName);
  bool removeDevice(int deviceId);
  bool assignDeviceToRoom(int deviceId, const string &roomName);
  bool controlDevice(int deviceId);
  bool toggleDevice(int deviceId);
  void listDeviceStatus() const;
  bool addAutomation(Automation *automation);
  void displayAutomations() const;
  void executeAutomations();
  EnergyLog *getEnergyLog() const;
  UserAuthentication *getAuthentication() const;
  int generateDeviceId();
  void saveData() const;
  void loadData();
  SmartDevice *createDeviceFromSerialized(const string &line) const;
  string getCurrentTime() const;
  string getCurrentDate() const;
};

#endif // SMARTHOME_H
