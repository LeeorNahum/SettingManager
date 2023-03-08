#ifndef SETTINGMANAGER_H
#define SETTINGMANAGER_H

#ifdef USE_ARDUINO_NVS
#include <ArduinoNvs.h>
#endif

#ifndef MAX_SETTINGS_ARRAY_SIZE
#define MAX_SETTINGS_ARRAY_SIZE 32
#endif

#include "Setting.h"

using SettingType = SettingBase*;

class SettingManager {
  public:
    template <typename... Settings>
    SettingManager(String restore_default_settings_key = "", Settings*... settings);
    template <typename... Settings>
    SettingManager(SettingType setting, Settings*... settings);
    template <uint8_t Size>
    SettingManager(String restore_default_settings_key, SettingType (&setting_array)[Size]);
    template <uint8_t Size>
    SettingManager(SettingType (&setting_array)[Size], String restore_default_settings_key = "");
    
    bool addSetting(SettingType setting);
    template <typename... Settings>
    bool addSettings(SettingType setting, Settings*... settings);
    template <uint8_t Size>
    bool addSettings(SettingType (&setting_array)[Size]);
    
    bool setSetting(SettingType setting);
    template <typename... Settings>
    bool setSettings(Settings*... settings);
    template <uint8_t Size>
    bool setSettings(SettingType (&setting_array)[Size]);
    
    void setRestoreDefaultSettingsKey(String restore_default_settings_key = "");
    String getRestoreDefaultSettingsKey();

    bool clearSettings();
    
    void restoreDefaultValues();
    
    #ifdef USE_ARDUINO_NVS
    void restoreSavedValues();
    #endif

    bool updateSettings(String input);
    
  private:
    SettingType settings[MAX_SETTINGS_ARRAY_SIZE] = {nullptr};
    uint8_t setting_count = 0;
    
    String restore_default_settings_key = "";
    
    bool addSettings();
};

#include "SettingManager.tpp"

#endif