#ifndef SETTINGMANAGER_H
#define SETTINGMANAGER_H

#ifndef MAX_SETTINGS_ARRAY_SIZE
#define MAX_SETTINGS_ARRAY_SIZE 32
#endif

#include "Setting.h"

//class SettingBase;

//template <typename Type>
//class Setting;

using SettingType = SettingBase*;

class SettingManager {
  public:
    //using Setting = SettingBase*;
    
    template <typename... Settings>
    SettingManager(Settings*... settings);
    template <uint8_t Size>
    SettingManager(SettingType (&setting_array)[Size]);
    
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

    bool clearSettings();
    
    bool restoreDefaultValues();

    bool updateSettings(String input);
    
  private:
    SettingType settings[MAX_SETTINGS_ARRAY_SIZE];
    uint8_t setting_count = 0;
    
    bool addSettings();
};

#include "SettingManager.tpp"

#endif