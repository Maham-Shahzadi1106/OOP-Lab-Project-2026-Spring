#include <iostream>
#include <string>
#include <limits>
#include "src/SmartHome.h"
#include "src/SmartLight.h"
#include "src/Thermostat.h"
#include "src/SecurityCamera.h"
#include "src/SmartAppliance.h"
#include "src/SmartLock.h"
#include "src/SmartSpeaker.h"
#include "src/SmartOutlet.h"
#include "src/SmartDoorbell.h"
using namespace std;
void displayMenu()
{
  cout << "\nSmart Home Simulator Menu" << endl;
  cout << "1. Create a new room" << endl;
  cout << "2. Register a new device" << endl;
  cout << "3. View rooms and devices" << endl;
  cout << "4. Assign device to room" << endl;
  cout << "5. Toggle device power" << endl;
  cout << "6. Create automation rule" << endl;
  cout << "7. Run automation rules now" << endl;
  cout << "8. Log device energy usage" << endl;
  cout << "9. View energy report" << endl;
  cout << "10. Lock/unlock SmartLock" << endl;
  cout << "11. SmartSpeaker voice command" << endl;
  cout << "12. Save and exit" << endl;
  cout << "13. Exit without saving" << endl;
  cout << "Select option: ";
}

int chooseDeviceType()
{
  cout << "Device types:" << endl;
  cout << "1. SmartLight" << endl;
  cout << "2. Thermostat" << endl;
  cout << "3. SecurityCamera" << endl;
  cout << "4. SmartAppliance" << endl;
  cout << "5. SmartLock" << endl;
  cout << "6. SmartSpeaker" << endl;
  cout << "7. SmartOutlet" << endl;
  cout << "8. SmartDoorbell" << endl;
  cout << "Choose device type: ";
  int selection;
  cin >> selection;
  return selection;
}

SmartDevice *createDevice(SmartHome &home)
{
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  int typeChoice = chooseDeviceType();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  string name;
  double power;
  cout << "Enter device name: ";
  getline(cin, name);
  cout << "Enter power usage (in watts): ";
  cin >> power;
  int id = home.generateDeviceId();
  switch (typeChoice)
  {
  case 1:
  {
    int brightness;
    bool colorMode;
    cout << "Enter brightness (0-100): ";
    cin >> brightness;
    cout << "Enable color mode? (1 = yes, 0 = no): ";
    cin >> colorMode;
    return new SmartLight(id, name, power, brightness, colorMode);
  }
  case 2:
  {
    double currentTemp;
    double targetTemp;
    cout << "Enter current temperature: ";
    cin >> currentTemp;
    cout << "Enter target temperature: ";
    cin >> targetTemp;
    return new Thermostat(id, name, power, currentTemp, targetTemp);
  }
  case 3:
  {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string resolution;
    cout << "Enter resolution (e.g. 1080p): ";
    getline(cin, resolution);
    bool recording = false;
    cout << "Start recording by default? (1 = yes, 0 = no): ";
    cin >> recording;
    return new SecurityCamera(id, name, power, resolution, recording);
  }
  case 4:
  {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string applianceType;
    cout << "Enter appliance type (e.g. Washer, Fridge): ";
    getline(cin, applianceType);
    bool running = false;
    cout << "Start appliance immediately? (1 = yes, 0 = no): ";
    cin >> running;
    return new SmartAppliance(id, name, power, applianceType, running);
  }
  case 5:
  {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string accessCode;
    cout << "Set access code: ";
    getline(cin, accessCode);
    bool locked = true;
    cout << "Leave locked after creation? (1 = yes, 0 = no): ";
    cin >> locked;
    return new SmartLock(id, name, power, accessCode, locked);
  }
  case 6:
  {
    int volume;
    cout << "Set starting volume (0-100): ";
    cin >> volume;
    return new SmartSpeaker(id, name, power, volume);
  }
  case 7:
  {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    double maxLoad;
    string deviceName;
    cout << "Enter maximum load (watts): ";
    cin >> maxLoad;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter connected device description: ";
    getline(cin, deviceName);
    return new SmartOutlet(id, name, power, maxLoad, deviceName);
  }
  case 8:
  {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string visitor;
    cout << "Enter last visitor name: ";
    getline(cin, visitor);
    int ringCount;
    cout << "Enter initial ring count: ";
    cin >> ringCount;
    return new SmartDoorbell(id, name, power, visitor, ringCount);
  }
  default:
    cout << "Invalid device type selected." << endl;
    return nullptr;
  }
}

int main()
{
  SmartHome home;
  home.loadData();
  cout << "Smart Home Simulator started. Current time: " << home.getCurrentTime() << endl;
  bool running = true;

  while (running)
  {
    displayMenu();
    int option;
    cin >> option;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (option)
    {
    case 1:
    {
      string roomName;
      cout << "Enter new room name: ";
      getline(cin, roomName);
      if (home.createRoom(roomName))
      {
        cout << "Room created: " << roomName << endl;
      }
      else
      {
        cout << "Room could not be created or already exists." << endl;
      }
      break;
    }
    case 2:
    {
      SmartDevice *device = createDevice(home);
      if (device != nullptr)
      {
        string roomName;
        cout << "Enter room name to assign device: ";
        getline(cin, roomName);
        if (roomName.empty())
        {
          roomName = "Ungrouped";
        }
        if (home.registerDevice(device, roomName))
        {
          cout << "Device registered successfully." << endl;
        }
        else
        {
          cout << "Failed to register device." << endl;
          delete device;
        }
      }
      break;
    }
    case 3:
      home.displayRooms();
      home.displayAllDevices();
      break;
    case 4:
    {
      int deviceId;
      string roomName;
      cout << "Enter device ID to reassign: ";
      cin >> deviceId;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Enter destination room name: ";
      getline(cin, roomName);
      if (home.assignDeviceToRoom(deviceId, roomName))
      {
        cout << "Device moved to " << roomName << "." << endl;
      }
      else
      {
        cout << "Device move failed." << endl;
      }
      break;
    }
    case 5:
    {
      int deviceId;
      cout << "Enter device ID to toggle: ";
      cin >> deviceId;
      if (home.toggleDevice(deviceId))
      {
        cout << "Device toggled successfully." << endl;
      }
      else
      {
        cout << "Device not found." << endl;
      }
      break;
    }
    case 6:
    {
      int targetId;
      string description;
      string triggerTime;
      string action;
      cout << "Enter automation description: ";
      getline(cin, description);
      cout << "Enter trigger time (HH:MM): ";
      getline(cin, triggerTime);
      cout << "Enter action (toggle/lock/unlock): ";
      getline(cin, action);
      cout << "Enter target device ID: ";
      cin >> targetId;
      Automation *automation = new Automation(home.generateDeviceId(), description, triggerTime, action, targetId);
      if (home.addAutomation(automation))
      {
        cout << "Automation rule created." << endl;
      }
      else
      {
        cout << "Failed to create automation." << endl;
        delete automation;
      }
      break;
    }
    case 7:
      home.executeAutomations();
      cout << "Automation rules executed for current time." << endl;
      break;
    case 8:
    {
      int deviceId;
      double usage;
      cout << "Enter device ID for energy log: ";
      cin >> deviceId;
      SmartDevice *device = home.findDeviceById(deviceId);
      if (device != nullptr)
      {
        cout << "Enter power consumed (W): ";
        cin >> usage;
        home.getEnergyLog()->addEntry(device->getName(), home.getCurrentDate(), usage);
        cout << "Energy usage logged." << endl;
      }
      else
      {
        cout << "Device not found." << endl;
      }
      break;
    }
    case 9:
      home.getEnergyLog()->displayLogs();
      break;
    case 10:
    {
      int deviceId;
      cout << "Enter SmartLock device ID: ";
      cin >> deviceId;
      SmartDevice *device = home.findDeviceById(deviceId);
      SmartLock *lockDevice = dynamic_cast<SmartLock *>(device);
      if (lockDevice == nullptr)
      {
        cout << "Device is not a SmartLock." << endl;
        break;
      }
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      string code;
      cout << "Enter access code: ";
      getline(cin, code);
      if (!lockDevice->verifyCode(code))
      {
        cout << "Access denied." << endl;
        break;
      }
      lockDevice->toggle();
      cout << "SmartLock state toggled." << endl;
      break;
    }
    case 11:
    {
      int deviceId;
      string command;
      cout << "Enter SmartSpeaker device ID: ";
      cin >> deviceId;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      SmartDevice *device = home.findDeviceById(deviceId);
      SmartSpeaker *speaker = dynamic_cast<SmartSpeaker *>(device);
      if (speaker == nullptr)
      {
        cout << "Device is not a SmartSpeaker." << endl;
        break;
      }
      cout << "Enter voice command: ";
      getline(cin, command);
      speaker->playVoiceCommand(command);
      cout << "Voice command recorded: " << command << endl;
      break;
    }
    case 12:
      home.saveData();
      cout << "Data saved. Exiting." << endl;
      running = false;
      break;
    case 13:
      cout << "Exiting without saving." << endl;
      running = false;
      break;
    default:
      cout << "Invalid option selected." << endl;
      break;
    }
  }

  return 0;
}
