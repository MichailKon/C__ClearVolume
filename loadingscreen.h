//
// Created by michael on 11.05.2021.
//

#ifndef C__CLEARVOLUME_LOADINGSCREEN_H
#define C__CLEARVOLUME_LOADINGSCREEN_H

#include <QWidget>
#include <QDialog>
#include <Qt>
#include <QDebug>
#include <QMovie>

QT_BEGIN_NAMESPACE
namespace Ui { class LoadingScreen; }
QT_END_NAMESPACE

class LoadingScreen : public QWidget {
Q_OBJECT

public:
    explicit LoadingScreen(QWidget *parent);

    ~LoadingScreen() override;

    void startAnimation();

    void endAnimation();

private:
    Ui::LoadingScreen *ui;
    QMovie movie;
signals:
    void closed();
};


#endif //C__CLEARVOLUME_LOADINGSCREEN_H
