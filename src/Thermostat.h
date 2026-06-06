#ifndef THERMOSTAT_H
#define THERMOSTAT_H

#include "SmartDevice.h"
#include "Schedulable.h"
#include <string>
using namespace std;
class Thermostat : public SmartDevice, public Schedulable
{
private:
  double currentTemperature;
  double targetTemperature;
  string scheduleTime;
  bool isScheduled;

public:
  Thermostat(int id, const string &name, double powerUsage, double currentTemperature = 22.0, double targetTemperature = 22.0);
  virtual ~Thermostat();
  void toggle() override;
  string getStatus() const override;
  string generateReport() const override;
  string getType() const override;
  void setTargetTemperature(double temp);
  double getTargetTemperature() const;
  double getCurrentTemperature() const;
  void setCurrentTemperature(double temp);
  void schedule(const string &time) override;
  void cancelSchedule() override;
  bool hasSchedule() const;
  string getScheduleTime() const;
  string serialize() const override;
};

#endif // THERMOSTAT_H
