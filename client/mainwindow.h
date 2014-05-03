#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Qt3Support/Q3SocketDevice>
#include <QSocketNotifier>
extern "c"{
    #include <stdio.h>
    #include <stdlib.h>
}


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
protected slots:
    virtual void OnMReceive();

private:
    Ui::MainWindow *ui;
    Q3SocketDevice *pSocketDevice;
    QSocketNotifier *pSocketNotifier;

};

#endif // MAINWINDOW_H
