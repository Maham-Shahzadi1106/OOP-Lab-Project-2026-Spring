#include "SmartHome.h"
#include "SmartDevice.h"
#include "SmartLight.h"
#include "Thermostat.h"
#include "SecurityCamera.h"
#include "SmartAppliance.h"
#include "SmartLock.h"
#include "SmartSpeaker.h"
#include "SmartOutlet.h"
#include "SmartDoorbell.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <ctime>
using namespace std;
SmartHome::SmartHome()
    : roomCount(0), automationCount(0), energyLog(new EnergyLog()), auth(new UserAuthentication("1234")), nextDeviceId(1)
{
  for (int i = 0; i < 20; ++i)
  {
    rooms[i] = nullptr;
  }
  for (int i = 0; i < 50; ++i)
  {
    automations[i] = nullptr;
  }
  createRoom("Ungrouped");
}

SmartHome::~SmartHome()
{
  for (int i = 0; i < roomCount; ++i)
  {
    delete rooms[i];
    rooms[i] = nullptr;
  }
  for (int i = 0; i < automationCount; ++i)
  {
    delete automations[i];
    automations[i] = nullptr;
  }
  delete energyLog;
  delete auth;
}

bool SmartHome::createRoom(const string &roomName)
{
  if (roomCount >= 20 || findRoom(roomName) != nullptr)
  {
    return false;
  }
  rooms[roomCount++] = new Room(roomName);
  return true;
}

bool SmartHome::deleteRoom(const string &roomName)
{
  if (roomName == "Ungrouped")
  {
    return false;
  }
  for (int i = 0; i < roomCount; ++i)
  {
    if (rooms[i] && rooms[i]->getName() == roomName)
    {
      delete rooms[i];
      for (int j = i; j < roomCount - 1; ++j)
      {
        rooms[j] = rooms[j + 1];
      }
      rooms[roomCount - 1] = nullptr;
      roomCount--;
      return true;
    }
  }
  return false;
}

Room *SmartHome::findRoom(const string &roomName) const
{
  for (int i = 0; i < roomCount; ++i)
  {
    if (rooms[i] && rooms[i]->getName() == roomName)
    {
      return rooms[i];
    }
  }
  return nullptr;
}

void SmartHome::displayRooms() const
{
  cout << "Rooms:" << endl;
  for (int i = 0; i < roomCount; ++i)
  {
    if (rooms[i])
    {
      cout << "  " << rooms[i]->getName() << " (" << rooms[i]->getDeviceCount() << " devices)" << endl;
    }
  }
}

void SmartHome::displayAllDevices() const
{
  for (int i = 0; i < roomCount; ++i)
  {
    if (rooms[i])
    {
      rooms[i]->displayDevices();
    }
  }
}

SmartDevice *SmartHome::findDeviceById(int deviceId) const
{
  for (int i = 0; i < roomCount; ++i)
  {
    if (rooms[i])
    {
      SmartDevice *device = rooms[i]->findDeviceById(deviceId);
      if (device)
      {
        return device;
      }
    }
  }
  return nullptr;
}

bool SmartHome::registerDevice(SmartDevice *device, const string &roomName)
{
  if (device == nullptr)
  {
    return false;
  }
  Room *room = findRoom(roomName);
  if (room == nullptr)
  {
    createRoom(roomName);
    room = findRoom(roomName);
  }
  return room->addDevice(device);
}

bool SmartHome::removeDevice(int deviceId)
{
  for (int i = 0; i < roomCount; ++i)
  {
    if (rooms[i] && rooms[i]->removeDevice(deviceId))
    {
      return true;
    }
  }
  return false;
}

bool SmartHome::assignDeviceToRoom(int deviceId, const string &roomName)
{
  Room *currentRoom = nullptr;
  SmartDevice *device = nullptr;
  for (int i = 0; i < roomCount; ++i)
  {
    if (rooms[i])
    {
      SmartDevice *found = rooms[i]->findDeviceById(deviceId);
      if (found)
      {
        currentRoom = rooms[i];
        device = rooms[i]->takeDevice(deviceId);
        break;
      }
    }
  }
  if (device == nullptr)
  {
    return false;
  }
  Room *destination = findRoom(roomName);
  if (destination == nullptr)
  {
    createRoom(roomName);
    destination = findRoom(roomName);
  }
  if (!destination->addDevice(device))
  {
    currentRoom->addDevice(device);
    return false;
  }
  return true;
}

bool SmartHome::controlDevice(int deviceId)
{
  SmartDevice *device = findDeviceById(deviceId);
  if (device == nullptr)
  {
    return false;
  }
  device->toggle();
  return true;
}

bool SmartHome::toggleDevice(int deviceId)
{
  return controlDevice(deviceId);
}

void SmartHome::listDeviceStatus() const
{
  displayAllDevices();
}

bool SmartHome::addAutomation(Automation *automation)
{
  if (automation == nullptr || automationCount >= 50)
  {
    return false;
  }
  automations[automationCount++] = automation;
  return true;
}

void SmartHome::displayAutomations() const
{
  if (automationCount == 0)
  {
    cout << "No automation rules found." << endl;
    return;
  }
  cout << "Automation Rules:" << endl;
  for (int i = 0; i < automationCount; ++i)
  {
    if (automations[i])
    {
      cout << "  " << automations[i]->getId() << ": " << automations[i]->getDescription()
           << " @ " << automations[i]->getTriggerTime()
           << " -> " << automations[i]->getAction() << " device "
           << automations[i]->getTargetDeviceId() << "\n";
    }
  }
}

void SmartHome::executeAutomations()
{
  string currentTime = getCurrentTime();
  for (int i = 0; i < automationCount; ++i)
  {
    if (automations[i] && automations[i]->matchesTime(currentTime))
    {
      automations[i]->execute(this);
    }
  }
}

EnergyLog *SmartHome::getEnergyLog() const
{
  return energyLog;
}

UserAuthentication *SmartHome::getAuthentication() const
{
  return auth;
}

int SmartHome::generateDeviceId()
{
  return nextDeviceId++;
}

void SmartHome::saveData() const
{
  ofstream roomsFile("data/rooms.txt");
  ofstream devicesFile("data/devices.txt");
  ofstream automationFile("data/automations.txt");
  ofstream energyFile("data/energy.txt");
  ofstream authFile("data/auth.txt");

  if (roomsFile.is_open())
  {
    for (int i = 0; i < roomCount; ++i)
    {
      if (rooms[i])
      {
        roomsFile << rooms[i]->getName() << "\n";
      }
    }
  }

  if (devicesFile.is_open())
  {
    for (int i = 0; i < roomCount; ++i)
    {
      if (rooms[i])
      {
        for (int idx = 0; idx < rooms[i]->getDeviceCount(); ++idx)
        {
          SmartDevice *device = rooms[i]->getDeviceAt(idx);
          if (device)
          {
            devicesFile << rooms[i]->getName() << ";" << device->serialize() << "\n";
          }
        }
      }
    }
  }

  if (automationFile.is_open())
  {
    for (int i = 0; i < automationCount; ++i)
    {
      if (automations[i])
      {
        automationFile << automations[i]->serialize() << "\n";
      }
    }
  }

  if (energyFile.is_open())
  {
    energyFile << energyLog->serialize();
  }

  if (authFile.is_open())
  {
    authFile << auth->serialize() << "\n";
  }
}

void SmartHome::loadData()
{
  ifstream roomsFile("data/rooms.txt");
  ifstream devicesFile("data/devices.txt");
  ifstream automationFile("data/automations.txt");
  ifstream energyFile("data/energy.txt");
  ifstream authFile("data/auth.txt");

  if (roomsFile.is_open())
  {
    string roomName;
    while (getline(roomsFile, roomName))
    {
      if (!roomName.empty())
      {
        createRoom(roomName);
      }
    }
  }
  if (devicesFile.is_open())
  {
    string line;
    while (getline(devicesFile, line))
    {
      if (line.empty())
      {
        continue;
      }
      istringstream stream(line);
      string roomName;
      if (!getline(stream, roomName, ';'))
      {
        continue;
      }
      string deviceData;
      getline(stream, deviceData);
      SmartDevice *device = createDeviceFromSerialized(deviceData);
      if (device != nullptr)
      {
        registerDevice(device, roomName);
      }
    }
  }
  if (automationFile.is_open())
  {
    string line;
    while (getline(automationFile, line))
    {
      if (line.empty())
      {
        continue;
      }
      istringstream stream(line);
      string idStr;
      string description;
      string triggerTime;
      string action;
      string targetIdStr;
      string activeStr;
      getline(stream, idStr, ';');
      getline(stream, description, ';');
      getline(stream, triggerTime, ';');
      getline(stream, action, ';');
      getline(stream, targetIdStr, ';');
      getline(stream, activeStr);
      int id = stoi(idStr);
      int targetId = stoi(targetIdStr);
      Automation *automation = new Automation(id, description, triggerTime, action, targetId);
      if (activeStr == "0")
      {
        automation->setActive(false);
      }
      addAutomation(automation);
    }
  }
  if (energyFile.is_open())
  {
    string line;
    while (getline(energyFile, line))
    {
      if (!line.empty())
      {
        energyLog->loadFromLine(line);
      }
    }
  }
  if (authFile.is_open())
  {
    string code;
    getline(authFile, code);
    if (!code.empty())
    {
      auth->setAccessCode(code);
    }
  }
}

SmartDevice *SmartHome::createDeviceFromSerialized(const string &line) const
{
  istringstream stream(line);
  string type;
  if (!getline(stream, type, ';'))
  {
    return nullptr;
  }
  string idStr;
  string name;
  string onState;
  string powerUsageStr;
  if (!getline(stream, idStr, ';'))
  {
    return nullptr;
  }
  if (!getline(stream, name, ';'))
  {
    return nullptr;
  }
  if (!getline(stream, onState, ';'))
  {
    return nullptr;
  }
  if (!getline(stream, powerUsageStr, ';'))
  {
    return nullptr;
  }
  int id = stoi(idStr);
  bool isOn = (onState == "1");
  double powerUsage = stod(powerUsageStr);

  if (type == "SmartLight")
  {
    string brightnessStr;
    string colorModeStr;
    getline(stream, brightnessStr, ';');
    getline(stream, colorModeStr);
    int brightness = stoi(brightnessStr);
    bool colorMode = (colorModeStr == "1");
    SmartLight *device = new SmartLight(id, name, powerUsage, brightness, colorMode);
    if (isOn)
      device->toggle();
    return device;
  }
  if (type == "Thermostat")
  {
    string currentTempStr;
    string targetTempStr;
    string scheduleTime;
    getline(stream, currentTempStr, ';');
    getline(stream, targetTempStr, ';');
    getline(stream, scheduleTime);
    double currentTemp = stod(currentTempStr);
    double targetTemp = stod(targetTempStr);
    Thermostat *device = new Thermostat(id, name, powerUsage, currentTemp, targetTemp);
    if (isOn)
      device->toggle();
    if (!scheduleTime.empty())
    {
      device->schedule(scheduleTime);
    }
    return device;
  }
  if (type == "SecurityCamera")
  {
    string resolution;
    string recordingStr;
    getline(stream, resolution, ';');
    getline(stream, recordingStr);
    bool recording = (recordingStr == "1");
    SecurityCamera *device = new SecurityCamera(id, name, powerUsage, resolution, recording);
    if (isOn)
      device->toggle();
    return device;
  }
  if (type == "SmartAppliance")
  {
    string applianceType;
    string runningStr;
    getline(stream, applianceType, ';');
    getline(stream, runningStr);
    bool running = (runningStr == "1");
    SmartAppliance *device = new SmartAppliance(id, name, powerUsage, applianceType, running);
    if (isOn)
      device->toggle();
    return device;
  }
  if (type == "SmartLock")
  {
    string lockedStr;
    string accessCode;
    getline(stream, lockedStr, ';');
    getline(stream, accessCode);
    bool locked = (lockedStr == "1");
    SmartLock *device = new SmartLock(id, name, powerUsage, accessCode, locked);
    if (isOn)
      device->toggle();
    return device;
  }
  if (type == "SmartSpeaker")
  {
    string volumeStr;
    string lastCommand;
    getline(stream, volumeStr, ';');
    getline(stream, lastCommand);
    int volume = stoi(volumeStr);
    SmartSpeaker *device = new SmartSpeaker(id, name, powerUsage, volume);
    device->playVoiceCommand(lastCommand);
    if (isOn)
      device->toggle();
    return device;
  }
  if (type == "SmartOutlet")
  {
    string maxLoadStr;
    string connectedDevice;
    getline(stream, maxLoadStr, ';');
    getline(stream, connectedDevice);
    double maxLoad = stod(maxLoadStr);
    SmartOutlet *device = new SmartOutlet(id, name, powerUsage, maxLoad, connectedDevice);
    if (isOn)
      device->toggle();
    return device;
  }
  if (type == "SmartDoorbell")
  {
    string lastVisitor;
    string ringCountStr;
    getline(stream, lastVisitor, ';');
    getline(stream, ringCountStr);
    int ringCount = stoi(ringCountStr);
    SmartDoorbell *device = new SmartDoorbell(id, name, powerUsage, lastVisitor, ringCount);
    if (isOn)
      device->toggle();
    return device;
  }
  return nullptr;
}

string SmartHome::getCurrentTime() const
{
  time_t now = time(nullptr);
  tm *local = localtime(&now);
  char buffer[6];
  strftime(buffer, sizeof(buffer), "%H:%M", local);
  return string(buffer);
}

string SmartHome::getCurrentDate() const
{
  time_t now = time(nullptr);
  tm *local = localtime(&now);
  char buffer[20];
  strftime(buffer, sizeof(buffer), "%Y-%m-%d", local);
  return string(buffer);
}
