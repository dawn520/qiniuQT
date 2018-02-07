#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
    void showMessages();
    void send(QFileInfoList files,
              QString path,QString sercertKey,
              QString accessKey,QString bucket){
        emit operate(files,path, sercertKey,accessKey, bucket);
    }

private slots:
    void handleResults(int value);
signals:
    void operate(QFileInfoList files,
                 QString path,QString sercertKey,
                 QString accessKey,QString bucket);
private:
    Ui::MainWindow *ui;
    QProgressDialog *progressDialog;
};

#endif // MAINWINDOW_H
