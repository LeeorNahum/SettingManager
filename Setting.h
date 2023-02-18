#ifndef SETTING_H
#define SETTING_H

#include <WString.h>
#include <stdint.h>
#include "TypeName.h"

class SettingBase {
  public:
    //virtual ~SettingBase() {}
    virtual String getKey() = 0;
    virtual bool restoreDefaultValue() = 0;
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
    
    void setDefaultValue(String default_value = "");
    String getDefaultValue();
    
    bool restoreDefaultValue() override;
    
    void setValue(String value = "") override;
    Type getValue();
    
  private:
    String key;
    Type* setting_pointer;
    SettingCallback callback;
    
    String default_value;
    
    template <typename T>
    static bool sameType(T type1, T type2);
    template <typename T, typename K>
    static bool sameType(T type1, K type2);
    
    void StringThing(String value);
};

#include "Setting.tpp"

#endif