//
// Created by michael on 11.05.2021.
//

#include "filesizecounter.h"
#include "functions.h"

std::uintmax_t FileSizeCounter::doWork(const boost::filesystem::path &path, int deep) {
    qDebug() << QString::fromStdString(path.string()) << '\n';
    std::uintmax_t sz = 0;
    try {

        if (boost::filesystem::is_regular_file(path)) {
            sz = boost::filesystem::file_size(path);
            if (deep <= maxDeep) {
                out.push_back(QPair(path, sz));
            }
            return sz;
        }

        boost::filesystem::directory_iterator it;
        it = boost::filesystem::directory_iterator(path);
        while (it != end(boost::filesystem::directory_iterator(path))) {

            if (QThread::currentThread()->isInterruptionRequested()) {
                return sz;
            }

            sz += doWork(*it, deep + 1);
            ++it;
        }
    } catch (const boost::filesystem::filesystem_error &ex) {
        qDebug() << ex.what() << "\n";
        emit finished();
        return 0;
    }

    if (deep <= maxDeep) {
        out.push_back(QPair(path, sz));
    }

    if (path == start) emit finished();
    return sz;
}

void FileSizeCounter::setStart(const boost::filesystem::path &newStart) {
    start = newStart;
}

void FileSizeCounter::setMaxDeep(const int &newMaxDeep) {
    maxDeep = newMaxDeep;
}

FileSizeCounter::FileSizeCounter(QVector<QPair<boost::filesystem::path, std::uintmax_t>> &out) : out(out) {
    maxDeep = INT_MAX;
    start = boost::filesystem::path();
}

std::uintmax_t FileSizeCounter::doWork1() {
    return doWork(start);
}

FileSizeCounter::~FileSizeCounter() = default;
