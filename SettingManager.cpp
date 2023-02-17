#include <SettingManager.h>

bool SettingManager::registerSetting(String key, bool* bool_pointer, BoolCallback bool_callback) {
  Setting* setting = this->getSetting(key);
  if (setting) {
    setting->bool_pointer = bool_pointer;
    setting->bool_callback = bool_callback;
  }
  else {
    if (this->setting_count >= MAX_SETTINGS_ARRAY_SIZE) return false;
    
    Setting setting = {key, SettingType::BOOL};
    setting.bool_pointer = bool_pointer;
    setting.bool_callback = bool_callback;
    
    this->settings[this->setting_count++] = setting;
  }
  return true;
}

bool SettingManager::registerSetting(String key, BoolCallback bool_callback, bool* bool_pointer) {
  this->registerSetting(key, bool_pointer, bool_callback);
}

bool SettingManager::registerSetting(String key, char* char_pointer, CharCallback char_callback) {
  Setting* setting = this->getSetting(key);
  if (setting) {
    setting->char_pointer = char_pointer;
    setting->char_callback = char_callback;
  }
  else {
    if (this->setting_count >= MAX_SETTINGS_ARRAY_SIZE) return false;
    
    Setting setting = {key, SettingType::CHAR};
    setting.char_pointer = char_pointer;
    setting.char_callback = char_callback;
    
    this->settings[this->setting_count++] = setting;
  }
  return true;
}

bool SettingManager::registerSetting(String key, CharCallback char_callback, char* char_pointer) {
  this->registerSetting(key, char_pointer, char_callback);
}

bool SettingManager::registerSetting(String key, int* int_pointer, IntCallback int_callback) {
  Setting* setting = this->getSetting(key);
  if (setting) {
    setting->int_pointer = int_pointer;
    setting->int_callback = int_callback;
  }
  else {
    if (this->setting_count >= MAX_SETTINGS_ARRAY_SIZE) return false;
    
    Setting setting = {key, SettingType::INT};
    setting.int_pointer = int_pointer;
    setting.int_callback = int_callback;
    
    this->settings[this->setting_count++] = setting;
  }
  return true;
}

bool SettingManager::registerSetting(String key, IntCallback int_callback, int* int_pointer) {
  this->registerSetting(key, int_pointer, int_callback);
}

bool SettingManager::registerSetting(String key, float* float_pointer, FloatCallback float_callback) {
  Setting* setting = this->getSetting(key);
  if (setting) {
    setting->float_pointer = float_pointer;
    setting->float_callback = float_callback;
  }
  else {
    if (this->setting_count >= MAX_SETTINGS_ARRAY_SIZE) return false;
    
    Setting setting = {key, SettingType::FLOAT};
    setting.float_pointer = float_pointer;
    setting.float_callback = float_callback;
    
    this->settings[this->setting_count++] = setting;
  }
  return true;
}

bool SettingManager::registerSetting(String key, FloatCallback float_callback, float* float_pointer) {
  this->registerSetting(key, float_pointer, float_callback);
}

bool SettingManager::registerSetting(String key, double* double_pointer, DoubleCallback double_callback) {
  Setting* setting = this->getSetting(key);
  if (setting) {
    setting->double_pointer = double_pointer;
    setting->double_callback = double_callback;
  }
  else {
    if (this->setting_count >= MAX_SETTINGS_ARRAY_SIZE) return false;
    
    Setting setting = {key, SettingType::DOUBLE};
    setting.double_pointer = double_pointer;
    setting.double_callback = double_callback;
    
    this->settings[this->setting_count++] = setting;
  }
  return true;
}

bool SettingManager::registerSetting(String key, DoubleCallback double_callback, double* double_pointer) {
  this->registerSetting(key, double_pointer, double_callback);
}

bool SettingManager::registerSetting(String key, String* string_pointer, StringCallback string_callback) {
  Setting* setting = this->getSetting(key);
  if (setting) {
    setting->string_pointer = string_pointer;
    setting->string_callback = string_callback;
  }
  else {
    if (this->setting_count >= MAX_SETTINGS_ARRAY_SIZE) return false;
    
    Setting setting = {key, SettingType::STRING};
    setting.string_pointer = string_pointer;
    setting.string_callback = string_callback;
    
    this->settings[this->setting_count++] = setting;
  }
  return true;
}

bool SettingManager::registerSetting(String key, StringCallback string_callback, String* string_pointer) {
  this->registerSetting(key, string_pointer, string_callback);
}

bool SettingManager::setValue(String key, String value) {
  Setting* setting = this->getSetting(key);
  if (!setting) return false;
  
  switch (setting->type) {
    case SettingType::BOOL: {
      bool bool_value = (value == "true" || value == "1" || value == "on" || value == "yes");
      if (setting->bool_pointer) {
        *setting->bool_pointer = bool_value;
      }
      if (setting->bool_callback) {
        setting->bool_callback(bool_value);
      }
      break;
    }
    case SettingType::CHAR: {
      char char_value = value[0];
      if (setting->char_pointer) {
        *setting->char_pointer = char_value;
      }
      if (setting->char_callback) {
        setting->char_callback(char_value);
      }
      break;
    }
    case SettingType::INT: {
      int int_value = value.toInt();
      if (setting->int_pointer) {
        *setting->int_pointer = int_value;
      }
      if (setting->int_callback) {
        setting->int_callback(int_value);
      }
      break;
    }
    case SettingType::FLOAT: {
      float float_value = value.toFloat();
      if (setting->float_pointer) {
        *setting->float_pointer = float_value;
      }
      if (setting->float_callback) {
        setting->float_callback(float_value);
      }
      break;
    }
    case SettingType::DOUBLE: {
      double double_value = value.toDouble();
      if (setting->double_pointer) {
        *setting->double_pointer = double_value;
      }
      if (setting->double_callback) {
        setting->double_callback(double_value);
      }
      break;
    }
    case SettingType::STRING: {
      if (setting->string_pointer) {
        *setting->string_pointer = value;
      }
      if (setting->string_callback) {
        setting->string_callback(value);
      }
      break;
    }
    default:
      return false;
  }
  return true;
}

bool SettingManager::updateSettings(String input) {
  int semicolonIndex = input.indexOf(":");
  if (semicolonIndex == -1) return false;
  
  String key = input.substring(0, semicolonIndex);
  String value = input.substring(semicolonIndex + 1, input.length() - 1);
  
  return this->setValue(key, value);
}

SettingManager::Setting* SettingManager::getSetting(String key) {
  for (uint8_t i = 0; i < setting_count; i++) {
    if (settings[i].key == key) {
      return &this->settings[i];
    }
  }
  return nullptr;
}