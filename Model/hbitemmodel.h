#ifndef HBITEMMODEL_H
#define HBITEMMODEL_H

#include <QAbstractItemModel>
#include "music.h"
#include "hbitem.h"

class HBItemModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit HBItemModel(QObject *parent = nullptr);


    void setData(const QList<Music *> data);

private:
    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value,
                                   int role = Qt::EditRole);


    // Basic functionality:
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:

    QList<Music *> m_data;


    HBItem *m_header;
    HBItem *m_getItem(const QModelIndex& index) const;


};

#endif // HBITEMMODEL_H
