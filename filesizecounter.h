//
// Created by michael on 11.05.2021.
//

#ifndef C__CLEARVOLUME_FILESIZECOUNTER_H
#define C__CLEARVOLUME_FILESIZECOUNTER_H

#include <QObject>
#include <boost/filesystem.hpp>
#include <QMutex>
#include "functions.h"

class FileSizeCounter : public QObject {
Q_OBJECT
private:
    boost::filesystem::path start;
    QVector<QPair<boost::filesystem::path, std::uintmax_t>> &out;
    int maxDeep;

public:
    explicit FileSizeCounter(QVector<QPair<boost::filesystem::path, std::uintmax_t>> &);

    ~FileSizeCounter() override;

    void setStart(const boost::filesystem::path &);

    void setMaxDeep(const int &);

public slots:

    std::uintmax_t doWork1();

    std::uintmax_t doWork(const boost::filesystem::path &, int = 0);

signals:

    void finished();
};


#endif //C__CLEARVOLUME_FILESIZECOUNTER_H
