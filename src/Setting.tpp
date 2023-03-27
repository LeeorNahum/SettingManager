template <typename Type>
Setting<Type>::Setting(String key, Callback callback) {
  this->setKey(key);
  this->setCallback(callback);
}

template <typename Type>
Setting<Type>::Setting(String key, ValueCallback value_callback) {
  this->setKey(key);
  this->setCallback(value_callback);
}

template <typename Type>
Setting<Type>::Setting(String key, ValuePointerCallback value_pointer_callback) {
  this->setKey(key);
  this->setCallback(value_pointer_callback);
}

template <typename Type>
Setting<Type>::Setting(String key, Type default_value, Callback callback) {
  this->setKey(key);
  this->setValueNoCallbacks(default_value);
  this->setDefaultValue(default_value);
  this->setCallback(callback);
}

template <typename Type>
Setting<Type>::Setting(String key, Type default_value, ValueCallback value_callback) {
  this->setKey(key);
  this->setValueNoCallbacks(default_value);
  this->setDefaultValue(default_value);
  this->setCallback(value_callback);
}

template <typename Type>
Setting<Type>::Setting(String key, Type default_value, ValuePointerCallback value_pointer_callback) {
  this->setKey(key);
  this->setValueNoCallbacks(default_value);
  this->setDefaultValue(default_value);
  this->setCallback(value_pointer_callback);
}

template <typename Type>
Setting<Type>::Setting(String key, Type* setting_pointer, Callback callback) {
  this->setKey(key);
  this->setSettingPointer(setting_pointer);
  this->setCallback(callback);
}

template <typename Type>
Setting<Type>::Setting(String key, Type* setting_pointer, ValueCallback value_callback) {
  this->setKey(key);
  this->setSettingPointer(setting_pointer);
  this->setCallback(value_callback);
}

template <typename Type>
Setting<Type>::Setting(String key, Type* setting_pointer, ValuePointerCallback value_pointer_callback) {
  this->setKey(key);
  this->setSettingPointer(setting_pointer);
  this->setCallback(value_pointer_callback);
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
bool Setting<Type>::hasKey() {
  return this->getKey().length() != 0;
}

template <typename Type>
void Setting<Type>::setValue(Type value) {
  if (this->value_pointer_callback != nullptr) this->value_pointer_callback(&value);
  else if (this->value_callback != nullptr) this->value_callback(value);
  else if (this->callback != nullptr) this->callback();
  
  this->setValueNoCallbacks(value);
  
  #ifdef USE_ARDUINO_NVS
  this->setSavedValue(value);
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
  if (this->setting_pointer != nullptr) {
    return *this->setting_pointer;
  }
  return this->getDefaultValue();
}

template <typename Type>
void Setting<Type>::setDefaultValue(Type default_value) {
  this->has_default_value = true;
  this->default_value = default_value;
}

template <typename Type>
void Setting<Type>::setDefaultValue() {
  this->has_default_value = false;
  this->default_value  = Type{};
}

template <typename Type>
Type Setting<Type>::getDefaultValue() {
  return this->default_value;
}

template <typename Type>
bool Setting<Type>::hasDefaultValue() {
  return this->has_default_value;
}

template <typename Type>
void Setting<Type>::setSettingPointer(Type* setting_pointer) {
  this->setting_pointer = setting_pointer;
  if (setting_pointer != nullptr) {
    this->setValueNoCallbacks(*setting_pointer);
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
void Setting<Type>::setCallback(Callback callback) {
  this->callback = callback;
  if (callback != nullptr) {
    this->value_callback = nullptr;
    this->value_pointer_callback = nullptr;
  }
}

template <typename Type>
void Setting<Type>::setCallback(ValueCallback value_callback) {
  this->value_callback = value_callback;
  if (value_callback != nullptr) {
    this->callback = nullptr;
    this->value_pointer_callback = nullptr;
  }
}

template <typename Type>
void Setting<Type>::setCallback(ValuePointerCallback value_pointer_callback) {
  this->value_pointer_callback = value_pointer_callback;
  if (value_pointer_callback != nullptr) {
    this->callback = nullptr;
    this->value_callback = nullptr;
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
  
  string_value.toLowerCase();
  bool bool_value = (string_value == "true" || string_value == "1" || string_value == "yes" || string_value == "on" || string_value == "high");
  
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

template <typename Type>
void Setting<Type>::setValueNoCallbacks(Type value) {
  this->value = value;
  if (this->setting_pointer != nullptr) *this->setting_pointer = value;
}