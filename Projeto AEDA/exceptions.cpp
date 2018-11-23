#include "exceptions.h"

string RepeatedObject::what() const {
    stringstream out;
    out << "The object of class " << object_class << " that you tried to add already exists.\n";
    return out.str();
}

string InexistentObject::what() const {
    stringstream out;
    out << "Could not find the object of class " << object_class << " in the data structure.\n";
    return out.str();
}

string WrongUseType::what() const {
    stringstream out;
    out << "You tried to add either an abstract use to a data structure, a Class Atendance to a Free Use list, or vice-versa\n";
    return out.str();
}

string SameName::what() const {
    stringstream out;
    out << "Multiple people with the name " << name << " exist. Use get_ids() to get a vector with their ids.";
    return out.str();
}

string CourtIsFull::what() const {
    stringstream out;
    out << "Court " << court << " is at maximum capacity for the period " << time.display_period();
    return out.str();
}
