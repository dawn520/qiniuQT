#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void openFile();
    void saveFile();
    void closeEvent(QCloseEvent *event);
    QAction *openAction;
    QAction *saveAction;
    QTextEdit *textEdit;

};

#endif // MAINWINDOW_H
