#include "utility.h"
using namespace std;

//====================================================================================================================//

bool is_leap_year(int y) {
    if (y % 100 == 0)
        return y % 400 == 0;
    else
        return y % 4 == 0;
}

int num_of_days(int y, int m) {
    if (m > 12 || m < 1)
        throw InexistentMonth(m);
    else if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)
        return 31;
    else if (m == 2)
        return is_leap_year(y) ? 29 : 28;
    else
        return 30;
}

Period generate_future_period(const Period& earlier_period, int blocks_to_adv) {
    int h = earlier_period
}

//====================================================================================================================//
//====================================================== MES =========================================================//
//====================================================================================================================//

Month::Month(int y, int m) {
    if (month < 1 || month > 12)
        throw InexistentMonth(month);
    else {
        year = y;
        month = y;
    }
}

//====================================================================================================================//

Month & Month::operator++ () {
    increment();
    return (*this);
}

//====================================================================================================================//

Month & Month::operator-- () {
    decrement();
    return (*this);
}

//====================================================================================================================//

const Month Month::operator++ (int) {
    const Month copy = *this;
    increment();
    return copy;
}

//====================================================================================================================//

const Month Month::operator-- (int) {
    const Month copy = *this;
    decrement();
    return copy;
}

//====================================================================================================================//

bool Month::equal_to (const Month & m) const{
    return (month == m.month) && (year == m.year);
}

//====================================================================================================================//

bool Month::less_than (const Month & m) const {
    return (year == m.year) ? (month < m.month) : (year < m.year);
}

//====================================================================================================================//

void Month::decrement() {
    if (month == 1) {
        month = 12;
        year--;
    }
    else
        month--;
}

//====================================================================================================================//

void Month::increment() {
    if (month == 12) {
        month = 1;
        year++;
    }
    else
        month++;
}

//====================================================================================================================//

bool Month::is_leap_year() const {
    return ::is_leap_year(year);
}

//====================================================================================================================//

int Month::num_of_days() const {
    return ::num_of_days(year,month);
}

//====================================================================================================================//
//==================================================== DATA ==========================================================//
//====================================================================================================================//

Date::Date(int y, int m, int d): Month(y,m) {
    if (d < 1 || d > num_of_days())
        throw InexistentDate(y,m,d);
    else
        day = d;
}

Date::Date(const Month &M, int d): Month(M) {
    if (d < 1 || d > num_of_days())
        throw InexistentDate(year,month,d);
    else
        day = d;
}

//====================================================================================================================//

Date & Date::operator++ () {
    increment();
    return (*this);
}

//====================================================================================================================//

Date & Date::operator-- () {
    decrement();
    return (*this);
}

//====================================================================================================================//

const Date Date::operator++ (int) {
    const Date copy = *this;
    increment();
    return copy;
}

//====================================================================================================================//

const Date Date::operator-- (int) {
    const Date copy = *this;
    decrement();
    return copy;
}

//====================================================================================================================//

void Date::increment() {
    if (day == num_of_days()) {
        Month::increment();
        day = 1;
    }
    else
        day++;
}

//====================================================================================================================//

void Date::decrement() {
    if (day == 1) {
        Month::decrement();
        day = num_of_days();
    }
    else
        day--;
}

//====================================================================================================================//

bool  Date::equal_to (const Date & d) const {
    return (Month::equal_to(d) && day == d.day);
}

//====================================================================================================================//

bool  Date::less_than (const Date & d) const {
    if (Month::equal_to(d))
        return day < d.day;
    else
        return Month::less_than(d);
}

//====================================================================================================================//
//===================================================== TIME =========================================================//
//====================================================================================================================//

Time::Time(int y, int m, int d, int h, int min): Date(y,m,d) {
    if (h > 23 || h < 0 || (min != 0 && min != 30))
        throw InvalidTime(h,min);
    else {
        hour = h;
        minute = min;
    }
}

//====================================================================================================================//

Time::Time(const Month& M, int d, int h, int min): Date(M,d) {
    if (h > 23 || h < 0 || (min != 0 && min != 30))
        throw InvalidTime(h,min);
    else {
        hour = h;
        minute = min;
    }
}

//====================================================================================================================//

Time::Time(const Date& D, int h, int min): Date(D) {
    if (h > 23 || h < 0 || (min != 0 && min != 30))
        throw InvalidTime(h,min);
    else {
        hour = h;
        minute = min;
    }
}

//====================================================================================================================//

void Time::increment() {
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

//====================================================================================================================//

void Time::decrement() {
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

//====================================================================================================================//

Time & Time::operator++ () {
    increment();
    return (*this);
}

//====================================================================================================================//

Time & Time::operator-- () {
    decrement();
    return (*this);
}

//====================================================================================================================//

const Time Time::operator++ (int) {
    const Time copy = *this;
    increment();
    return copy;
}

//====================================================================================================================//

const Time Time::operator-- (int) {
    const Time copy = *this;
    decrement();
    return copy;
}

//====================================================================================================================//

bool Time::equal_to(const Time & t) const {
    return (Date::equal_to(t) && hour == t.hour && minute == t.minute);
}

//====================================================================================================================//

bool Time::less_than(const Time & t) const {
    if (Date::equal_to(t)) {
        if (hour == t.hour)
            return minute < t.minute;
        else
            return hour < t.hour;
    }
    else
        return Date::less_than(t);
}
//====================================================================================================================//
//==================================================== PERIODO =======================================================//
//====================================================================================================================//

void Period::valid_check(int h, int m, int b) {
    if (h < 0 || h > 23 || !(m == 0 || m == 30) || b < 1 || b > 4 )
        throw InvalidPeriod(h,m,b);
}

Period::Period(Date& dt, int h, int min, int b): date(dt) {
    valid_check();
    hour = h;
    minute = min;
    blocks = b;
}

Period::Period(int y, int m, int d, int h, int min, int b): date(y,m,d) {
    valid_check();
    hour = h;
    minute = min;
    blocks = b;
}

bool Period::operator==(const Period &rhs) const {
    return (date == rhs.date && hour == rhs.hour && minute == rhs.minute && blocks == rhs.blocks);
}

bool Period::operator<(const Period &rhs) const {
    if (date == rhs.date) {
        if (hour == rhs.hour) {
            if (minute == rhs.minute)
                return blocks < rhs.blocks;
            else
                return minute < rhs.minute;
        }
        else
            return hour < rhs.hour;
    }
    else
        return date < rhs.date;
}
