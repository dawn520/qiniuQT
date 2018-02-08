#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qiniu.h"

#include <QFileInfoList>
#include <QMainWindow>
#include <QProgressDialog>
#include <QThread>
#include <QMetaType>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QThread workerThread;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void openFile();
    void startUpload();
    QFileInfoList GetFileList(QString path);
    QFileInfoList files;
    void showMessages();
    void send(QFileInfoList files,
              QString path,QString sercertKey,
              QString accessKey,QString bucket, int location){
        emit operate(files,path, sercertKey,accessKey, bucket, location);
    }

    void quitThread();
    void openUrl();

private slots:
    void handleResults(int value,qiniuReturn qReturn);
signals:
    void operate(QFileInfoList files,
                 QString path,QString sercertKey,
                 QString accessKey,QString bucket, int location);
private:
    Ui::MainWindow *ui;
    QProgressDialog *progressDialog;
};

#endif // MAINWINDOW_H
