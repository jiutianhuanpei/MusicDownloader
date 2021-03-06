#include "music.h"


using namespace HBTools;

Music::Music(QObject *parent) : QObject(parent)
{

}

Music::~Music()
{

}

void Music::setValue(const QJsonObject json)
{
    id  = getInt(json, "id");
    name = getString(json, "name");

    QJsonArray artistsArray = getArray(json, "artists");

    artists = QList<Artist *>();

    for (int i = 0; i < artistsArray.count(); i++) {
        QJsonValue v = artistsArray.at(i);
        QJsonObject obj = v.toObject();

        Artist *a = new Artist;
        a->setValue(obj);
        artists << a;
    }

    QJsonObject albumObj = getObject(json, "album");
    album = new Album;
    album->setValue(albumObj);

    duration = getDouble(json, "duration");
    copyrightId = getInt(json, "copyrightId");
    status = getInt(json, "status");

    QJsonArray ary = getArray(json, "alias");
    foreach (QJsonValue value, ary) {
        alias << value.toString();
    }

    rtype = getInt(json, "rtype");
    ftype = getInt(json, "ftype");
    mvid = getDouble(json, "mvid");
    fee = getInt(json, "fee");
    rUrl = getString(json, "rUrl");
    mark = getInt(json, "mark");
}

QVector<QVariant> Music::itemData()
{
    QVector<QVariant> list;
    list << name ;

    list << ((artists.count() > 0) ? artists.first()->name : "");
    list << status;
    list << id;
    return list;
}

QString Music::showName(const NameType type)
{
    if (artists.count() > 0)
    {
        QString singer = artists.first()->name;

        if (type == Song_Singer)
            return QString("%1-%2").arg(name, singer);
        if (type == Singer_Song)
            return QString("%1-%2").arg(singer, name);
    }
    return name;
}

QString Music::downloadUrlStr()
{
	QString urlStr = QString("https://music.163.com/song/media/outer/url?id=%1.mp3").arg(id);
	return urlStr;
}


Artist::Artist(QObject *parent) : QObject(parent)
{

}

Artist::~Artist()
{

}

void Artist::setValue(const QJsonObject json)
{
    id = getInt(json, "id");
    name = getString(json, "name");
    picUrl = getString(json, "picUrl");

    QJsonArray ary = getArray(json, "alias");
    foreach (QJsonValue value, ary) {
        alias << value.toString();
    }

    albumSize = getInt(json, "albumSize");
    picId = getInt(json, "picId");
    img1v1Url = getString(json, "img1v1Url");
    img1v1 = getInt(json, "img1v1");
    trans = getString(json, "trans");
}

Album::Album(QObject *parent) : QObject(parent)
{

}

Album::~Album()
{

}

void Album::setValue(const QJsonObject json)
{

    id = getInt(json, "id");
    name = getString(json, "name");

    QJsonObject obj = getObject(json, "artist");
    artist = new Artist();
    artist->setValue(obj);

    double time = getDouble(json, "publishTime");

    publishTime = static_cast<qint64>(time);
    size = getInt(json, "size");
    copyrightId = getInt(json, "copyrightId");
    status = getInt(json, "status");
    picId = getInt(json, "picId");
    mark = getInt(json, "mark");
}

MusicList::MusicList(QObject *parent): QObject(parent)
{

}

MusicList::~MusicList()
{

}

void MusicList::setValue(const QJsonObject json)
{
    hasMore = getBool(json, "hasMore");
    songCount = getInt(json, "songCount");

    foreach (Music *m, musicList) {
        m->deleteLater();
    }
    musicList.clear();

    QJsonArray songArray = getArray(json, "songs");

    for (int i = 0; i < songArray.count(); i++)
    {
        QJsonObject obj = songArray.at(i).toObject();

        Music *m = new Music;
        m->setValue(obj);
        musicList << m;
    }
}

