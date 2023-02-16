#ifndef SETTINGMANAGER_H
#define SETTINGMANAGER_H

#ifndef MAX_SETTINGS_ARRAY_SIZE
#define MAX_SETTINGS_ARRAY_SIZE 32
#endif

#include <Arduino.h>
#include <stdint.h>

class SettingManager {
public:
  using BoolCallback = void (*)(bool);
  using CharCallback = void (*)(char);
  using IntCallback = void (*)(int);
  using FloatCallback = void (*)(float);
  using DoubleCallback = void (*)(double);
  using StringCallback = void (*)(String);
  
  bool registerSetting(String key, bool* bool_pointer, StringCallback bool_callback = nullptr) {
    Setting* setting = this->getSetting(key);
    if (setting) {
      setting->bool_pointer = bool_pointer;
      setting->bool_callback = bool_callback;
    }
    else {
      if (this->setting_count >= MAX_SETTINGS_ARRAY_SIZE) return false;
      
      Setting setting = {key, Type::BOOL};
      setting.bool_pointer = bool_pointer;
      setting.bool_callback = bool_callback;
      
      this->settings[this->setting_count++] = setting;
    }
    return true;
  }
  
  bool registerSetting(String key, BoolCallback bool_callback, bool* bool_pointer = nullptr) {
    this->registerSetting(key, bool_pointer, bool_callback);
  }
  
  bool registerSetting(String key, char* char_pointer, StringCallback char_callback = nullptr) {
    Setting* setting = this->getSetting(key);
    if (setting) {
      setting->char_pointer = char_pointer;
      setting->char_callback = char_callback;
    }
    else {
      if (this->setting_count >= MAX_SETTINGS_ARRAY_SIZE) return false;
      
      Setting setting = {key, Type::CHAR};
      setting.char_pointer = char_pointer;
      setting.char_callback = char_callback;
      
      this->settings[this->setting_count++] = setting;
    }
    return true;
  }
  
  bool registerSetting(String key, CharCallback char_callback, char* char_pointer = nullptr) {
    this->registerSetting(key, char_pointer, char_callback);
  }
  
  bool registerSetting(String key, int* int_pointer, StringCallback int_callback = nullptr) {
    Setting* setting = this->getSetting(key);
    if (setting) {
      setting->int_pointer = int_pointer;
      setting->int_callback = int_callback;
    }
    else {
      if (this->setting_count >= MAX_SETTINGS_ARRAY_SIZE) return false;
      
      Setting setting = {key, Type::INT};
      setting.int_pointer = int_pointer;
      setting.int_callback = int_callback;
      
      this->settings[this->setting_count++] = setting;
    }
    return true;
  }
  
  bool registerSetting(String key, IntCallback int_callback, int* int_pointer = nullptr) {
    this->registerSetting(key, int_pointer, int_callback);
  }
  
  bool registerSetting(String key, float* float_pointer, StringCallback float_callback = nullptr) {
    Setting* setting = this->getSetting(key);
    if (setting) {
      setting->float_pointer = float_pointer;
      setting->float_callback = float_callback;
    }
    else {
      if (this->setting_count >= MAX_SETTINGS_ARRAY_SIZE) return false;
      
      Setting setting = {key, Type::FLOAT};
      setting.float_pointer = float_pointer;
      setting.float_callback = float_callback;
      
      this->settings[this->setting_count++] = setting;
    }
    return true;
  }
  
  bool registerSetting(String key, FloatCallback float_callback, float* float_pointer = nullptr) {
    this->registerSetting(key, float_pointer, float_callback);
  }
  
  bool registerSetting(String key, double* double_pointer, StringCallback double_callback = nullptr) {
    Setting* setting = this->getSetting(key);
    if (setting) {
      setting->double_pointer = double_pointer;
      setting->double_callback = double_callback;
    }
    else {
      if (this->setting_count >= MAX_SETTINGS_ARRAY_SIZE) return false;
      
      Setting setting = {key, Type::DOUBLE};
      setting.double_pointer = double_pointer;
      setting.double_callback = double_callback;
      
      this->settings[this->setting_count++] = setting;
    }
    return true;
  }
  
  bool registerSetting(String key, DoubleCallback double_callback, double* double_pointer = nullptr) {
    this->registerSetting(key, double_pointer, double_callback);
  }
  
  bool registerSetting(String key, String* string_pointer, StringCallback string_callback = nullptr) {
    Setting* setting = this->getSetting(key);
    if (setting) {
      setting->string_pointer = string_pointer;
      setting->string_callback = string_callback;
    }
    else {
      if (this->setting_count >= MAX_SETTINGS_ARRAY_SIZE) return false;
      
      Setting setting = {key, Type::STRING};
      setting.string_pointer = string_pointer;
      setting.string_callback = string_callback;
      
      this->settings[this->setting_count++] = setting;
    }
    return true;
  }
  
  bool registerSetting(String key, StringCallback string_callback, string* string_pointer = nullptr) {
    this->registerSetting(key, string_pointer, string_callback);
  }
  
  bool setValue(String key, String value) {
    Setting* setting = this->getSetting(key);
    
    if (!setting) return false;
    
    switch (setting->type) {
      case Type::BOOL:
        bool bool_value = (value == "true" || value == "1" || value == "on" || value == "yes");
        if (setting->bool_pointer) {
          *setting->bool_pointer = bool_value;
        }
        if (setting->bool_callback) {
          setting->bool_callback(bool_value);
        }
        break;
      case Type::CHAR:
        char char_value = value[0];
        if (setting->char_pointer) {
          *setting->char_pointer = char_value;
        }
        if (setting->char_callback) {
          setting->char_callback(char_value);
        }
        break;
      case Type::INT:
        int int_value = value.toInt();
        if (setting->int_pointer) {
          *setting->int_pointer = int_value;
        }
        if (setting->int_callback) {
          setting->int_callback(int_value);
        }
        break;
      case Type::FLOAT:
        float float_value = value.toFloat();
        if (setting->float_pointer) {
          *setting->float_pointer = float_value;
        }
        if (setting->float_callback) {
          setting->float_callback(float_value);
        }
        break;
      case Type::DOUBLE:
        double double_value = value.toDouble();
        if (setting->double_pointer) {
          *setting->double_pointer = double_value;
        }
        if (setting->double_callback) {
          setting->double_callback(double_value);
        }
        break;
      case Type::STRING:
        if (setting->string_pointer) {
          *setting->string_pointer = value;
        }
        if (setting->string_callback) {
          setting->string_callback(value);
        }
        break;
      default:
        return false;
    }
    return true;
  }

  bool updateSetting(String input) {
    int semicolonIndex = input.indexOf(":");
    if (semicolonIndex == -1) return;
    
    String key = input.substring(0, semicolonIndex);
    String value = input.substring(semicolonIndex + 1, input.length() - 1);
    
    return this->setValue(key, value);
  }
  
private:
  enum class Type {BOOL, CHAR, INT, FLOAT, DOUBLE, STRING};
  
  struct Setting {
    String key;
    Type type;
    
    bool* bool_pointer = nullptr;
    BoolCallback bool_callback = nullptr;
    
    char* char_pointer = nullptr;
    CharCallback char_callback = nullptr;
    
    int* int_pointer = nullptr;
    IntCallback int_callback = nullptr;
    
    float* float_pointer = nullptr;
    FloatCallback float_callback = nullptr;
    
    double* double_pointer = nullptr;
    DoubleCallback double_callback = nullptr;
    
    String* string_pointer = nullptr;
    StringCallback string_callback = nullptr;
  };
  
  Setting settings[MAX_SETTINGS_ARRAY_SIZE];
  uint8_t setting_count = 0;
  
  Setting* getSetting(String key) {
    for (int i = 0; i < setting_count; i++) {
      if (settings[i].key == key) {
        return &this->settings[i];
      }
    }
    return nullptr;
  }
};

#endif