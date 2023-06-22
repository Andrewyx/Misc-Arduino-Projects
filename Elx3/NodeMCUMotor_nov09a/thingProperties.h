// Code generated by Arduino IoT Cloud, DO NOT EDIT.

#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>


const char THING_ID[]           = "11e15862-5152-4a08-80bc-c20877b01491";
const char DEVICE_LOGIN_NAME[]  = "4c94df90-b107-42a7-9224-8b63ac1f1ed8";

const char SSID[]               = SECRET_SSID;    // Network SSID (name)
const char PASS[]               = SECRET_PASS;    // Network password (use for WPA, or use as key for WEP)
const char DEVICE_KEY[]  = SECRET_DEVICE_KEY;    // Secret device password

void onServoposleftChange();
void onSpeedadjustChange();
void onServoposrightChange();

bool servoposleft;
int speedadjust;
bool servoposright;

void initProperties(){

  ArduinoCloud.setBoardId(DEVICE_LOGIN_NAME);
  ArduinoCloud.setSecretDeviceKey(DEVICE_KEY);
  ArduinoCloud.setThingId(THING_ID);
  ArduinoCloud.addProperty(servoposleft, READWRITE, ON_CHANGE, onServoposleftChange);
  ArduinoCloud.addProperty(speedadjust, READWRITE, ON_CHANGE, onSpeedadjustChange);
  ArduinoCloud.addProperty(servoposright, READWRITE, ON_CHANGE, onServoposrightChange);

}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);