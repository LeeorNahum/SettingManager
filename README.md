# SettingManager

SettingManager is an Arduino library that provides an abstraction to manage settings, allowing easy access to save and load different data types with the support of NVS (Non-Volatile Storage) on ESP32.

## Features

- Save and load multiple settings from NVS with ease.
- Default settings initialization.
- Supports multiple data types including int, float, and String.

## Table of Contents

- [Usage](#usage)
  - [Initialization](#initialization)
  - [Begin NVS](#begin-nvs)
  - [Creating variables](#creating-variables)
  - [Adding settings](#adding-settings)
  - [Loading and Saving Settings](#loading-and-saving-settings)
    - [Load saved settings from NVS](#load-saved-settings-from-nvs)
    - [Load default settings](#load-default-settings)
    - [Save current settings](#save-current-settings)

## Usage

### Initialization

Start by initializing the `SettingManager` with the desired NVS instance:

``` C++
#include <SettingManager.h>

ArduinoNvs my_nvs;
SettingManager setting_manager(my_nvs);
```

...or with the default:

``` C++
#include <SettingManager.h>

SettingManager setting_manager; // Same as: SettingManager setting_manager(NVS);
```

### Begin NVS

Before performing any operations, initialize NVS. You can optionally provide a namespace.

``` C++
setting_manager.nvsBegin();  // Using default namespace "storage"
```

``` C++
setting_manager.nvsBegin("myNamespace"); // Using your own namespace
```

### Creating variables

Create variables which you want to preserve in non-volatile storage. To set the default value of the setting, initialize the variable.

``` C++
String device_name = "My ESP32";
bool led_red = HIGH;
bool led_green;
```

### Adding settings

You can add settings by providing a key (limted to 15 characters), a variable to associate with that key, and optionally a default value.

``` C++
// If you don't provide a default value, the current value of the variable is taken as the default:
setting_manager.addSetting("device.name", &device_name);
setting_manager.addSetting("red_led_state", &led_red);
// The default value of `LOW` is used instead:
setting_manager.addSetting("green_led_state", &led_green, LOW);
```

### Loading and Saving Settings

#### Load saved settings from NVS

Apply the saved values to the variables. If nothing is saved then the default value is applied instead.

``` C++
setting_manager.loadSavedSettings();
```

#### Load default settings

Apply the default values to the variables.

``` C++
setting_manager.loadDefaultSettings();
```

#### Save current settings

Saves all of the current values of the variables to their NVS key.

``` C++
setting_manager.saveSettings();
```