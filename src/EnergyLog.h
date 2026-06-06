#ifndef ENERGYLOG_H
#define ENERGYLOG_H

#include <string>
using namespace std;
class EnergyLog
{
public:
  struct Entry
  {
    string deviceName;
    string date;
    double powerConsumed;
  };

private:
  Entry entries[200];
  int entryCount;

public:
  EnergyLog();
  ~EnergyLog();
  bool addEntry(const string &deviceName, const string &date, double powerConsumed);
  void displayLogs() const;
  string serialize() const;
  bool loadFromLine(const string &line);
};

#endif // ENERGYLOG_H
