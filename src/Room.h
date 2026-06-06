#ifndef ROOM_H
#define ROOM_H

#include <string>
#include "SmartDevice.h"
using namespace std;
class Room
{
private:
  string name;
  SmartDevice *devices[100];
  int deviceCount;

public:
  Room(const string &name);
  ~Room();
  string getName() const;
  bool addDevice(SmartDevice *device);
  bool removeDevice(int deviceId);
  SmartDevice *findDeviceById(int deviceId) const;
  void displayDevices() const;
  int getDeviceCount() const;
  SmartDevice *getDeviceAt(int index) const;
  SmartDevice *takeDevice(int deviceId);
  string serializeRoom() const;
};

#endif // ROOM_H
