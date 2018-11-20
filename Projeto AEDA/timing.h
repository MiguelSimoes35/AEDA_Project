#ifndef TIMING_H
#define TIMING_H

#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

//====================================================================================================================//

/**
 * Returns whether an year has an extra day in February
 * @param y Year
 * @return Whether the year is a multiple of 4 but not of 100 (except for multiples of 400)
 */
bool is_leap_year(int y);
/**
 * Returns the number of months in a certain month
 * @param y Year
 * @param m Month
 * @return Number of days in that month
 */
int num_of_days(int y, int m);

//====================================================================================================================//

class Month {
protected:
    int month, year;

    /**
     * Increments a month. Handles year changes.
     */
    virtual void increment();
    /**
     * Decrements a month. Handles year changes.
     */
    virtual void decrement();
    /**
     * Compares to a second month and sees if they are the same
     * @param m The month to compare to
     * @return Whether both objects refer to the same month
     */
    virtual bool equal_to (const Month & m) const;
    /**
     * Compares to a second month and sees whether self is an earlier month
     * @param m The month to compare to
     * @return Whether self is an earlier month
     */
    virtual bool less_than  (const Month & m) const;
    /**
     * Checks if the month checked is valid [1-12]. Throws InvalidMonth if not
     * @see InvalidMonth
     * @param m The month to check
     */
    static void valid_check(int m);

public:

	/**
	* Default constructor for class Month, set month to 1/1
	*/
	Month();

    /**
     * Checks if the month is valid and constructs the object
     * @param y Year
     * @param m Month
     */
    Month(int y, int m);

    /**
     * Returns string representing month in machine readable form
     * @return Parseable string
     */
    virtual string get_export() const;

    /**
     * Returns the month
     * @return The month
     */
    int get_month() const { return month; }
    /**
     * Returns the year
     * @return The year
     */
    int get_year() const { return year; }

    /**
     * Checks if the new month is valid and sets the object to it
     * @see valid_check
     * @param y The new year
     * @param m The new month
     */
    virtual void set_month(int y, int m);

    friend Month & operator++ (Month& rhs);
    friend const Month operator++ (Month& lhs, int);
    friend Month & operator-- (Month& rhs);
    friend const Month operator-- (Month& lhs, int);

    /**
     * Compares to a second month and sees whether self is an earlier month. Wraps equal_to
     * @param rhs The month to compare to
     * @return Whether self is an earlier month
     */
    bool operator== (const Month & rhs) const { return equal_to(rhs); }
    /**
     * Compares to a second month and sees whether self is an earlier month. Wraps less_than
     * @param rhs The month to compare to
     * @return Whether self is an earlier month
     */
    bool operator<  (const Month & rhs) const { return less_than(rhs); }

    /**
     * Returns whether the object's year is a leap year
     * @return Whether the year is a multiple of 4, except if it is divisible by 100 and not by 400
     */
    bool is_leap_year() const;
    /**
     * Returns the number of days in the month
     * @return The number of days in the object's month
     */
    int num_of_days() const;
};

/**
 * Increments the month and returns a reference to it
 * @param rhs The month to increment
 * @return A reference to the month
 */
Month & operator++ (Month& rhs);

/**
 * Increments the month and returns a copy in the previous state
 * @param lhs   The month to increment
 * @return  A copy of it before the operation
 */
const Month operator++ (Month& lhs, int);

/**
 * Decrements the month and returns a reference to it
 * @param rhs The month to decrement
 * @return A reference to the month
 */
Month & operator-- (Month& rhs);

/**
 * Decrements the month and returns a copy in the previous state
 * @param lhs   The month to decrement
 * @return  A copy of it before the operation
 */
const Month operator-- (Month& lhs, int);

/**
 * Prints the month to an output stream (yyyy.mm)
 * @param lhs   Output stream
 * @param rhs   Month
 * @return  Reference to the output stream
 */
ostream& operator<<(ostream& lhs, const Month& rhs) {
    lhs << rhs.get_year() << "." << setfill('0') << setw(2) << rhs.get_month();
    return lhs;
}

//====================================================================================================================//

class Date: public Month {
protected:
    int day;

    /**
     * Increments the date, handles month changes
     */
    void increment() override;
    /**
     * Decrements the date, handles month changes
     */
    void decrement() override;
    /**
     * Compares to a second Date object and sees if they are the same
     * @param d The date to compare to
     * @return Whether they represent the same date
     */
    virtual bool equal_to (const Date & d) const;
    /**
     * Compares to a second Date object and checks if self is earlier
     * @param d The date to compare to
     * @return Whether self represents an earlier date
     */
    virtual bool less_than  (const Date & d) const;
    /**
     * Checks whether the parameters configure a valid date. If not, throws InvalidDate
     * @see InvalidDate
     * @param y Year
     * @param m Month
     * @param d Day
     */
    static void valid_check(int y, int m, int d);

public:

	/**
	* Default constructor for class date. Sets date to 1/1/1
	*/
	Date();

    /**
     * Constructs base Month object, checks if the parameters are valid, and constructs the object
     * @param y Year
     * @param m Month
     * @param d Day
     */
    Date(int y, int m, int d);
    /**
     * Constructs base Month object, checks if the parameters are valid, and constructs the object
     * @param M Month object to copy
     * @param d Day
     */
    Date(const Month & M, int d);

    /**
     * Returns string representing date in machine readable form
     * @return Parseable string
     */
    string get_export() const override;

    /**
     * Returns the day
     * @return The day
     */
    int get_day() const { return day; };

    /**
     * Invokes the base class set_month function and checks if the object's day remains valid
     * @param y New year
     * @param m New month
     */
    void set_month(int y, int m) override;
    /**
     * Checks if the parameters are valid and changes the date to them
     * @param y New year
     * @param m New month
     * @param d New day
     */
    void set_date(int y, int m, int d);
    /**
     * Checks if the parameters are valid and changes the date to them
     * @param M Month object to copy the new year and month from
     * @param d New day
     */
    void set_date(const Month & M, int d) { set_date(M.get_year(),M.get_month(),d); }

    friend Date & operator++ (Date& rhs);
    friend const Date operator++ (Date& lhs, int);
    friend Date & operator-- (Date& rhs);
    friend const Date operator-- (Date& lhs, int);


    /**
     * Compares to a second Date object and sees if they are the same
     * @param rhs The date to compare to
     * @return Whether they represent the same date
     */
    bool operator== (const Date & rhs) const { return equal_to(rhs); }
    /**
     * Compares to a second Date object and checks if self is earlier
     * @param rhs The date to compare to
     * @return Whether self represents an earlier date
     */
    bool operator<  (const Date & rhs) const { return less_than(rhs); }
};

/**
 * Increments the date and returns a reference to it
 * @param rhs The date to increment
 * @return A reference to the date
 */
Date & operator++ (Date& rhs);

/**
 * Increments the date and returns a copy in the previous state
 * @param lhs   The date to increment
 * @return  A copy of it before the operation
 */
const Date operator++ (Date& lhs, int);

/**
 * Decrements the date and returns a reference to it
 * @param rhs The date to decrement
 * @return A reference to the date
 */
Date & operator-- (Date& rhs);

/**
 * Decrements the date and returns a copy in the previous state
 * @param lhs   The date to decrement
 * @return  A copy of it before the operation
 */
const Date operator-- (Date& lhs, int);

/**
 * Prints a date to an output stream (yyyy.mm.dd).
 * @param lhs Output stream
 * @param rhs Date
 * @return Reference to the output stream
 */
 ostream& operator<<(ostream& lhs, const Date& rhs) {
     operator<<(lhs,Month(rhs)) << "." << setfill('0') << setw(2) << rhs.get_day();
     return lhs;
 }

//====================================================================================================================//

class Period : public Date {
protected:
    int hour, minute, blocks;

    /**
     * Increments the starting hour by one block (30 minutes)
     */
    void increment() override;
    /**
     * Decrements the starting hour by one block (30 minutes)
     */
    void decrement() override;
    /**
     * Checks if self and the other Period object refer to the same period
     * @param p Period object to compare to
     * @return Whether they refer to the same period
     */
    virtual bool equal_to (const Period & p) const;
    /**
     * Checks if self refers to an earlier period than p
     * @param   p   Period object to compare to
     * @return If the starting hours of self are earlier, or, if they are equal, whether self is shorter
     */
    virtual bool less_than  (const Period & p) const;
    /**
     * Checks to see if the parameters for the period are valid, that being starting at [0-23]:[0|30] for [1-4] blocks.
     * If not, throws InvalidPeriod
     * @see InvalidPeriod
     * @param h Starting hour
     * @param min Starting minute
     * @param b Duration in blocks
     */
    static void valid_check(int h, int min, int b);

public:
    /**
     * Constructs the underlying Date object, checks the validity of the other parameters, and constructs the object
     * @param y Year
     * @param m Month
     * @param d Day
     * @param h Starting hour
     * @param min Starting minute
     * @param b Duration in blocks
     */
    Period(int y, int m, int d, int h, int min, int b);
    /**
     * Constructs the underlying Date object, checks the validity of the other parameters, and constructs the object
     * @param M Month object to copy
     * @param d Day
     * @param h Starting hour
     * @param min Starting minute
     * @param b Duration in blocks
     */
    Period(const Month & M, int d, int h, int min, int b);
    /**
     * Constructs the underlying Date object, checks the validity of the other parameters, and constructs the object
     * @param D Date object to copy
     * @param h Starting hour
     * @param min Starting minute
     * @param b Duration in blocks
     */
    Period(const Date & D, int h, int min, int b);

    /**
     * Returns string representing period in machine readable form
     * @return Parseable string
     */
    string get_export() const override;

    /**
     * Returns the starting hour
     * @return Starting hour
     */
    int get_hour() const { return hour; }
    /**
     * Returns the starting minute
     * @return Starting minute
     */
    int get_min() const { return minute; }
    /**
     * Returns the duration in blocks
     * @return The duration in blocks
     */
    int get_blocks() const { return blocks; }
    /**
     * Returns the duration in minutes
     * @return The duration in minutes
     */
    int get_duration() const { return blocks * 30; }
    /**
     * Gets a sub-period indicated by an index from 1 to the duration in blocks. Throws NonExistentSubPeriod if the index
     * is invalid.
     * @see NonExistentSubPeriod
     * @param i The index of the sub-period
     * @return Sub-period i
     */
    Period get_sub_period(int i) const;

    /**
     * Checks if the parameters are valid and changes the starting time
     * @param h New starting hour
     * @param min New starting minute
     */
    void set_time(int h, int min) { valid_check(h,min,blocks); hour = h; minute = min; }
    /**
     * Checks if the parameter is valid and changes the duration
     * @param b New duration in blocks
     */
    void set_blocks(int b) { valid_check(hour,minute,b); blocks = b; }

    friend Period & operator++ (Period& rhs);
    friend const Period operator++ (Period& lhs, int);
    friend Period & operator-- (Period& rhs);
    friend const Period operator-- (Period& lhs, int);

    /**
     * Checks if self and the other Period object refer to the same period
     * @param rhs Period object to compare to
     * @return Whether they refer to the same period
     */
    bool operator== (const Period & rhs) const { return equal_to(rhs); }
    /**
     * Checks if self refers to an earlier period than rhs
     * @param   rhs   Period object to compare to
     * @return If the starting hours of self are earlier, or, if they are equal, whether self is shorter
     */
    bool operator< (const Period & rhs) const { return less_than(rhs); }

    /**
     * Advances the starting time b number of blocks
     * @param b Number of blocks to advance the starting time by
     */
    void postpone(int b);
    /**
     * Recedes the starting time b number of blocks
     * @param b Number of blocks to recede the starting time by
     */
    void hasten(int b);
};

/**
 * Increments the period and returns a reference to it
 * @param rhs The period to increment
 * @return A reference to the period
 */
Period & operator++ (Period& rhs);

/**
 * Increments the period and returns a copy in the previous state
 * @param lhs   The period to increment
 * @return  A copy of it before the operation
 */
const Period operator++ (Period& lhs, int);

/**
 * Decrements the period and returns a reference to it
 * @param rhs The period to decrement
 * @return A reference to the period
 */
Period & operator-- (Period& rhs);

/**
 * Decrements the period and returns a copy in the previous state
 * @param lhs   The period to decrement
 * @return  A copy of it before the operation
 */
const Period operator-- (Period& lhs, int);

/**
 * Prints a Period to an output stream
 * @param lhs Output stream
 * @param rhs Period
 * @return Reference to the output stream
 */
 ostream& operator<<(ostream& lhs, const Period& rhs) {
     operator<<(lhs,Date(rhs)) << " " << setfill('0') << setw(2) << rhs.get_hour() << ":" << setfill('0') << setw(2)
        << rhs.get_min() << "-" << setfill('0') << setw(2) << (rhs.get_hour() + (rhs.get_min() + rhs.get_duration()) / 60)
        << ":" << setfill('0') << setw(2) << ( (rhs.get_min() + rhs.get_duration()) % 60 );
 }

//====================================================================================================================//

/**
 * Checks if two periods overlap
 * @param p1 Period to check
 * @param p2 Period to check
 * @return Whether there is any overlap between them
 */
bool check_overlap(const Period& p1, const Period& p2);

/*
Period generate_future_period(const Period& earlier_period, int blocks_to_adv);
 */

//====================================================================================================================//

class InvalidMonth {
    int month;
public:
    explicit InvalidMonth(int m): month(m) { }
    const char* what() const;
};

class InvalidDate {
    int year, month, day;
public:
    explicit InvalidDate(int y, int m, int d): month(m), day(d), year(y) { }
    const char* what() const;
};

class InvalidPeriod {
    int hour, minute, blocks;
public:
    explicit InvalidPeriod(int h, int min, int b): hour(h), minute(min), blocks(b) { }
    const char* what() const;
};

class NonExistentSubPeriod {
    int blocks, index;
public:
    explicit NonExistentSubPeriod(int b, int i): blocks(b), index(i) { }
    const char* what() const;
};

#endif //TIMING_H
