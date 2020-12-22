#ifndef NETTOOLS_H
#define NETTOOLS_H

#include <QObject>
#include <QVariantMap>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

namespace NetTools {

QString queryPathFrom(const QVariantMap param);
QByteArray postBodyFrom(const QVariantMap param);

}

#endif // NETTOOLS_H
