#ifndef ROOTWGT_H
#define ROOTWGT_H

#include <QWidget>
#include "Model/hbitemmodel.h"
#include "Model/music.h"
#include <QItemSelectionModel>

namespace Ui {
class RootWgt;
}

class RootWgt : public QWidget
{
    Q_OBJECT

public:
    explicit RootWgt(QWidget *parent = nullptr);
    ~RootWgt();



signals:
    void signal_didReceivedMusicList();

private slots:
    void slot_didReceiveMusicList();

    void on_pBtn_search_clicked();

    void on_pBtn_last_clicked();

    void on_pBtn_next_clicked();

    void on_pBtn_download_clicked();
	void on_pBtn_tryListen_clicked();
    void slot_didSelectedItem(const QModelIndex &current, const QModelIndex &previous);


    void on_pBtn_setting_clicked();

    void on_pEdit_search_returnPressed();

    void slot_didDoubleClickedItem(const QModelIndex& index);

private:
    Ui::RootWgt *ui;
    HBItemModel *m_model;
    QItemSelectionModel *m_selectionModel;

    MusicList m_currentList;

    int m_page = 0;
    int m_pageSize = 20;


private:
    void m_fetchOnePageMusic();

};

#endif // ROOTWGT_H
