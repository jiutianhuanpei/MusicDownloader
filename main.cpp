#include "widget.h"

#include <QApplication>
#include <QPixmapCache>

#include "rootwgt.h"
#include <QImageReader>
#include <QDebug>

int main(int argc, char *argv[])
{
    qDebug() << QImageReader::supportedImageFormats();
    QPixmapCache::setCacheLimit(1);

    QApplication a(argc, argv);
    RootWgt w;
    w.show();
    return a.exec();
}
