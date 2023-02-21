template <typename... Settings>
SettingManager::SettingManager(String restore_default_settings_key, Settings*... settings) {
  this->setRestoreDefaultSettingsKey(restore_default_settings_key);
  this->setSettings(settings...);
}

template <typename... Settings>
SettingManager::SettingManager(SettingType setting, Settings*... settings) {
  this->setSettings(setting, settings...);
}

template <uint8_t Size>
SettingManager::SettingManager(String restore_default_settings_key, SettingType (&setting_array)[Size]) {
  this->setRestoreDefaultSettingsKey(restore_default_settings_key);
  this->setSettings(setting_array);
}

template <uint8_t Size>
SettingManager::SettingManager(SettingType (&setting_array)[Size], String restore_default_settings_key) {
  this->setSettings(setting_array);
  this->setRestoreDefaultSettingsKey(restore_default_settings_key);
}

bool SettingManager::addSetting(SettingType setting) {
  if (this->setting_count >= MAX_SETTINGS_ARRAY_SIZE) {
    return false;
  }

  this->settings[this->setting_count++] = setting;
  return true;
}

template <typename... Settings>
bool SettingManager::addSettings(SettingType setting, Settings*... settings) {
  bool success = true;
  
  success = success && addSetting(setting);
  success = success && addSettings(settings...);
  
  return success;
}

bool SettingManager::addSettings() {
  return true;
}

template <uint8_t Size>
bool SettingManager::addSettings(SettingType (&setting_array)[Size]) {
  bool success = true;

  for (uint8_t i = 0; i < Size; i++) {
    success = success && this->addSetting(setting_array[i]);
  }

  return success;
}

bool SettingManager::setSetting(SettingType setting) {
  this->clearSettings();
  return this->addSetting(setting);
}

template <typename... Settings>
bool SettingManager::setSettings(Settings*... settings) {
  this->clearSettings();
  return this->addSettings(settings...);
}

template <uint8_t Size>
bool SettingManager::setSettings(SettingType (&setting_array)[Size]) {
  this->clearSettings();
  return this->addSettings(setting_array);
}

void SettingManager::setRestoreDefaultSettingsKey(String restore_default_settings_key) {
  this->restore_default_settings_key = restore_default_settings_key;
}

String SettingManager::getRestoreDefaultSettingsKey() {
  return this->restore_default_settings_key;
}

bool SettingManager::clearSettings() {
  if (!this->setting_count > 0) {
    return false;
  }
  
  for (uint8_t i = 0; i < MAX_SETTINGS_ARRAY_SIZE; i++) {
    this->settings[i] = nullptr;
  }
  
  this->setting_count = 0;
  return true;
}

void SettingManager::restoreDefaultSettings() {
  for (uint8_t i = 0; i < setting_count; i++) {
    settings[i]->restoreDefaultSetting();
  }
}

bool SettingManager::updateSettings(String input) {
  int semicolonIndex = input.indexOf(":");
  if (semicolonIndex == -1) return false;
  
  String key = input.substring(0, semicolonIndex);
  String value = input.substring(semicolonIndex + 1);
  
  if (value.charAt(value.length() - 1) == '\n') {
    value.remove(value.length() - 1);
  }
  
  if (this->getRestoreDefaultSettingsKey() == key) {
    if (this->getRestoreDefaultSettingsKey().length() > 0) {
      this->restoreDefaultSettings();
      return true;
    }
  }
  
  bool success = false;
  for (uint8_t i = 0; i < setting_count; i++) {
    if (settings[i]->getKey() == key) {
      settings[i]->setValue(value);
      success = true;
    }
  }
  return success;
}