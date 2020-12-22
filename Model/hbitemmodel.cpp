#include "hbitemmodel.h"
#include <QDebug>

HBItemModel::HBItemModel( QObject *parent)
    : QAbstractItemModel(parent)
{
    m_header = new HBItem(QVector<QVariant>() << "歌名" << "歌手" << "状态" << "id");
}

void HBItemModel::setData(const QList<Music *> data)
{

    if (m_header->childrenNum() > 0)
    {
        beginRemoveRows(QModelIndex(), 0, m_header->childrenNum());
        m_header->clear();
        endRemoveRows();
    }

    beginInsertRows(QModelIndex(), 0, data.count());


    foreach (Music *m, data) {

        HBItem *item = new HBItem(m->itemData(), m_header);
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
    if (orientation != Qt::Horizontal || role != Qt::EditRole)
        return false;
    return true;
}

QModelIndex HBItemModel::index(int row, int column, const QModelIndex &parent) const
{
    HBItem *parentItem = m_getItem(parent);
    HBItem *item = parentItem->child(row);
    if (item)
        return createIndex(row, column, item);

    return QModelIndex();
}

QModelIndex HBItemModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    HBItem *item = m_getItem(index);
    HBItem *parentItem = item->parentItem();

    if (parentItem == m_header || parentItem == nullptr)
        return QModelIndex();

    return createIndex(parentItem->index(), 0, parentItem);
}

int HBItemModel::rowCount(const QModelIndex &parent) const
{
    HBItem *parentitem = m_getItem(parent);

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

    HBItem *item = m_getItem(index);

    return item->data(index.column());

}

HBItem *HBItemModel::m_getItem(const QModelIndex &index) const
{
    if (index.isValid())
    {
        HBItem *item = static_cast<HBItem *>(index.internalPointer());
        if (item)
            return item;
    }
    return m_header;
}
