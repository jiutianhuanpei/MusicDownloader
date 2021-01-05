#include "rootwgt.h"
#include "ui_rootwgt.h"
#include <QtWidgets/QTreeView>
#include <Net/netclient.h>
#include "Model/HBMusicItem.h"
#include <QDebug>
#include "settingwgt.h"
#include "Base/settingconfig.h"
#include <QProgressBar>
#include <QMetaType>

RootWgt::RootWgt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RootWgt)
{
//    qRegisterMetaType<MusicList>("MusicList");
//    qRegisterMetaType<MusicList>("MusicList&");
    //qRegisterMetaType<MusicList>("const MusicList&");


    ui->setupUi(this);
    m_model = new HBItemModel(this);
    ui->treeView->setModel(m_model);

    m_selectionModel = new QItemSelectionModel(m_model);
    ui->treeView->setSelectionModel(m_selectionModel);


    connect(this, &RootWgt::signal_didReceivedMusicList, this, &RootWgt::slot_didReceiveMusicList);

    connect(m_selectionModel, &QItemSelectionModel::currentRowChanged, this, &RootWgt::slot_didSelectedItem);
    connect(ui->treeView, &QTreeView::doubleClicked, this, &RootWgt::slot_didDoubleClickedItem);
}

RootWgt::~RootWgt()
{
    delete ui;
}


void RootWgt::on_pBtn_search_clicked()
{
    m_selectionModel->reset();
    m_page = 0;
    m_fetchOnePageMusic();
}

void RootWgt::on_pBtn_last_clicked()
{

   m_page--;
   m_fetchOnePageMusic();
}

void RootWgt::on_pBtn_next_clicked()
{
    m_page++;
    m_fetchOnePageMusic();
}

void RootWgt::on_pBtn_download_clicked()
{
    HBMusicItem *item = static_cast<HBMusicItem *>(m_selectionModel->currentIndex().internalPointer());

    Music *music = item->currentMusic();

	QString url = music->downloadUrlStr();

    qDebug() << url;

    QString downloadDir = SettingCore()->setting(DownloadDirPath).toString();
    int type = SettingCore()->setting(SaveType).toInt();


    QString localPath;
    NetClient::downloadFile(url, downloadDir, localPath, music->showName(static_cast<NameType>(type)) + ".mp3", [&](qint64 received, qint64 total) {

        qDebug() << "Progress: " << received << "  " << total;

        if (total == 0)
            return ;

        int pro = static_cast<int>((static_cast<float>(received) / static_cast<float>(total)) * 100);



    });

}

void RootWgt::on_pBtn_tryListen_clicked()
{
	HBMusicItem *item = static_cast<HBMusicItem *>(m_selectionModel->currentIndex().internalPointer());

	Music *music = item->currentMusic();

	QString url = music->downloadUrlStr();

	qDebug() << "I'll listen music: " << url;

}

void RootWgt::slot_didSelectedItem(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(previous);

	if (!current.isValid())
		return;

    HBMusicItem *item = static_cast<HBMusicItem *>(current.internalPointer());

    Music *music = item->currentMusic();
    QString urlStr = music->downloadUrlStr();

//    std::thread th([&]{

//        bool enable = false;
//        NetClient::fetchMusicEnable(music->id, enable);
//    });

//    ui->pLbl_status->setText(enable ? "YES" : "NO");

//    ui->pLbl_url->setText(urlStr);

}

void RootWgt::m_fetchOnePageMusic()
{

    std::thread th([&]{
        NetClient::fetchMusic(ui->pEdit_search->text(), m_page, m_pageSize, m_currentList);

        emit signal_didReceivedMusicList();
    });
    th.detach();
}

void RootWgt::slot_didReceiveMusicList()
{

    qDebug() << "Will setData";
    m_model->setData(m_currentList.musicList);

    qDebug() << "Did setData";

    ui->pBtn_last->setEnabled(m_page != 0);
    ui->pBtn_next->setEnabled(m_currentList.hasMore);
}


void RootWgt::on_pBtn_setting_clicked()
{
    SettingWgt *set = new SettingWgt;
    set->show();
}

void RootWgt::on_pEdit_search_returnPressed()
{
    on_pBtn_search_clicked();
}

void RootWgt::slot_didDoubleClickedItem(const QModelIndex &index)
{
    HBMusicItem *item = static_cast<HBMusicItem *>(index.internalPointer());

    Music *music = item->currentMusic();

    ui->control_wgt->setCurrentMusic(music);

    QString url = music->downloadUrlStr();

    qDebug() << "I'll listen music: " << url;



}
