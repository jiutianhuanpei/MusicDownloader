#include "hbwebimage.h"
#include "netclient.h"
#include <QDir>
#include <QUrl>
#include <QFile>
#include <QDebug>
#include <QPixmap>
#include <QCoreApplication>
#include <QThread>
#include <QImage>



namespace HBWebImage {

void hb_setImage(const QString urlStr, QLabel *imgView)
{
    std::thread th([&, urlStr, imgView]{

        QString dirName = "CacheImg";

        QString cacheImgPath = QCoreApplication::applicationDirPath() + QString("/%1").arg(dirName);
        QDir dir(cacheImgPath);
        if (!dir.exists())
        {
            dir.mkdir(cacheImgPath);
        }

        QString fileName = QUrl(urlStr).fileName();

        QString localPath = QString("%1/%2").arg(cacheImgPath).arg(fileName);

        do {
            QFile file(localPath);
            if (file.exists())
            {
                qDebug() << "\nThis music was downloaded" << urlStr << localPath;
                break;
            }

            NetClient::downloadFile(urlStr, cacheImgPath, localPath);
        } while (0);


        QFile file(localPath);
        if (!file.exists())
        {
            qDebug() << "\ndownload image failure";
            return;
        }

        if (!file.open(QIODevice::ReadOnly))
            return;

        QByteArray byte = file.readAll();

        QImage bitm;
        bitm.loadFromData(byte);
        file.close();

        QPixmap bmp = QPixmap::fromImage(bitm);
        bmp = bmp.scaled(imgView->sizeHint(), Qt::IgnoreAspectRatio);
        imgView->setPixmap(bmp);
    });
    th.detach();
}

} // namespace HBWebImage
