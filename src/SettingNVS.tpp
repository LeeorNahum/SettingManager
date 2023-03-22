#ifdef USE_ARDUINO_NVS

template <typename Type>
void SettingNVS<Type>::setKey(String key) {
  if (key.length() > 15) {
    key = key.substring(0, 15);
  }
  this->key = key;
}

template <typename Type>
void SettingNVS<Type>::setSavedValue(Type value) {
  NVS.setInt(this->getKey(), value);
}

template <>
void SettingNVS<float>::setSavedValue(float value) {
  NVS.setFloat(this->getKey(), value);
}

template <>
void SettingNVS<double>::setSavedValue(double value) {
  NVS.setFloat(this->getKey(), value);
}

template <>
void SettingNVS<String>::setSavedValue(String value) {
  NVS.setString(this->getKey(), value);
}

template <typename Type>
Type SettingNVS<Type>::getSavedValue() {
  return NVS.getInt(this->getKey());
}

template <>
float SettingNVS<float>::getSavedValue() {
  return NVS.getFloat(this->getKey());
}

template <>
double SettingNVS<double>::getSavedValue() {
  return NVS.getFloat(this->getKey());
}

template <>
String SettingNVS<String>::getSavedValue() {
  return NVS.getString(this->getKey());
}

template <typename Type>
void SettingNVS<Type>::restoreSavedValue() {
  this->setValue(this->getSavedValue());
}

#endif