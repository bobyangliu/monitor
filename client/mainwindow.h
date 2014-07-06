#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QTime>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#define __STDC_CONSTANT_MACROS
#define UINT64_C
extern "C"{
#include <libavutil/imgutils.h>
#include <libswscale/swscale.h>
}

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
    void controlSet();
    void controlClean();

signals:
    void recvReady();

private:
    Ui::MainWindow *ui;
    QImage *img;

    bool isRuning;
    int sock_fd, numbytes, over, count;/* 套接字描述符 */
    uchar buf[MAXDATASIZE];
    uchar *pictureHead;
    uchar picture[320*240*3+15];
	struct hostent *he;
	struct sockaddr_in their_addr;/* 连接者的主机信息 */

    struct SendDataHead{
        int length;
    }recvData;

    struct RecvDataHead{
        int length;
    }control;

    u_int8_t *src_data[4], *dst_data[4];
    int src_linesize[4], dst_linesize[4];
    int src_w, src_h, dst_w, dst_h;
    struct SwsContext* sws_ctx;
    void InitScale();
    void ConvertToRgb();

protected:
    void timerEvent(QTimerEvent *);

};

#endif // MAINWINDOW_H
