#include "exceptions.h"

const char* InvalidMonth::what() const {
    stringstream out;
    out << month << " is not a valid month. Only integers between 1 (January) and 12 (December) are accepted.\n";
    return out.str().c_str();
}

const char* InvalidDate::what() const {
    stringstream out;
    out << "The month " << month << "of the year " << year
        << " does not have a day " << day << ". Please make sure you respect proper date construction.\n";
    return out.str().c_str();
}


const char* InvalidTime::what() const {
    stringstream out;
    out << "The time indicated (" << hour << ':' << minute << ") is not valid. Please make sure your time, h:min, is "
        << "of the type [0-23]:[0|30].\n";
    return out.str().c_str();
}
const char* InvalidPeriod::what() const {
    stringstream out;
    out << "You set the period to last " << blocks << " blocks, but that number is not valid. Please choose a number"
        << " between 1 and 4.\n";
    return out.str().c_str();
}

const char* NonExistentSubPeriod::what() const {
    stringstream out;
    out << "You asked for the subperiod " << index << " of a period that has " << blocks << " blocks. Please use an index"
        << " between 1 and " << blocks << ".\n";
    return out.str().c_str();
}
