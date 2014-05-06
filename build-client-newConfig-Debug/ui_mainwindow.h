/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Tue May 6 14:07:58 2014
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
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLineEdit *address;
    QPushButton *connect;
    QPushButton *unconnect;
    QLabel *picture;
    QLabel *disName;
    QPushButton *goButton;
    QPushButton *LeftButton;
    QPushButton *RightButton;
    QPushButton *BackButton;
    QLCDNumber *lcdNumber;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(547, 400);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayoutWidget = new QWidget(centralWidget);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(20, 310, 469, 29));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        address = new QLineEdit(horizontalLayoutWidget);
        address->setObjectName(QString::fromUtf8("address"));

        horizontalLayout->addWidget(address);

        connect = new QPushButton(horizontalLayoutWidget);
        connect->setObjectName(QString::fromUtf8("connect"));

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
        goButton = new QPushButton(centralWidget);
        goButton->setObjectName(QString::fromUtf8("goButton"));
        goButton->setGeometry(QRect(420, 100, 71, 27));
        LeftButton = new QPushButton(centralWidget);
        LeftButton->setObjectName(QString::fromUtf8("LeftButton"));
        LeftButton->setGeometry(QRect(370, 150, 71, 27));
        RightButton = new QPushButton(centralWidget);
        RightButton->setObjectName(QString::fromUtf8("RightButton"));
        RightButton->setGeometry(QRect(470, 150, 71, 27));
        BackButton = new QPushButton(centralWidget);
        BackButton->setObjectName(QString::fromUtf8("BackButton"));
        BackButton->setGeometry(QRect(420, 200, 71, 27));
        lcdNumber = new QLCDNumber(centralWidget);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));
        lcdNumber->setGeometry(QRect(370, 50, 64, 23));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 547, 25));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        address->setText(QApplication::translate("MainWindow", "127.0.0.1", 0, QApplication::UnicodeUTF8));
        connect->setText(QApplication::translate("MainWindow", "connect", 0, QApplication::UnicodeUTF8));
        unconnect->setText(QApplication::translate("MainWindow", "unconnect", 0, QApplication::UnicodeUTF8));
        picture->setText(QApplication::translate("MainWindow", "   Monitot Area", 0, QApplication::UnicodeUTF8));
        disName->setText(QApplication::translate("MainWindow", "monitor_car", 0, QApplication::UnicodeUTF8));
        goButton->setText(QApplication::translate("MainWindow", "Go", 0, QApplication::UnicodeUTF8));
        LeftButton->setText(QApplication::translate("MainWindow", "Left", 0, QApplication::UnicodeUTF8));
        RightButton->setText(QApplication::translate("MainWindow", "Right", 0, QApplication::UnicodeUTF8));
        BackButton->setText(QApplication::translate("MainWindow", "Back", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
