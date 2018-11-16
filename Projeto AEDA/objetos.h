#ifndef OBJETOS_H
#define OBJETOS_H

#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include "timing.h"
#include "comparators.h"

using namespace std;

						//   ----------------------------------   //
						//   -------- Class Prototypes --------   //
						//   ----------------------------------   //

class User;
class Teacher;
class Court;
class Class;
class Use;
class Class_Attendance;
class Free_Use;


						//   -----------------------------------   //
						//   --------- Global Variables --------   //
						//   -----------------------------------   //

#define PT_PT /**< @brief Current locale */

#define DEFAULT_COMP Compare_ID

#ifdef PT_PT
/**
 * @defgroup LOCALE_PT_PT
 * Locale defining European Portuguese string constants
 * @{
 */

#define DEFAULT_USER "Utente " /**< @brief String for the construction of an unnamed user */
#define DEFAULT_TEACHER "Professor " /**< @brief String for the construction of an unnamed teacher */

/** @} */ //LOCALE_PT_PT
#endif //PT_PT


						//   -----------------------------------   //
						//   -------- Class Definitions --------   //
						//   -----------------------------------   //


//=================================================================================================================//
/**
 * @Class User
 * Stores the attributes of an user,
 */
class User {
private:
	static id_t largest_id;

	id_t id;
	double debt;
	string name;
	bool gold_card;
	vector<Use*> uses;

	static void set_largest_id(id_t new_l_id) { largest_id = new_l_id; }
	string export_attributes() const;

public:
    /**
     * Default constructor for the User. Generates unique ID, sets gold card status to false, sets name to a
     * locale-appropriate string plus the ID
     */
    User();
    /**
     * Standard constructor for an user. Takes the name and gold status (default is false), and generates unique ID
     * @param name  Name of the user
     * @param gold_card     Whether the user has a gold card (Default: false)
     */
	User(string name, bool gold_card = false);

	/**
	 * Returns the largest ID currently attributed to any User object
	 * @return The largest ID currently attributed
	 */
	static id_t get_largest_id() { return largest_id; }

	/**
	 * Returns ID of the User
	 * @return ID
	 */
	id_t get_id() const { return id; }
	/**
	 * Returns current registered debt from the User's part
	 * @return Current registered debt
	 */
	double get_debt() const { return debt; }
	/**
	 * Returns the user's name
	 * @return  Name of the user
	 */
	string get_name() const { return name; }
	/**
	 * Returns the gold card status of the user
	 * @return Whether the user has a gold card
	 */
	bool get_gold_card() const { return gold_card; }
	/**
	 * Returns the Uses the user has made
	 * @return A structure with the pointers to the Uses
	 */
	vector<Use*> get_uses() const { return uses; }

	/**
	 * Sets the name of the user
	 * @param new_name Name to set
	 */
	void set_name(const string & new_name) { name = new_name; }
	/**
	 * Sets the gold card status
	 * @param new_gold_card The desired status
	 */
	void set_gold_card(bool new_gold_card) { gold_card = new_gold_card; }

	/**
	 * Adds use to the internal data structure.
	 * @param use Pointer to the use to add
	 */
	void add_use(Use* use);
	/**
	 * Removes an use from the internal data structure.
	 * @param use Pointer to the use to remove
	 */
	void remove_use(Use* use);

	/**
	 * Returns a string formatting a report on the classes taken by the user that month.
	 * @param month Month from which to generate class report
	 * @return  String with the formatted report
	 */
    string get_report(Month month) const;
    /**
     * Returns a string formatting a bill describing the expenses due from that month.
     * @param month Month from which to generate bill
     * @return  String with the formatted bill
     */
	string get_bill(Month month) const;
	/**
	 * Marks all unpaid Uses in that month as paid
	 * @param month Month whose bill has been paid
	 */
	void pay_bill(Month month);

	/**
	 * Sets the debt to the sum of the costs of all unpaid uses and returns it.
	 */
	void update_debt();

	bool  operator== (const User & u) const;
	bool  operator<  (const User & u) const;

	friend class Empresa;
};

//=================================================================================================================//

class Teacher {
private:
	static id_t greatest_id;
	id_t id;
	string name;

	vector<Class*> classes;

public:
    /**
     * Default constructor for the Teacher class. Generates an unique ID and sets the name to the concatenation of a
     * locale appropriate string and the ID.
     */
	Teacher();
	/**
	 * Standard constructor for the Teacher class. Sets the name to the one given in the paraneters and generates unique
	 * ID
	 * @param name Name of the teacher
	 */
	Teacher(string name);

	/**
	 * Returns the unique ID of the teacher
	 * @return Teacher's ID
	 */
	id_t get_id() const { return id; }
	/**
	 * Returns the name of the teacher
	 * @return  Teacher's name
	 */
	string get_name() const { return name; }
	/**
	 * Returns the classes the Teacher has given or is due to give.
	 * @return A structure with pointers to the classes
	 */
	vector<Class*> get_classes() const { return classes; }

	/**
	 * Changes the name of the teacher
	 * @param new_name	New name of the teacher
	 */
	void set_name(string new_name) { name = move(new_name); }
	/**
	 * Adds a Class object to the internal data structure
	 * @param class_ Pointer to the Class object to add
	 */
	void add_class(Class *class_);
	/**
	 * Removes a Class object from the internal data structure
	 * @param class_ Pointer to the class object to remove
	 */
	void rm_class(Class *class_);

	/**
	 * Returns a formatted string containing the schedule of the teacher for framed time interval.
	 * @param from Lower bound of the interval (inclusive)
	 * @param to Higher bound of the interval (exclusive)
	 * @return String with the formatted schedule
	 */
	string get_schedule(Date from, Date to) const;
	/**
	 * Returns the number of classes the teacher is due to give within the framed time interval.
	 * @param from Lower bound of the interval (inclusive)
	 * @param to Higher bound of the interval (exclusive)
	 * @return Number of classes scheduled for the teacher
	 */
	size_t get_num_classes(Date from, Date to) const;

	bool  operator== (const Teacher & p) const;
	bool  operator<  (const Teacher & p) const;

	friend class Empresa;
};

//=================================================================================================================//

class Court {
private:
	static id_t largest_id;
	id_t id;
    vector<Class*> classes;
    vector<Free_Use*> free_uses;
    size_t capacity;

public:
	/**
	 * Default constructor, generates unique ID and sets maximum capacity to 0
	 */
	Court();
	/**
	 * Standard constructor, generates unique ID and sets maximum capacity from parameter
	 * @param max_capacity Maximum number of users the court can have at once
	 */
	Court(size_t max_capacity);
	Court(vector<Class_Attendance*> usos); //TODO: CLARIFICAR

	/**
	 * Returns largest unique ID currently attributed
	 * @return Largest unique ID currently attributed
	 */
	 static id_t get_largest_id() { return largest_id; }
	/**
	 * Returns maximum capacity of the court
	 * @return Maximum capacity of the court
	 */
	size_t get_capacity() const { return capacity; }
	/**
	 * Returns the unique ID of the object
	 * @return Unique ID of the object
	 */
	id_t get_id() const { return id; }
	/**
	 * Returns the minimum available capacity during the time period in the parameters
	 * @param time Period to check
	 * @return Minimum available capacity (capacity - max. ammount of users)
	 */
    size_t get_available_capacity(Period time) const;

    /**
     * Adds a class to the internal data structure
     * @param class_ Pointer to the Class object
     */
	void add_class(Class *class_);
	/**
	 * Removes a class from the internal data structure
	 * @param class_ Pointer to the Class object
	 */
	void rm_class(Class *class_);

	/**
	 * Adds a free use to the internal data structure
	 * @param use Pointer to the free use
	 */
	void add_free_use(Use *use);
	/**
	 * Removes a free use from the internal data structure
	 * @param use Pointer to the free use
	 */
	void rm_free_use(Use *use);

	/**
	 * Returns a formatted string with the classes to be given in that court in the time frame set in the parameters
	 * @param from	Lower bound of the interval (inclusive)
	 * @param to	Higher bound of the interval (exclusive)
	 * @return	String with the formatted list of classes
	 */
	string list_classes(Date from, Date to) const;
	/**
	 * Returns a formatted string with the free uses planned for that court in the time frame set in the parameters
	 * @param from	Lower bound of the interval (inclusive)
	 * @param to	Higher bound of the interval (exclusive)
	 * @return	String with the formatted list of free uses
	 */
	string list_free_uses(Date from, Date to) const;

	friend class Empresa;
};

//=================================================================================================================//

class Class {
private:
    static id_t largest_id;

    id_t id;
    Period time;
    Court* court;
    Teacher* teacher;
    vector<Class_Attendance*> attendances;
public:
	/**
	 * Returns largest ID currently attributed
	 * @return Largest ID currently attributed
	 */
    static id_t get_largest_id() { return largest_id; }

    /**
     * Returns the object's ID
     * @return The object's ID
     */
    id_t get_id() const { return id; }
    /**
     * Returns the time of the class
     * @return When the class is scheduled
     */
    Period get_time() const { return time; }
    /**
     * Returns the teacher assigned to the class
     * @return Pointer to the teacher
     */
    Teacher* get_teacher() const { return teacher; }
    /**
     * Returns the court where the class will be given
     * @return Pointer to the court
     */
    Court* get_court() const { return court; }
    /**
     * Returns a vector with all the attendances to that class
     * @return Vector with all the attendances to the class
     */
    vector<Class_Attendance*> get_attendances() const { return attendances; }
    /**
     * Returns the number of users expected to attend the class
     * @return Number of registered attendances
     */
    size_t get_num_attendants() const { return attendances.size(); }

    /**
     * Sets the time the class is scheduled to
     * @param new_time The new time to schedule the class
     */
    void set_time(Period new_time) { time = move(new_time); }
    /**
     * Sets the teacher of the class
     * @param new_teacher	Pointer to the teacher
     */
    void set_teacher(Teacher* new_teacher) { teacher = new_teacher; }
    /**
     * Sets the court where the class will take place
     * @param new_court Pointer to the court
     */
    void set_court(Court* new_court) { court = new_court; }

    /**
     * Adds an attendance to the internal data structure
     * @param attendance Pointer to the attendance to add
     */
    void add_attendance(Class_Attendance* attendance);
    /**
     * Removes an attendance from the internal data structure
     * @param attendance Pointer to the attendance to remove
     */
    void rm_attendance(Class_Attendance* attendance);

};

//=================================================================================================================//

enum use_t { ABSTRACT, CLASS, FREE };

class Use {
protected:
	static id_t largest_id;
	static double price_for_class, price_for_free_use;
	id_t id;
    use_t type;
	User *user;
	Period time;
	bool paid;
public:
	/**
	 * Constructs the object generating a new ID, and setting the user and time to the parameters
	 * @param user Pointer to the user
	 * @param time Pointer to the time in which the use takes place
	 */
    Use(User* user, Period time);

    /**
     * Returns largest ID currently attributed
     * @return Largest ID currently attributed
     */
    static id_t get_largest_id() { return largest_id; }
    /**
     * Returns object's ID
     * @return Object's ID
     */
    id_t get_id() const { return id; }
    /**
     * Returns the User making the use
     * @return Pointer to the User
     */
    User * get_user() const { return user; }
    /**
     * Returns the time the use takes place in
     * @return Time of use
     */
    Period get_time() const { return time; }
    /**
     * Returns the cost of the use
     * @return Cost, in euros
     */
    virtual double get_cost() const;
    /**
     * Returns whether the use has been paid
     * @return
     */
    bool get_paid_status() const { return paid; }
    /**
     * Gets the type of use
     * @return whether the use is an abstract use (ABSTRACT), a class attendance (CLASS), or a free use (FREE)
     */
    use_t get_type() const { return type; }

	/**
	 * Sets the user
	 * @param u Pointer to the user
	 */
    void set_user(User *u);
    /**
     * Sets the time wherein the use takes place
     * @param t Period of time of use
     */
    void set_time(Period t);
    /**
     * Sets the paid status of the object
     * @param p Whether the use has been paid for
     */
    void set_paid(bool p) { paid = p; }


    virtual bool operator== (const Use & rhs) const;

    friend class Empresa;
};

//=================================================================================================================//
typedef int grade_t;

class Class_Attendance: public Use {
private:
	Class* class_;
    grade_t grade;

public:
	Class_Attendance(User *u, Period p, Class *c);

	Class * get_class() const { return class_; }
	double get_cost() const override { return price_for_class }
	grade_t get_grade() const { return grade; }

	void set_class(Class* new_class) { class_ = new_class; }
	void set_grade(grade_t new_grade) { grade = new_grade; }

	bool operator== (const Class_Attendance & rhs) const;

	friend class Empresa;
};

//====================================================================================================================//

class Free_Use: public Use {
private:
    Court* court;
public:
    Free_Use(User* u, Period p, Court* court);

    Court* get_court() const { return court; }
    double get_cost() const override { return price_for_free_use * double(time.get_blocks()); }

    void set_court() const;
};


#endif//OBJETOS_H
