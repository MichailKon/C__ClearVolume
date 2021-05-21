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
    ui->progressBar->setValue(0);
    countingThread = new QThread();
    ui->pushButton_cancel->hide();

    connect(ui->pushButton_chooseFolder, &QPushButton::pressed, this, &mainWindow::chooseFolder);
    connect(ui->pushButton_calculate, &QPushButton::pressed, this, &mainWindow::compute);
    connect(ui->checkBox_hidePrefix, &QCheckBox::stateChanged, this, &mainWindow::showFiles);

    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setHorizontalHeaderLabels({"File path", "File size"});
}

mainWindow::~mainWindow() {
    delete ui;
    offThread();
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
    calculatedPath = curPath;

    ui->pushButton_cancel->show();
    delete counter;
    counter = new FileSizeCounter(curFiles);

    connect(counter, &FileSizeCounter::moreFiles, ui->progressBar, &QProgressBar::setValue);
    connect(counter, &FileSizeCounter::newInfo, ui->label_info, &QLabel::setText);

    connect(countingThread, &QThread::started, counter, &FileSizeCounter::doWork1);

    connect(ui->pushButton_cancel, &QPushButton::clicked, this, &mainWindow::unlockUi);
    connect(counter, &FileSizeCounter::finished, countingThread, &QThread::quit);
    connect(counter, &FileSizeCounter::finished, this, &mainWindow::showFiles);
    connect(counter, &FileSizeCounter::finished, this, &mainWindow::unlockUi);

    counter->setStart(curPath);
    counter->setMaxDeep(maxDeep);
    counter->moveToThread(countingThread);

    curFiles.clear();
    ui->tableWidget->setRowCount(0);
    lockUi();

    countingThread->start();
}

void mainWindow::showFiles() {
    ui->pushButton_cancel->hide();
    lockUi();
    ui->tableWidget->hide();

    std::sort(curFiles.begin(), curFiles.end(),
              [](const QPair<QDir, qint64> &l,
                 const QPair<QDir, qint64> &r) {
                  return l.second > r.second;
              });

    ui->tableWidget->setRowCount(0);

    for (const QPair<QDir, qint64> &path : curFiles) {
        int nowRow = ui->tableWidget->rowCount();
        ui->tableWidget->setRowCount(nowRow + 1);

        QString nowPath = path.first.path();
        if (ui->checkBox_hidePrefix->isChecked()) {
            nowPath = calculatedPath.relativeFilePath(path.first.path());
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
    ui->checkBox_hidePrefix->setEnabled(true);
    ui->spinBox_recursionLimit->setEnabled(true);
}

void mainWindow::lockUi() {
    ui->pushButton_chooseFolder->setEnabled(false);
    ui->pushButton_calculate->setEnabled(false);
    ui->checkBox_hidePrefix->setEnabled(false);
    ui->spinBox_recursionLimit->setEnabled(false);
}
