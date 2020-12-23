#ifndef HBITEM_H
#define HBITEM_H

#include <QObject>
#include <QVariant>
#include <QVector>

class HBItem : public QObject
{
    Q_OBJECT
public:
    explicit HBItem(const QVector<QVariant> data = {}, QObject *parent = nullptr);
    ~HBItem();



//    QString showText();

    HBItem *parentItem() { return  m_parentItem;}

    void appendChild(HBItem *item);
    HBItem *child(const int row);

    int childrenNum() { return m_childItems.count();};
    int columnNum() { return m_data.count();}

    QVariant data(const int column);

    int index();

    void clear();



private:

    QVector<QVariant> m_data;
    QList<HBItem *> m_childItems;
    HBItem *m_parentItem;

};

#endif // HBITEM_H
