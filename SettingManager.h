#ifndef SETTINGMANAGER_H
#define SETTINGMANAGER_H

#ifndef MAX_SETTINGS_ARRAY_SIZE
#define MAX_SETTINGS_ARRAY_SIZE 32
#endif

//#include <Arduino.h>
#include <stdint.h>
#include <WString.h>

class SettingManager {
public:
  using BoolCallback = void (*)(bool);
  using CharCallback = void (*)(char);
  using IntCallback = void (*)(int);
  using FloatCallback = void (*)(float);
  using DoubleCallback = void (*)(double);
  using StringCallback = void (*)(String);
  
  bool registerSetting(String key, bool* bool_pointer, BoolCallback bool_callback = nullptr);
  bool registerSetting(String key, BoolCallback bool_callback, bool* bool_pointer = nullptr);
  
  bool registerSetting(String key, char* char_pointer, CharCallback char_callback = nullptr);
  bool registerSetting(String key, CharCallback char_callback, char* char_pointer = nullptr);
  
  bool registerSetting(String key, int* int_pointer, IntCallback int_callback = nullptr);
  bool registerSetting(String key, IntCallback int_callback, int* int_pointer = nullptr);
  
  bool registerSetting(String key, float* float_pointer, FloatCallback float_callback = nullptr);
  bool registerSetting(String key, FloatCallback float_callback, float* float_pointer = nullptr);
  
  bool registerSetting(String key, double* double_pointer, DoubleCallback double_callback = nullptr);
  bool registerSetting(String key, DoubleCallback double_callback, double* double_pointer = nullptr);
  
  bool registerSetting(String key, String* string_pointer, StringCallback string_callback = nullptr);
  bool registerSetting(String key, StringCallback string_callback, String* string_pointer = nullptr);
  
  bool setValue(String key, String value);

  bool updateSettings(String input);
  
private:
  enum class SettingType {BOOL, CHAR, INT, FLOAT, DOUBLE, STRING};
  
  struct Setting {
    String key;
    SettingType type;
    
    union {
      bool* bool_pointer;
      char* char_pointer;
      int* int_pointer;
      float* float_pointer;
      double* double_pointer;
      String* string_pointer;
    };
    
    union {
      BoolCallback bool_callback;
      CharCallback char_callback;
      IntCallback int_callback;
      FloatCallback float_callback;
      DoubleCallback double_callback;
      StringCallback string_callback;
    };
  };
  
  Setting settings[MAX_SETTINGS_ARRAY_SIZE];
  uint8_t setting_count = 0;
  
  Setting* getSetting(String key);
};

#endif