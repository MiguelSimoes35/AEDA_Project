#ifndef PROJETO_AEDA_EXCEPTIONS_H
#define PROJETO_AEDA_EXCEPTIONS_H

#include <string>
#include <sstream>
#include <vector>
#include "timing.h"

using namespace std;



class RepeatedObject {
    string object_class;
public:
    explicit RepeatedObject(string object_class): object_class(object_class) { }
    string get_class() const { return object_class; }
    const char* what() const;
};

class InexistentObject {
    string object_class;
public:
    explicit InexistentObject(string object_class): object_class(object_class) { }
    string get_class() const { return object_class; }
    const char* what() const;
};

class WrongUseType {
public:
    const char* what() const;
};

class SameName {
private:
    vector<id_t> people;
    string name;
public:
    explicit SameName(string name, vector<id_t> people): name(move(name)), people(move(people)) { }
    const char* what() const;
};

class CourtIsFull {
    id_t court;
    Period time;
public:
    explicit CourtIsFull(id_t court, Period time): court(court), time(move(time)) { }
    const char* what() const;
};
#endif //PROJETO_AEDA_EXCEPTIONS_H
