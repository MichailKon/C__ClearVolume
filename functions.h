//
// Created by michael on 10.05.2021.
//



#ifndef C__CLEARVOLUME_FUNCTIONS_H
#define C__CLEARVOLUME_FUNCTIONS_H

#include <QString>
#include <QMap>
#include <boost/filesystem.hpp>
#include <cmath>
#include <QDebug>
#include <Qt>

namespace funcs {
    std::uintmax_t
    getSizes(const boost::filesystem::path &, QVector<QPair<QString, std::uintmax_t>> &, int = INT_MAX, int = 0);

    QString toHumanReadable(std::uintmax_t);
}

#endif //C__CLEARVOLUME_FUNCTIONS_H
