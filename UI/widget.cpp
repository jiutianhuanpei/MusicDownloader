#include "widget.h"
#include "ui_widget.h"
#include "Net/netclient.h"
#include <QLineEdit>
#include <QDebug>
#include <QStandardItemModel>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);


    connect(ui->pTab_wgt, &QTableView::clicked, this, &Widget::slot_clickedTabItem);

}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pBtn_search_clicked()
{


    MusicList list;


    NetClient::fetchMusic(ui->lineEdit->text(),0, 30, list);



    QStandardItemModel *model = new QStandardItemModel;
//    model->setHorizontalHeaderLabels(QStringList() << "歌名" << "歌手" << "状态" << "id");
    model->setHorizontalHeaderLabels(QStringList() << "SongName" << "Songer" << "Status" << "Id");

//    for (int i = 0; i < list.count(); i++) {

//        Music *m = static_cast<Music *>(list[i]);

//        QStandardItem *item = new QStandardItem(m->name);
//        model->setItem(i, 0, item);

//        if (m->artists.count() > 0)
//        {
//            QStandardItem *item2 = new QStandardItem(m->artists.first()->name);
//            model->setItem(i, 1, item2);
//        }

//        QStandardItem *item3 = new QStandardItem(QString("%1").arg(m->status));
//        model->setItem(i, 2, item3);

//        QStandardItem *item4 = new QStandardItem(QString("%1").arg(m->id));
//        model->setItem(i, 3, item4);
//    }

    ui->pTab_wgt->setModel(model);
}


void Widget::on_pBtn_searchId_clicked()
{

}

void Widget::slot_clickedTabItem(const QModelIndex &index)
{

    if (index.column() != 3)
        return;

    qDebug() << index.row() << index.column();


    QString id = ui->pTab_wgt->model()->data(index).toString();

    bool ret = false;
    NetClient::fetchMusicEnable(id.toInt(), ret);
//    ui->pLbl_status->setText(ret ? "是" : "否");

    QString urlStr = QString("https://music.163.com/song/media/outer/url?id=%1.mp3").arg(id);
    ui->pLbl_url->setText(urlStr);
}

void Widget::slot_doubleClickedTabItem(const QModelIndex &index)
{

}
