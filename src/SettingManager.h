#ifndef SETTINGMANAGER_H
#define SETTINGMANAGER_H

#include <Arduino.h>
#include <vector>
#include <ArduinoNvs.h>
#include "Setting.h"

class SettingManager {
  public:
  SettingManager(); // TODO use NVS pointer
  ~SettingManager();

  bool initNvs(String nvs_namespace = "storage");

  template <typename Type>
  bool addSetting(String key, Type* var, Type default_value);

  template <typename Type>
  bool addSetting(String key, Type* var);

  void loadSavedSettings();
  void loadDefaultSettings();
  bool saveSettings();

  private:
  std::vector<SettingBase*> settings;
};

#include "SettingManager.tpp"

#endif /* SETTINGMANAGER_H */
