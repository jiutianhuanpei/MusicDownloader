#ifndef SETTINGWGT_H
#define SETTINGWGT_H

#include <QWidget>
#include <QButtonGroup>

namespace Ui {
class SettingWgt;
}

class SettingWgt : public QWidget
{
    Q_OBJECT

public:
    explicit SettingWgt(QWidget *parent = nullptr);
    ~SettingWgt();

private slots:
    void on_pBtn_close_clicked();
    void slot_didClickedSaveType(int index);

    void on_pushButton_clicked();

private:
    Ui::SettingWgt *ui;
    QButtonGroup *m_btns;
};

#endif // SETTINGWGT_H
