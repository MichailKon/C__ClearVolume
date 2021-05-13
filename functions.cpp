//
// Created by michael on 10.05.2021.
//

#include "functions.h"

QString funcs::toHumanReadable(qint64 size) {
    int i = 0;
    long double mantissa = size;
    for (; mantissa >= 1000.; mantissa /= 1000., ++i) {}
    mantissa = std::ceil(mantissa * 10.) / 10.;
    QString res;

    res += QString::number((double)mantissa);
    res += "BKMGTPE"[i];
    if (i != 0) res += QString("B (") + QString::number(size) + QString(")");
    return res;
}
