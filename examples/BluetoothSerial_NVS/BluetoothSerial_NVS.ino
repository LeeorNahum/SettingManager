#include <BluetoothSerial.h>
#include <ArduinoNvs.h>
#include <SettingManager.h>

BluetoothSerial SerialBT;

String bluetooth_name = "Bluetooth Serial";

void startBluetooth() {
  SerialBT.end();
  SerialBT.begin(bluetooth_name.c_str());
}

void bluetoothCallback(String name) {
  NVS.setString("bluetooth_name", bluetooth_name);

  startBluetooth();
}

Setting<String> BluetoothName("name", &bluetooth_name, bluetoothCallback);

SettingManager settingManager(&BluetoothName);

void setup() {
  Serial.begin(115200);

  NVS.begin();
  bluetooth_name = NVS.getString("bluetooth_name");

  startBluetooth();
}

void loop() {
  if (Serial.available()) {
    settingManager.updateSettings(Serial.readString());
  }

  if (SerialBT.available()) {
    settingManager.updateSettings(SerialBT.readString());
  }

  delay(1000);
}