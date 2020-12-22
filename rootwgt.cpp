#include "rootwgt.h"
#include "ui_rootwgt.h"
#include <QtWidgets/QTreeView>
#include <Net/netclient.h>
#include "Model/hbitem.h"

RootWgt::RootWgt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RootWgt)
{
    ui->setupUi(this);
    m_model = new HBItemModel(this);
    ui->treeView->setModel(m_model);

    m_selectionModel = new QItemSelectionModel(m_model);
    ui->treeView->setSelectionModel(m_selectionModel);

    connect(m_selectionModel, &QItemSelectionModel::currentRowChanged, this, &RootWgt::slot_didSelectedItem);
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

    QString url = ui->pLbl_url->text();

//    url = "https://ss1.bdstatic.com/70cFuXSh_Q1YnxGkpoWK1HF6hhy/it/u=743529986,3105896967&fm=26&gp=0.jpg";
//    url = "https://stream7.iqilu.com/10339/upload_transcode/202002/18/20200218114723HDu3hhxqIT.mp4";

    qDebug() << url;

    NetClient::downloadFile(url, "/Users/bang/Desktop", DefaultName, [](qint64 received, qint64 total) {

        qDebug() << "Progress: " << received << "  " << total;
    });

}

void RootWgt::slot_didSelectedItem(const QModelIndex &current, const QModelIndex &previous)
{
    HBItem *item = static_cast<HBItem *>(current.internalPointer());

    int id = item->data(3).toInt();

    bool enable = false;
    NetClient::fetchMusicEnable(id, enable);

    ui->pLbl_status->setText(enable ? "是" : "否");

    QString urlStr = QString("https://music.163.com/song/media/outer/url?id=%1.mp3").arg(id);
    ui->pLbl_url->setText(urlStr);


}

void RootWgt::m_fetchOnePageMusic()
{
    MusicList list;

    qDebug() << "FetchMusic: " << m_page << m_pageSize;
    NetClient::fetchMusic(ui->pEdit_search->text(), m_page, m_pageSize, list);

    m_model->setData(list.musicList);

    ui->pBtn_last->setEnabled(m_page != 0);
    ui->pBtn_next->setEnabled(list.hasMore);

}

void RootWgt::on_pBtn_setting_clicked()
{

}
