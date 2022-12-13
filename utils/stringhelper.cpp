#include "stringhelper.h"


QString qstr(const std::string &str)
{
    return QString::fromStdString(str);
}

QString qstr(const char *str)
{
    return QString(str);
}

std::string stdstr(const QString &str)
{
    return str.toStdString();
}
