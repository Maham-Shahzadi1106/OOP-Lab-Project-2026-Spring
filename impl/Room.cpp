#include "Room.h"
#include <iostream>
using namespace std;
Room::Room(const string &name)
    : name(name), deviceCount(0)
{
  for (int i = 0; i < 100; ++i)
  {
    devices[i] = nullptr;
  }
}

Room::~Room()
{
  for (int i = 0; i < deviceCount; ++i)
  {
    delete devices[i];
    devices[i] = nullptr;
  }
  deviceCount = 0;
}

string Room::getName() const
{
  return name;
}

bool Room::addDevice(SmartDevice *device)
{
  if (deviceCount >= 100 || device == nullptr)
  {
    return false;
  }
  devices[deviceCount++] = device;
  return true;
}

bool Room::removeDevice(int deviceId)
{
  for (int i = 0; i < deviceCount; ++i)
  {
    if (devices[i] && devices[i]->getId() == deviceId)
    {
      delete devices[i];
      for (int j = i; j < deviceCount - 1; ++j)
      {
        devices[j] = devices[j + 1];
      }
      devices[deviceCount - 1] = nullptr;
      deviceCount--;
      return true;
    }
  }
  return false;
}

SmartDevice *Room::findDeviceById(int deviceId) const
{
  for (int i = 0; i < deviceCount; ++i)
  {
    if (devices[i] && devices[i]->getId() == deviceId)
    {
      return devices[i];
    }
  }
  return nullptr;
}

void Room::displayDevices() const
{
  if (deviceCount == 0)
  {
    cout << "  No devices in room " << name << ".\n";
    return;
  }
  cout << "  Devices in " << name << ":\n";
  for (int i = 0; i < deviceCount; ++i)
  {
    if (devices[i])
    {
      cout << "    " << *devices[i] << "\n";
    }
  }
}

int Room::getDeviceCount() const
{
  return deviceCount;
}

SmartDevice *Room::getDeviceAt(int index) const
{
  if (index < 0 || index >= deviceCount)
  {
    return nullptr;
  }
  return devices[index];
}

SmartDevice *Room::takeDevice(int deviceId)
{
  for (int i = 0; i < deviceCount; ++i)
  {
    if (devices[i] && devices[i]->getId() == deviceId)
    {
      SmartDevice *device = devices[i];
      for (int j = i; j < deviceCount - 1; ++j)
      {
        devices[j] = devices[j + 1];
      }
      devices[deviceCount - 1] = nullptr;
      deviceCount--;
      return device;
    }
  }
  return nullptr;
}

string Room::serializeRoom() const
{
  return name;
}
