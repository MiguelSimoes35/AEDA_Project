#ifndef OBJETOS_H
#define OBJETOS_H

#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include "timing.h"
#include "comparators.h"
#include "exceptions.h"
#include <iomanip>
#include <iostream>

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
typedef unsigned int id_t;

#ifdef PT_PT
/**
 * @defgroup LOCALE_PT_PT
 * Locale defining European Portuguese string constants
 * @{
 */

#define DEFAULT_USER	" User " 				/**< @brief String for the construction of an unnamed user */
#define DEFAULT_TEACHER " Teacher "				/**< @brief String for the construction of an unnamed teacher */
#define DEFAULT_CLASS	" || Classes || " 		/**< @brief String for the header of Classes list */
#define DEFAULT_FREE	" || Free uses || " 	/**< @brief String for the header of Free uses list */

#define INFO_NAME		" Name: " 				/**< @brief String for the indicator of the name */
#define INFO_ID			" ID number: " 			/**< @brief String for the indicator of the ID number */
#define INFO_DEBT		" Pending debt: " 		/**< @brief String for the indicator of the pending debt fo a user */
#define INFO_CARD		" Gold card: " 			/**< @brief String for the indicator of the gold card status of a user */
#define INFO_GRADE		" Class grade: " 		/**< @brief String for the indicator of the class grade */
#define INFO_DATE		" Date: " 				/**< @brief String for the indicator of th date */

#define INFO_USER		" User: " 				/**< @brief String for the header of the user information display */
#define INFO_TEACHER	" Teacher: " 			/**< @brief String for the header of the teacher information display */
#define INFO_COURT		" Court: " 				/**< @brief String for the header of the court information display */

#define class_price		13.00 					/**< @brief Cost in euros of one class */
#define free_price		8.00 					/**< @brief Cost in euros, per block, of a free use */
#define card_fee		2.00 					/**< @brief Monthly fee in euros of a golden card holder */
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

	/**
	 * Set the largest_id global class variable
	 * @param new_l_id New largest id
	 */
	static void set_largest_id(id_t new_l_id) { largest_id = new_l_id; }
	/**
     * Exports attributes in machine readable form.
     * @return Parseable string describing attributes of the object
     */
	string export_attributes() const;
	/**
     * Exports use list in machine readable form
     * @return Parseable string describing uses the user has made
     */
	string export_uses() const;

	static string export_globals();
	static void set_globals(istream& globals);

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
	explicit User(string name, bool gold_card = false);

	explicit User(istream &attributes);

	/**
	 * Returns the largest ID currently attributed to any User object
	 *
	 * @return The largest ID currently attributed
	 */
	static id_t get_largest_id() { return largest_id; }

	/**
	 * @brief Decreases the largest_id by one.
	 *
	 */
	static void dec_largestID() { largest_id > 0 ? largest_id-- : largest_id==0; }

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
	void rm_use(Use *use);

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
	* Returns a formatted string containing the schedule of the user for framed time interval.
	* @param from Lower bound of the interval (inclusive)
	* @param to Higher bound of the interval (exclusive)
	* @return String with the formatted schedule
	*/
	string get_schedule(Date from, Date to) const;
	/**
	 * Marks all unpaid Uses in that month as paid
	 * @param month Month whose bill has been paid
	 */
	void pay_bill(Month month);

	/**
	 * Sets the debt to the sum of the cost of all unpaid uses and returns it.
	 */
	void update_debt();

	/**
	 * @brief Sets all uses of the player to payed.
	 *
	 */
	void pay_debt();

	/**
	 * @brief Returns a string, to be displayed in a machine friendly way, with
	 * the information about the user.
	 *
	 * @return string Information about the user to be displayed
	 */
	string get_info() const;

	bool  operator== (const User & u) const;
	bool  operator<  (const User & u) const;

	friend class Empresa;
};

//=================================================================================================================//

class Teacher {
private:
	static id_t largest_id;
	id_t id;
	string name;

	vector<Class*> classes;

	/**
     * Exports attributes in machine readable form.
     * @return Parseable string describing attributes of the object
     */
	string export_attributes() const;

	/**
     * Exports class list in machine readable form
     * @return Parseable string describing classes attributed to the teacher
     */
	string export_classes() const;

	static string export_globals();
	static void set_globals(istream& set_globals);

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
	explicit Teacher(string name);

	explicit Teacher(istream& attributes);

	/**
	 * @brief Returns a string, to be displayed in a machine friendly way, with
	 * the information about the teacher.
	 *
	 * @return string Information about the teacher to be displayed
	 */
	string get_info() const;

	/**
	 * Returns the unique ID of the teacher
	 * @return Teacher's ID
	 */
	id_t get_id() const { return id; }

	/**
	 * @brief Decreases the largest_id by one.
	 *
	 */
	static void dec_largestID() { largest_id > 0 ? largest_id-- : largest_id==0; }

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

	/**
     * Exports attributes in machine readable form.
     * @return Parseable string describing attributes of the object
     */
    string export_attributes() const;

	/**
     * Exports class list in machine readable form
     * @return Parseable string describing classes on that court
     */
    string export_classes() const;

	/**
     * Exports free use list in machine readable form
     * @return Parseable string describing free uses in the court
     */
    string export_free_uses() const;

    static string export_globals();
    static string set_globals(istream& globals);

public:
	/**
	 * Default constructor, generates unique ID and sets maximum capacity to 0
	 */
	Court();
	/**
	 * Standard constructor, generates unique ID and sets maximum capacity from parameter
	 * @param max_capacity Maximum number of users the court can have at once
	 */
	explicit Court(size_t max_capacity);

	explicit Court(istream& attributes);

	/**
	 * @brief Returns a string, to be displayed in a machine friendly way, with
	 * the information about the court.
	 *
	 * @return string Information about the court to be displayed
	 */
	string get_info() const;

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
	 * @return Available capacity (capacity - amount of users)
	 */
    size_t get_available_capacity(Period time) const;

	/**
	 * @brief Decreases the largest_id by one.
	 *
	 */
	static void dec_largestID() { largest_id > 0 ? largest_id-- : largest_id==0; }

	/**
	* @brief Checks if there are any classes or free uses happening in the cour in the
	* given time frame.
	*
	* @param time Time frame to be checked
	*
	* @return true 	 Someone is using the court during the given period
	* @return false  The court is free in the given period
	*/
	bool check_on_going(Period time) const;

	/**
	 * @brief Checks if there are any classes or free uses happening in the cour in the
	 * given day.
	 *
	 * @param time Time frame to be checked
	 *
	 * @return true   Someone is using the court on the given day
	 * @return false  The court is free in the given day
	 */
	bool check_on_day(Date time) const;

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
	void add_free_use(Free_Use *use);

	/**
	 * Removes a free use from the internal data structure
	 * @param use Pointer to the free use
	 */
	void rm_free_use(Free_Use *use);

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

	bool  operator== (const Court & p) const;
	bool  operator<  (const Court & p) const;

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

    /**
     * Exports attributes in machine readable form.
     * @return Parseable string describing attributes of the object
     */
    string export_attributes() const;
    /**
     * Exports attendance list in machine readable form
     * @return Parseable string describing attendances to the class object
     */
    string export_attendances() const;
    /**
     * Exports court and teacher ids in machine readable form
     * @return Parseable string describing external links on the class object
     */
    string export_externals() const;

    static string export_globals();
    static void set_globals(istream& globals);
public:
	Class(istream &attributes);

	/**
	 * @brief Construct a new Class with the given teacher, in the given court at
	 * the given time period.
	 *
	 * @param teacher 	Teacher who will teach the class
	 * @param periodo 	Time period which the class will take place
	 * @param court 	Court where the class will take place
	 */
	Class(Period time, Teacher* teacher, Court* court);

	/**
	 * @brief Returns a string, to be displayed in a machine friendly way, with
	 * the information about the class.
	 *
	 * @return string Information about the class to be displayed
	 */
	string get_info() const;
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
	 * @brief Decreases the largest_id by one.
	 *
	 */
	static void dec_largestID() { largest_id > 0 ? largest_id-- : largest_id==0; }

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

    friend class Empresa;
};

//=================================================================================================================//

enum use_t { ABSTRACT, CLASS, FREE};

class Use {
protected:
	static id_t largest_id;
	static double price_for_class, price_for_free_use;
	id_t id;
    use_t type;
	User *user;
	Period time;
	Court* court;
	bool paid;

	virtual string export_attributes() const;
	virtual string export_externals() const;
	static string export_globals();
	static void set_globals(istream& globals);
public:
	static use_t get_enum(const string &use);
    static string get_enum_string(use_t use);

    virtual ~Use() = 0;

	/**
	* @brief Sets the court used to the given court.
	*
	* @param new_court  New court that will now be used
	*/
    void set_court(Court* new_court) { court = new_court; }

	/**
	* @brief Returns a pointer to the court where the use will take place
	*
	* @return court Pointer to the court of the use
	*/
    Court* get_court() const { return court; }

	/**
	 * @brief Decreases the largest_id by one.
	 *
	 */
	static void dec_largestID() { largest_id > 0 ? largest_id-- : largest_id==0; }

	/**
	 * @brief Returns a string, to be displayed in a machine friendly way, with
	 * the information about the use.
	 *
	 * @return string Information about the use to be displayed
	 */
	virtual string get_info() const = 0;

	/**
	 * Constructs the object generating a new ID, and setting the user and time to the parameters
	 * @param user Pointer to the user
	 * @param time Pointer to the time in which the use takes place
	 */
    Use(User* user, Period time, Court* court);

    explicit Use(istream& attributes);

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
    virtual double get_cost() const = 0;

    /**
     * Returns whether the use has been paid
     * @return Whether the use has been paid
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
    void set_user(User *u) { user = u; }

    /**
     * Sets the time wherein the use takes place
     * @param t Period of time of use
     */
    void set_time(Period t) { time = t; }

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
	string export_attributes() const override;
	string export_externals() const override;
public:
	Class_Attendance(User *u, Class *c);
	explicit Class_Attendance(istream& attributes);

	Class * get_class() const { return class_; }
	double get_cost() const override { return user->get_gold_card() ? (class_price*0.85) : class_price;
	}
	grade_t get_grade() const { return grade; }

	/**
	 * @brief Sets the class of the Class Attendance to be the given class.
	 *
	 * @param new_class Class that was attendend
	 */
	void set_class(Class* new_class) { class_ = new_class; }

	/**
	 * @brief Set the grade of the user in that class to be the given grade.
	 *
	 * @param new_grade Grade of the class
	 */
	void set_grade(grade_t new_grade) { grade = new_grade; }

	/**
	 * @brief Returns a string, to be displayed in a machine friendly way, with
	 * the information about the class attendance.
	 *
	 * @return string Information about the class attendance to be displayed
	 */
	string get_info() const override;

	bool operator== (const Class_Attendance & rhs) const;

	friend class Empresa;
};

//====================================================================================================================//

class Free_Use: public Use {
private:
    string export_attributes() const override;
    string export_externals() const override;
public:
	explicit Free_Use(istream& attributes);

	/**
	 * @brief Returns a string, to be displayed in a machine friendly way, with
	 * the information about the free use.
	 *
	 * @return string Information about the free use to be displayed
	 */
	string get_info() const override;

	/**
	 * @brief Construct a free use by the given user, in the given court at the
	 * given time period.
	 *
	 * @param u  User that will use the court
	 * @param p  Time period when the free use will happen
	 * @param c  Court where the use will take place
	 */
    Free_Use(User* u, Period p, Court* c);

	/**
	 * @brief Calculates the cost of the free use.
	 *
	 * @return double Cost of the free use
	 */
    double get_cost() const override { return price_for_free_use * double(time.get_blocks()); }

};


#endif//OBJETOS_H
