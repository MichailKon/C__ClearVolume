#include <QApplication>
#include <QPushButton>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    mainWindow win;
    win.show();

    return QApplication::exec();
}
