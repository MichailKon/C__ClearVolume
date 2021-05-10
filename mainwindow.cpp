//
// Created by michael on 10.05.2021.
//

// You may need to build the project (run Qt uic code generator) to get "ui_mainWindow.h" resolved

#include "mainwindow.h"
#include "ui_mainWindow.h"
#include "functions.h"


mainWindow::mainWindow(QWidget *parent) :
        QWidget(parent), ui(new Ui::mainWindow) {
    ui->setupUi(this);
    this->setLayout(ui->gridLayout);

    connect(ui->pushButton_chooseFolder, &QPushButton::pressed,
            this, &mainWindow::chooseFolder);
    connect(ui->pushButton_calculate, &QPushButton::pressed,
            this, &mainWindow::compute);
    connect(ui->checkBox_hidePrefix, &QCheckBox::stateChanged,
            this, &mainWindow::showFiles);

    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setHorizontalHeaderLabels({"File path", "File size"});
}

mainWindow::~mainWindow() {
    delete ui;
}

QString mainWindow::chooseFolder() {
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "",
                                                    QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    ui->chosenFolder->setText(dir);
    this->curPath = boost::filesystem::path(dir.toStdString());

    return dir;
}

void mainWindow::compute() {
    int maxDeep = (ui->spinBox_recursionLimit->value() == 0 ? INT_MAX : ui->spinBox_recursionLimit->value());
    this->curFiles.clear();
    funcs::getSizes(this->curPath, this->curFiles, maxDeep);

    std::sort(this->curFiles.begin(), this->curFiles.end(),
              [](const QPair<QString, unsigned long> &l, const QPair<QString, unsigned long> &r) {
                  return l.second > r.second;
              });
    showFiles();
}

void mainWindow::showFiles() {
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->hide();

    for (const QPair<QString, unsigned long> &path : this->curFiles) {
        int nowRow = ui->tableWidget->rowCount();
        ui->tableWidget->setRowCount(nowRow + 1);

        QString nowPath = path.first;
        if (ui->checkBox_hidePrefix->isChecked()) {
            nowPath.remove(0, ui->chosenFolder->text().length());
        }
        auto *filePath = new QTableWidgetItem(nowPath);
        auto *fileSize = new QTableWidgetItem(funcs::toHumanReadable(path.second));
        ui->tableWidget->setItem(nowRow, 0, filePath);
        ui->tableWidget->setItem(nowRow, 1, fileSize);
    }

    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->show();
}
