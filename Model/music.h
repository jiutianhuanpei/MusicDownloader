#ifndef MUSIC_H
#define MUSIC_H

#include <QObject>
#include <QVariant>
#include <QVector>
#include "Base/hbtools.h"
#include "Base/commonheaders.h"


class Artist : public QObject
{
    Q_OBJECT
public:
    explicit Artist(QObject *parent = nullptr);
    ~Artist();

    int id;
    QString name;
    QString picUrl;
    QStringList alias;
    int albumSize;
    int picId;
    QString img1v1Url;
    int img1v1;
    QString trans;

    void setValue(const QJsonObject json);

};

class Album : public QObject
{
    Q_OBJECT
public:
    explicit Album(QObject *parent = nullptr);
    ~Album();

    int id;
    QString name;
    Artist *artist = nullptr;
    qint64 publishTime;
    int size;
    int copyrightId;
    int status;
    qint64 picId;
    int mark;

    void setValue(const QJsonObject json);
};


class Music : public QObject
{
    Q_OBJECT
public:
    explicit Music(QObject *parent = nullptr);
    ~Music();

    int id;
    QString name;

    QList<Artist *> artists;
    Album *album;
    double duration;
    int copyrightId;
    int status;

    QStringList alias;

    int rtype;
    int ftype;
    double mvid;
    int fee;
    QString rUrl;
    int mark;

    void setValue(const QJsonObject json);

    QVector<QVariant> itemData();


    QString showName(const NameType type);
};


class MusicList : public QObject
{
    Q_OBJECT
public:
    explicit MusicList(QObject *parent = nullptr);
    ~MusicList();

    QList<Music *> musicList;
    bool hasMore;
    int songCount;

    void setValue(const QJsonObject json);



};


#endif // MUSIC_H
