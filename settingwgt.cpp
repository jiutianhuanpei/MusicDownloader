#include "settingwgt.h"
#include "ui_settingwgt.h"

SettingWgt::SettingWgt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingWgt)
{
    ui->setupUi(this);
}

SettingWgt::~SettingWgt()
{
    delete ui;
}
