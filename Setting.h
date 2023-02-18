#ifndef SETTING_H
#define SETTING_H

#include <WString.h>

//
// Generic catch-all implementation.
template <typename T_ty> struct TypeInfo { static const char * name; };
template <typename T_ty> const char * TypeInfo<T_ty>::name = "unknown";

// Handy macro to make querying stuff easier.
#define TYPE_NAME(var) TypeInfo< typeof(var) >::name

// Handy macro to make defining stuff easier.
#define MAKE_TYPE_INFO(type)  template <> const char * TypeInfo<type>::name = #type;

// Type-specific implementations.
MAKE_TYPE_INFO( int )
MAKE_TYPE_INFO( float )
MAKE_TYPE_INFO( String )
//

class SettingBase {
  public:
    virtual ~SettingBase() {} //
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
};

#include "Setting.tpp"

#endif