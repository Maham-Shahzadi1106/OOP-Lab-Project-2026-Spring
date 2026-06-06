#include "SmartDevice.h"
using namespace std;
SmartDevice::SmartDevice(int id, const string &name, double powerUsage)
    : id(id), name(name), isOn(false), powerUsage(powerUsage)
{
}

SmartDevice::~SmartDevice()
{
}

string SmartDevice::getStatus() const
{
  string status = isOn ? "On" : "Off";
  status += ", Power Usage: " + to_string(powerUsage) + " W";
  return status;
}

int SmartDevice::getId() const
{
  return id;
}

string SmartDevice::getName() const
{
  return name;
}

void SmartDevice::setName(const string &newName)
{
  name = newName;
}

bool SmartDevice::isPoweredOn() const
{
  return isOn;
}

void SmartDevice::setPowerUsage(double usage)
{
  powerUsage = usage;
}

double SmartDevice::getPowerUsage() const
{
  return powerUsage;
}

bool SmartDevice::operator==(const SmartDevice &other) const
{
  return id == other.id;
}

ostream &operator<<(ostream &os, const SmartDevice &device)
{
  os << "[" << device.getType() << "] " << device.getName()
     << " (ID: " << device.id << ") - " << device.getStatus();
  return os;
}
