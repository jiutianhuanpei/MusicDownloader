#ifndef HBMUSICITEM_H
#define HBMUSICITEM_H

#include <QObject>
#include "music.h"

class HBMusicItem : public QObject
{
    Q_OBJECT
public:
    explicit HBMusicItem(Music *music, QObject *parent = nullptr);
    ~HBMusicItem();

    HBMusicItem *parentItem() { return  m_parentItem;}

    void appendChild(HBMusicItem *item);
    HBMusicItem *child(const int row);

    int childrenNum() { return m_childItems.count();}
    int columnNum() { return 1;}

    QVariant data(const int column);

    int index();

    void clear();

    Music *currentMusic() { return  m_music;}

private:
    Music *m_music;
    QList<HBMusicItem *> m_childItems;
    HBMusicItem *m_parentItem;
};

#endif // HBMUSICITEM_H
