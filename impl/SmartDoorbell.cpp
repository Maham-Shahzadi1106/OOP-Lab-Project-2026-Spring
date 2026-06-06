#include "SmartDoorbell.h"
using namespace std;
SmartDoorbell::SmartDoorbell(int id, const string &name, double powerUsage, const string &lastVisitor, int ringCount)
    : SmartDevice(id, name, powerUsage), lastVisitor(lastVisitor), ringCount(ringCount)
{
}

SmartDoorbell::~SmartDoorbell()
{
}

void SmartDoorbell::toggle()
{
  isOn = !isOn;
}

string SmartDoorbell::getStatus() const
{
  string status = SmartDevice::getStatus();
  status += ", Last Visitor: " + lastVisitor;
  status += ", Rings: " + to_string(ringCount);
  return status;
}

string SmartDoorbell::generateReport() const
{
  return "SmartDoorbell " + name + " is " + (isOn ? "On" : "Off") + ", last visitor " + lastVisitor + ".";
}

string SmartDoorbell::getType() const
{
  return "SmartDoorbell";
}

void SmartDoorbell::ring(const string &visitor)
{
  lastVisitor = visitor;
  ringCount++;
}

string SmartDoorbell::getLastVisitor() const
{
  return lastVisitor;
}

int SmartDoorbell::getRingCount() const
{
  return ringCount;
}

string SmartDoorbell::serialize() const
{
  return "SmartDoorbell;" + to_string(id) + ";" + name + ";" + (isOn ? "1" : "0") + ";" + to_string(powerUsage) + ";" + lastVisitor + ";" + to_string(ringCount);
}
