#ifndef AUTOMATION_H
#define AUTOMATION_H

#include <string>
using namespace std;
class SmartHome;

class Automation
{
private:
  int id;
  string description;
  string triggerTime;
  string action;
  int targetDeviceId;
  bool active;

public:
  Automation(int id, const string &description, const string &triggerTime,
             const string &action, int targetDeviceId);
  ~Automation();
  int getId() const;
  string getDescription() const;
  string getTriggerTime() const;
  string getAction() const;
  int getTargetDeviceId() const;
  bool isActive() const;
  void setActive(bool value);
  bool matchesTime(const string &currentTime) const;
  void execute(SmartHome *home) const;
  string serialize() const;
};

#endif // AUTOMATION_H
