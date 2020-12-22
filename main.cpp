#include "widget.h"

#include <QApplication>

#include "rootwgt.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RootWgt w;
    w.show();
    return a.exec();
}
