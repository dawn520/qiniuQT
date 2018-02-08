#include <QDebug>
#include <QThread>
#include <QString>
#include <QtConcurrent>
#include "mainwindow.h"
#include "qiniu.h"
#include "ui_mainwindow.h"
#include <QComboBox>
#include <QDesktopServices>
#include <QFileDialog>
#include <QFuture>
#include <QMessageBox>
#include <QProgressBar>
#include <QProgressDialog>
#include <QTextStream>
#include "iostream"
#include <uploadworker.h>


#pragma execution_character_set("utf-8")


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    qRegisterMetaType<QFileInfoList>("QFileInfoList");
    qRegisterMetaType<qiniuReturn>("qiniuReturn");

    MainWindow::setFixedSize(this->width(), this->height());

    MainWindow::setWindowIcon(QIcon(":/resource/images/qiniu.png"));
    ui->setupUi(this);

    connect(ui->DirButton, &QPushButton::clicked, this, &MainWindow::openFile);
    connect(ui->UploadButton, &QPushButton::clicked, this, &MainWindow::startUpload);
    //    connect(ui->site, &QLabel::linkActivated, this, &MainWindow::openUrl);
    //    openUrl();
}

MainWindow::~MainWindow()
{
    delete ui;
    workerThread.quit();
    workerThread.wait();
}

void MainWindow::openFile()
{
    QString path = QFileDialog::getExistingDirectory(this,"请选择上传需要上传的文件夹","./");
    if(!path.isEmpty()) {
        ui->DirEdit->setText(path);
    }

}

void MainWindow::startUpload(){

    QString sercertKey = ui->SercertKeyEdit->text();
    QString accessKey = ui->AccessKeyEdit->text();
    QString bucket = ui->BucketEdit->text();
    QString path = ui->DirEdit->text();
    int location = ui->location->currentIndex();
//        QString sercertKey = "n3MtMSgmSucSfygNEx3CHuP_6AUUPXzUK64dlKiU";
//        QString accessKey = "0W_4wL_5ldYISAnty8M39hFQ1f7iN-F7vU1Vqpvo";
//        QString bucket = "test";
    //    QString path = "C:/Users/admin/Desktop/hhh";

    if(sercertKey.length()==0){
        QMessageBox::warning(this, tr("提示"), "请填写SercertKey");
        return;
    }
    if(accessKey.length()==0){
        QMessageBox::warning(this, tr("提示"), "请填写AccessKey");
        return;
    }
    if(bucket.length()==0){
        QMessageBox::warning(this, tr("提示"), "请填写目标Bucket");
        return;
    }
    if(path.length()==0){
        QMessageBox::warning(this, tr("提示"), "请选择一个文件夹");
        return;
    }
    if (QMessageBox::No == QMessageBox::question(this,
                                                 tr("提示"),
                                                 tr("所选文件夹相当于bucket根目录，是否继续?"),
                                                 QMessageBox::Yes | QMessageBox::No,
                                                 QMessageBox::Yes)) {
        return;
    }

    files = GetFileList(path);

    progressDialog = new QProgressDialog(this);
    QFont font("宋体", 12);
    progressDialog->setFont(font);
    progressDialog->setMinimumSize(QSize(463, 179));
    progressDialog->setWindowModality(Qt::WindowModal);      //采用模拟的方式进行显示，即显示进度的同时，其他窗口将不响应输入信号
    progressDialog->setMinimumDuration(0);   //设置进度条显示的等待时间，5秒
    progressDialog->setWindowTitle(tr("请稍候"));   //设置标题的显示时间
    progressDialog->setLabelText(tr("正在上传中"));
    progressDialog->setCancelButtonText(tr("取消"));     //退出按钮名字
    progressDialog->setRange(0, files.size());    //设置显示的范围
    progressDialog->setValue(1);

    connect(progressDialog, &QProgressDialog::canceled, &workerThread, &QThread::terminate);

    UploadWorker *uploadWorker = new UploadWorker;

    uploadWorker->moveToThread(&workerThread);
    connect(&workerThread, &QThread::finished, uploadWorker, &QObject::deleteLater);
    connect(this, &MainWindow::operate, uploadWorker, &UploadWorker::doWork);
    connect(uploadWorker, &UploadWorker::resultReady, this, &MainWindow::handleResults);
    workerThread.start();

    send(files,path, sercertKey,accessKey, bucket,location);

}

QFileInfoList MainWindow::GetFileList(QString path)
{
    QDir dir(path);
    QFileInfoList file_list = dir.entryInfoList(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    QFileInfoList folder_list = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);

    for(int i = 0; i != folder_list.size(); i++)
    {
        QString name = folder_list.at(i).absoluteFilePath();
        QFileInfoList child_file_list = GetFileList(name);
        file_list.append(child_file_list);
    }

    return file_list;
}

// 更新进度
void MainWindow::handleResults(int value,qiniuReturn qReturn)
{
    qDebug() << "Handle Thread : " << QThread::currentThreadId();
    if(qReturn.code != 200 && qReturn.code != 614){
        int code = qReturn.code;
        std::string message = qReturn.message;
        quitThread();
        progressDialog->cancel();
        switch (code) {
        case 400:
            message = "存储区域选择不正确！请重新选择";
            break;
        case 401:
            message = "accessKey或sercertKey有误！";
            break;
        case 631:
            message = "目标bucket不存在！";
            break;
        default:
            break;
        }
        QMessageBox::warning(this, tr("上传失败"),  message.data());
    }else{
        progressDialog->setValue(value+1);
        if(value+1 == files.size()){
            quitThread();
            QMessageBox::information(this, tr("提示"),  "上传成功!");
        }
    }
}
void MainWindow::quitThread(){
    workerThread.requestInterruption();
    workerThread.quit();
    workerThread.wait();
}
void MainWindow::openUrl(){
    const QUrl regUrl(QLatin1String("http://github.com/dawn520/qiniuQT"));
    QDesktopServices::openUrl(regUrl);
}

void MainWindow::showMessages()
{

}
