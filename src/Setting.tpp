template <typename Type>
Setting<Type>::Setting(String key, Type default_setting, SettingCallback callback) {
  this->setKey(key);
  this->setValue(default_setting);
  this->setDefaultSetting(default_setting);
  this->setCallback(callback);
}

template <typename Type>
Setting<Type>::Setting(String, Type default_setting, SettingCallbackVoid callback_void) {
  this->setKey(key);
  this->setValue(default_setting);
  this->setDefaultSetting(default_setting);
  this->setCallback(callback_void);
}

template <typename Type>
Setting<Type>::Setting(String key, Type* setting_pointer, SettingCallback callback) {
  this->setKey(key);
  this->setSettingPointer(setting_pointer);
  this->setCallback(callback);
}

template <typename Type>
Setting<Type>::Setting(String key, Type* setting_pointer, SettingCallbackVoid callback_void) {
  this->setKey(key);
  this->setSettingPointer(setting_pointer);
  this->setCallback(callback_void);
}

template <typename Type>
Setting<Type>::Setting(String key, SettingCallback callback, Type* setting_pointer) {
  this->setKey(key);
  this->setCallback(callback);
  this->setSettingPointer(setting_pointer);
}

template <typename Type>
Setting<Type>::Setting(String key, SettingCallbackVoid callback_void, Type* setting_pointer) {
  this->setKey(key);
  this->setCallback(callback_void);
  this->setSettingPointer(setting_pointer);
}

template <typename Type>
void Setting<Type>::setKey(String key) {
  this->key = key;
}

template <typename Type>
String Setting<Type>::getKey() {
  return this->key;
}

template <typename Type>
void Setting<Type>::setValue(Type value) {
  this->value = value;
  
  if (this->setting_pointer) *this->setting_pointer = this->value;
  if (this->callback) this->callback(this->value);
  else if (this->callback_void) this->callback_void();
}

template <typename Type>
void Setting<Type>::setValue() {
  return this->restoreDefaultSetting();
}

template <typename Type>
Type Setting<Type>::getValue() {
  return this->value;
}

template <typename Type>
Type Setting<Type>::getSettingPointerValue() {
  if (this->setting_pointer) {
    return *this->setting_pointer;
  }
  return this->getDefaultSetting();
}

template <typename Type>
void Setting<Type>::setDefaultSetting(Type default_setting) {
  this->has_default_setting = true;
  this->default_setting = default_setting;
}

template <typename Type>
void Setting<Type>::setDefaultSetting() {
  this->has_default_setting = false;
  this->default_setting = 0;
}

template <typename Type>
Type Setting<Type>::getDefaultSetting() {
  if (this->hasDefaultSetting()) {
    return this->default_setting;
  }
  return Type{};
}

template <typename Type>
bool Setting<Type>::hasDefaultSetting() {
  return this->has_default_setting;
}

template <typename Type>
void Setting<Type>::setSettingPointer(Type* setting_pointer) {
  this->setting_pointer = setting_pointer;
  if (setting_pointer) {
    this->setDefaultSetting(*setting_pointer);
  }
  else {
    this->setDefaultSetting();
  }
}

template <typename Type>
Type* Setting<Type>::getSettingPointer() {
  return this->setting_pointer;
}

template <typename Type>
void Setting<Type>::setCallback(SettingCallback callback) {
  this->callback = callback;
  if (callback) {
    this->callback_void = nullptr;
  }
}

template <typename Type>
void Setting<Type>::setCallback(SettingCallbackVoid callback_void) {
  this->callback_void = callback_void;
  if (callback_void) {
    this->callback = nullptr;
  }
}

template <typename Type>
bool Setting<Type>::restoreDefaultSetting() {
  if (this->hasDefaultSetting()) {
    this->setValue(this->getDefaultSetting());
    return true;
  }
  return false;
}

template <typename Type>
void Setting<Type>::setValueParseString(String string_value) {
  if (string_value.length() == 0) {
    this->restoreDefaultSetting();
    return;
  }
  
  Type value = string_value.toInt();
  
  this->setValue(value);
}

template <>
void Setting<bool>::setValueParseString(String string_value) {
  if (string_value.length() == 0) {
    this->restoreDefaultSetting();
    return;
  }
  
  bool setting_value = (string_value == "true" || string_value == "1" || string_value == "yes" || string_value == "on" || string_value == "HIGH");
  
  this->setValue(setting_value);
}

template <>
void Setting<char>::setValueParseString(String string_value) {
  if (string_value.length() == 0) {
    this->restoreDefaultSetting();
    return;
  }
  
  char char_value = string_value[0];
  
  this->setValue(char_value);
}

template <>
void Setting<float>::setValueParseString(String string_value) {
  if (string_value.length() == 0) {
    this->restoreDefaultSetting();
    return;
  }
  
  float float_value = string_value.toFloat();
  
  this->setValue(float_value);
}

template <>
void Setting<double>::setValueParseString(String string_value) {
  if (string_value.length() == 0) {
    this->restoreDefaultSetting();
    return;
  }
  
  double double_value = string_value.toDouble();
  
  this->setValue(double_value);
}

template <>
void Setting<String>::setValueParseString(String string_value) {
  if (string_value.length() == 0) {
    this->restoreDefaultSetting();
    return;
  }
  
  this->setValue(string_value);
}