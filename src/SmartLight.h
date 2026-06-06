#ifndef SMARTLIGHT_H
#define SMARTLIGHT_H

#include "SmartDevice.h"
using namespace std;
class SmartLight : public SmartDevice
{
private:
  int brightness;
  bool colorMode;

public:
  SmartLight(int id, const string &name, double powerUsage, int brightness = 100, bool colorMode = false);
  virtual ~SmartLight();
  void toggle() override;
  string getStatus() const override;
  string generateReport() const override;
  string getType() const override;
  void setBrightness(int level);
  int getBrightness() const;
  void setColorMode(bool enabled);
  bool getColorMode() const;
  string serialize() const override;
};

#endif // SMARTLIGHT_H
#ifndef SMARTLIGHT_H
#define SMARTLIGHT_H

#include "SmartDevice.h"

class SmartLight : public SmartDevice
{
private:
  int brightness;
  bool colorMode;

public:
  SmartLight(int id, const string &name, double powerUsage, int brightness = 100, bool colorMode = false);
  virtual ~SmartLight();
  void toggle() override;
  string getStatus() const override;
  string generateReport() const override;
  string getType() const override;
  void setBrightness(int level);
  int getBrightness() const;
  void setColorMode(bool enabled);
  bool getColorMode() const;
  string serialize() const override;
};

#endif // SMARTLIGHT_H
