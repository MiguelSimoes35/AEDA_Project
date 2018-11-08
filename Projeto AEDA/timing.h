#ifndef TIMING_H
#define TIMING_H

#include "exceptions.h"
using namespace std;

//====================================================================================================================//

bool is_leap_year(int y);

int num_of_days(int y, int m);

//====================================================================================================================//

class Month {
protected:
    int month, year;

    virtual void increment();
    virtual void decrement();
    virtual bool equal_to (const Month & m) const;
    virtual bool less_than  (const Month & m) const;
    static void valid_check(int m);

public:
    Month(int y, int m);

    int get_month() const { return month; }
    int get_year() const { return year; }

    virtual void set_month(int y, int m);

    virtual Month & operator++ ();
    virtual const Month operator++(int);
    virtual Month & operator-- ();
    virtual const Month operator--(int);

    virtual bool operator== (const Month & rhs) const { return equal_to(rhs); }
    virtual bool operator<  (const Month & rhs) const { return less_than(rhs); }

    bool is_leap_year() const;
    int num_of_days() const;
};


//====================================================================================================================//

class Date: public Month {
protected:
    int day;

    virtual void increment();
    virtual void decrement();
    virtual bool equal_to (const Date & d) const;
    virtual bool less_than  (const Date & d) const;
    static void valid_check(int y, int m, int d);

public:
    Date(int y, int m, int d);
    Date(const Month & M, int d);

    int get_day() const { return day; };

    void set_month(int y, int m);
    void set_date(int y, int m, int d);
    void set_date(const Month & M, int d) { set_date(M.get_year(),M.get_month(),d); }

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
    static void valid_check(int h, int min);

public:
    Time(int y, int m, int d, int h, int min);
    Time(const Month & M, int d, int h, int min);
    Time(const Date & D, int h, int min);

    int get_hour() const { return hour; }
    int get_min() const { return minute; }

    void set_time(int h, int min) { valid_check(h,min); hour = h; minute = min; }

    Time & operator++ ();
    const Time operator++ (int);
    Time & operator-- ();
    const Time operator-- (int);

    bool operator== (const Time & rhs) const { return equal_to(rhs); }
    bool operator< (const Time & rhs) const { return less_than(rhs); }

    void advance(int b);
    void recede(int b);
};

//====================================================================================================================//

class  Period: Time {
private:
    int blocks;

    static void valid_check(int b);
    bool equal_to (const Period & p) const;
    bool less_than (const Period & p) const;

public:
    Period(int y, int m, int d, int h, int min, int b): Time(y,m,d,h,min) { valid_check(b); blocks = b; }
    Period(const Month & M, int d, int h, int min, int b): Time(M,d,h,min) { valid_check(b); blocks = b; }
    Period(const Date & D, int h, int min, int b): Time(D,h,min) { valid_check(b); blocks = b; }
    Period(const Time & T, int b): Time(T) { valid_check(b); blocks = b; }

    int get_blocks() const { return blocks; }
    int get_duration() const { return blocks * 30; }
    Period get_sub_period(int i) const;

    void set_blocks(int b) { valid_check(b); blocks = b; }

    bool operator== (const Period & rhs) const { return equal_to(rhs); }
    bool operator< (const Period & rhs) const { return less_than(rhs); }

};

//====================================================================================================================//

bool overlap_check(const Period& p1, const Period& p2);

Period generate_future_period(const Period& earlier_period, int blocks_to_adv);

//====================================================================================================================//

#endif //TIMING_H
