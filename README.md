# SettingManager

The SettingManager library provides a way to manage and update settings for an Arduino project.

## Table of Contents

- [Usage](#usage)
  - [Creating setting variables](#creating-setting-variables)
  - [Creating setting objects](#creating-setting-objects)
  - [Adding settings](#adding-settings)
  - [Updating settings](#updating-settings)
  - [Serial Monitor](#serial-monitor)
- [Examples](#examples)
  - [LED Example](#led-example)

## Usage

The SettingManager library provides a simple interface for managing settings for an Arduino project. To use the library in your project, you need to include the library header:

``` C++
#include <SettingManager.h>
```

### Creating setting variables

To create a setting, you need to make a variable which will store the value and be passed to the Setting object. To set the default value of the setting, initialize the variable:

``` C++
bool LED_Red = HIGH;
bool LED_Green = LOW;
uint8_t LED_Blue = 0;
```

### Creating setting objects

Now with the variables created, declare a Setting object with a key and the address of the setting variables. Use the same template type as the variable:

``` C++
Setting<bool> RedLEDSetting("led.red.state", &LED_Red);
Setting<bool> GreenLEDSetting("led.green.state", &LED_Green);
Setting<uint8_t> BlueLEDSetting("led.blue.brightness", &LED_Blue);
```

### Adding settings

Add settings to the SettingManager in the SettingManager constructor or using the addSetting() method. The first parameter specifies the key which will restore all of the settings to their defaults:

``` C++
SettingManager settingManager("settings.default", &RedLEDSetting, &GreenLEDSetting, &BlueLEDSetting);

// or

SettingManager settingManager("settings.default");

void setup() {
  settingManager.addSettings(&RedLEDSetting, &GreenLEDSetting, &BlueLEDSetting);
}
```

### Updating settings

You can now write settings to the Serial Monitor in a `key:value` format to change the settings:

``` C++
void loop() {
  if (Serial.available()) {
    settingManager.updateSettings(Serial.readString());
  }
}
```

### Serial Monitor

Typing the following into the Serial Monitor will update the setting variables

>led.red.state:LOW

`LED_Red = LOW`

>led.green.state:HIGH

`LED_Green = HIGH`

>led.blue.brightness:150

`LED_Blue = 150`

>led.blue.brightness:255

`LED_Blue = 255`

>settings.default: `value ignored`

`LED_Red = HIGH`

`LED_Green = LOW`

`LED_Blue = 0`

## Examples

### LED Example

This is the full example from the [Usage](#usage) section. We first create three LEDs and a SettingManager object and set an initial values LEDs. In the loop function, we read from the Serial Monitor and pass the reading to the SettingManager's updateSettings method and then set the LEDs with digitalWrite or analogWrite.

``` C++
#include <SettingManager.h>

// Define LED pins
#define RED_LED_PIN 13
#define GREEN_LED_PIN 2
#define BLUE_LED_PIN 3 // PWM pin for analogWrite

// Create setting variables with default values
bool LED_Red = HIGH;
bool LED_Green = LOW;
uint8_t LED_Blue = 0;

// Initialize Setting objects for all LEDs
Setting<bool> RedLEDSetting("led.red.state", &LED_Red);
Setting<bool> GreenLEDSetting("led.green.state", &LED_Green);
Setting<uint8_t> BlueLEDSetting("led.blue.brightness", &LED_Blue);

// Initialize the SettingManager object
SettingManager settingManager("settings.default", &RedLEDSetting, &GreenLEDSetting, &BlueLEDSetting);

void setup() {
  // Begin serial communication
  Serial.begin(115200);
  
  // Set the pins as output
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);
}

void loop() {
  // Check if there is any data available on the serial port
  if (Serial.available()) {
    // Update the settings using the serial port
    bool settings_updated = settingManager.updateSettings(Serial.readString());
    
    // Check if any settings were updated
    if (settings_updated) {
      digitalWrite(RED_LED_PIN, LED_Red);
      digitalWrite(GREEN_LED_PIN, LED_Green);
      analogWrite(BLUE_LED_PIN, LED_Blue);
    }
  }
  
  // Wait for 1 second
  delay(1000);
}
```

### BluetoothSerial NVS

This example demonstrates reading from both Serial and BluetoothSerial and then saving the variable in flash using the NVS library.

``` C++
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
```
