#include "hbmusicitem.h"
#include "Base/settingconfig.h"
#include <QDebug>

HBMusicItem::HBMusicItem(Music *music, QObject *parent) : QObject(parent), m_music(music)
{

}

HBMusicItem::~HBMusicItem()
{
    clear();
    m_music->deleteLater();
    m_parentItem->deleteLater();
}

void HBMusicItem::appendChild(HBMusicItem *item)
{
    item->m_parentItem = this;
    m_childItems.append(item);
}

HBMusicItem *HBMusicItem::child(const int row)
{
    if (m_childItems.count() > row)
        return m_childItems[row];
    return nullptr;
}

QVariant HBMusicItem::data(const int column)
{
    Q_UNUSED(column);
    int i = SettingCore()->setting(SaveType).toInt();

    return m_music->showName(static_cast<NameType>(i));
}

int HBMusicItem::index()
{
    if (m_parentItem)
            return m_parentItem->m_childItems.indexOf(const_cast<HBMusicItem *>(this));
        return 0;
}

void HBMusicItem::clear()
{
    foreach (HBMusicItem *i, m_childItems)
    {
		qDebug() << "Child item clear: " << i;
		i->clear();
    }
	qDebug() << "Items Num: " << m_childItems.count();
    m_childItems.clear();
	qDebug() << "Items Num: " << m_childItems.count() << "end;";
}





