#include "mainwindow.h"
#include "qiniu.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include "iostream"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    MainWindow::setFixedSize(this->width(), this->height());  //这种最好。
    ui->setupUi(this);
    connect(ui->DirButton, &QPushButton::clicked, this, &MainWindow::openFile);
    connect(ui->UploadButton, &QPushButton::clicked, this, &MainWindow::showMessage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFile()
{
    QString path = QFileDialog::getExistingDirectory(this,"请选择模板保存路径...","./");
    if(!path.isEmpty()) {
        ui->DirEdit->setText(path);
    } else {
        QMessageBox::warning(this, tr("Path"),
                             tr("You did not select any directory."));
    }
}

void MainWindow::showMessage(){
    QString sercertKey = ui->SercertKeyEdit->text();
    QString accessKey = ui->AccessKeyEdit->text();
    QString bucket = ui->BucketEdit->text();
    QString path = ui->DirEdit->text();
    Qiniu qiniu(sercertKey.toStdString(),accessKey.toStdString());

    QFileInfoList files = GetFileList(path);
    for (int i = 0; i<files.size(); i++)
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

        //        std::cout << qPrintable(QString("%1 %2 %3").arg(fileInfo.size(), 10)
        //                                .arg(fileInfo.fileName()).arg(fileInfo.path()));

    }


    QMessageBox::warning(this, tr("提示"), "SercertKey:"+sercertKey+"  " +"AccessKey:"+accessKey);

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
