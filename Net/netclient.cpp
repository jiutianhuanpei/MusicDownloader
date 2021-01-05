#include "netclient.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>

#include <QEventLoop>

#include "Base/hbtools.h"
#include "nettools.h"

#include <QDebug>
#include <QFile>
#include <QDataStream>

using namespace HBTools;
using namespace NetTools;

NetClient::NetClient(QObject *parent) : QObject(parent)
{

}

NetClient::~NetClient()
{

}

int NetClient::httpUrlStr(const NetClient::HttpType type, const QString url, const QVariantMap param, QJsonObject &response)
{
    QString urlStr = url;

    QNetworkRequest request;

    if (type == GET && !param.isEmpty())
    {
        urlStr = QString("%1?%2").arg(urlStr).arg(queryPathFrom(param));
    }

    request.setUrl(QUrl(urlStr));

    qDebug() << "Url: " << urlStr;

    QNetworkAccessManager manager;

    QNetworkReply *reply;

    if (type == GET)
    {
        reply = manager.get(request);
    }
    else
    {
        QByteArray body = postBodyFrom(param);
        reply = manager.post(request, body);
    }

    QEventLoop loop;
    connect(&manager, &QNetworkAccessManager::finished, &loop, &QEventLoop::quit);
    loop.exec();


    QNetworkReply::NetworkError error = reply->error();

    if (error != QNetworkReply::NoError)
    {
        qDebug() << "NetError: " << reply->errorString();
        reply->deleteLater();
        return static_cast<int>(error);
    }


    QByteArray re = reply->readAll();

    reply->deleteLater();
    qDebug() << "\n\n\n" << "NetResponse: " << re << "\n\n\n";


    QJsonDocument doc = QJsonDocument::fromJson(re);
    response = doc.object();

    return 0;
}

int NetClient::http(const HttpType type, const QString path, const QVariantMap param, QJsonObject &response)
{
    QString urlStr = "http://musicapi.leanapp.cn/" + path;

    return httpUrlStr(type, urlStr, param, response);
}

int NetClient::fetchMusic(const QString keywords, const int page, const int pageSize, MusicList& musicList)
{

    QVariantMap param;
    param.insert("keywords", keywords);
    param.insert("limit", pageSize);
    param.insert("offset", page * pageSize);


    QJsonObject json;

    int ret = http(GET, "search", param, json);
    if (ret != 0)
        return ret;

    int code = getInt(json, "code");
    if (code != 200)
    {
        qDebug()  << "FetchMusicList failure: " << code;
        return code;
    }

    QJsonObject resultObj = getObject(json, "result");

    musicList.setValue(resultObj);

    return 0;
}

int NetClient::fetchMusicEnable(const int musicId, bool &enable)
{
    QVariantMap param;
    param.insert("id", musicId);

    QJsonObject json;
    int ret = http(GET, "check/music", param, json);

    if (ret != 0)
        return ret;

    bool en = getBool(json, "success");
    enable = en;

    return 0;
}

int NetClient::downloadFile(const QString urlStr, const QString toDirPath, QString &downloadFilePath, const QString fileName, const std::function<void(qint64 bytesReceived, qint64 bytesTotal)>& progress)
{
    QNetworkRequest request;
    request.setUrl(QUrl(urlStr));

    QNetworkAccessManager manager;

    QNetworkReply *reply = manager.get(request);

    QEventLoop loop;
    connect(&manager, &QNetworkAccessManager::finished, &loop, &QEventLoop::quit);

    if (progress != nullptr)
    {
        connect(reply, &QNetworkReply::downloadProgress, [&, progress](qint64 _bytesReceived, qint64 _bytesTotal) {
            progress(_bytesReceived, _bytesTotal);
        });
    }


    loop.exec();

    QString redirectionUrl = reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toString();

    if (!redirectionUrl.isEmpty())
    {
        qDebug() << "Enter redirection: " << redirectionUrl;
        reply->deleteLater();
        return downloadFile(redirectionUrl, toDirPath, downloadFilePath, fileName, progress);
    }


    QNetworkReply::NetworkError error = reply->error();

    if (error != QNetworkReply::NoError)
    {
        qDebug() << "NetError: " << reply->errorString();
        reply->deleteLater();
        return static_cast<int>(error);
    }

    QByteArray re = reply->readAll();
    reply->deleteLater();

    if (re.isEmpty())
    {
        qDebug() << "Download failure";
        return -1;
    }


    QString filePath = QString("%1/%2").arg(toDirPath, fileName);

    if (fileName == DefaultName)
    {
        filePath = QString("%1/%2").arg(toDirPath).arg(QUrl(urlStr).fileName());
    }
    qDebug() << "Write file" << filePath;

    QFile *file = new QFile(filePath);
    file->open(QIODevice::WriteOnly);

    file->write(re);
    file->flush();
    file->close();
    downloadFilePath = filePath;
    return 0;
}
