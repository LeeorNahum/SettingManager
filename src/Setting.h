#ifndef SETTING_H
#define SETTING_H

#include <WString.h>

class SettingBase {
  public:
    virtual String getKey() = 0;
    virtual bool hasKey() = 0;
    virtual bool restoreDefaultValue() = 0;
    virtual void setValueParseString(String string_value = "") = 0;
    #ifdef USE_ARDUINO_NVS
    virtual void restoreSavedValue() = 0;
    #endif
};

using SettingType = SettingBase*;

template <typename Type = int>
class Setting: public SettingBase {
  public:
    using Callback = void (*)();
    using ValueCallback = void (*)(Type);
    using ValuePointerCallback = void (*)(Type*);
    
    Setting(String key = "", Callback callback = nullptr);
    Setting(String key, ValueCallback value_callback);
    Setting(String key, ValuePointerCallback value_pointer_callback);
    
    Setting(String key, Type default_value, Callback callback = nullptr);
    Setting(String key, Type default_value, ValueCallback value_callback);
    Setting(String key, Type default_value, ValuePointerCallback value_pointer_callback);
    
    Setting(String key, Type* setting_pointer, Callback callback = nullptr);
    Setting(String key, Type* setting_pointer, ValueCallback value_callback);
    Setting(String key, Type* setting_pointer, ValuePointerCallback value_pointer_callback);
    
    virtual void setKey(String key);
    String getKey() override;
    bool hasKey();
    
    virtual void setValue(Type value);
    void setValue();
    Type getValue();
    
    Type getSettingPointerValue();
    
    void setDefaultValue(Type default_value);
    void setDefaultValue();
    Type getDefaultValue();
    bool hasDefaultValue();
    
    void setSettingPointer(Type* setting_pointer = nullptr);
    Type* getSettingPointer();
    
    void setCallback(Callback callback = nullptr);
    void setCallback(ValueCallback value_callback);
    void setCallback(ValuePointerCallback value_pointer_callback);
    
    bool restoreDefaultValue() override;
    
    void setValueParseString(String string_value = "") override;
    
  protected:
    String key = "";
    
    Type value = Type{};
    
    bool has_default_value = false;
    Type default_value = Type{};
    
    Type* setting_pointer = nullptr;
    
    Callback callback = nullptr;
    ValueCallback value_callback = nullptr;
    ValuePointerCallback value_pointer_callback = nullptr;
    
    void setValueNoCallbacks(Type value);
    
    #ifdef USE_ARDUINO_NVS
    virtual void setSavedValue(Type value) {}
    
    virtual void restoreSavedValue() {}
    #endif
};

#include "Setting.tpp"

#endif