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
	string get_name() const { return id; }
	/**
	 * Returns the classes the Teacher has given or is due to give.
	 * @return A structure with pointers to the classes
	 */
	vector<Class*> get_classes() const { return classes; }

	/**
	 * Returns
	 * @param new_name
	 */
	void set_name(string new_name) { name = move(new_name); }
	void add_class(Class *class_);
	void rm_class(Class *class_);

	string get_schedule(Date from, Date to) const;
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
    vector<Use*> free_uses;
    size_t capacity;

public:
	Court();
	Court(vector<Class_Attendance*> usos); //CLARIFICAR

	size_t get_capacity() const { return capacity; }
	id_t get_id() const;
    size_t get_available_capacity(Period time) const;

	void add_class(Class *class_);
	void rm_class(Class *class_);

	void add_free_use(Use *use);
	void rm_free_use(Use *use);

	string list_classes(Date from, Date to) const;
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
    static id_t get_largest_id() { return largest_id; }

    id_t get_id() const { return id; }
    Period get_time() const { return time; }
    Teacher* get_teacher() const { return teacher; }
    Court* get_court() const { return court; }
    vector<Class_Attendance*> get_attendances() const { return attendances; }
    size_t get_num_attendants() const { return attendances.size(); }

    void set_time(Period new_time) { time = move(new_time); }
    void set_teacher(Teacher* new_teacher) { teacher = new_teacher; }
    void set_court(Court* new_court) { court = new_court; }

    void add_attendance(Class_Attendance* attendance);
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
    Use(User* user, Period time);

    static id_t get_largest_id() { return largest_id; }
    id_t get_id() const { return id; }
    User * get_user() const { return user; }
    Period get_time() const { return time; }
    virtual double get_cost() const;
    bool get_paid_status() const { return paid; }
    use_t get_type() const { return type; }


    void set_user(User *u);
    void set_time(Period *t);
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
