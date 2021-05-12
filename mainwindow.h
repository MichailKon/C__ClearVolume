//
// Created by michael on 10.05.2021.
//

#ifndef C__CLEARVOLUME_MAINWINDOW_H
#define C__CLEARVOLUME_MAINWINDOW_H

#include <QWidget>
#include <QFileDialog>
#include <boost/filesystem.hpp>
#include <QMap>
#include <QThread>
#include <QMutex>
#include "filesizecounter.h"
#include "loadingscreen.h"

QT_BEGIN_NAMESPACE
namespace Ui { class mainWindow; }
QT_END_NAMESPACE

class mainWindow : public QWidget {
Q_OBJECT

public:
    explicit mainWindow(QWidget *parent = nullptr);

    ~mainWindow() override;

private slots:

    QString chooseFolder();

    void compute();

    void showFiles();

    void offThread();

    void lockUi();

    void unlockUi();

private:
    Ui::mainWindow *ui;
    LoadingScreen *loadingScreen;

    boost::filesystem::path curPath;

    QVector<QPair<boost::filesystem::path, std::uintmax_t>> curFiles;
    QThread *countingThread;
};


#endif //C__CLEARVOLUME_MAINWINDOW_H
