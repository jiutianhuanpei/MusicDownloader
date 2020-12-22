#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pBtn_search_clicked();

    void on_pBtn_searchId_clicked();


    void slot_clickedTabItem(const QModelIndex& index);
    void slot_doubleClickedTabItem(const QModelIndex& index);

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
