/********************************************************************************
** Form generated from reading UI file 'Window.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOW_H
#define UI_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WindowClass
{
public:
    QWidget *centralWidget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout_4;
    QPushButton *pushButton;
    QLabel *label;
    QComboBox *comboBox;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *WindowClass)
    {
        if (WindowClass->objectName().isEmpty())
            WindowClass->setObjectName("WindowClass");
        WindowClass->resize(914, 768);
        centralWidget = new QWidget(WindowClass);
        centralWidget->setObjectName("centralWidget");
        gridLayoutWidget = new QWidget(centralWidget);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(150, 80, 641, 541));
        gridLayout_4 = new QGridLayout(gridLayoutWidget);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName("gridLayout_4");
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(410, 680, 101, 31));
        label = new QLabel(centralWidget);
        label->setObjectName("label");
        label->setGeometry(QRect(240, 20, 451, 51));
        comboBox = new QComboBox(centralWidget);
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(350, 640, 231, 24));
        WindowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(WindowClass);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 914, 21));
        WindowClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(WindowClass);
        mainToolBar->setObjectName("mainToolBar");
        WindowClass->addToolBar(Qt::ToolBarArea::TopToolBarArea, mainToolBar);

        retranslateUi(WindowClass);

        QMetaObject::connectSlotsByName(WindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *WindowClass)
    {
        WindowClass->setWindowTitle(QCoreApplication::translate("WindowClass", "Window", nullptr));
        pushButton->setText(QCoreApplication::translate("WindowClass", "Start", nullptr));
        label->setText(QCoreApplication::translate("WindowClass", "turn label", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WindowClass: public Ui_WindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOW_H
