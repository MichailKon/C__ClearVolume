/********************************************************************************
** Form generated from reading UI file 'mainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mainWindow
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *pushButton_calculate;
    QPushButton *pushButton_chooseFolder;
    QTableWidget *tableWidget;
    QLabel *chosenFolder;
    QCheckBox *checkBox_hidePrefix;
    QSpinBox *spinBox_recursionLimit;

    void setupUi(QWidget *mainWindow)
    {
        if (mainWindow->objectName().isEmpty())
            mainWindow->setObjectName(QString::fromUtf8("mainWindow"));
        mainWindow->resize(472, 354);
        gridLayoutWidget = new QWidget(mainWindow);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 10, 451, 331));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_calculate = new QPushButton(gridLayoutWidget);
        pushButton_calculate->setObjectName(QString::fromUtf8("pushButton_calculate"));
        pushButton_calculate->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"margin: 5px;\n"
"color: #333;\n"
"border: 2px solid #555;\n"
"border-radius: 11px;\n"
"padding: 5px;\n"
"background: qradialgradient(cx: 0.3, cy: -0.4,\n"
"fx: 0.3, fy: -0.4,\n"
"radius: 1.35, stop: 0 #4ff, stop: 1 #A99);\n"
"min-width: 80px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"background: qradialgradient(cx: 0.3, cy: -0.4,\n"
"fx: 0.3, fy: -0.4,\n"
"radius: 1.35, stop: 0 #4ff, stop: 1 #Abb);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"background: qradialgradient(cx: 0.4, cy: -0.1,\n"
"fx: 0.4, fy: -0.1,\n"
"radius: 1.35, stop: 0 #fff, stop: 1 #ddd);\n"
"}\n"
""));

        gridLayout->addWidget(pushButton_calculate, 4, 0, 1, 2);

        pushButton_chooseFolder = new QPushButton(gridLayoutWidget);
        pushButton_chooseFolder->setObjectName(QString::fromUtf8("pushButton_chooseFolder"));
        pushButton_chooseFolder->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"margin: 5px;\n"
"color: #333;\n"
"border: 2px solid #555;\n"
"border-radius: 11px;\n"
"padding: 5px;\n"
"background: qradialgradient(cx: 0.3, cy: -0.4,\n"
"fx: 0.3, fy: -0.4,\n"
"radius: 1.35, stop: 0 #fff, stop: 1 #888);\n"
"min-width: 80px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"background: qradialgradient(cx: 0.3, cy: -0.4,\n"
"fx: 0.3, fy: -0.4,\n"
"radius: 1.35, stop: 0 #fff, stop: 1 #bbb);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"background: qradialgradient(cx: 0.4, cy: -0.1,\n"
"fx: 0.4, fy: -0.1,\n"
"radius: 1.35, stop: 0 #fff, stop: 1 #ddd);\n"
"}\n"
"\n"
""));

        gridLayout->addWidget(pushButton_chooseFolder, 0, 0, 1, 2);

        tableWidget = new QTableWidget(gridLayoutWidget);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setStyleSheet(QString::fromUtf8("QTableWidget:item:selected\n"
"{\n"
"	border: 3px solid  black; \n"
"}\n"
""));

        gridLayout->addWidget(tableWidget, 3, 0, 1, 2);

        chosenFolder = new QLabel(gridLayoutWidget);
        chosenFolder->setObjectName(QString::fromUtf8("chosenFolder"));

        gridLayout->addWidget(chosenFolder, 1, 0, 1, 2);

        checkBox_hidePrefix = new QCheckBox(gridLayoutWidget);
        checkBox_hidePrefix->setObjectName(QString::fromUtf8("checkBox_hidePrefix"));

        gridLayout->addWidget(checkBox_hidePrefix, 2, 0, 1, 1);

        spinBox_recursionLimit = new QSpinBox(gridLayoutWidget);
        spinBox_recursionLimit->setObjectName(QString::fromUtf8("spinBox_recursionLimit"));
        spinBox_recursionLimit->setStyleSheet(QString::fromUtf8("spinBox {\n"
"}"));
        spinBox_recursionLimit->setMinimum(0);

        gridLayout->addWidget(spinBox_recursionLimit, 2, 1, 1, 1);


        retranslateUi(mainWindow);

        QMetaObject::connectSlotsByName(mainWindow);
    } // setupUi

    void retranslateUi(QWidget *mainWindow)
    {
        mainWindow->setWindowTitle(QApplication::translate("mainWindow", "mainWindow", nullptr));
        pushButton_calculate->setText(QApplication::translate("mainWindow", "Calculate", nullptr));
        pushButton_chooseFolder->setText(QApplication::translate("mainWindow", "Choose folder", nullptr));
        chosenFolder->setText(QString());
        checkBox_hidePrefix->setText(QApplication::translate("mainWindow", "Hide path prefix", nullptr));
    } // retranslateUi

};

namespace Ui {
    class mainWindow: public Ui_mainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
