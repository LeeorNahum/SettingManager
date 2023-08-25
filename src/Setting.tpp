template <typename Type>
Setting<Type>::Setting(String key, Type* var, Type default_value)
  : key((key.length() > 15) ? key.substring(0, 15) : key), var(var), default_value(default_value) {}

template <typename Type>
Setting<Type>::Setting(String key, Type* var)
  : key((key.length() > 15) ? key.substring(0, 15) : key), var(var), default_value(*var) {}

template <typename Type>
void Setting<Type>::loadSavedSetting() {
  *var = NVS.getInt(this->key, this->default_value);
}

template <>
void Setting<float>::loadSavedSetting() {
  *var = NVS.getFloat(this->key, this->default_value);
}

template <>
void Setting<String>::loadSavedSetting() {
  String result = NVS.getString(this->key);
  *var = (result == String()) ? this->default_value : result;
}

template <typename Type>
void Setting<Type>::loadDefaultSetting() {
  *var = this->default_value;
}

template <typename Type>
void Setting<Type>::saveSetting() {
  NVS.setInt(this->key, *var, false);
}

template <>
void Setting<float>::saveSetting() {
  NVS.setFloat(this->key, *var, false);
}

template <>
void Setting<String>::saveSetting() {
  NVS.setString(this->key, *var, false);
}
