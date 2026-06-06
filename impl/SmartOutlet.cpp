#include "SmartOutlet.h"
using namespace std;
SmartOutlet::SmartOutlet(int id, const string &name, double powerUsage, double maxLoad, const string &connectedDevice)
    : SmartDevice(id, name, powerUsage), maxLoad(maxLoad), connectedDevice(connectedDevice)
{
}

SmartOutlet::~SmartOutlet()
{
}

void SmartOutlet::toggle()
{
  isOn = !isOn;
}

string SmartOutlet::getStatus() const
{
  string status = SmartDevice::getStatus();
  status += ", Max Load: " + to_string(maxLoad) + " W";
  status += ", Connected: " + connectedDevice;
  return status;
}

string SmartOutlet::generateReport() const
{
  return "SmartOutlet " + name + " is " + (isOn ? "On" : "Off") + ", connected to " + connectedDevice + ".";
}

string SmartOutlet::getType() const
{
  return "SmartOutlet";
}

void SmartOutlet::setMaxLoad(double load)
{
  maxLoad = load;
}

double SmartOutlet::getMaxLoad() const
{
  return maxLoad;
}

void SmartOutlet::setConnectedDevice(const string &deviceName)
{
  connectedDevice = deviceName;
}

string SmartOutlet::getConnectedDevice() const
{
  return connectedDevice;
}

string SmartOutlet::serialize() const
{
  return "SmartOutlet;" + to_string(id) + ";" + name + ";" + (isOn ? "1" : "0") + ";" + to_string(powerUsage) + ";" + to_string(maxLoad) + ";" + connectedDevice;
}
