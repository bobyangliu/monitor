#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QMovie>
#include <QTime>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>


#define PORT 4000
#define MAXDATASIZE 43770

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void connectServer();
    int displayPicture();
    void unconnect();

signals:
    void recvReady();

private:
    Ui::MainWindow *ui;
    QImage *img;
    QTime time;

    bool isRuning;
    int sock_fd, numbytes, over, count;/* 套接字描述符 */
    uchar buf[MAXDATASIZE];
    uchar picture[184320];
    char control[4];
	struct hostent *he;
	struct sockaddr_in their_addr;/* 连接者的主机信息 */

};

#endif // MAINWINDOW_H
