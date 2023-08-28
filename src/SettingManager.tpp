SettingManager::SettingManager(ArduinoNvs &nvs)
  : nvs(nvs) {}

SettingManager::~SettingManager() {
  for (SettingBase* setting : this->settings) {
    delete setting;
  }
}

bool SettingManager::nvsBegin(String nvs_namespace) {
  return this->nvs.begin(nvs_namespace);
}

template <typename Type>
bool SettingManager::addSetting(String key, Type* var, Type default_value) {
  if (var == nullptr) {
    return false;
  }
  this->settings.push_back(new Setting<Type>(this->nvs, key, var, default_value));
  return true;
}

template <typename Type>
bool SettingManager::addSetting(String key, Type* var) {
  if (var == nullptr) {
    return false;
  }
  this->settings.push_back(new Setting<Type>(this->nvs, key, var));
  return true;
}

void SettingManager::loadSavedSettings() {
  for (SettingBase* setting : this->settings) {
    setting->loadSavedSetting();
  }
}

void SettingManager::loadDefaultSettings() {
  for (SettingBase* setting : this->settings) {
    setting->loadDefaultSetting();
  }
}

bool SettingManager::saveSettings() {
  for (SettingBase* setting : this->settings) {
    setting->saveSetting();
  }
  return this->nvs.commit();
}
