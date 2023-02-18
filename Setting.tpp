template <typename Type>
Setting<Type>::Setting(String key, Type* setting_pointer, SettingCallback callback) {
  this->setKey(key);
  this->setSettingPointer(setting_pointer);
  this->setCallback(callback);
  this->setDefaultValue(setting_pointer ? String(*setting_pointer) : "");
}

template <typename Type>
Setting<Type>::Setting(String key, SettingCallback callback, Type* setting_pointer) {
  this->setKey(key);
  this->setSettingPointer(setting_pointer);
  this->setCallback(callback);
  this->setDefaultValue(setting_pointer ? String(*setting_pointer) : "");
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
void Setting<Type>::setDefaultValue(String default_value) {
  this->default_value = default_value;
}

template <typename Type>
String Setting<Type>::getDefaultValue() {
  return this->default_value;
}

template <typename Type>
bool Setting<Type>::restoreDefaultValue() {
  if (this->getDefaultValue().length() > 0) {
    this->setValue();
    return true;
  }
  return false;
}

template <typename Type>
void Setting<Type>::setValue(String value) {
  if (value.length() == 0 && this->getDefaultValue().length() > 0) value = this->getDefaultValue();
  
  Type setting_value;

  if (this->sameType((Type)1, (bool)true)) {
    setting_value = (value == "true" || value == "1" || value == "on" || value == "yes");
  }
  else if (this->sameType((Type)1, (char)'a')) {
    setting_value = value[0];
  }
  else if (this->sameType((Type)1, (float)1.0)) {
    setting_value = value.toFloat();
  }
  else if (this->sameType((Type)1, (double)1.0)) {
    setting_value = value.toDouble();
  }
  /*else if (this->sameType((Type)1, (unsigned char)1)) {
    char buf[value.length() + 1];
    value.toCharArray(buf, value.length() + 1);
    setting_value = (unsigned char) strtoul(buf, NULL, 10);
  }*/
  else if (this->sameType((Type)1, (int)1)) {
    setting_value = value.toInt();
  }
  /*else if (this->sameType((Type)1, String(1))) {
    setting_value = value;
  }*/
  else {  
    setting_value = value.toInt();
  }
  
  Serial.print(this->getKey()); Serial.print(":"); Serial.print(setting_value); Serial.print(" "); Serial.println( TYPE_NAME(setting_value) );

  if (this->setting_pointer) *this->setting_pointer = setting_value;
  if (this->callback) this->callback(setting_value);
}

// BOOL, CHAR, INT, FLOAT, DOUBLE, STRING

/*template <typename Type>
void Setting<Type>::setValue(String value) {
  if (value.length() == 0 && this->getDefaultValue().length() > 0) value = this->getDefaultValue();
  
  Type setting_value = value.toInt();
  
  if (this->setting_pointer) *this->setting_pointer = setting_value;
  if (this->callback) this->callback(setting_value);
}


template <>
void Setting<bool>::setValue(String value) {
  if (value.length() == 0 && this->getDefaultValue().length() > 0) value = this->getDefaultValue();
  
  bool setting_value = (value == "true" || value == "1" || value == "on" || value == "yes");

  if (this->setting_pointer) *this->setting_pointer = setting_value;
  if (this->callback) this->callback(setting_value);
}

template <>
void Setting<char>::setValue(String value) {
  if (value.length() == 0 && this->getDefaultValue().length() > 0) value = this->getDefaultValue();
  
  char setting_value = value[0];

  if (this->setting_pointer) *this->setting_pointer = setting_value;
  if (this->callback) this->callback(setting_value);
}

template <>
void Setting<float>::setValue(String value) {
  if (value.length() == 0 && this->getDefaultValue().length() > 0) value = this->getDefaultValue();
  
  float setting_value = value.toFloat();

  if (this->setting_pointer) *this->setting_pointer = setting_value;
  if (this->callback) this->callback(setting_value);
}

template <>
void Setting<double>::setValue(String value) {
  if (value.length() == 0 && this->getDefaultValue().length() > 0) value = this->getDefaultValue();
  
  double setting_value = value.toDouble();

  if (this->setting_pointer) *this->setting_pointer = setting_value;
  if (this->callback) this->callback(setting_value);
}

template <>
void Setting<String>::setValue(String value) {
  if (value.length() == 0 && this->getDefaultValue().length() > 0) value = this->getDefaultValue();
  
  if (this->setting_pointer) *this->setting_pointer = value;
  if (this->callback) this->callback(value);
}*/

template <typename Type>
Type Setting<Type>::getValue() {
  return *this->setting_pointer;
}

template <typename Type>
template <typename T>
bool Setting<Type>::sameType(T type1, T type2) {
  return true;
}

template <typename Type>
template <typename T, typename K>
bool Setting<Type>::sameType(T type1, K type2) {
  return true;
}