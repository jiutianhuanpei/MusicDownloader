#include "hbitem.h"

HBItem::HBItem(const QVector<QVariant> data, QObject *parent) : QObject(parent)
{
    m_data = data;
}

HBItem::~HBItem()
{

}

//QString HBItem::showText()
//{
//    return "";
//}

void HBItem::appendChild(HBItem *item)
{
    item->m_parentItem = this;
    m_childItems.append(item);
}

HBItem *HBItem::child(const int row)
{
    if (m_childItems.count() > row)
        return m_childItems[row];
    return nullptr;
}

QVariant HBItem::data(const int column)
{
    return m_data.value(column);
}

int HBItem::index()
{
    if (m_parentItem)
        return m_parentItem->m_childItems.indexOf(const_cast<HBItem *>(this));
    return 0;
}

void HBItem::clear()
{
    foreach (HBItem *i, m_childItems)
    {
        i->deleteLater();
    }
    m_childItems.clear();
}
