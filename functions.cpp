//
// Created by michael on 10.05.2021.
//

#include "functions.h"

std::uintmax_t
funcs::getSizes(const boost::filesystem::path &path, QVector<QPair<QString, std::uintmax_t>> &now, int maxDeep,
                int nowDeep) {

    QString nowPath(path.c_str());
    if (boost::filesystem::is_regular_file(path)) {
        std::uintmax_t sz = boost::filesystem::file_size(path);
        if (nowDeep <= maxDeep) {
            now.push_back(QPair(nowPath, sz));
        }
        return sz;
    }

    std::uintmax_t sz = 0;

    boost::filesystem::directory_iterator it;
    try {
        it = boost::filesystem::directory_iterator(path);
        while (it != end(boost::filesystem::directory_iterator(path))) {
            sz += getSizes(*it, now, maxDeep, nowDeep + 1);
            ++it;
        }
    } catch (const boost::filesystem::filesystem_error &ex) {
        qDebug() << ex.what() << "\n";
        return 0;
    }

    if (nowDeep <= maxDeep) {
        now.push_back(QPair(nowPath, sz));
    }
    return sz;
}

QString funcs::toHumanReadable(std::uintmax_t size) {
    int i = 0;
    double mantissa = size;
    for (; mantissa >= 1000.; mantissa /= 1000., ++i) {}
    mantissa = std::ceil(mantissa * 10.) / 10.;
    QString res;
    res += QString::number(mantissa);
    res += "BKMGTPE"[i];
    if (i != 0) res += QString("B (") + QString::number(size) + QString(")");
    return res;
}
