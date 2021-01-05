#include "musiccontrol.h"
#include "ui_musiccontrol.h"
#include "Net/hbwebimage.h"
#include <QDebug>
#include "Model/music.h"
#include <QDateTime>

using namespace HBWebImage;

MusicControl::MusicControl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MusicControl)
{
    ui->setupUi(this);
    m_player = new QMediaPlayer;


    _InitConnects();
}

MusicControl::~MusicControl()
{
    delete ui;
}


void MusicControl::setCurrentMusic(Music * music)
{
    ui->pLbl_name->setText(music->name);

    QString urlStr = music->artists.first()->img1v1Url;
    hb_setImage(urlStr, ui->imgView);


    QString musicUrl = music->downloadUrlStr();

    m_player->setMedia(QMediaContent(QUrl(musicUrl)));
    m_player->play();
}

void MusicControl::on_pBtn_last_clicked()
{

}

void MusicControl::on_pBtn_play_clicked()
{
    switch (m_player->state()) {
    case QMediaPlayer::PlayingState:
    {
        m_player->pause();
        break;
    }
    case QMediaPlayer::PausedState:
    {
        m_player->play();
        break;
    }
    case QMediaPlayer::StoppedState:
    {
        m_player->setPosition(0);
        m_player->play();
        break;
    }
    }
}

void MusicControl::on_pBtn_next_clicked()
{

}

void MusicControl::_InitConnects()
{
    connect(m_player, &QMediaPlayer::stateChanged, this, [&](QMediaPlayer::State newState) {
        qDebug() << "State:" << newState;
//        ui->pBtn_play->setEnabled(newState != QMediaPlayer::StoppedState);
        ui->pBtn_play->setChecked(newState == QMediaPlayer::PlayingState);
    });
    connect(m_player, &QMediaPlayer::mediaStatusChanged, this, [](QMediaPlayer::MediaStatus status) {
        qDebug() << "MediaStatus: " << status;
    });

    connect(m_player, &QMediaPlayer::durationChanged, this, [&](qint64 duration) {
        qDebug() << "Duration: " << duration;
        ui->progressBar->setMaximum(static_cast<int>(duration));
        ui->pLbl_totalTime->setText(m_timeString(duration));
    });
    connect(m_player, &QMediaPlayer::positionChanged, this, [&](qint64 position) {
        qDebug() << "Position: " << position;
        ui->progressBar->setValue(static_cast<int>(position));
        ui->pLbl_currentTime->setText(m_timeString(position));
    });
    connect(m_player, &QMediaPlayer::volumeChanged, this, [](int volume) {
        qDebug() << "Volume: " << volume;
    });
}

QString MusicControl::m_timeString(qint64 time)
{
    qint64 seconds = time / 1000;
    QDateTime a = QDateTime::fromTime_t(static_cast<uint>(seconds));

    QString str = a.toString("mm:ss");
    return  str;
}
