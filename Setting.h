#ifndef SETTING_H
#define SETTING_H

#include <WString.h>

class SettingBase {
  public:
    virtual String getKey() = 0;
    virtual void restoreDefaultSetting() = 0;
    virtual void setValue(String value = "") = 0;
};

template <typename Type>
class Setting: public SettingBase {
  public:
    using SettingCallback = void (*)(Type); // using SettingCallback = void (*)(Setting<Type>*);
    
    Setting(String key, Type* setting_pointer, SettingCallback callback = nullptr);
    Setting(String key, SettingCallback callback, Type* setting_pointer = nullptr);
    
    void setKey(String key);
    String getKey() override;
    
    void setSettingPointer(Type* setting_pointer = nullptr);
    Type* getSettingPointer();
    
    void setCallback(SettingCallback callback = nullptr);
    
    void setDefaultSetting(String default_setting = "");
    String getDefaultSetting();
    
    void restoreDefaultSetting() override;
    
    void setValue(String value = "") override;
    Type getValue();
    
  private:
    String key = "";
    Type* setting_pointer = nullptr;
    SettingCallback callback = nullptr;
    
    String default_setting = "";
};

#include "Setting.tpp"

#endif