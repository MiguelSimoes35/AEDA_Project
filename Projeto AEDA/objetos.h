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

#define PRICE_FOR_FREE_USE 3 /**<  @brief Cost of a 30 minute block of free use, in euros */
#define PRICE_FOR_CLASS 15.0 /**< @brief Cost of a class, in euros */
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

class User {
private:
	static id_t largest_id;

	id_t id;
	int debt;
	string name;
	bool gold_card;
	vector<Use*> uses;


public:
    User();
	User(string name, bool gold_card = false);

	static id_t get_largest_id() { return largest_id; }

	id_t get_id() const { return id; }
	int get_debt() const { return debt; }
	string get_name() const { return name; }
	bool get_gold_card() const { return gold_card; }
	vector<Use*> get_uses() const { return uses; }

	void set_name(const string & new_name) { name = new_name; }
	void set_gold_card(bool new_gold_card) { gold_card = new_gold_card; }
	void set_debt(int new_debt) { debt = new_debt; }

	void add_use(Use* use);
	void remove_use(Use* use);

	void print_report(Month month) const;
	void print_bill(Month month) const;
	void pay_bill(Month month);

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
	Teacher();
	Teacher(string name);

	id_t get_id() const;
	string get_name() const;
	vector<Class*> get_classes() const { return classes; }

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

enum use_type { ABSTRACT, CLASS, FREE };

class Use {
protected:
	static id_t largest_id;

	id_t id;
    use_type type;
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
    use_type get_type() const { return type; }


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
	double get_cost() const override { return PRICE_FOR_CLASS; }
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
    double get_cost() const override { return PRICE_FOR_FREE_USE * double(time.get_blocks()); }

    void set_court() const;
};


#endif//OBJETOS_H
