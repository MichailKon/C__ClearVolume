//
// Created by michael on 11.05.2021.
//

#ifndef C__CLEARVOLUME_FILESIZECOUNTER_H
#define C__CLEARVOLUME_FILESIZECOUNTER_H

#include <QObject>
#include <boost/filesystem.hpp>
#include <QMutex>
#include <QDir>
#include <QFileInfo>
#include <QDirIterator>
#include "functions.h"

class FileSizeCounter : public QObject {
Q_OBJECT
private:
    QDir start;
    QVector<QPair<QDir, qint64>> &out;
    int maxDeep;

public:
    explicit FileSizeCounter(QVector<QPair<QDir, qint64>> &);

    ~FileSizeCounter() override;

    void setStart(const QDir &);

    void setMaxDeep(const int &);

public slots:

    qint64 doWork1();

    qint64 doWork(const QDir&, int = 0);

signals:

    void finished();
};


#endif //C__CLEARVOLUME_FILESIZECOUNTER_H
