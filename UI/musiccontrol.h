#ifndef MUSICCONTROL_H
#define MUSICCONTROL_H

#include <QWidget>
#include "Model/music.h"
#include <QtMultimedia/QtMultimedia>

namespace Ui {
class MusicControl;
}

class MusicControl : public QWidget
{
    Q_OBJECT

public:
    explicit MusicControl(QWidget *parent = nullptr);
    ~MusicControl();

    void setCurrentMusic(Music *music);


signals:
    void signal_didClickedLastBtn();
    void signal_didClickedPlayBtn(bool isChecked);
    void signal_didClickedNextBtn();

private slots:
    void on_pBtn_last_clicked();

    void on_pBtn_play_clicked();

    void on_pBtn_next_clicked();

private:
    Ui::MusicControl *ui;
    QMediaPlayer *m_player;

private:
    void _InitConnects();
    QString m_timeString(qint64 time);
};

#endif // MUSICCONTROL_H
