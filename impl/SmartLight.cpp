#include "SmartLight.h"
using namespace std;
SmartLight::SmartLight(int id, const string &name, double powerUsage, int brightness, bool colorMode)
    : SmartDevice(id, name, powerUsage), brightness(brightness), colorMode(colorMode)
{
}

SmartLight::~SmartLight()
{
}

void SmartLight::toggle()
{
  isOn = !isOn;
}

string SmartLight::getStatus() const
{
  string status = SmartDevice::getStatus();
  status += ", Brightness: " + to_string(brightness) + "%";
  status += ", Color Mode: ";
  status += colorMode ? "Enabled" : "Disabled";
  return status;
}

string SmartLight::generateReport() const
{
  return "SmartLight " + name + " is " + (isOn ? "On" : "Off") + ".";
}

string SmartLight::getType() const
{
  return "SmartLight";
}

void SmartLight::setBrightness(int level)
{
  if (level < 0)
  {
    brightness = 0;
  }
  else if (level > 100)
  {
    brightness = 100;
  }
  else
  {
    brightness = level;
  }
}

int SmartLight::getBrightness() const
{
  return brightness;
}

void SmartLight::setColorMode(bool enabled)
{
  colorMode = enabled;
}

bool SmartLight::getColorMode() const
{
  return colorMode;
}

string SmartLight::serialize() const
{
  return "SmartLight;" + to_string(id) + ";" + name + ";" + (isOn ? "1" : "0") + ";" + to_string(powerUsage) + ";" + to_string(brightness) + ";" + (colorMode ? "1" : "0");
}
