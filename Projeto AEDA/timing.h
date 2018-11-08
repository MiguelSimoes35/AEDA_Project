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

    friend Month & operator++ (Month& rhs);
    friend const Month operator++ (Month& lhs, int);
    friend Month & operator-- (Month& rhs);
    friend const Month operator-- (Month& lhs, int);

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

    friend Date & operator++ (Date& rhs);
    friend const Date operator++ (Date& lhs, int);
    friend Date & operator-- (Date& rhs);
    friend const Date operator-- (Date& lhs, int);

    virtual bool operator== (const Date & rhs) const { return equal_to(rhs); }
    virtual bool operator<  (const Date & rhs) const { return less_than(rhs); }
};

//====================================================================================================================//

class Period : public Date {
protected:
    int hour, minute, blocks;

    void increment();
    void decrement();
    virtual bool equal_to (const Period & t) const;
    virtual bool less_than  (const Period & t) const;
    static void valid_check(int h, int min, int b);

public:
    Period(int y, int m, int d, int h, int min, int b);
    Period(const Month & M, int d, int h, int min, int b);
    Period(const Date & D, int h, int min, int b);

    int get_hour() const { return hour; }
    int get_min() const { return minute; }
    int get_blocks() const { return blocks; }
    int get_duration() const { return blocks * 30; }
    Period get_sub_period(int i) const;

    void set_time(int h, int min) { valid_check(h,min,blocks); hour = h; minute = min; }
    void set_blocks(int b) { valid_check(hour,minute,b); blocks = b; }

    friend Period & operator++ (Period& rhs);
    friend const Period operator++ (Period& lhs, int);
    friend Period & operator-- (Period& rhs);
    friend const Period operator-- (Period& lhs, int);

    bool operator== (const Period & rhs) const { return equal_to(rhs); }
    bool operator< (const Period & rhs) const { return less_than(rhs); }

    void advance(int b);
    void recede(int b);
};

//====================================================================================================================//

bool overlap_check(const Period& p1, const Period& p2);

Period generate_future_period(const Period& earlier_period, int blocks_to_adv);

//====================================================================================================================//

#endif //TIMING_H
