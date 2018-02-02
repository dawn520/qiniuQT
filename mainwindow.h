#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileInfoList>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void openFile();
    void showMessage();
    QFileInfoList GetFileList(QString path);
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
