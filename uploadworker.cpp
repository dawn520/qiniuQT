#include "qiniu.h"
#include "uploadworker.h"



void UploadWorker::doWork(QFileInfoList files,
                          QString path,QString sercertKey,
                          QString accessKey,QString bucket) {
    std::cout << "11111....\n";
    Qiniu qiniu(sercertKey.toStdString(),accessKey.toStdString());
    int i;
    for (i=0; i<files.size(); i++)
    {
        QString remoteName;
        QString localName;
        QFileInfo fileInfo = files.at(i);
        if(fileInfo.path() == path){
            remoteName = "";
        }else{
            remoteName = fileInfo.path().remove(0,path.size()+1);
            remoteName = remoteName.append("/").append(fileInfo.fileName());
        }
        localName = fileInfo.path().append("/").append(fileInfo.fileName());
        std::cout << qPrintable(QString("%1\n").arg(remoteName));
        std::cout << qPrintable(QString("%1\n").arg(localName));
        std::cout << std::endl;
        qiniu.uploadFile(bucket.toStdString(),remoteName.toStdString(),localName.toStdString());
        emit resultReady(i);
    }
}
