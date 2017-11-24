#include <QCoreApplication>
#include <QRegularExpression>
#include <QDebug>

QString formatThousandsSeparators(const QString &str)
{
    QString result = str;
    int startPos = result.indexOf(QRegularExpression("[0-9]"));
    if (startPos >= 0) {
        int endPos = result.indexOf(QRegularExpression("[.]"));

        if (endPos < 0) {
            endPos = result.length();
        }

        for (int i = endPos - 3; i >= startPos + 1; i -= 3) {
            result.insert(i, ",");
        }
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

    QString expression = "22222222222×(2323333)222+21232-23343|";
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
        // QRegExp reg("\\d*");
        // if (reg.exactMatch(item)) {
        //     qDebug() << item << "is digit";
        // }
        if (stringIsDigit(item)) {
            item = formatThousandsSeparators(item);
        }

        formatStr.append(item);
    }

    qDebug() << formatStr.replace("|", "");

    return 0;
}
