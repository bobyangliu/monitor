/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Thu Jul 3 11:11:07 2014
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_URL;
    QLineEdit *addressEdit;
    QLabel *label_port;
    QLineEdit *portEdit;
    QPushButton *connect;
    QPushButton *unconnect;
    QLabel *picture;
    QLabel *disName;
    QPushButton *goButton;
    QPushButton *LeftButton;
    QPushButton *RightButton;
    QPushButton *BackButton;
    QPushButton *quitBtn;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(555, 358);
        MainWindow->setStyleSheet(QString::fromUtf8("QWidget{\n"
"    color: #b1b1b1;\n"
"    background-color: #3c3f41;\n"
"}\n"
"QWidget#centralWidget{\n"
"    color: #b1b1b1;\n"
"	border:2px solid #8f8f91;\n"
"	border-radius:6px;\n"
"    background-color: #3c3f41;\n"
"}\n"
"QLabel#picture{\n"
"border:2px solid #8f8f91;\n"
"border-radius:5px;\n"
"back-ground-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,stop:0 #f6f7fa ,stop:1 #dadbde);\n"
"}\n"
"QPushButton{\n"
"    color: #b1b1b1;\n"
"    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #565656, stop: 0.1 #525252, stop: 0.5 #4e4e4e, stop: 0.9 #4a4a4a, stop: 1 #464646);\n"
"    border-width: 1px;\n"
"    border-color: #1e1e1e;\n"
"    border-style: solid;\n"
"    border-radius: 6;\n"
"    padding: 3px;\n"
"    font-size: 12px;\n"
"    padding-left: 5px;\n"
"    padding-right: 5px;\n"
"    min-width: 32px;\n"
"    min-height: 18px;\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #2d2d2d, stop: 0.1 #2b2b2b, stop: 0.5 #292929"
                        ", stop: 0.9 #282828, stop: 1 #252525);\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"	/* background-color: QLinearGradient(x1:0, y1:0, x2:0, y2:1, stop:0 #d7801a, stop:0.5 #b56c17 stop:1 #ffa02f);\n"
"    color: white;\n"
"    padding-left: 4px;\n"
"    border: 1px solid #6c6c6c;\n"
"    spacing: 3px; spacing between items in the tool bar */\n"
"    border-color:  QLinearGradient(x1:0, y1:0, x2:0, y2:1, stop:0 #d7801a, stop:0.5 #b56c17 stop:1 #ffa02f);\n"
"    border-width: 2px;\n"
"}\n"
"\n"
"QMainWindow::separator\n"
"{\n"
"    background-color: QLinearGradient(x1:0, y1:0, x2:0, y2:1, stop:0 #161616, stop: 0.5 #151515, stop: 0.6 #212121, stop:1 #343434);\n"
"    color: white;\n"
"    padding-left: 4px;\n"
"    border: 1px solid #4c4c4c;\n"
"    spacing: 3px; /* spacing between items in the tool bar */\n"
"}\n"
"\n"
"QMainWindow::separator:hover\n"
"{\n"
"    background-color: QLinearGradient(x1:0, y1:0, x2:0, y2:1, stop:0 #d7801a, stop:0.5 #b56c17 stop:1 #ffa02f);\n"
"    color: white;\n"
"    padding-left: 4px;\n"
""
                        "    border: 1px solid #6c6c6c;\n"
"    spacing: 3px; /* spacing between items in the tool bar */\n"
"}\n"
""));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayoutWidget = new QWidget(centralWidget);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(30, 310, 469, 29));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_URL = new QLabel(horizontalLayoutWidget);
        label_URL->setObjectName(QString::fromUtf8("label_URL"));

        horizontalLayout->addWidget(label_URL);

        addressEdit = new QLineEdit(horizontalLayoutWidget);
        addressEdit->setObjectName(QString::fromUtf8("addressEdit"));
        addressEdit->setMaximumSize(QSize(170, 16777215));

        horizontalLayout->addWidget(addressEdit);

        label_port = new QLabel(horizontalLayoutWidget);
        label_port->setObjectName(QString::fromUtf8("label_port"));

        horizontalLayout->addWidget(label_port);

        portEdit = new QLineEdit(horizontalLayoutWidget);
        portEdit->setObjectName(QString::fromUtf8("portEdit"));
        portEdit->setMaximumSize(QSize(50, 16777));

        horizontalLayout->addWidget(portEdit);

        connect = new QPushButton(horizontalLayoutWidget);
        connect->setObjectName(QString::fromUtf8("connect"));
        connect->setMinimumSize(QSize(44, 26));
        connect->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout->addWidget(connect);

        unconnect = new QPushButton(horizontalLayoutWidget);
        unconnect->setObjectName(QString::fromUtf8("unconnect"));

        horizontalLayout->addWidget(unconnect);

        picture = new QLabel(centralWidget);
        picture->setObjectName(QString::fromUtf8("picture"));
        picture->setEnabled(true);
        picture->setGeometry(QRect(30, 50, 320, 240));
        picture->setAutoFillBackground(false);
        disName = new QLabel(centralWidget);
        disName->setObjectName(QString::fromUtf8("disName"));
        disName->setGeometry(QRect(220, 10, 101, 21));
        QFont font;
        font.setFamily(QString::fromUtf8("OpenSymbol"));
        font.setPointSize(12);
        disName->setFont(font);
        disName->setStyleSheet(QString::fromUtf8(""));
        goButton = new QPushButton(centralWidget);
        goButton->setObjectName(QString::fromUtf8("goButton"));
        goButton->setGeometry(QRect(420, 100, 71, 28));
        goButton->setStyleSheet(QString::fromUtf8(""));
        LeftButton = new QPushButton(centralWidget);
        LeftButton->setObjectName(QString::fromUtf8("LeftButton"));
        LeftButton->setGeometry(QRect(370, 150, 71, 27));
        RightButton = new QPushButton(centralWidget);
        RightButton->setObjectName(QString::fromUtf8("RightButton"));
        RightButton->setGeometry(QRect(470, 150, 71, 27));
        BackButton = new QPushButton(centralWidget);
        BackButton->setObjectName(QString::fromUtf8("BackButton"));
        BackButton->setGeometry(QRect(420, 200, 71, 27));
        quitBtn = new QPushButton(centralWidget);
        quitBtn->setObjectName(QString::fromUtf8("quitBtn"));
        quitBtn->setGeometry(QRect(490, 10, 51, 51));
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        label_URL->setText(QApplication::translate("MainWindow", "URL:", 0, QApplication::UnicodeUTF8));
        addressEdit->setText(QApplication::translate("MainWindow", "127.0.0.1", 0, QApplication::UnicodeUTF8));
        label_port->setText(QApplication::translate("MainWindow", "Port:", 0, QApplication::UnicodeUTF8));
        connect->setText(QApplication::translate("MainWindow", "connect", 0, QApplication::UnicodeUTF8));
        unconnect->setText(QApplication::translate("MainWindow", "unconnect", 0, QApplication::UnicodeUTF8));
        picture->setText(QApplication::translate("MainWindow", "   Monitot Area", 0, QApplication::UnicodeUTF8));
        disName->setText(QApplication::translate("MainWindow", "monitor_car", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        goButton->setWhatsThis(QApplication::translate("MainWindow", "go", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        goButton->setText(QApplication::translate("MainWindow", "Go", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        LeftButton->setWhatsThis(QApplication::translate("MainWindow", "left", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        LeftButton->setText(QApplication::translate("MainWindow", "Left", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        RightButton->setWhatsThis(QApplication::translate("MainWindow", "right", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        RightButton->setText(QApplication::translate("MainWindow", "Right", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        BackButton->setWhatsThis(QApplication::translate("MainWindow", "back", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        BackButton->setText(QApplication::translate("MainWindow", "Back", 0, QApplication::UnicodeUTF8));
        quitBtn->setText(QApplication::translate("MainWindow", "quit", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
