#ifndef SETTINGNVS_H
#define SETTINGNVS_H

#ifdef USE_ARDUINO_NVS

#include <ArduinoNvs.h>

template <typename Type = int>
class SettingNVS: public Setting<Type> {
  public:
    template <typename CallbackType>
    SettingNVS(String key, CallbackType callback = nullptr) :
      Setting<Type>(key, callback) {}
    
    template <typename CallbackType>
    SettingNVS(String key, Type default_value, CallbackType callback = nullptr) :
      Setting<Type>(key, default_value, callback) {}
    
    template <typename CallbackType>
    SettingNVS(String key, Type* setting_pointer, CallbackType callback = nullptr) :
      Setting<Type>(key, setting_pointer, callback) {}
    
    void setKey(String key) override;
    
    void setSavedValue(Type value) override;
    Type getSavedValue();
        
    void restoreSavedValue() override;
};

#include "SettingNVS.tpp"

#endif
#endif