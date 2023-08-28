#include <BluetoothSerial.h>
#include <SettingManager.h>

BluetoothSerial SerialBT;

String bluetooth_name = "Bluetooth Serial";
SettingManager setting_manager;

void startBluetooth() {
  SerialBT.end();
  SerialBT.begin(bluetooth_name.c_str());
}

void setup() {
  Serial.begin(115200);

  setting_manager.nvsBegin();
  setting_manager.addSetting("bluetooth_name", &bluetooth_name);
  setting_manager.loadSavedSettings();

  startBluetooth();
}

void loop() {
  if (Serial.available()) {
    bluetooth_name = Serial.readString();
    setting_manager.saveSettings();
  }
  if (SerialBT.available()) {
    bluetooth_name = SerialBT.readString();
    setting_manager.saveSettings();
  }
  delay(20);
}
