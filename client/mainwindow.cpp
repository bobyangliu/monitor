#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pSocketDevice = new Q3SocketDevice(Q3SocketDevice::Datagram);

    QHostAddress myAddr;
    myAddr.setAddress("127.0.0.1");
    //pSocketDevice->bind(myAddr, 8888);
    pSocketDevice->connect(myAddr, 8888);
    pSocketNotifier = new QSocketNotifier(pSocketDevice->socket(), QSocketNotifier::Read, this);


    connect(pSocketNotifier, SIGNAL(activated(int), this, SLOT(OnMReceive());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::OnMReceive()
{
    int byteCount, readCount;
    char * inCommingChar;

    fprintf(stderr, "Load a piece of message!\n");

    byteCount = pSocketDevice->bytesAvailable();
    inCommingChar = (char *)malloc(byteCount + 1);
    readCount = pSocketDevice->readBlock(inCommingChar, byteCount);
    inCommingChar[byteCount] = '\0';
    fprintf(stderr, "%s", inCommingChar);
}
