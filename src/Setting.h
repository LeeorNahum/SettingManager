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

template <typename Type>
class Setting: public SettingBase {
  public:
    using Callback = void (*)(Type);
    using CallbackVoid = void (*)();
    using SetValueCallback = Type (*)(Type);
    using SetValueCallbackVoid = Type (*)();
    
    template <typename CallbackType>
    Setting(String key = "", CallbackType callback = nullptr);
    
    template <typename CallbackType>
    Setting(String key, Type default_value, CallbackType callback = nullptr);
    
    template <typename CallbackType>
    Setting(String key, Type* setting_pointer, CallbackType callback = nullptr);
    
    virtual void setKey(String key);
    String getKey() override;
    bool hasKey();
    
    virtual void setValue(Type value);
    void setValue();
    Type getValue();
    
    Type getSettingPointerValue();
    
    void setDefaultValue(Type default_value = Type{});
    Type getDefaultValue();
    bool hasDefaultValue();
    
    void setSettingPointer(Type* setting_pointer = nullptr);
    Type* getSettingPointer();
    
    void setCallback(Callback callback = nullptr);
    void setCallback(CallbackVoid callback_void);
    void setCallback(SetValueCallback set_value_callback);
    void setCallback(SetValueCallbackVoid set_value_callback_void);
    
    bool restoreDefaultValue() override;
    
    void setValueParseString(String string_value = "") override;
    
  protected:
    String key = "";
    
    Type value = Type{};
    
    Type default_value = Type{};
    
    Type* setting_pointer = nullptr;
    
    Callback callback = nullptr;
    CallbackVoid callback_void = nullptr;
    SetValueCallback set_value_callback = nullptr;
    SetValueCallbackVoid set_value_callback_void = nullptr;
    
    void setCallback(Type default_value);
    void setCallback(Type* setting_pointer);
    
    void setValueNoUpdate(Type value);
    
    #ifdef USE_ARDUINO_NVS
    virtual void setSavedValue(Type value) {}
    
    virtual void restoreSavedValue() {}
    #endif
};

#include "Setting.tpp"

#endif