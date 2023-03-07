#ifndef SETTING_H
#define SETTING_H

#include <WString.h>

class SettingBase {
  public:
    virtual String getKey() = 0;
    virtual bool restoreDefaultSetting() = 0;
    virtual void setValueParseString(String string_value = "") = 0;
};

template <typename Type>
class Setting: public SettingBase {
  public:
    using SettingCallback = void (*)(Type);
    using SettingCallbackVoid = void (*)();
    //using UpdateSettingCallback = Type (*)(Type);
    //using UpdateSettingCallbackVoid = Type (*)();
    
    Setting(String key, Type default_setting, SettingCallback callback = nullptr);
    Setting(String key, Type default_setting, SettingCallbackVoid callback_void);
    Setting(String key, Type* setting_pointer, SettingCallback callback = nullptr);
    Setting(String key, Type* setting_pointer, SettingCallbackVoid callback_void);
    Setting(String key, SettingCallback callback, Type* setting_pointer = nullptr);
    Setting(String key, SettingCallbackVoid callback_void, Type* setting_pointer = nullptr);
    
    void setKey(String key);
    String getKey() override;
    
    void setValue(Type value);
    void setValue();
    Type getValue();
    
    Type getSettingPointerValue();
    
    void setDefaultSetting(Type default_setting);
    void setDefaultSetting(); // TODO ? rename Setting to Value
    Type getDefaultSetting();
    bool hasDefaultSetting();
    
    void setSettingPointer(Type* setting_pointer = nullptr);
    Type* getSettingPointer();
    
    void setCallback(SettingCallback callback = nullptr);
    void setCallback(SettingCallbackVoid callback_void = nullptr);
    
    bool restoreDefaultSetting() override;
    
    void setValueParseString(String string_value = "") override;
    
  private:
    String key = "";
    
    Type value = Type{};
    
    bool has_default_setting = false;
    Type default_setting = Type{};
    
    Type* setting_pointer = nullptr;
    
    SettingCallback callback = nullptr;
    SettingCallbackVoid callback_void = nullptr;
};

#include "Setting.tpp"

#endif