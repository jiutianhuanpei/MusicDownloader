#ifndef SETTINGCONFIG_H
#define SETTINGCONFIG_H

#include <QJsonValue>
#include <QObject>
#include <QVariant>
#include "commonheaders.h"

class SettingConfig : public QObject
{
    Q_OBJECT
public:

    static SettingConfig *shared();

    void setSetting(const SettingType type, QJsonValue value);
    QJsonValue setting(const SettingType type);

private:
    explicit SettingConfig(QObject *parent = nullptr);
    ~SettingConfig();

    QString m_settingConfigStr;

    static SettingConfig *m_Instance;

    QString keyFromType(const SettingType type);


};

SettingConfig * SettingCore();

#endif // SETTINGCONFIG_H
