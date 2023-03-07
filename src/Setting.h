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
    //using UpdateSettingCallback = Type (*)(Type);
    //using UpdateSettingCallbackVoid = Type (*)();
    
    Setting(String key, Type default_value, SettingCallback callback = nullptr);
    Setting(String key, Type default_value, SettingCallbackVoid callback_void);
    Setting(String key, Type* setting_pointer, SettingCallback callback = nullptr);
    Setting(String key, Type* setting_pointer, SettingCallbackVoid callback_void);
    Setting(String key, SettingCallback callback);
    Setting(String key, SettingCallbackVoid callback_void);
    
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
};

#include "Setting.tpp"

#endif