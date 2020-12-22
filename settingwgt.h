#ifndef SETTINGWGT_H
#define SETTINGWGT_H

#include <QWidget>

namespace Ui {
class SettingWgt;
}

class SettingWgt : public QWidget
{
    Q_OBJECT

public:
    explicit SettingWgt(QWidget *parent = nullptr);
    ~SettingWgt();

private:
    Ui::SettingWgt *ui;
};

#endif // SETTINGWGT_H
