#include "hbitemmodel.h"
#include <QDebug>

HBItemModel::HBItemModel( QObject *parent)
    : QAbstractItemModel(parent)
{

    QVector<QVariant> header;
//    header << "歌名" << "歌手" << "状�? << "iid";
    header << "SongName" << "Songer" << "Status" << "Id";

    qDebug() << "Header: " << header;

    Music *music = new Music;
    music->name = "SongName";

    m_header = new HBMusicItem(music);
}

void HBItemModel::setData(const QList<Music *> data)
{

    if (m_header->childrenNum() > 0)
    {
        beginRemoveRows(QModelIndex(), 0, m_header->childrenNum() - 1);
        m_header->clear();
        endRemoveRows();
    }

    beginInsertRows(QModelIndex(), 0, data.count());


    foreach (Music *m, data) {

        HBMusicItem *item = new HBMusicItem(m, m_header);
        m_header->appendChild(item);
    }

    endInsertRows();

}

QVariant HBItemModel::headerData(int section, Qt::Orientation orientation, int role) const
{

    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        QString h = m_header->data(section).toString();
        return h;
    }
    return QVariant();
}

bool HBItemModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    Q_UNUSED(section);
    Q_UNUSED(value);

    if (orientation != Qt::Horizontal || role != Qt::EditRole)
        return false;
    return true;
}

QModelIndex HBItemModel::index(int row, int column, const QModelIndex &parent) const
{
    HBMusicItem *parentItem = m_getItem(parent);
    if (parentItem == nullptr)
        return QModelIndex();
    HBMusicItem *item = parentItem->child(row);
    if (item)
        return createIndex(row, column, item);

    return QModelIndex();
}

QModelIndex HBItemModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    HBMusicItem *item = m_getItem(index);
    HBMusicItem *parentItem = item->parentItem();

    if (parentItem == m_header || parentItem == nullptr)
        return QModelIndex();

    return createIndex(parentItem->index(), 0, parentItem);
}

int HBItemModel::rowCount(const QModelIndex &parent) const
{
    HBMusicItem *parentitem = m_getItem(parent);

    return parentitem->childrenNum();
}

int HBItemModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_header->columnNum();
}

QVariant HBItemModel::data(const QModelIndex &index, int role) const
{

    if (!index.isValid() || role != Qt::DisplayRole)
        return QVariant();

    HBMusicItem *item = m_getItem(index);

    return item->data(index.column());

}

HBMusicItem *HBItemModel::m_getItem(const QModelIndex &index) const
{
    if (index.isValid())
    {
        HBMusicItem *item = static_cast<HBMusicItem *>(index.internalPointer());
        if (item)
            return item;
    }
    return m_header;
}
