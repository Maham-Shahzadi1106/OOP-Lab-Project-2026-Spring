CXX = g++
CXXFLAGS = -Wall -std=c++11 -I src

SOURCES = main.cpp \
	impl/SmartDevice.cpp \
	impl/SmartLight.cpp \
	impl/Thermostat.cpp \
	impl/SecurityCamera.cpp \
	impl/SmartAppliance.cpp \
	impl/SmartLock.cpp \
	impl/SmartSpeaker.cpp \
	impl/SmartOutlet.cpp \
	impl/SmartDoorbell.cpp \
	impl/Room.cpp \
	impl/Automation.cpp \
	impl/EnergyLog.cpp \
	impl/SmartHome.cpp \
	impl/UserAuthentication.cpp
TARGET = SmartHome

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
