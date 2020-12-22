#include "nettools.h"

namespace NetTools {

QString queryPathFrom(const QVariantMap param)
{
    QStringList list;

    foreach (QString key, param.keys()) {
        QString str = QString("%1=%2").arg(key).arg(param[key].toString());
        list << str;
    }

    return list.join("&");
}

QByteArray postBodyFrom(const QVariantMap param)
{

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(param));
    return doc.toJson(QJsonDocument::Compact);
}

}
