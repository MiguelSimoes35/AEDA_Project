#include "timing.h"
using namespace std;

//====================================================================================================================//
//==================================================== MONTH =========================================================//
//====================================================================================================================//

string Month::get_export() const {
    return to_string(year) + "," + to_string(month) + ",";
}
void Month::valid_check(int m) {
    if (m < 1 || m > 12)
        throw InvalidMonth(m);
}

Month::Month(istream& input) {
    string temp;
    getline(input,temp,',');
    year = stoi(temp);
    getline(input,temp,',');
    int m = stoi(temp);
    valid_check(m);
    month = m;
}
Month::Month() {
	month = 1;
	year = 1;
}

Month::Month(int y, int m) {
    valid_check(m);
    year = y;
    month = m;
}

void Month::set_month(int y, int m) {
    valid_check(m);
    year = y;
    month = m;
}

Month & operator++ (Month& rhs) {
    rhs.increment();
    return rhs;
}

Month & operator-- (Month& rhs) {
    rhs.decrement();
    return rhs;
}

const Month operator++ (Month& lhs, int) {
    const Month copy = lhs;
    lhs.increment();
    return copy;
}

const Month operator-- (Month& lhs, int) {
    const Month copy = lhs;
    lhs.decrement();
    return copy;
}

bool Month::equal_to (const Month & m) const {
    return (month == m.month) && (year == m.year);
}

bool Month::less_than (const Month & m) const {
    return (year == m.year) ? (month < m.month) : (year < m.year);
}

void Month::decrement() {
    if (month == 1) {
        month = 12;
        year--;
    }
    else
        month--;
}

void Month::increment() {
    if (month == 12) {
        month = 1;
        year++;
    }
    else
        month++;
}

bool Month::is_leap_year() const {
    return ::is_leap_year(year);
}

int Month::num_of_days() const {
    return ::num_of_days(year,month);
}

//====================================================================================================================//
//==================================================== DATE ==========================================================//
//====================================================================================================================//

Date::Date()
: Month() {
	day = 1;
}

Date::Date(istream &input): Month(input) {
    string temp;
    getline(input,temp,',');
    int d = stoi(temp);
    valid_check(year,month,d);
    day = d;
}

string Date::get_export() const {
    return Month::get_export()  + to_string(day) + ",";
}
void Date::valid_check(int y, int m, int d) {
    Month::valid_check(m);
    if (d < 1 || d > ::num_of_days(y,m))
        throw InvalidDate(y,m,d);
}

Date::Date(int y, int m, int d): Month(y,m) {
    if (d < 1 || d > num_of_days())
        throw InvalidDate(y,m,d);
    else
        day = d;
}

Date::Date(const Month &M, int d): Month(M) {
    if (d < 1 || d > num_of_days())
        throw InvalidDate(year,month,d);
    else
        day = d;
}

void Date::set_month(int y, int m) {
    Month::set_month(y,m);
    valid_check(y,m,day);
}

void Date::set_date(int y, int m, int d) {
    valid_check(y,m,d);
    year = y; month = m; day = d;
}

Date & operator++ (Date& rhs) {
    rhs.increment();
    return rhs;
}

Date & operator-- (Date& rhs) {
    rhs.decrement();
    return rhs;
}

const Date operator++ (Date& lhs, int) {
    const Date copy = lhs;
    lhs.increment();
    return copy;
}

const Date operator-- (Date& lhs, int) {
    const Date copy = lhs;
    lhs.decrement();
    return copy;
}

void Date::increment() {
    if (day == num_of_days()) {
        Month::increment();
        day = 1;
    }
    else
        day++;
}

void Date::decrement() {
    if (day == 1) {
        Month::decrement();
        day = num_of_days();
    }
    else
        day--;
}

bool  Date::equal_to (const Date & d) const {
    return (Month::equal_to(d) && day == d.day);
}

bool  Date::less_than (const Date & d) const {
    if (Month::equal_to(d))
        return day < d.day;
    else
        return Month::less_than(d);
}

//====================================================================================================================//
//==================================================== PERIOD ========================================================//
//====================================================================================================================//

Period::Period(istream& input): Date(input) {
    string temp;
    int h, min, b;
    getline(input,temp,',');
    h = stoi(temp);
    getline(input,temp,',');
    min = stoi(temp);
    getline(input,temp,',');
    b = stoi(temp);
    valid_check(h,min,b);
    hour = h; minute = min; blocks = b;
}

string Period::get_export() const {
    return Date::get_export() + to_string(hour) + "," + to_string(minute) + "," + to_string(blocks) + ",";
}

void Period::valid_check(int h, int min, int b) {
    if (h > 23 || h < 0 || (min != 0 && min != 30) || b < 1 || b > 4)
        throw InvalidPeriod(h,min,b);

}

Period::Period(int y, int m, int d, int h, int min, int b): Date(y,m,d) {
    valid_check(h,min,b);
    hour = h; minute = min; blocks = b;
}

Period::Period(const Month& M, int d, int h, int min, int b): Date(M,d) {
    valid_check(h,min,b);
    hour = h; minute = min; blocks = b;
}

Period::Period(const Date& D, int h, int min, int b): Date(D) {
    valid_check(h,min,b);
    hour = h; minute = min; blocks = b;
}

void Period::increment() {
    if (hour == 23 && minute == 30) {
        Date::increment();
        hour = 0;
        minute = 0;
    }
    else {
        if (minute == 0)
            minute = 30;
        else {
            hour++;
            minute = 0;
        }
    }
}

void Period::decrement() {
    if (hour == 0 && minute == 0) {
        Date::decrement();
        hour = 23;
        minute = 30;
    }
    else {
        if (minute == 30)
            minute = 0;
        else {
            hour--;
            minute = 30;
        }
    }
}

Period & operator++ (Period& rhs) {
    rhs.increment();
    return rhs;
}

Period & operator-- (Period& rhs) {
    rhs.decrement();
    return rhs;
}

const Period operator++ (Period& lhs, int) {
    const Period copy = lhs;
    lhs.increment();
    return copy;
}

const Period operator-- (Period& lhs, int) {
    const Period copy = lhs;
    lhs.decrement();
    return copy;
}

bool Period::equal_to(const Period & p) const {
    return (Date::equal_to(p) && hour == p.hour && minute == p.minute && blocks == p.blocks);
}

bool Period::less_than(const Period & p) const {
    if (Date::equal_to(p)) {
        if (hour == p.hour) {
            if (minute == p.minute)
                return blocks < p.blocks;
            else
                return minute < p.minute;
        }
        else
            return hour < p.hour;
    }
    else
        return Date::less_than(p);
}

void Period::postpone(int b) {
    if (b < 0) hasten(-b);
    for (int i = 0; i < b; i++) increment();
}

void Period::hasten(int b) {
    if (b < 0) postpone(-b);
    for (int i = 0; i < b; i++) decrement();
}

Period Period::get_sub_period(int i) const {
    if (i < 1 || i > blocks)
        throw NonExistentSubPeriod(blocks,i);
    else {
        Period copy = *this;
        copy.set_blocks(1);
        copy.postpone(i - 1);
        return copy;
    }
}

//====================================================================================================================//
//============================================ UTILITY FUNCTIONS =====================================================//
//====================================================================================================================//

bool is_leap_year(int y) {
    if (y % 100 == 0)
        return y % 400 == 0;
    else
        return y % 4 == 0;
}

int num_of_days(int y, int m) {
    if (m > 12 || m < 1)
        throw InvalidMonth(m);
    else if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)
        return 31;
    else if (m == 2)
        return is_leap_year(y) ? 29 : 28;
    else
        return 30;
}

bool check_overlap(const Period& p1, const Period& p2) {
    //p1 ends before p2 starts
    bool check1 = p1.get_sub_period(p1.get_blocks()) < p2.get_sub_period(1);
    //p2 ends before p1 starts
    bool check2 = p2.get_sub_period(p2.get_blocks()) < p1.get_sub_period(1);
    return check1 == check2;
}
/*
Period generate_future_period(const Period& earlier_period, int blocks_to_adv) {
    Period copy = earlier_period;
    copy.advance(blocks_to_adv);
    return copy;
}
 */
//====================================================================================================================//
//================================================== EXCEPTIONS ======================================================//
//====================================================================================================================//

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

const char* InvalidPeriod::what() const {
    stringstream out;
    out << "You set the period to last " << blocks << " blocks from " << hour << ':' << minute
        << ", but that number is not valid. Please choose a time of the type [0-23]:[0|30]"
        << " and a number of blocks between 1 and 4.\n";
    return out.str().c_str();
}

const char* NonExistentSubPeriod::what() const {
    stringstream out;
    out << "You asked for the subperiod " << index << " of a period that has " << blocks << " blocks. Please use an index"
        << " between 1 and " << blocks << ".\n";
    return out.str().c_str();
}

//====================================================================================================================//
