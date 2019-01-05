#ifndef PROJETO_AEDA_EXCEPTIONS_H
#define PROJETO_AEDA_EXCEPTIONS_H

#include <string>
#include <sstream>
#include <vector>
#include "timing.h"

using namespace std;

typedef unsigned int id_t;

/**
 * @brief Exception thrown when there are two repeated objects.
 * 
 */
class RepeatedObject {
    string object_class;
public:
    explicit RepeatedObject(string object_class): object_class(object_class) { }
    string get_class() const { return object_class; }
    string what() const;
};

/**
 * @brief Exception thrown when an object does not exists.
 * 
 */
class InexistentObject {
    string object_class;
public:
    explicit InexistentObject(string object_class): object_class(object_class) { }
    string get_class() const { return object_class; }
    string what() const;
};

/**
 * @brief Exception thrown when the type of Use (Free or Class) is wrong:
 * 
 */
class WrongUseType {
public:
    string what() const;
};

/**
 * @brief Exception thrown when two objects of the same class have the same
 * name.
 * 
 */
class SameName {
private:
    vector<id_t> people;
    string name;
public:
    explicit SameName(string name, vector<id_t> people): name(move(name)), people(move(people)) { }
    string what() const;
};

/**
 * @brief Exception thrown when the court is at maximum capacity for a given
 * type frame:
 * 
 */
class CourtIsFull {
    id_t court;
    Period time;
public:
    explicit CourtIsFull(id_t court, Period time): court(court), time(move(time)) { }
    string what() const;
};
#endif //PROJETO_AEDA_EXCEPTIONS_H
