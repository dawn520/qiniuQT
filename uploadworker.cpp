#include "c_chinese_code.h"
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
        qReturn = qiniu.uploadFile(bucket.toStdString(),remoteName.toStdString(),UTF8_To_string(localName.toStdString()),location);
        emit resultReady(i,qReturn);
//        Sleep(1);
        QThread::currentThread()->sleep(1);
    }

}

std::string UploadWorker::UTF8_To_string(const std::string & str)
{
    int nwLen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);

    wchar_t * pwBuf = new wchar_t[nwLen + 1];//一定要加1，不然会出现尾巴
    memset(pwBuf, 0, nwLen * 2 + 2);

    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), pwBuf, nwLen);

    int nLen = WideCharToMultiByte(CP_ACP, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

    char * pBuf = new char[nLen + 1];
    memset(pBuf, 0, nLen + 1);

    WideCharToMultiByte(CP_ACP, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

    std::string retStr = pBuf;

    delete []pBuf;
    delete []pwBuf;

    pBuf = NULL;
    pwBuf = NULL;

    return retStr;
}
