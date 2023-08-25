#ifndef SETTING_H
#define SETTING_H

class SettingBase {
  public:
  virtual ~SettingBase() = default;
  virtual void loadSavedSetting() = 0;
  virtual void loadDefaultSetting() = 0;
  virtual void saveSetting() = 0;

  private:
  friend class SettingManager;
};

template <typename Type = int>
class Setting : public SettingBase {
  public:
  void loadSavedSetting() override;
  void loadDefaultSetting() override;
  void saveSetting() override;

  private:
  friend class SettingManager;

  Setting(String key, Type* var, Type default_value);
  Setting(String key, Type* var);

  String key;
  Type* var; // TODO ? enum typecasting
  Type default_value;
};

#include "Setting.tpp"

#endif /* SETTING_H */
