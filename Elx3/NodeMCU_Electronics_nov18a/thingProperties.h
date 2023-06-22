// Code generated by Arduino IoT Cloud, DO NOT EDIT.

#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>

const char DEVICE_LOGIN_NAME[]  = "dc42e347-38ae-4e1e-abf8-3d665c92538f";

const char SSID[]               = SECRET_SSID;    // Network SSID (name)
const char PASS[]               = SECRET_OPTIONAL_PASS;    // Network password (use for WPA, or use as key for WEP)
const char DEVICE_KEY[]  = SECRET_DEVICE_KEY;    // Secret device password

void onPlaystateChange();

CloudMotionSensor motionCloud;
CloudTemperatureSensor temperature;
int distance;
int lDRCloud;
bool playstate;

void initProperties(){

  ArduinoCloud.setBoardId(DEVICE_LOGIN_NAME);
  ArduinoCloud.setSecretDeviceKey(DEVICE_KEY);
  ArduinoCloud.addProperty(motionCloud, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(temperature, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(distance, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(lDRCloud, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(playstate, READWRITE, ON_CHANGE, onPlaystateChange, 1);

}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);
