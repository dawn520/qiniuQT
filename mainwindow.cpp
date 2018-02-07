#include <QDebug>
#include <QThread>
#include <QString>
#include <QtConcurrent>
#include "mainwindow.h"
#include "qiniu.h"
#include "ui_mainwindow.h"
#include <QComboBox>
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
    MainWindow::setFixedSize(this->width(), this->height());  //这种最好。
    ui->setupUi(this);

    QProgressBar *progressBar;
    progressBar = new QProgressBar;
    progressBar->setFormat("%p%");    //按完成的百分比显示

    connect(ui->DirButton, &QPushButton::clicked, this, &MainWindow::openFile);
    connect(ui->UploadButton, &QPushButton::clicked, this, &MainWindow::startUpload);
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

    //    QString sercertKey = ui->SercertKeyEdit->text();
    //    QString accessKey = ui->AccessKeyEdit->text();
    //    QString bucket = ui->BucketEdit->text();
    QString path = ui->DirEdit->text();
    QString sercertKey = "n3MtMSgmSucSfygNEx3CHuP_6AUUPXzUK64dlKiU";
    QString accessKey = "0W_4wL_5ldYISAnty8M39hFQ1f7iN-F7vU1Vqpvo";
    QString bucket = "test";
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

    std::cout << "start....\n";



    //    for(int i =  1; i <= num; ++i)
    //    {
    //        progressDialog->setValue(i);   //设置当前的值
    //        Sleep(1000);
    //        //             cout<<i<<endl;
    //        //如果检测到按钮取消被激活，就跳出去
    //        if(progressDialog->wasCanceled())
    //            return;

    //    }

    QFileInfoList files = GetFileList(path);


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

    UploadWorker *uploadWorker = new UploadWorker;

    uploadWorker->moveToThread(&workerThread);
    connect(&workerThread, &QThread::finished, uploadWorker, &QObject::deleteLater);
    connect(this, &MainWindow::operate, uploadWorker, &UploadWorker::doWork);
    connect(uploadWorker, &UploadWorker::resultReady, this, &MainWindow::handleResults);
    workerThread.start();

    send(files,path, sercertKey,accessKey, bucket);
    std::cout << "hhhhhh\n";
    //    while(1){
    //        std::cout << future.progressValue();
    //    }

    //        printf(future.result());

    //            if($re)
    //                return;


    //        std::cout << qPrintable(QString("%1 %2 %3").arg(fileInfo.size(), 10)
    //                                .arg(fileInfo.fileName()).arg(fileInfo.path()));


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
void MainWindow::handleResults(int value)
{
    qDebug() << "Handle Thread : " << QThread::currentThreadId();
    progressDialog->setValue(value+1);
    //    if(progressDialog->wasCanceled())
    //        return;
}

void MainWindow::showMessages()
{

}
