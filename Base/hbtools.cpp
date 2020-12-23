#include "hbtools.h"
#include <QJsonValue>

namespace HBTools {

int getInt(const QJsonObject json, const QString key)
{
    QJsonValue value = json.value(key);
    if (value.isDouble())
        return value.toInt();
    return 0;
}

double getDouble(const QJsonObject json, const QString key)
{
    QJsonValue value = json.value(key);
    if (value.isDouble())
        return value.toDouble();
    return 0;
}

QString getString(const QJsonObject json, const QString key)
{
    QJsonValue value = json.value(key);
    if (value.isString())
        return value.toString();
    return "";
}

QJsonArray getArray(const QJsonObject json, const QString key)
{
    QJsonValue value = json.value(key);
    if (value.isArray())
        return value.toArray();
    return QJsonArray();
}

QJsonObject getObject(const QJsonObject json, const QString key)
{
    QJsonValue value = json.value(key);
    if (value.isObject())
        return value.toObject();
    return QJsonObject();
}

bool getBool(const QJsonObject json, const QString key)
{
    QJsonValue value = json.value(key);
    if (value.isBool())
        return value.toBool();
    if (value.isString())
    {
        QString str = value.toString();
        str = str.toLower();
        return str == "yes" || str == "true";
    }
    if (value.isDouble())
    {
        int ret = value.toInt();
        return ret != 0;
    }
    return false;
}

QJsonObject jsonFromStr(const QString str)
{
    QJsonDocument doc = QJsonDocument::fromJson(str.toStdString().c_str());
    return doc.object();
}

QByteArray stringFromJson(const QJsonObject json, QJsonDocument::JsonFormat formate)
{
    QJsonDocument doc(json);
    return doc.toJson(formate);
}



}
