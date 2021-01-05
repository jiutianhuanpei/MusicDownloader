#ifndef NETCLIENT_H
#define NETCLIENT_H

#include <QObject>
#include <QVariantMap>
#include <QJsonObject>

#include "Model/music.h"

#define DefaultName "default"

class NetClient : public QObject
{
    Q_OBJECT
public:
    explicit NetClient(QObject *parent = nullptr);
    ~NetClient();

    enum HttpType {
        GET,
        POST
    };



    static int httpUrlStr(const HttpType type, const QString urlStr, const QVariantMap param, QJsonObject &response);
    static int http(const HttpType type, const QString path, const QVariantMap param, QJsonObject &response);


    static int fetchMusic(const QString keywords, const int page, const int pageSize, MusicList & musicList);

    static int fetchMusicEnable(const int musicId, bool & enable);

    static int downloadFile(const QString urlStr, const QString toDirPath, QString &downloadFilePath, const QString fileName = "default", const std::function<void(qint64 bytesReceived, qint64 bytesTotal)>& progress = nullptr);


signals:

};



#endif // NETCLIENT_H
