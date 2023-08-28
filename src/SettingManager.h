#ifndef SETTINGMANAGER_H
#define SETTINGMANAGER_H

#include <Arduino.h>
#include <vector>
#include <ArduinoNvs.h>
#include "Setting.h"

class SettingManager {
  public:
  SettingManager(ArduinoNvs &nvs = NVS);
  ~SettingManager();

  bool nvsBegin(String nvs_namespace = "storage");

  template <typename Type>
  bool addSetting(String key, Type* var, Type default_value);

  template <typename Type>
  bool addSetting(String key, Type* var);

  void loadSavedSettings();
  void loadDefaultSettings();
  bool saveSettings();

  private:
  ArduinoNvs& nvs;
  
  std::vector<SettingBase*> settings;
};

#include "SettingManager.tpp"

#endif /* SETTINGMANAGER_H */
