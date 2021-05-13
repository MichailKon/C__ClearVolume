//
// Created by michael on 10.05.2021.
//

// You may need to build the project (run Qt uic code generator) to get "ui_mainWindow.h" resolved

#include "mainwindow.h"
#include "uis/ui_mainWindow.h"
#include "functions.h"


mainWindow::mainWindow(QWidget *parent) :
        QWidget(parent), ui(new Ui::mainWindow), curPath(), calculatedPath(), curFiles(), counter(nullptr) {
    ui->setupUi(this);
    setLayout(ui->gridLayout);
    countingThread = new QThread();
    loadingScreen = new LoadingScreen(this);
    loadingScreen->hide();

    connect(ui->pushButton_chooseFolder, &QPushButton::pressed, this, &mainWindow::chooseFolder);
    connect(ui->pushButton_calculate, &QPushButton::pressed, this, &mainWindow::compute);
    connect(ui->checkBox_hidePrefix, &QCheckBox::stateChanged, this, &mainWindow::showFiles);

    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setHorizontalHeaderLabels({"File path", "File size"});
}

mainWindow::~mainWindow() {
    delete ui;
    delete loadingScreen;
    delete countingThread;
}

QString mainWindow::chooseFolder() {
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "",
                                                    QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    ui->chosenFolder->setText(dir);
    curPath = QDir(dir);

    return dir;
}

void mainWindow::compute() {
    offThread();

    int maxDeep = (ui->spinBox_recursionLimit->value() == 0 ? INT_MAX : ui->spinBox_recursionLimit->value());

    delete counter;
    counter = new FileSizeCounter(curFiles);
    connect(countingThread, &QThread::started, loadingScreen, &LoadingScreen::startAnimation);
    connect(countingThread, &QThread::started, counter, &FileSizeCounter::doWork1);
    connect(loadingScreen, &LoadingScreen::closed, this, &mainWindow::unlockUi);
    connect(counter, &FileSizeCounter::finished, countingThread, &QThread::quit);
    connect(counter, &FileSizeCounter::finished, this, &mainWindow::showFiles);
    connect(counter, &FileSizeCounter::finished, this, &mainWindow::unlockUi);
    connect(counter, &FileSizeCounter::finished, loadingScreen, &LoadingScreen::endAnimation);
    counter->setStart(curPath);
    counter->setMaxDeep(maxDeep);
    counter->moveToThread(countingThread);

    curFiles.clear();
    ui->tableWidget->setRowCount(0);
    lockUi();

    countingThread->start();
}

void mainWindow::showFiles() {
    lockUi();

    std::sort(curFiles.begin(), curFiles.end(),
              [](const QPair<QDir, qint64> &l,
                 const QPair<QDir, qint64> &r) {
                  return l.second > r.second;
              });

    for (int i = 0; i < ui->tableWidget->rowCount(); i++) {
        for (int j = 0; j < ui->tableWidget->columnCount(); i++) {
            delete ui->tableWidget->item(i, j);
        }
    }

    ui->tableWidget->setRowCount(0);
    ui->tableWidget->hide();

    for (const QPair<QDir, qint64> &path : curFiles) {
        int nowRow = ui->tableWidget->rowCount();
        ui->tableWidget->setRowCount(nowRow + 1);

        QString nowPath = path.first.path();
        if (ui->checkBox_hidePrefix->isChecked()) {
            nowPath.remove(0, calculatedPath.absolutePath().size());
        }
        auto *filePath = new QTableWidgetItem(nowPath);
        filePath->setFlags(filePath->flags() ^ Qt::ItemIsEditable);
        auto *fileSize = new QTableWidgetItem(funcs::toHumanReadable(path.second));
        fileSize->setFlags(fileSize->flags() ^ Qt::ItemIsEditable);
        ui->tableWidget->setItem(nowRow, 0, filePath);
        ui->tableWidget->setItem(nowRow, 1, fileSize);
    }

    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->show();

    unlockUi();
}

void mainWindow::offThread() {
    if (countingThread != nullptr) {
        countingThread->requestInterruption();
        countingThread = new QThread();
    }
}

void mainWindow::unlockUi() {
    offThread();

    ui->pushButton_chooseFolder->setEnabled(true);
    ui->pushButton_calculate->setEnabled(true);
}

void mainWindow::lockUi() {
    ui->pushButton_chooseFolder->setEnabled(false);
    ui->pushButton_calculate->setEnabled(false);
}
