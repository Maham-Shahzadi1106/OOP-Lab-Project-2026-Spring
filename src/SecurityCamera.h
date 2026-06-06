#ifndef SECURITYCAMERA_H
#define SECURITYCAMERA_H

#include "SmartDevice.h"
#include <string>
using namespace std;
class SecurityCamera : public SmartDevice
{
private:
  string resolution;
  bool isRecording;

public:
  SecurityCamera(int id, const string &name, double powerUsage, const string &resolution = "1080p", bool isRecording = false);
  virtual ~SecurityCamera();
  void toggle() override;
  string getStatus() const override;
  string generateReport() const override;
  string getType() const override;
  void setResolution(const string &resolution);
  string getResolution() const;
  void setRecording(bool recording);
  bool getRecording() const;
  string serialize() const override;
};

#endif // SECURITYCAMERA_H
