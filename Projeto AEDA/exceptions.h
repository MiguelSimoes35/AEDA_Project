#ifndef PROJETO_AEDA_EXCEPTIONS_H
#define PROJETO_AEDA_EXCEPTIONS_H

#include <string>
#include <sstream>
using namespace std;

class InexistentMonth {
    int month;
public:
    explicit InexistentMonth(int m): month(m) { }
    const char* what() const;
};

class InexistentDate {
    int year, month, day;
public:
    explicit InexistentDate(int y, int m, int d): month(m), day(d), year(y) { }
    const char* what() const;
};

class InvalidTime {
    int hour, minute;
public:
    explicit InvalidTime(int h, int min): hour(h), minute(min) { }
    const char* what() const;
};

class InvalidPeriod {
    int hour, minute, blocks;
public:
    explicit InvalidPeriod(int h, int m, int b): hour(h), minute(m), blocks(b) { }
    const char* what() const;
};

#endif //PROJETO_AEDA_EXCEPTIONS_H
