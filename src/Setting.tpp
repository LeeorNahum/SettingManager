template <typename Type>
Setting<Type>::Setting(ArduinoNvs &nvs, String key, Type* var, Type default_value)
  : nvs(nvs), key((key.length() > 15) ? key.substring(0, 15) : key), var(var), default_value(default_value) {}

template <typename Type>
Setting<Type>::Setting(ArduinoNvs &nvs, String key, Type* var)
  : nvs(nvs), key((key.length() > 15) ? key.substring(0, 15) : key), var(var), default_value(*var) {}

template <typename Type>
void Setting<Type>::loadSavedSetting() {
  *this->var = this->nvs.getInt(this->key, this->default_value);
}

template <>
void Setting<float>::loadSavedSetting() {
  *this->var = this->nvs.getFloat(this->key, this->default_value);
}

template <>
void Setting<String>::loadSavedSetting() {
  String result = this->nvs.getString(this->key);
  *this->var = (result == String()) ? this->default_value : result;
}

template <typename Type>
void Setting<Type>::loadDefaultSetting() {
  *this->var = this->default_value;
}

template <typename Type>
void Setting<Type>::saveSetting() {
  this->nvs.setInt(this->key, *this->var, false);
}

template <>
void Setting<float>::saveSetting() {
  this->nvs.setFloat(this->key, *this->var, false);
}

template <>
void Setting<String>::saveSetting() {
  this->nvs.setString(this->key, *this->var, false);
}
