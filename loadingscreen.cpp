//
// Created by michael on 11.05.2021.
//

// You may need to build the project (run Qt uic code generator) to get "ui_loadingscreen.h" resolved

#include "loadingscreen.h"
#include "uis/ui_loadingscreen.h"


LoadingScreen::LoadingScreen(QWidget *parent) :
        QWidget(parent), ui(new Ui::LoadingScreen), movie("images/loading.gif") {
    ui->setupUi(this);
    ui->label->setAlignment(Qt::AlignCenter);
    setLayout(ui->gridLayout);
    qDebug() << movie.isValid() << '\n';
    connect(ui->pushButton_cancel, &QPushButton::clicked, this, &LoadingScreen::endAnimation);

    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::CustomizeWindowHint);
    ui->label->setMovie(&movie);
}

LoadingScreen::~LoadingScreen() {
    delete ui;
}

void LoadingScreen::startAnimation() {
    qDebug() << QString::fromStdString("Started\n");
    movie.start();
    show();
}

void LoadingScreen::endAnimation() {
    qDebug() << QString::fromStdString("Stopped\n");
    movie.stop();
    hide();
    emit closed();
}