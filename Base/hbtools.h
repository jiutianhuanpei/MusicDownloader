#ifndef HBTOOLS_H
#define HBTOOLS_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

namespace HBTools {

int getInt(const QJsonObject json, const QString key);
double getDouble(const QJsonObject json, const QString key);
QString getString(const QJsonObject json, const QString key);
QJsonArray getArray(const QJsonObject json, const QString key);
QJsonObject getObject(const QJsonObject json, const QString key);
bool getBool(const QJsonObject json, const QString key);

QJsonObject jsonFromStr(const QString str);
QByteArray stringFromJson(const QJsonObject json, QJsonDocument::JsonFormat formate = QJsonDocument::Indented);



}

#endif // HBTOOLS_H
