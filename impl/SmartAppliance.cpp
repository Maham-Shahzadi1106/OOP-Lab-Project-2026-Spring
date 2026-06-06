#include "SmartAppliance.h"
using namespace std;
SmartAppliance::SmartAppliance(int id, const string &name, double powerUsage, const string &applianceType, bool isRunning)
    : SmartDevice(id, name, powerUsage), applianceType(applianceType), isRunning(isRunning)
{
}

SmartAppliance::~SmartAppliance()
{
}

void SmartAppliance::toggle()
{
  isOn = !isOn;
}

string SmartAppliance::getStatus() const
{
  string status = SmartDevice::getStatus();
  status += ", Type: " + applianceType;
  status += ", Running: ";
  status += isRunning ? "Yes" : "No";
  return status;
}

string SmartAppliance::generateReport() const
{
  return "SmartAppliance " + name + " is " + (isOn ? "On" : "Off") + ", " + (isRunning ? "Running" : "Stopped") + ".";
}

string SmartAppliance::getType() const
{
  return "SmartAppliance";
}

void SmartAppliance::setApplianceType(const string &type)
{
  applianceType = type;
}

string SmartAppliance::getApplianceType() const
{
  return applianceType;
}

void SmartAppliance::setRunning(bool running)
{
  isRunning = running;
}

bool SmartAppliance::getRunning() const
{
  return isRunning;
}

string SmartAppliance::serialize() const
{
  return "SmartAppliance;" + to_string(id) + ";" + name + ";" + (isOn ? "1" : "0") + ";" + to_string(powerUsage) + ";" + applianceType + ";" + (isRunning ? "1" : "0");
}
