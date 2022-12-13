#ifndef STRINGHELPER_H
#define STRINGHELPER_H

#include <QString>
#include <string>
// convert QString to const char *
#define cstr(qstr) qstr.toStdString().c_str()

// copy QString to char array buffer
template <int Size>
void qstr2carray(const QString &qstr, char (&carray)[Size]) {
    strncpy(carray, cstr(qstr), Size - 1);
    carray[Size - 1] = '\0';
}
// convert std::string to QString
QString qstr(const std::string &str);
// convert const char * to QString
QString qstr(const char *str);
// convert QString to std::string
std::string stdstr(const QString &str);

#endif // STRINGHELPER_H
