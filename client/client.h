#ifndef CLIENT_H
#define CLIENT_H

#include <QDialog>
#include <QSocketNotifier>
#include <Qt3Support/Q3SocketDevice>
//#include <Q>
//#include <QIODevice>
//#include <qsocketdevice.h>

class Client : public QDialog
{
    Q_OBJECT

public:
    Client(QWidget *parent = 0);

private slots:

private:


};

#endif // CLIENT_H
