#ifndef PROJETO_AEDA_UTILITY_H
#define PROJETO_AEDA_UTILITY_H

#include "exceptions.h"
using namespace std;

//====================================================================================================================//

bool is_leap_year(int y);

int num_of_days(int y, int m);

//====================================================================================================================//

class Month {
protected:
    int month;
    int year;

    virtual void increment();
    virtual void decrement();
    virtual bool equal_to (const Month & m) const;
    virtual bool less_than  (const Month & m) const;

public:
    Month(int y, int m);

    int get_month() const { return month; }
    int get_year() const { return year; }

    virtual Month & operator++ ();
    virtual const Month operator++(int);
    virtual Month & operator-- ();
    virtual const Month operator--(int);

    virtual bool operator== (const Month & rhs) const { return equal_to(rhs); }
    virtual bool operator<  (const Month & rhs) const { return less_than(rhs); }
};


//====================================================================================================================//

class Date: public Month {
protected:
    int day;

    virtual void increment();
    virtual void decrement();
    virtual bool equal_to (const Date & d) const;
    virtual bool less_than  (const Date & d) const;

public:
    Date(int y, int m, int d);
    Date(const Month & M, int d);

    int get_day() const { return day; };

    virtual Date & operator++ ();
    virtual const Date operator++(int);
    virtual Date & operator-- ();
    virtual const Date operator--(int);

    virtual bool operator== (const Date & rhs) const { return equal_to(rhs); }
    virtual bool operator<  (const Date & rhs) const { return less_than(rhs); }
};

//====================================================================================================================//

class Time : public Date {
protected:
    int hour, minute;

    void increment();
    void decrement();
    virtual bool equal_to (const Time & t) const;
    virtual bool less_than  (const Time & t) const;

public:
    Time(int y, int m, int d, int h, int min);
    Time(const Month & M, int d, int h, int min);
    Time(const Date & D, int h, int min);

    int get_hour() const { return hour; }
    int get_min() const { return minute; }

    Time & operator++ ();
    const Time operator++ (int);
    Time & operator-- ();
    const Time operator-- (int);

    bool operator== (const Time & rhs) const { return equal_to(rhs); }
    bool operator< (const Time & rhs) const { return less_than(rhs); }
};

class  Period: Time { //TODO
private:
    int blocks;

    static void valid_check(int h, int m, int b);

    void increment();
    void decrement();

public:
    Period(Date& dt, int h, int min, int b);
    Period(int y, int m, int d, int h, int min, int b);

    Date get_date() const { return date; }
    int get_hour() const { return hour; }
    int get_min() const { return minute; }
    int get_blocks() const { return blocks; }
    int get_duration() const { return blocks * 30; }

    bool operator== (const Period & rhs) const;
    bool operator< (const Period & rhs) const;

};

//====================================================================================================================//

bool overlap_check(const Period& p1, const Period& p2);

//====================================================================================================================//

#endif //PROJETO_AEDA_UTILITY_H
