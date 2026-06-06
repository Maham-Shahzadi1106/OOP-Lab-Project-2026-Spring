#include "EnergyLog.h"
#include <iostream>
#include <sstream>
using namespace std;
EnergyLog::EnergyLog()
    : entryCount(0)
{
}

EnergyLog::~EnergyLog()
{
}

bool EnergyLog::addEntry(const string &deviceName, const string &date, double powerConsumed)
{
  if (entryCount >= 200)
  {
    return false;
  }
  entries[entryCount].deviceName = deviceName;
  entries[entryCount].date = date;
  entries[entryCount].powerConsumed = powerConsumed;
  entryCount++;
  return true;
}

void EnergyLog::displayLogs() const
{
  if (entryCount == 0)
  {
    cout << "No energy logs available." << endl;
    return;
  }
  cout << "Energy Usage Logs:" << endl;
  for (int i = 0; i < entryCount; ++i)
  {
    cout << "  " << entries[i].date << " - " << entries[i].deviceName
         << " consumed " << entries[i].powerConsumed << " W" << endl;
  }
}

string EnergyLog::serialize() const
{
  string content;
  for (int i = 0; i < entryCount; ++i)
  {
    content += entries[i].deviceName + ";" + entries[i].date + ";" + to_string(entries[i].powerConsumed) + "\n";
  }
  return content;
}

bool EnergyLog::loadFromLine(const string &line)
{
  istringstream stream(line);
  string deviceName;
  string date;
  string powerString;
  if (!getline(stream, deviceName, ';'))
  {
    return false;
  }
  if (!getline(stream, date, ';'))
  {
    return false;
  }
  if (!getline(stream, powerString))
  {
    return false;
  }
  double power = 0.0;
  power = stod(powerString);
  return addEntry(deviceName, date, power);
}
