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