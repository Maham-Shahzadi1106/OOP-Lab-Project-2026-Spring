#include "SecurityCamera.h"
using namespace std;
SecurityCamera::SecurityCamera(int id, const string &name, double powerUsage, const string &resolution, bool isRecording)
    : SmartDevice(id, name, powerUsage), resolution(resolution), isRecording(isRecording)
{
}

SecurityCamera::~SecurityCamera()
{
}

void SecurityCamera::toggle()
{
  isOn = !isOn;
}

string SecurityCamera::getStatus() const
{
  string status = SmartDevice::getStatus();
  status += ", Resolution: " + resolution;
  status += ", Recording: ";
  status += isRecording ? "Yes" : "No";
  return status;
}

string SecurityCamera::generateReport() const
{
  return "SecurityCamera " + name + " is " + (isOn ? "On" : "Off") + ", Recording " + (isRecording ? "Active" : "Inactive") + ".";
}

string SecurityCamera::getType() const
{
  return "SecurityCamera";
}

void SecurityCamera::setResolution(const string &res)
{
  resolution = res;
}

string SecurityCamera::getResolution() const
{
  return resolution;
}

void SecurityCamera::setRecording(bool recording)
{
  isRecording = recording;
}

bool SecurityCamera::getRecording() const
{
  return isRecording;
}

string SecurityCamera::serialize() const
{
  return "SecurityCamera;" + to_string(id) + ";" + name + ";" + (isOn ? "1" : "0") + ";" + to_string(powerUsage) + ";" + resolution + ";" + (isRecording ? "1" : "0");
}
