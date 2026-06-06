#ifndef SMARTSPEAKER_H
#define SMARTSPEAKER_H

#include "SmartDevice.h"
#include <string>
using namespace std;
class SmartSpeaker : public SmartDevice
{
private:
  int volume;
  string lastCommand;

public:
  SmartSpeaker(int id, const string &name, double powerUsage, int volume = 50);
  virtual ~SmartSpeaker();
  void toggle() override;
  string getStatus() const override;
  string generateReport() const override;
  string getType() const override;
  void setVolume(int level);
  int getVolume() const;
  void playVoiceCommand(const string &command);
  string getLastCommand() const;
  string serialize() const override;
};

#endif // SMARTSPEAKER_H
