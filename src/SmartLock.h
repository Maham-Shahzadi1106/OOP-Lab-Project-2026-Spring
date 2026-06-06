#ifndef SMARTLOCK_H
#define SMARTLOCK_H

#include "SmartDevice.h"
#include <string>
using namespace std;
class SmartLock : public SmartDevice
{
private:
  bool isLocked;
  string accessCode;

public:
  SmartLock(int id, const string &name, double powerUsage, const string &accessCode = "0000", bool isLocked = true);
  virtual ~SmartLock();
  void toggle() override;
  string getStatus() const override;
  string generateReport() const override;
  string getType() const override;
  void lock();
  void unlock();
  bool getLocked() const;
  bool verifyCode(const string &code) const;
  void setAccessCode(const string &code);
  string getAccessCode() const;
  string serialize() const override;
};

#endif // SMARTLOCK_H
