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

   QMessageBox::warning(this, tr("提示"), "SercertKey:"+sercertKey+"  " +"AccessKey:"+accessKey);
   Qiniu qiniu(sercertKey.toStdString(),accessKey.toStdString());
   qiniu.uploadFile();
}
