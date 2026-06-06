#include "Automation.h"
#include "SmartHome.h"
#include "SmartLock.h"
#include <iostream>
using namespace std;
Automation::Automation(int id, const string &description, const string &triggerTime,
                       const string &action, int targetDeviceId)
    : id(id), description(description), triggerTime(triggerTime), action(action),
      targetDeviceId(targetDeviceId), active(true)
{
}

Automation::~Automation()
{
}

int Automation::getId() const
{
  return id;
}

string Automation::getDescription() const
{
  return description;
}

string Automation::getTriggerTime() const
{
  return triggerTime;
}

string Automation::getAction() const
{
  return action;
}

int Automation::getTargetDeviceId() const
{
  return targetDeviceId;
}

bool Automation::isActive() const
{
  return active;
}

void Automation::setActive(bool value)
{
  active = value;
}

bool Automation::matchesTime(const string &currentTime) const
{
  return active && !triggerTime.empty() && currentTime == triggerTime;
}

void Automation::execute(SmartHome *home) const
{
  if (home == nullptr)
  {
    return;
  }
  SmartDevice *device = home->findDeviceById(targetDeviceId);
  if (device == nullptr)
  {
    return;
  }
  if (action == "toggle")
  {
    device->toggle();
  }
  else if (action == "lock")
  {
    SmartLock *lockDevice = dynamic_cast<SmartLock *>(device);
    if (lockDevice)
    {
      lockDevice->lock();
    }
  }
  else if (action == "unlock")
  {
    SmartLock *lockDevice = dynamic_cast<SmartLock *>(device);
    if (lockDevice)
    {
      lockDevice->unlock();
    }
  }
}

string Automation::serialize() const
{
  return to_string(id) + ";" + description + ";" + triggerTime + ";" + action + ";" + to_string(targetDeviceId) + ";" + (active ? "1" : "0");
}
