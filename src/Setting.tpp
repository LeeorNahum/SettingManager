template <typename Type>
Setting<Type>::Setting(String key, Type* setting_pointer, SettingCallback callback) {
  this->setKey(key);
  this->setSettingPointer(setting_pointer);
  this->setCallback(callback);
}

template <typename Type>
Setting<Type>::Setting(String key, SettingCallback callback, Type* setting_pointer) {
  this->setKey(key);
  this->setSettingPointer(setting_pointer);
  this->setCallback(callback);
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
void Setting<Type>::setSettingPointer(Type* setting_pointer) {
  this->setting_pointer = setting_pointer;
  this->setDefaultSetting(setting_pointer ? String(*setting_pointer) : "");
}

template <typename Type>
Type* Setting<Type>::getSettingPointer() {
  return this->setting_pointer;
}

template <typename Type>
void Setting<Type>::setCallback(SettingCallback callback) {
  this->callback = callback;
}

template <typename Type>
void Setting<Type>::setDefaultSetting(String default_setting) {
  this->default_setting = default_setting;
}

template <typename Type>
String Setting<Type>::getDefaultSetting() {
  return this->default_setting;
}

template <typename Type>
void Setting<Type>::restoreDefaultSetting() {
  this->setValue();
}

template <typename Type>
void Setting<Type>::setValue(String value) {
  if (value.length() == 0 && this->getDefaultSetting().length() > 0) value = this->getDefaultSetting();
  
  Type setting_value = value.toInt();
  
  if (this->setting_pointer) *this->setting_pointer = setting_value;
  if (this->callback) this->callback(setting_value);
}

template <>
void Setting<bool>::setValue(String value) {
  if (value.length() == 0 && this->getDefaultSetting().length() > 0) value = this->getDefaultSetting();
  
  bool setting_value = (value == "true" || value == "1" || value == "yes" || value == "on" || value == "HIGH");
  Serial.println(value);

  if (this->setting_pointer) *this->setting_pointer = setting_value;
  if (this->callback) this->callback(setting_value);
}

template <>
void Setting<char>::setValue(String value) {
  if (value.length() == 0 && this->getDefaultSetting().length() > 0) value = this->getDefaultSetting();
  
  char setting_value = value[0];

  if (this->setting_pointer) *this->setting_pointer = setting_value;
  if (this->callback) this->callback(setting_value);
}

template <>
void Setting<float>::setValue(String value) {
  if (value.length() == 0 && this->getDefaultSetting().length() > 0) value = this->getDefaultSetting();
  
  float setting_value = value.toFloat();

  if (this->setting_pointer) *this->setting_pointer = setting_value;
  if (this->callback) this->callback(setting_value);
}

template <>
void Setting<double>::setValue(String value) {
  if (value.length() == 0 && this->getDefaultSetting().length() > 0) value = this->getDefaultSetting();
  
  double setting_value = value.toDouble();

  if (this->setting_pointer) *this->setting_pointer = setting_value;
  if (this->callback) this->callback(setting_value);
}

template <>
void Setting<String>::setValue(String value) {
  if (value.length() == 0 && this->getDefaultSetting().length() > 0) value = this->getDefaultSetting();
  
  if (this->setting_pointer) *this->setting_pointer = value;
  if (this->callback) this->callback(value);
}

template <typename Type>
Type Setting<Type>::getValue() {
  return *this->setting_pointer;
}