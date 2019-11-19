/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *network_layout;
    QLineEdit *layer_count_edit;
    QPushButton *button_draw;
    QPushButton *button_random;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *para_layout;
    QPushButton *button_update;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *activation_layout;
    QPushButton *button_compute_all;
    QPushButton *button_debug;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(140, 0, 131, 191));
        network_layout = new QVBoxLayout(verticalLayoutWidget);
        network_layout->setObjectName(QString::fromUtf8("network_layout"));
        network_layout->setContentsMargins(0, 0, 0, 0);
        layer_count_edit = new QLineEdit(centralwidget);
        layer_count_edit->setObjectName(QString::fromUtf8("layer_count_edit"));
        layer_count_edit->setGeometry(QRect(10, 20, 113, 21));
        button_draw = new QPushButton(centralwidget);
        button_draw->setObjectName(QString::fromUtf8("button_draw"));
        button_draw->setGeometry(QRect(10, 50, 112, 32));
        button_random = new QPushButton(centralwidget);
        button_random->setObjectName(QString::fromUtf8("button_random"));
        button_random->setGeometry(QRect(310, 10, 112, 32));
        verticalLayoutWidget_2 = new QWidget(centralwidget);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(440, 0, 101, 191));
        para_layout = new QVBoxLayout(verticalLayoutWidget_2);
        para_layout->setObjectName(QString::fromUtf8("para_layout"));
        para_layout->setContentsMargins(0, 0, 0, 0);
        button_update = new QPushButton(centralwidget);
        button_update->setObjectName(QString::fromUtf8("button_update"));
        button_update->setGeometry(QRect(310, 60, 112, 32));
        verticalLayoutWidget_3 = new QWidget(centralwidget);
        verticalLayoutWidget_3->setObjectName(QString::fromUtf8("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(570, 10, 101, 161));
        activation_layout = new QVBoxLayout(verticalLayoutWidget_3);
        activation_layout->setObjectName(QString::fromUtf8("activation_layout"));
        activation_layout->setContentsMargins(0, 0, 0, 0);
        button_compute_all = new QPushButton(centralwidget);
        button_compute_all->setObjectName(QString::fromUtf8("button_compute_all"));
        button_compute_all->setGeometry(QRect(690, 10, 112, 32));
        button_debug = new QPushButton(centralwidget);
        button_debug->setObjectName(QString::fromUtf8("button_debug"));
        button_debug->setGeometry(QRect(690, 60, 112, 32));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        button_draw->setText(QCoreApplication::translate("MainWindow", "Draw", nullptr));
        button_random->setText(QCoreApplication::translate("MainWindow", "RandomPara", nullptr));
        button_update->setText(QCoreApplication::translate("MainWindow", "UpdatePara", nullptr));
        button_compute_all->setText(QCoreApplication::translate("MainWindow", "ComputeAll", nullptr));
        button_debug->setText(QCoreApplication::translate("MainWindow", "Debug", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
