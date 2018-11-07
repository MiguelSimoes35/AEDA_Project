#include "exceptions.h"

const char* InexistentMonth::what() const {
    stringstream out;
    out << month << " is not a valid month. Only integers between 1 (January) and 12 (December) are accepted.\n";
    return out.str().c_str();
}

const char* InexistentDate::what() const {
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
    out << "The period " << blocks << "half hour blocks from " << hour << ':' << minute << " is not valid."
        << "Please make sure you set a valid hour (0-23), either 0 or 30 minutes and a number of blocks between 1 and 4\n";
    return out.str().c_str();
}