//
// Created by michael on 11.05.2021.
//

#include "filesizecounter.h"
#include "functions.h"

qint64 FileSizeCounter::doWork(const QDir &path, int deep) {
    QFileInfo info(path.path());
    qint64 sz = 0;
    cnt++;
    if (info.isFile()) {
        sz = info.size();
        if (deep <= maxDeep) {
            out.push_back(QPair(path.path(), sz));
        }
        return sz;
    }

    QDirIterator it(path.path(), QDir::Hidden | QDir::AllEntries | QDir::NoDotAndDotDot | QDir::NoSymLinks);
    while (it.hasNext()) {
        if (QThread::currentThread()->isInterruptionRequested()) {
            return sz;
        }
        QDir next = it.next();
        qint64 res = doWork(next, deep + 1);
        emit moreFiles(100 * cnt / allCnt);
        sz += res;
    }

    if (deep <= maxDeep) {
        out.push_back(QPair(path.absolutePath(), sz));
    }
    return sz;
}

void FileSizeCounter::setStart(const QDir &newStart) {
    start = newStart;
}

void FileSizeCounter::setMaxDeep(const int &newMaxDeep) {
    maxDeep = newMaxDeep;
}

FileSizeCounter::FileSizeCounter(QVector<QPair<QDir, qint64>> &out) : out(out) {
    maxDeep = INT_MAX;
    cnt = 0;
    start = QDir();
}

void FileSizeCounter::doWork1() {
    emit newInfo(QString("Calculating cnt files"));
    allCnt = getCntFiles(start);
    if (QThread::currentThread()->isInterruptionRequested()) {
        return;
    }
    emit newInfo(QString("Calculating sizes"));
    out.reserve(allCnt);
    cnt = 0;
    doWork(start);
    emit newInfo(QString("Ready"));
    emit finished();
}

int FileSizeCounter::getCntFiles(const QDir &path) {
    allCnt = 1;
    QDirIterator it(path.path(), QDir::NoDotAndDotDot | QDir::AllEntries | QDir::Hidden | QDir::NoSymLinks,
                    QDirIterator::Subdirectories);
    while (it.hasNext()) {
        if (QThread::currentThread()->isInterruptionRequested()) {
            return allCnt;
        }
        allCnt++;
        it.next();
    }
    return allCnt;
}

FileSizeCounter::~FileSizeCounter() = default;
