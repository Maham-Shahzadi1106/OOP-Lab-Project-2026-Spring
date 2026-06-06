#ifndef SMARTDEVICE_H
#define SMARTDEVICE_H

#include <string>
#include <iostream>
using namespace std;
class SmartDevice
{
protected:
  int id;
  string name;
  bool isOn;
  double powerUsage;

public:
  SmartDevice(int id, const string &name, double powerUsage);
  virtual ~SmartDevice();

  virtual void toggle() = 0;
  virtual string getStatus() const;
  virtual string generateReport() const = 0;
  virtual string getType() const = 0;

  int getId() const;
  string getName() const;
  void setName(const string &newName);

  bool isPoweredOn() const;
  void setPowerUsage(double usage);
  double getPowerUsage() const;

  bool operator==(const SmartDevice &other) const;
  friend ostream &operator<<(ostream &os, const SmartDevice &device);

  virtual string serialize() const = 0;
};

#endif // SMARTDEVICE_H
