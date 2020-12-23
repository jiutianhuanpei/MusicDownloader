#include "settingconfig.h"
#include <QFile>
#include <QMutex>
#include "hbtools.h"
#include <QDebug>

using namespace HBTools;

SettingConfig * SettingConfig::m_Instance = nullptr;

static QMutex k_setting_mutex;

const QString SettingFilePath = ".setPath";

SettingConfig *SettingConfig::shared()
{
    if (m_Instance == nullptr)
    {
        QMutexLocker locker(&k_setting_mutex);
        if (m_Instance == nullptr)
        {
            m_Instance = new SettingConfig;

            QFile file(SettingFilePath);
            if (!file.exists())
            {
                file.open(QIODevice::WriteOnly);
                file.write("");
                file.close();
            }

        }
    }
    return m_Instance;
}

void SettingConfig::setSetting(const SettingType type, QJsonValue value)
{
    QString key = keyFromType(type);
    if (key.isEmpty())
        return;

    QFile file(SettingFilePath);
    file.open(QIODevice::ReadWrite);
    QString allStr = file.readAll();


    QJsonObject json = jsonFromStr(allStr);
    json[key] = value;

    QByteArray str = stringFromJson(json);

    m_settingConfigStr = str;
    file.reset();
    file.write(str);
    file.close();

}

QJsonValue SettingConfig::setting(const SettingType type)
{
    QString key = keyFromType(type);
    if (key.isEmpty())
        return QJsonValue();

    if (m_settingConfigStr.isEmpty())
    {
        QFile file(SettingFilePath);
        file.open(QIODevice::ReadOnly);

        m_settingConfigStr = file.readAll();
        file.close();
    }

    QJsonObject json = jsonFromStr(m_settingConfigStr);
    return json.value(key);
}

SettingConfig::SettingConfig(QObject *parent) : QObject(parent)
{

}

SettingConfig::~SettingConfig()
{

}

QString SettingConfig::keyFromType(const SettingType type)
{
    if (type == SaveType)
        return "SaveType";
    if (type == DownloadDirPath)
        return "DownloadDirPath";
    return "";
}

SettingConfig * SettingCore()
{
    return SettingConfig::shared();
}
