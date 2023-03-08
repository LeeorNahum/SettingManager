template <typename Type>
#ifndef USE_ARDUINO_NVS
Setting<Type>::Setting(String key, Type default_value, SettingCallback callback)
#else
Setting<Type>::Setting(String key, Type default_value, SettingCallback callback, bool use_nvs) : use_nvs(use_nvs)
#endif
{
  this->setKey(key);
  this->setValue(default_value);
  this->setDefaultValue(default_value);
  this->setCallback(callback);
}

template <typename Type>
#ifndef USE_ARDUINO_NVS
Setting<Type>::Setting(String key, Type default_value, SettingCallbackVoid callback_void)
#else
Setting<Type>::Setting(String key, Type default_value, SettingCallbackVoid callback_void, bool use_nvs) : use_nvs(use_nvs)
#endif
{
  this->setKey(key);
  this->setValue(default_value);
  this->setDefaultValue(default_value);
  this->setCallback(callback_void);
}

template <typename Type>
#ifndef USE_ARDUINO_NVS
Setting<Type>::Setting(String key, Type* setting_pointer, SettingCallback callback)
#else
Setting<Type>::Setting(String key, Type* setting_pointer, SettingCallback callback, bool use_nvs) : use_nvs(use_nvs)
#endif
{
  this->setKey(key);
  this->setSettingPointer(setting_pointer);
  this->setCallback(callback);
}

template <typename Type>
#ifndef USE_ARDUINO_NVS
Setting<Type>::Setting(String key, Type* setting_pointer, SettingCallbackVoid callback_void)
#else
Setting<Type>::Setting(String key, Type* setting_pointer, SettingCallbackVoid callback_void, bool use_nvs) : use_nvs(use_nvs)
#endif
{
  this->setKey(key);
  this->setSettingPointer(setting_pointer);
  this->setCallback(callback_void);
}

template <typename Type>
#ifndef USE_ARDUINO_NVS
Setting<Type>::Setting(String key, SettingCallback callback)
#else
Setting<Type>::Setting(String key, SettingCallback callback, bool use_nvs) : use_nvs(use_nvs)
#endif
{
  this->setKey(key);
  this->setCallback(callback);
}

template <typename Type>
#ifndef USE_ARDUINO_NVS
Setting<Type>::Setting(String key, SettingCallbackVoid callback_void)
#else
Setting<Type>::Setting(String key, SettingCallbackVoid callback_void, bool use_nvs) : use_nvs(use_nvs)
#endif
{
  this->setKey(key);
  this->setCallback(callback_void);
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
  
  #ifdef USE_ARDUINO_NVS
  this->setValueNVS(this->value);
  #endif
}

template <typename Type>
void Setting<Type>::setValue() {
  return this->restoreDefaultValue();
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
  return this->getDefaultValue();
}

template <typename Type>
void Setting<Type>::setDefaultValue(Type default_value) {
  this->has_default_setting = true;
  this->default_value = default_value;
}

template <typename Type>
void Setting<Type>::setDefaultValue() {
  this->has_default_setting = false;
  this->default_value = Type{};
}

template <typename Type>
Type Setting<Type>::getDefaultValue() {
  if (this->hasDefaultValue()) {
    return this->default_value;
  }
  return Type{};
}

template <typename Type>
bool Setting<Type>::hasDefaultValue() {
  return this->has_default_setting;
}

template <typename Type>
void Setting<Type>::setSettingPointer(Type* setting_pointer) {
  this->setting_pointer = setting_pointer;
  if (setting_pointer) {
    this->setDefaultValue(*setting_pointer);
  }
  else {
    this->setDefaultValue();
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
bool Setting<Type>::restoreDefaultValue() {
  if (this->hasDefaultValue()) {
    this->setValue(this->getDefaultValue());
    return true;
  }
  return false;
}

template <typename Type>
void Setting<Type>::setValueParseString(String string_value) {
  if (string_value.length() == 0) {
    this->restoreDefaultValue();
    return;
  }
  
  Type value = string_value.toInt();
  
  this->setValue(value);
}

template <>
void Setting<bool>::setValueParseString(String string_value) {
  if (string_value.length() == 0) {
    this->restoreDefaultValue();
    return;
  }
  
  bool bool_value = (string_value == "true" || string_value == "1" || string_value == "yes" || string_value == "on" || string_value == "HIGH");
  
  this->setValue(bool_value);
}

template <>
void Setting<char>::setValueParseString(String string_value) {
  if (string_value.length() == 0) {
    this->restoreDefaultValue();
    return;
  }
  
  char char_value = string_value[0];
  
  this->setValue(char_value);
}

template <>
void Setting<float>::setValueParseString(String string_value) {
  if (string_value.length() == 0) {
    this->restoreDefaultValue();
    return;
  }
  
  float float_value = string_value.toFloat();
  
  this->setValue(float_value);
}

template <>
void Setting<double>::setValueParseString(String string_value) {
  if (string_value.length() == 0) {
    this->restoreDefaultValue();
    return;
  }
  
  double double_value = string_value.toDouble();
  
  this->setValue(double_value);
}

template <>
void Setting<String>::setValueParseString(String string_value) {
  if (string_value.length() == 0) {
    this->restoreDefaultValue();
    return;
  }
  
  this->setValue(string_value);
}

#ifdef USE_ARDUINO_NVS

template <typename Type>
void Setting<Type>::useNVS(bool use_nvs) {
  this->use_nvs = use_nvs;
}

template <typename Type>
void Setting<Type>::restoreSavedValue() {
  if (this->use_nvs) {
    this->setValue(this->getValueNVS());
  }
}

template <typename Type>
void Setting<Type>::setValueNVS(Type value) {
  if (this->use_nvs) {
    NVS.setInt(this->getKey(), value);
  }
}

template <>
void Setting<float>::setValueNVS(float value) {
  if (this->use_nvs) {
    NVS.setFloat(this->getKey(), value);
  }
}

template <>
void Setting<double>::setValueNVS(double value) {
  if (this->use_nvs) {
    NVS.setFloat(this->getKey(), value);
  }
}

template <>
void Setting<String>::setValueNVS(String value) {
  if (this->use_nvs) {
    NVS.setString(this->getKey(), value);
  }
}

template <typename Type>
Type Setting<Type>::getValueNVS() {
  if (this->use_nvs) {
    return NVS.getInt(this->getKey());
  }
}

template <>
float Setting<float>::getValueNVS() {
  if (this->use_nvs) {
    return NVS.getFloat(this->getKey());
  }
}

template <>
double Setting<double>::getValueNVS() {
  if (this->use_nvs) {
    return NVS.getFloat(this->getKey());
  }
}

template <>
String Setting<String>::getValueNVS() {
  if (this->use_nvs) {
    return NVS.getString(this->getKey());
  }
}

#endif