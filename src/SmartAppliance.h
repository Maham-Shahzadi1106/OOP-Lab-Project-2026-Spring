#ifndef SMARTAPPLIANCE_H
#define SMARTAPPLIANCE_H

#include "SmartDevice.h"
#include <string>
using namespace std;
class SmartAppliance : public SmartDevice
{
private:
  string applianceType;
  bool isRunning;

public:
  SmartAppliance(int id, const string &name, double powerUsage, const string &applianceType = "General", bool isRunning = false);
  virtual ~SmartAppliance();
  void toggle() override;
  string getStatus() const override;
  string generateReport() const override;
  string getType() const override;
  void setApplianceType(const string &type);
  string getApplianceType() const;
  void setRunning(bool running);
  bool getRunning() const;
  string serialize() const override;
};

#endif // SMARTAPPLIANCE_H
