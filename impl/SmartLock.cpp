#include "SmartLock.h"
using namespace std;
SmartLock::SmartLock(int id, const string &name, double powerUsage, const string &accessCode, bool isLocked)
    : SmartDevice(id, name, powerUsage), isLocked(isLocked), accessCode(accessCode)
{
}

SmartLock::~SmartLock()
{
}

void SmartLock::toggle()
{
  if (isLocked)
  {
    unlock();
  }
  else
  {
    lock();
  }
}

string SmartLock::getStatus() const
{
  string status = SmartDevice::getStatus();
  status += ", Locked: ";
  status += isLocked ? "Yes" : "No";
  return status;
}

string SmartLock::generateReport() const
{
  return "SmartLock " + name + " is " + (isLocked ? "Locked" : "Unlocked") + ".";
}

string SmartLock::getType() const
{
  return "SmartLock";
}

void SmartLock::lock()
{
  isLocked = true;
}

void SmartLock::unlock()
{
  isLocked = false;
}

bool SmartLock::getLocked() const
{
  return isLocked;
}

bool SmartLock::verifyCode(const string &code) const
{
  return code == accessCode;
}

void SmartLock::setAccessCode(const string &code)
{
  accessCode = code;
}

string SmartLock::getAccessCode() const
{
  return accessCode;
}

string SmartLock::serialize() const
{
  return "SmartLock;" + to_string(id) + ";" + name + ";" + (isOn ? "1" : "0") + ";" + to_string(powerUsage) + ";" + (isLocked ? "1" : "0") + ";" + accessCode;
}
