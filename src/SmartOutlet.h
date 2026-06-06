#ifndef SMARTOUTLET_H
#define SMARTOUTLET_H

#include "SmartDevice.h"
#include <string>
using namespace std;
class SmartOutlet : public SmartDevice
{
private:
  double maxLoad;
  string connectedDevice;

public:
  SmartOutlet(int id, const string &name, double powerUsage, double maxLoad = 200.0, const string &connectedDevice = "None");
  virtual ~SmartOutlet();
  void toggle() override;
  string getStatus() const override;
  string generateReport() const override;
  string getType() const override;
  void setMaxLoad(double load);
  double getMaxLoad() const;
  void setConnectedDevice(const string &deviceName);
  string getConnectedDevice() const;
  string serialize() const override;
};

#endif // SMARTOUTLET_H
