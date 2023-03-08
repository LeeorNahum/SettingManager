#ifndef SETTING_H
#define SETTING_H

#include <WString.h>

class SettingBase {
  public:
    virtual String getKey() = 0;
    virtual bool restoreDefaultValue() = 0;
    virtual void setValueParseString(String string_value = "") = 0;
    #ifdef USE_ARDUINO_NVS
    virtual void restoreSavedValue() = 0;
    #endif
};

template <typename Type>
class Setting: public SettingBase {
  public:
    using SettingCallback = void (*)(Type);
    using SettingCallbackVoid = void (*)();
    
    #ifndef USE_ARDUINO_NVS
    Setting(String key, Type default_value, SettingCallback callback = nullptr);
    Setting(String key, Type default_value, SettingCallbackVoid callback_void);
    Setting(String key, Type* setting_pointer, SettingCallback callback = nullptr);
    Setting(String key, Type* setting_pointer, SettingCallbackVoid callback_void);
    Setting(String key, SettingCallback callback);
    Setting(String key, SettingCallbackVoid callback_void);
    #else
    Setting(String key, Type default_value, SettingCallback callback = nullptr, bool use_nvs = true);
    Setting(String key, Type default_value, SettingCallbackVoid callback_void, bool use_nvs = true);
    Setting(String key, Type* setting_pointer, SettingCallback callback = nullptr, bool use_nvs = true);
    Setting(String key, Type* setting_pointer, SettingCallbackVoid callback_void, bool use_nvs = true);
    Setting(String key, SettingCallback callback, bool use_nvs = true);
    Setting(String key, SettingCallbackVoid callback_void, bool use_nvs = true);
    #endif
    
    void setKey(String key);
    String getKey() override;
    
    void setValue(Type value);
    void setValue();
    Type getValue();
    
    Type getSettingPointerValue();
    
    void setDefaultValue(Type default_value);
    void setDefaultValue();
    Type getDefaultValue();
    bool hasDefaultValue();
    
    void setSettingPointer(Type* setting_pointer = nullptr);
    Type* getSettingPointer();
    
    void setCallback(SettingCallback callback = nullptr);
    void setCallback(SettingCallbackVoid callback_void = nullptr);
    
    bool restoreDefaultValue() override;
    
    void setValueParseString(String string_value = "") override;
    
    #ifdef USE_ARDUINO_NVS
    void useNVS(bool use_nvs);
    
    void restoreSavedValue() override;
    
    void setValueNVS(Type value);
    Type getValueNVS();
    #endif
    
  private:
    String key = "";
    
    Type value = Type{};
    
    bool has_default_setting = false;
    Type default_value = Type{};
    
    Type* setting_pointer = nullptr;
    
    SettingCallback callback = nullptr;
    SettingCallbackVoid callback_void = nullptr;
    
    #ifdef USE_ARDUINO_NVS
    bool use_nvs = true;
    #endif
};

#include "Setting.tpp"

#endif