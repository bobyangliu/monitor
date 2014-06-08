#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("Monitor Car"));
    connect(this, SIGNAL(recvReady()), this, SLOT(displayPicture()));
    connect(ui->connect, SIGNAL(clicked()), this, SLOT(connectServer()));
    connect(ui->unconnect, SIGNAL(clicked()), this, SLOT(unconnect()));

    connect(ui->goButton, SIGNAL(pressed()), this, SLOT(controlSet()));
    connect(ui->RightButton, SIGNAL(pressed()), this, SLOT(controlSet()));
    connect(ui->LeftButton, SIGNAL(pressed()), this, SLOT(controlSet()));
    connect(ui->BackButton, SIGNAL(pressed()), this, SLOT(controlSet()));

    connect(ui->goButton, SIGNAL(released()), this, SLOT(controlClean()));
    connect(ui->RightButton, SIGNAL(released()), this, SLOT(controlClean()));
    connect(ui->LeftButton, SIGNAL(released()), this, SLOT(controlClean()));
    connect(ui->BackButton, SIGNAL(released()), this, SLOT(controlClean()));

    img = new QImage();

    if(! ( img->load("/home/liu/桌面/monitor/client/welcome.png") ) ) //加载图像
    {
        QMessageBox::information(this,
                                 tr("failed!"),
                                 tr("failed!"));
        ::exit(1);
    }
    ui->picture->setPixmap(QPixmap::fromImage(*img));
    isRuning = false;

    memset(&control, 0, 4);
}

void MainWindow::timerEvent(QTimerEvent *e)
{
    if(isRuning == false)
    {
        return;
    }
    count = 0;
    ::recv(sock_fd, &recvData, sizeof(struct SendDataHead), 0);
    over = recvData.length;
    while(over)
    {
        if((numbytes = ::recv(sock_fd, buf, over, 0)) == -1)
        {
            perror("recv");/* 如果接收数据错误,则显示错误信息并退出 */
            exit(1);
        }
        memcpy(&(picture[count]), buf, numbytes);
        count += numbytes;
        over    -= numbytes;
        memset(buf, 0, sizeof(buf));
    }
    emit recvReady();
    ::send(sock_fd, &control, sizeof(struct RecvDataHead), 0);
    memset(picture, 0, sizeof(picture));
}

void MainWindow::connectServer()
{
//    QByteArray tmp = ui->address->text().toLatin1();
//    QMessageBox::information(this,
//                             tmp.data(),
//                             tmp.data());
//    return;
    if(isRuning == true)
    {
        return;
    }
    if ((he=gethostbyname("127.0.0.1")) == NULL)/* 取得主机信息 */
    {
        /* 如果 gethostbyname()发生错误,则显示错误信息并退出 */
        perror("gethostbyname");
        exit(1);
    }

    if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        {
            perror("socket");/* 如果 socket()调用出现错误则显示错误信息并退出 */
            exit(1);
        }

        their_addr.sin_family = AF_INET;/* 主机字节顺序 */
        their_addr.sin_port = htons(PORT);/* 网络字节顺序,短整型 */
        their_addr.sin_addr = *((struct in_addr *)he->h_addr);
        bzero(&(their_addr.sin_zero), 8);/* 将结构剩下的部分清零*/

        if(::connect(sock_fd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr)) == -1)
        {
            perror("connect");/* 如果 connect()建立连接错误,则显示出错误信息,退出 */
            exit(1);
        }

        startTimer(100);
        isRuning = true;
}

void MainWindow::unconnect()
{
    isRuning = false;
    if(! ( img->load(tr("/home/liu/桌面/monitor/client/welcome.png")) ) ) //加载图像
    {
        QMessageBox::information(this,
                                 tr("failed!"),
                                 tr("failed!"));
        return;
    }
    ui->picture->setPixmap(QPixmap::fromImage(*img));
    ::close(sock_fd);
}


int MainWindow::displayPicture()
{
       if(! ( img->loadFromData(picture, sizeof(picture)) ) ) //加载图像
       {
//           QMessageBox::information(this,
//                                    tr("display failed!"),
//                                    tr("display failed!"));
           return 1;
       }


       ui->picture->setPixmap(QPixmap::fromImage(*img));
       ui->picture->update();

//       QMessageBox::information(this,
//                                tr("display!"),
//                                tr("display ok!"));
//        ::usleep(200);
       return 0;
}

void MainWindow::controlSet()
{
    QPushButton *tmp = dynamic_cast<QPushButton *>(sender());
    if("go" == tmp->whatsThis())
    {
        control.length |= 0x01;
    }else if("left" == tmp->whatsThis())
    {
        control.length |= 0x02;
    }else if("right" == tmp->whatsThis())
    {
        control.length |= 0x04;
    }else if("back" == tmp->whatsThis())
    {
        control.length |= 0x08;
    }
}

void MainWindow::controlClean()
{
    QPushButton *tmp = dynamic_cast<QPushButton *>(sender());
    if("go" == tmp->whatsThis())
    {
        control.length &= ~0x01;
    }else if("left" == tmp->whatsThis())
    {
        control.length &= ~0x02;
    }else if("right" == tmp->whatsThis())
    {
        control.length &= ~0x04;
    }else if("back" == tmp->whatsThis())
    {
        control.length &= ~0x08;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    delete img;
}


