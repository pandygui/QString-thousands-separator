/* -*- Mode: C++; indent-tabs-mode: nil; tab-width: 4 -*-
 * -*- coding: utf-8 -*-
 *
 * Copyright (C) 2017 Rekols
 *
 * Author:     Rekols <rekols@foxmail.com>
 * Maintainer: Rekols <rekols@foxmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QCoreApplication>
#include <QRegularExpression>
#include <QDebug>

QString formatThousandsSeparators(const QString &str)
{
    QString result = str;

    for (int i = result.count() - 3; i >= 1; i -= 3) {
        result.insert(i, ",");
    }

    return result;
}

bool stringIsDigit(const QString &str)
{
    bool isDigit = true;

    for (auto &ch : str) {
        if (!ch.isDigit()) {
            isDigit = false;
            break;
        }
    }

    return isDigit;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString expression = "23482342389478923904823904823908237890732489237894×(2323333)222+21232-23343|";
    QString seg;
    QStringList expList;

    for (auto &ch : expression) {
        if (ch.isDigit()) {
            seg.append(ch);
        } else {
            expList << seg;
            seg.clear();
            expList << ch;
        }
    }

    QString formatStr;
    for (auto item : expList) {
        if (stringIsDigit(item)) {
            item = formatThousandsSeparators(item);
        }

        formatStr.append(item);
    }

    qDebug() << formatStr.replace("|", "");

    return 0;
}
