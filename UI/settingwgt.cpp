#include "settingwgt.h"
#include "ui_settingwgt.h"
#include <QGraphicsDropShadowEffect>
#include "Base/settingconfig.h"
#include <QFileDialog>
#include <QDebug>

SettingWgt::SettingWgt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingWgt)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    setWindowModality(Qt::ApplicationModal);
    setAttribute(Qt::WA_TranslucentBackground);

    m_btns = new QButtonGroup;
    m_btns->setExclusive(true);
    m_btns->addButton(ui->pBtn_song, Only_Song);
    m_btns->addButton(ui->pBtn_song_singer, Song_Singer);
    m_btns->addButton(ui->pBtn_singer_song, Singer_Song);
    connect(m_btns, qOverload<int>(&QButtonGroup::buttonClicked), this, &SettingWgt::slot_didClickedSaveType);

    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(ui->frame);
    shadow->setOffset(0, 0);
    shadow->setBlurRadius(20);
    shadow->setColor(QColor(255, 0, 0, 100));

    ui->frame->setGraphicsEffect(shadow);

    int type = SettingCore()->setting(SaveType).toInt();

    m_btns->button(type)->setChecked(true);

    QString path = SettingCore()->setting(DownloadDirPath).toString();

    qDebug() << "read path: " << path;
    ui->lineEdit->setText(path);

}

SettingWgt::~SettingWgt()
{
    delete ui;
}

void SettingWgt::on_pBtn_close_clicked()
{
    close();
}

void SettingWgt::slot_didClickedSaveType(int index)
{
    NameType type = static_cast<NameType>(index);

//    SettingCore()->setNameType(type);
    SettingCore()->setSetting(SaveType, type);

}

void SettingWgt::on_pushButton_clicked()
{
    QString path = ui->lineEdit->text();
    path = QFileDialog::getExistingDirectory(this, "Choose Download Dir", path);
    if (path.isEmpty())
    {
        qDebug() << "Need choose dir";
        return;
    }

    SettingCore()->setSetting(DownloadDirPath, path);
    ui->lineEdit->setText(path);

}
