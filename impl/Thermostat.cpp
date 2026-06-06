#include "Thermostat.h"
using namespace std;
Thermostat::Thermostat(int id, const string &name, double powerUsage, double currentTemperature, double targetTemperature)
    : SmartDevice(id, name, powerUsage), currentTemperature(currentTemperature), targetTemperature(targetTemperature), scheduleTime(""), isScheduled(false)
{
}

Thermostat::~Thermostat()
{
}

void Thermostat::toggle()
{
  isOn = !isOn;
}

string Thermostat::getStatus() const
{
  string status = SmartDevice::getStatus();
  status += ", Current: " + to_string(currentTemperature) + " C";
  status += ", Target: " + to_string(targetTemperature) + " C";
  if (isScheduled)
  {
    status += ", Scheduled: " + scheduleTime;
  }
  return status;
}

string Thermostat::generateReport() const
{
  return "Thermostat " + name + " is " + (isOn ? "On" : "Off") + ", Target temp " + to_string(targetTemperature) + " C.";
}

string Thermostat::getType() const
{
  return "Thermostat";
}

void Thermostat::setTargetTemperature(double temp)
{
  targetTemperature = temp;
}

double Thermostat::getTargetTemperature() const
{
  return targetTemperature;
}

double Thermostat::getCurrentTemperature() const
{
  return currentTemperature;
}

void Thermostat::setCurrentTemperature(double temp)
{
  currentTemperature = temp;
}

void Thermostat::schedule(const string &time)
{
  scheduleTime = time;
  isScheduled = true;
}

void Thermostat::cancelSchedule()
{
  scheduleTime.clear();
  isScheduled = false;
}

bool Thermostat::hasSchedule() const
{
  return isScheduled;
}

string Thermostat::getScheduleTime() const
{
  return scheduleTime;
}

string Thermostat::serialize() const
{
  return "Thermostat;" + to_string(id) + ";" + name + ";" + (isOn ? "1" : "0") + ";" + to_string(powerUsage) + ";" + to_string(currentTemperature) + ";" + to_string(targetTemperature) + ";" + (isScheduled ? scheduleTime : "");
}
