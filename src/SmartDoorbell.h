#ifndef SMARTDOORBELL_H
#define SMARTDOORBELL_H

#include "SmartDevice.h"
#include <string>
using namespace std;
class SmartDoorbell : public SmartDevice
{
private:
  string lastVisitor;
  int ringCount;

public:
  SmartDoorbell(int id, const string &name, double powerUsage, const string &lastVisitor = "None", int ringCount = 0);
  virtual ~SmartDoorbell();
  void toggle() override;
  string getStatus() const override;
  string generateReport() const override;
  string getType() const override;
  void ring(const string &visitor);
  string getLastVisitor() const;
  int getRingCount() const;
  string serialize() const override;
};

#endif // SMARTDOORBELL_H
