#include "mainwindow.h"
#include "qiniu.h"
#include "uploadworker.h"

#include <QMessageBox>
#include <QTextCodec>


void UploadWorker::doWork(QFileInfoList files,
                          QString path,QString sercertKey,
                          QString accessKey,QString bucket, int location) {
    Qiniu qiniu(sercertKey.toStdString(),accessKey.toStdString());
    int i;
    for (i=0; i<files.size() && !QThread::currentThread()->isInterruptionRequested(); i++)
    {
        QString remoteName;
        QString localName;
        QFileInfo fileInfo = files.at(i);
        if(fileInfo.path() == path){
            remoteName = fileInfo.fileName();
        }else{
            remoteName = fileInfo.path().remove(0,path.size()+1);
            remoteName = remoteName.append("/").append(fileInfo.fileName());
        }
        localName = fileInfo.path().append("/").append(fileInfo.fileName());
        std::cout << qPrintable(QString("%1\n").arg(remoteName));
        std::cout << qPrintable(QString("%1\n").arg(localName));
        std::cout << std::endl;
        qiniuReturn qReturn;
        qReturn = qiniu.uploadFile(bucket.toStdString(),remoteName.toStdString(),localName.toStdString(),location);
        emit resultReady(i,qReturn);
//        Sleep(1);
        QThread::currentThread()->sleep(1);
    }

}

