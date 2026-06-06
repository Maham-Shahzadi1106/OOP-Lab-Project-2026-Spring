#include "SmartSpeaker.h"
using namespace std;
SmartSpeaker::SmartSpeaker(int id, const string &name, double powerUsage, int volume)
    : SmartDevice(id, name, powerUsage), volume(volume), lastCommand("None")
{
}

SmartSpeaker::~SmartSpeaker()
{
}

void SmartSpeaker::toggle()
{
  isOn = !isOn;
}

string SmartSpeaker::getStatus() const
{
  string status = SmartDevice::getStatus();
  status += ", Volume: " + to_string(volume);
  return status;
}

string SmartSpeaker::generateReport() const
{
  return "SmartSpeaker " + name + " is " + (isOn ? "On" : "Off") + ", last voice command: " + lastCommand + ".";
}

string SmartSpeaker::getType() const
{
  return "SmartSpeaker";
}

void SmartSpeaker::setVolume(int level)
{
  if (level < 0)
  {
    volume = 0;
  }
  else if (level > 100)
  {
    volume = 100;
  }
  else
  {
    volume = level;
  }
}

int SmartSpeaker::getVolume() const
{
  return volume;
}

void SmartSpeaker::playVoiceCommand(const string &command)
{
  lastCommand = command;
}

string SmartSpeaker::getLastCommand() const
{
  return lastCommand;
}

string SmartSpeaker::serialize() const
{
  return "SmartSpeaker;" + to_string(id) + ";" + name + ";" + (isOn ? "1" : "0") + ";" + to_string(powerUsage) + ";" + to_string(volume) + ";" + lastCommand;
}
