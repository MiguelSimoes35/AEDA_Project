#ifndef PROJETO_AEDA_EXCEPTIONS_H
#define PROJETO_AEDA_EXCEPTIONS_H

#include <string>
#include <sstream>
using namespace std;

class InvalidMonth {
    int month;
public:
    explicit InvalidMonth(int m): month(m) { }
    const char* what() const;
};

class InvalidDate {
    int year, month, day;
public:
    explicit InvalidDate(int y, int m, int d): month(m), day(d), year(y) { }
    const char* what() const;
};

class InvalidPeriod {
    int hour, minute, blocks;
public:
    explicit InvalidPeriod(int h, int min, int b): hour(h), minute(min), blocks(b) { }
    const char* what() const;
};

class NonExistentSubPeriod {
    int blocks, index;
public:
    explicit NonExistentSubPeriod(int b, int i): blocks(b), index(i) { }
    const char* what() const;
};

class RepeatedObject {
    string object_class;
public:
    explicit RepeatedObject(string object_class): object_class(object_class) { }
    const char* what() const;
};

class InexistentObject {
    string object_class;
public:
    explicit InexistentObject(string object_class): object_class(object_class) { }
    const char* what() const;
};
#endif //PROJETO_AEDA_EXCEPTIONS_H
