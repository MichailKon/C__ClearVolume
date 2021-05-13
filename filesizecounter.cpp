//
// Created by michael on 11.05.2021.
//

#include "filesizecounter.h"
#include "functions.h"

qint64 FileSizeCounter::doWork(const QDir &path, int deep) {
    QFileInfo info(path.path());
    qint64 sz = 0;
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
        sz += doWork(next, deep + 1);
    }

    if (deep <= maxDeep) {
        out.push_back(QPair(path.absolutePath(), sz));
    }

    if (path.path() == start.path()) {
        emit finished();
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
    start = QDir();
}

qint64 FileSizeCounter::doWork1() {
    return doWork(start);
}

FileSizeCounter::~FileSizeCounter() = default;
