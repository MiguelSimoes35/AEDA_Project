#ifndef OBJETOS_H
#define OBJETOS_H

#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <utility>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include "timing.h"
#include "comparators.h"
#include "exceptions.h"

using namespace std;


//   ----------------------------------   //
//   -------- Class Prototypes --------   //
//   ----------------------------------   //

typedef unsigned int id_t;

class User;
class Teacher;
class TeacherPtr;
class Court;
class Class;
class Use;
class Class_Attendance;
class Free_Use;
class Technician;


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

#define DEFAULT_USER	" User " 				/**< @brief String for the construction of an unnamed user */
#define DEFAULT_TEACHER " Teacher "				/**< @brief String for the construction of an unnamed teacher */
#define DEFAULT_CLASS	" || Classes || " 		/**< @brief String for the header of Classes list */
#define DEFAULT_FREE	" || Free uses || " 	/**< @brief String for the header of Free uses list */

#define INFO_NAME		" Name: " 				/**< @brief String for the indicator of the name */
#define INFO_ID			" ID number: " 			/**< @brief String for the indicator of the ID number */
#define INFO_DEBT		" Pending debt: " 		/**< @brief String for the indicator of the pending debt fo a user */
#define INFO_CARD		" Gold card: " 			/**< @brief String for the indicator of the gold card status of a user */
#define INFO_NIF		" NIF: "				/**< @brief String for the indicator of the user's NIF */
#define INFO_ADDESS		" Address: "			/**< @brief String for the indicator of the user's address */
#define INFO_GRADE		" Class grade: " 		/**< @brief String for the indicator of the class grade */
#define INFO_DATE		" Date: " 				/**< @brief String for the indicator of th date */
#define INFO_AVL		" Availability: " 		/**< @brief String for the indicator of th date */
#define INFO_REPAIR		" Number of repairs: " 	/**< @brief String for the indicator of th date */


#define INFO_USER		" User: " 				/**< @brief String for the header of the user information display */
#define INFO_TEACHER	" Teacher: " 			/**< @brief String for the header of the teacher information display */
#define INFO_COURT		" Court: " 				/**< @brief String for the header of the court information display */
#define INFO_TECHNICIAN " Technician: " 		/**< @brief String for the header of the user information display */


#define CLASS_PRICE		13.00 					/**< @brief Cost in euros of one class */
#define FREE_PRICE		8.00 					/**< @brief Cost in euros, per block, of a free use */
#define CARD_FEE		2.00 					/**< @brief Monthly fee in euros of a golden card holder */
 /** @} */ //LOCALE_PT_PT
#endif //PT_PT


						//   -----------------------------------   //
						//   -------- Class Definitions --------   //
						//   -----------------------------------   //



//====================================================== USER ==============================================================//


/**
 * @Class User
 * Stores the attributes of an user,
 */
class User {
private:
	static id_t largest_id;

	id_t id;
	string name;
	string address;
	unsigned NIF;
	bool gold_card;
	double debt;
	vector<Use*> uses;

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

	/**
	 * @brief Sets the largest id to the given one.
	 * 
	 * @param largest 	New largest id
	 */
	static void set_largest_id(id_t largest) { largest_id = largest; }

public:

	/**
	 * Default constructor for the User. Generates unique ID, sets gold card status to false, sets name to a
	 * locale-appropriate string plus the ID
	 */
	//User();

	/**
	 * Standard constructor for an user. Takes the name and gold status (default is false), and generates unique ID
	 * @param name  		Name of the user
	 * @param gold_card     Whether the user has a gold card (Default: false)
	 */
	explicit User(string name, string address, unsigned NIF, bool gold_card = false);

	/**
	 * @brief Construct a new User object with the given name. Used only for
	 * dummie user, not meant for actual user objects.
	 * 
	 * @param name 			Name of the user
	 */
	explicit User(string name);

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
	static void dec_largestID() { largest_id > 0 ? largest_id-- : largest_id == 0; }

	/**
	 * @brief Returns ID of the User
	 *
	 * @return ID
	 */
	id_t get_id() const { return id; }

	/**
	 * @brief Returns current registered debt from the user's.
	 *
	 * @return Current registered debt
	 */
	double get_debt() const { return debt; }

	/**
	 * @brief Returns the name of the user.
	 * 
	 * @return string 	User's name
	 */
	string get_name() const { return name; }

	/**
	 * @brief Returns the address of the user
	 * 
	 * @return string 	User's address
	 */
	string get_address() const { return address; }

	/**
	 * @brief Returns the NIF os the user
	 * 	
	 * @return unsigned  User's NIF
	 */
	unsigned get_NIF() const { return NIF; }

	/**
	 * Returns the gold card status of the user
	 * @return Whether the user has a gold card
	 */
	bool get_gold_card() const { return gold_card; }

	/**
	 * @brief Returns a vector with pointers to all of the user's
	 * uses.
	 * 
	 * @return vector<Use*> All the user's uses
	 */
	vector<Use*> get_uses() const { return uses; }

	/**
	 * @brief Returns the number of uses (class atendances and free uses)
	 * the user has had.
	 * 
	 * @return unsigned	 	Number of uses 
	 */
	unsigned get_frequency() const { return uses.size(); }

	/**
	 * @brief Sets the user's name to the given string.
	 * 
	 * @param new_name 	 	New user's name
	 */
	void set_name(const string & new_name) { name = new_name; }

	/**
	 * @brief Sets the user's address to the given string.
	 * 
	 * @param new_address 	New user's address
	 */
	void set_address(const string & new_address) { address = new_address; }

	/**
	 * @brief Sets the gold card status to the given boolean.
	 * 
	 * @param new_gold_card New gold card status
	 */
	void set_gold_card(bool new_gold_card) { gold_card = new_gold_card; }

	/**
	 * @brief Adds the given use to the user's uses vector unless it already
	 * exists, in this case it throws an exception of tYpe RepeatedObject
	 * 
	 * @param use 	Use to be added
	 */
	void add_use(Use* use);

	/**
	 * @brief Removes the given use from the internal data structure. If it
	 * doesn't exist it throws a InexistentObject exception.
	 *
	 * @param use 	Pointer to the use to be removed
	 */
	void rm_use(Use *use);

	/**
	 * @brief Returns a string formatting a report on the classes taken by the user
	 * that month.
	 *
	 * @param month 	Month from which to generate class report
	 * @return  		String with the formatted report
	 */
	string get_report(Month month) const;

	/**
	 * @brief Returns a string formatting a bill describing the expenses due from that
	 * month.
	 *
	 * @param month 	Month from which to generate bill
	 * @return  		String with the formatted bill
	 */
	string get_bill(Month month) const;

	/**
	* @brief Returns a formatted string containing the schedule of the user for framed
	* time interval.
	*
	* @param from 		Lower bound of the interval (inclusive)
	* @param to 		Higher bound of the interval (exclusive)
	* @return 			String with the formatted schedule
	*/
	string get_schedule(Date from, Date to) const;

	/**
	 * @brief Marks all unpaid Uses in that month as paid
	 *
	 * @param month 	Month whose bill has been paid
	 */
	void pay_bill(Month month);

	/**
	 * @brief Sets the debt to the sum of the cost of all unpaid uses.
	 */
	void update_debt();

	/**
	 * @brief Sets all uses of the player to payed.
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
	friend class UserPtr;
};

/**
 * @brief Stores a user pointer. This classed is used to store User information in a set
 * but also allowing information to be changed. It then encapsulates the class user for
 * set data structure.
 * 
 */
class UserPtr {
	User* user;

public:

	/**
	 * @brief Construct a new User Ptr object from a given user pointer.
	 * 
	 * @param user 		Pointer to user that will be encapsulated
	 */
	UserPtr(User* user);

	/**
	 * @brief Return a pointer to the user that is incapsulated.
	 * 
	 * @return User* 	Pointer to the associated user
	 */
	User* get_ptr() const { return user; };

	/**
	 * @brief Returns the name of the associated user.
	 * 
	 * @return string 	Name of the associated user
	 */
	string get_name() const;

	/**
	 * @brief Returns the id of the associated user.
	 * 
	 * @return id_t 	Id of the associated user
	 */
	id_t get_id() const;

	/**
	 * @brief Returns the frequency of the associated user.
	 * 
	 * @return unsigned Frequency of the associated user
	 */
	unsigned get_frequency() const;

	/**
	 * @brief Returns the address of the associated user.
	 * 
	 * @return string 	Address of the associated user
	 */
	string get_address() const;

	/**
	 * @brief returns the NIF of the associated user.
	 * 
	 * @return unsigned NIF of the associated user
	 */
	unsigned get_NIF() const;
};

//==================================================== TEACHER ============================================================//

class Teacher {
private:
	id_t id;
	string name;
	bool active;
	vector<Class*> classes;

	/**
	 * @brief Exports attributes in machine readable form.
	 *
	 * @return Parseable string describing attributes of the object
	 */
	string export_attributes() const;

	/**
	 * @brief Exports class list in machine readable form.
	 *
	 * @return Parseable string describing classes attributed to the teacher
	 */
	string export_classes() const;

	/**
	 * @brief Calculated a unique ID based on the teachers name. Ranges from 1 to 9887.
	 * 
	 * @param name 		Teacher's name
	 * @return id_t 	resulting id, based on the given name
	 */
	id_t calculate_id(string name) const;

public:

	/**
	 * @brief Standard constructor for the Teacher class. Sets the name to the one given
	 * in the paraneters and generates unique ID.
	 *
	 * @param name		 Name of the teacher
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
	 * @brief Returns the unique ID of the teacher.
	 *
	 * @return 			Teacher's id
	 */
	id_t get_id() const { return id; };

	/**
	 * @brief Returns the id of a teacher with that name using the function calculate_id.
	 * 
	 * @param name 		Teachers name
	 * @return id_t 	Resulting teachers id
	 */
	id_t get_id(string name) const;

	/**
	 * @brief Returns the name of the teacher.
	 *
	 * @return  	Teacher's name
	 */
	string get_name() const { return name; }

	/**
	 * Returns whether the teacher is employed at the moment
	 *
	 * @return true if employed, false otherwise
	 */
	bool get_status() const { return active; }

	/**
	 * @brief Returns the classes the Teacher has given or is due to give.
	 *
	 * @return 		A structure with pointers to the classes
	 */
	vector<Class*> get_classes() const { return classes; }

	/**
	 * @brief Changes the name of the teacher to the given name.
	 *
	 * @param new_name		New name of the teacher
	 */
	void set_name(string new_name) { name = move(new_name); }

	/**
	 * @brief Changes the current state of the professor, i.e if he is active or not
	 *
	 * @param state  		New teacher state ( 0 = inactive ; 1 = active )
	 */
	void change_status(bool state) { active = state; }

	/**
	 * @brief Adds a Class object to the internal data structure fo the teacher
	 *
	 * @param class_ 		Pointer to the Class object to add
	 */
	void add_class(Class *class_);

	/**
	 * @brief Removes the Class object from the internal data structure. If it
	 * doesn't exist then it throws a InexistingObject exception.
	 *
	 * @param class_ 		Pointer to the class object to remove
	 */
	void rm_class(Class *class_);

	/**
	 * @brief Returns a formatted string containing the schedule of the teacher for the
	 * given time interval.
	 *
	 * @param from 			Lower bound of the interval (inclusive)
	 * @param to 			Higher bound of the interval (exclusive)
	 * @return 				String with the formatted schedule
	 */
	string get_schedule(Date from, Date to) const;

	/**
	 * @brief Returns the number of classes the teacher is due to give within the framed
	 * time interval.
	 *
	 * @param from Lower bound of the interval (inclusive)
	 * @param to Higher bound of the interval (exclusive)
	 * @return Number of classes scheduled for the teacher
	 */
	size_t get_num_classes(Date from, Date to) const;

	bool  operator== (const Teacher & p) const;

	bool  operator<  (const Teacher & p) const;

	friend class Empresa;
	friend class TeacherPtr;
};

/**
 * @brief Stores a teacher pointer. This classed is used to store Teacher information in
 * a unordered set but allowing information to be changed. It then encapsulates the class
 * teacher for the unordered set data structure.
 * 
 */
class TeacherPtr {
	Teacher* teacher;

public:

	/**
	 * @brief Construct a new Teacher Ptr object with the given pointer to a teacher.
	 * 
	 * @param teacher 	Pointer to the teacher to be encapsulated
	 */
	TeacherPtr(Teacher* teacher);

	/**
	 * @brief Returns a pointer to the associated teacher.
	 * 
	 * @return Teacher* Pointer to the associated teacher
	 */
	Teacher* get_ptr() const { return teacher; };

	/**
	 * @brief Returns the name of the associated teacher.
	 * 
	 * @return string 	Name of the associated teacher.
	 */
	string get_name() const;

	/**
	 * @brief Return the id of the associated teacher.
	 * 
	 * @return id_t 	Id of the associated teacher
	 */
	id_t get_id() const;
};

//===================================================== COURT =============================================================//

class Court {
private:
	static id_t largest_id;
	id_t id;
	vector<Class*> classes;
	vector<Free_Use*> free_uses;
	size_t capacity;

	/**
	 * @brief Exports attributes in machine readable form.
	 *
	 * @return Parseable string describing attributes of the object
	 */
	string export_attributes() const;

	/**
	 * @brief Exports class list in machine readable form.
	 *
	 * @return Parseable string describing classes on that court
	 */
	string export_classes() const;

	/**
	 * @brief Exports free use list in machine readable form.
	 *
	 * @return Parseable string describing free uses in the court
	 */
	string export_free_uses() const;

	static string export_globals();

	static void set_globals(istream& globals);

	/**
	 * @brief Set the largest id to be the given one. 
	 * 
	 * @param largest 		New largest id
	 */
	static void set_largest_id(id_t largest) { largest_id = largest; }

public:
	/**
	 * @brief Default constructor, generates unique ID and sets maximum capacity to 0
	 */
	Court();

	/**
	 * @brief Standard constructor, generates unique ID and sets maximum capacity from
	 * parameter.
	 *
	 * @param max_capacity Maximum number of users the court can have at once
	 */
	explicit Court(size_t max_capacity);

	explicit Court(istream& attributes);

	/**
	 * @brief Returns a string, to be displayed in a machine friendly way, with
	 * the information about the court.
	 *
	 * @return string 	Information about the court to be displayed
	 */
	string get_info() const;

	/**
	 * @brief Returns largest unique ID currently attributed.
	 *
	 * @return 			Largest unique ID currently attributed
	 */
	static id_t get_largest_id() { return largest_id; }

	/**
	 * @brief Returns maximum capacity of the court.
	 *
	 * @return 			Maximum capacity of the court
	 */
	size_t get_capacity() const { return capacity; }

	/**
	 * @brief Returns the unique ID of the object.
	 *
	 * @return 			Unique ID of the object
	 */
	id_t get_id() const { return id; }

	/**
	 * @brief Returns the minimum available capacity during the time period in the
	 * parameters
	 *
	 * @param time 		Period to check
	 * @return 			Available capacity (capacity - amount of users)
	 */
	size_t get_available_capacity(Period time) const;

	void change_capacity(size_t new_capacity) { this->capacity = new_capacity; }

	/**
	 * @brief Decreases the largest_id by one.
	 *
	 */
	static void dec_largestID() { largest_id > 0 ? largest_id-- : largest_id == 0; }

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
	 * @brief Adds a class to the internal data structure.
	 *
	 * @param class_ Pointer to the Class object
	 */
	void add_class(Class *class_);

	/**
	 * @brief Removes a class from the internal data structure.
	 *
	 * @param class_ Pointer to the Class object
	 */
	void rm_class(Class *class_);

	/**
	 * @brief Adds a free use to the internal data structure.
	 *
	 * @param use Pointer to the free use
	 */
	void add_free_use(Free_Use *use);

	/**
	 * @brief Removes a free use from the internal data structure.
	 *
	 * @param use Pointer to the free use
	 */
	void rm_free_use(Free_Use *use);

	/**
	 * @brief Returns a formatted string with the classes to be given in that court
	 * in the time frame set in the parameters.
	 *
	 * @param from	Lower bound of the interval (inclusive)
	 * @param to	Higher bound of the interval (exclusive)
	 *
	 * @return	String with the formatted list of classes
	 */
	string list_classes(Date from, Date to) const;

	/**
	 * @brief Returns a formatted string with the free uses planned for that court in
	 * the time frame set in the parameters.
	 *
	 * @param from	Lower bound of the interval (inclusive)
	 * @param to	Higher bound of the interval (exclusive)
	 * @return	String with the formatted list of free uses
	 */
	string list_free_uses(Date from, Date to) const;

	bool  operator== (const Court & p) const;

	bool  operator<  (const Court & p) const;

	friend class Empresa;
};

//==================================================== CLASSES ============================================================//

class Class {
private:
	static id_t largest_id;

	id_t id;
	Period time;
	Court* court;
	Teacher* teacher;
	vector<Class_Attendance*> attendances;

	/**
	 * @brief Exports attributes in machine readable form.
	 *
	 * @return Parseable string describing attributes of the object
	 */
	string export_attributes() const;
	/**
	 * @brief Exports attendance list in machine readable form.
	 *
	 * @return Parseable string describing attendances to the class object
	 */
	string export_attendances() const;
	/**
	 * @brief Exports court and teacher ids in machine readable form.
	 *
	 * @return Parseable string describing external links on the class object
	 */
	string export_externals() const;

	static string export_globals();

	static void set_globals(istream& globals);

	/**
	 * @brief Sets the largest id to the given one. 
	 * 
	 * @param largest 	New largest id
	 */
	static void set_largest_id(id_t largest) { largest_id = largest; }
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
	 * @brief Returns largest ID currently attributed.
	 *
	 * @return Largest ID currently attributed
	 */
	static id_t get_largest_id() { return largest_id; }

	/**
	 * @brief Returns the object's ID.
	 *
	 * @return The object's ID
	 */
	id_t get_id() const { return id; }

	/**
	 * @brief Decreases the largest_id by one.
	 *
	 */
	static void dec_largestID() { largest_id > 0 ? largest_id-- : largest_id == 0; }

	/**
	 * @brief Returns the time of the class.
	 *
	 * @return When the class is scheduled
	 */
	Period get_time() const { return time; }

	/**
	 * @brief Returns the teacher assigned to the class.
	 *
	 * @return Pointer to the teacher
	 */
	Teacher* get_teacher() const { return teacher; }

	/**
	 * @brief Returns the court where the class will be given.
	 *
	 * @return Pointer to the court
	 */
	Court* get_court() const { return court; }

	/**
	 * @brief Returns a vector with all the attendances to that class.
	 *
	 * @return Vector with all the attendances to the class
	 */
	vector<Class_Attendance*> get_attendances() const { return attendances; }

	/**
	 * @brief Returns the number of users expected to attend the class.
	 *
	 * @return Number of registered attendances
	 */
	size_t get_num_attendants() const { return attendances.size(); }

	/**
	 * @brief Sets the time the class is scheduled to the given one.
	 *
	 * @param new_time The new time to schedule the class
	 */
	void set_time(Period new_time) { time = move(new_time); }

	/**
	 * @brief Sets the teacher of the class to the given one.
	 *
	 * @param new_teacher	Pointer to the teacher
	 */
	void set_teacher(Teacher* new_teacher) { teacher = new_teacher; }

	/**
	 * @brief Sets the court where the class will take place to the given one.
	 *
	 * @param new_court Pointer to the court
	 */
	void set_court(Court* new_court) { court = new_court; }

	/**
	 * @brief Adds an attendance to the internal data structure.
	 *
	 * @param attendance Pointer to the attendance to add
	 */
	void add_attendance(Class_Attendance* attendance);

	/**
	 * @brief Removes an attendance from the internal data structure.
	 *
	 * @param attendance Pointer to the attendance to remove
	 */
	void rm_attendance(Class_Attendance* attendance);

	friend class Empresa;
};

//===================================================== USE =============================================================//

enum use_t { ABSTRACT, CLASS, FREE };

class Use {
protected:
	static id_t largest_id;
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

	/**
	 * @brief Sets the largest id to be the given one. 
	 * 
	 * @param largest 		New largest id
	 */
	static void set_largest_id(id_t largest) { largest_id = largest; }

public:

	static use_t get_enum(const string &use);

	static string get_enum_string(use_t use);

	/**
	* @brief Sets the court used to the given court.
	*
	* @param new_court  New court that will now be used
	*/
	void set_court(Court* new_court) { court = new_court; }

	/**
	* @brief Returns a pointer to the court where the use will take place.
	*
	* @return court Pointer to the court of the use
	*/
	Court* get_court() const { return court; }

	/**
	 * @brief Decreases the largest_id by one.
	 *
	 */
	static void dec_largestID() { largest_id > 0 ? largest_id-- : largest_id == 0; }

	/**
	 * @brief Returns a string, to be displayed in a machine friendly way, with
	 * the information about the use.
	 *
	 * @return string 	Information about the use to be displayed
	 */
	virtual string get_info() const = 0;

	/**
	 * @brief Constructs the object generating a new ID, and setting the user and time 
	 * to the parameters.
	 *
	 * @param user 		Pointer to the user
	 * @param time 		Pointer to the time in which the use takes place
	 */
	Use(User* user, Period time, Court* court);

	explicit Use(istream& attributes);

	/**
	 * @brief Returns largest ID currently attributed.
	 * @return 			Largest ID currently attributed
	 */
	static id_t get_largest_id() { return largest_id; }

	/**
	 * @brief Returns object's ID.
	 * @return 			Object's ID
	 */
	id_t get_id() const { return id; }

	/**
	 * @brief Returns the User for the schedule use.
	 *
	 * @return 			Pointer to the User
	 */
	User * get_user() const { return user; }

	/**
	 * @brief Returns the time the use will occur.
	 *
	 * @return 			Time of use
	 */
	Period get_time() const { return time; }

	/**
	 * @brief Returns the cost of the use.
	 *
	 * @return 			Cost, in euros
	 */
	virtual double get_cost() const = 0;

	/**
	 * @brief Returns whether the use has been paid.
	 *
	 * @return true 	The use has been payed.
	 * @return flase 	The use is not yet payed
	 */
	bool get_paid_status() const { return paid; }

	/**
	 * @brief Returns the type of use.
	 *
	 * @return whether the use is an abstract use (ABSTRACT), a class attendance (CLASS), or a free use (FREE)
	 */
	use_t get_type() const { return type; }

	/**
	 * @brief Sets the user to be the given one.
	 *
	 * @param u 		Pointer to the user
	 */
	void set_user(User *u) { user = u; }

	/**
	 * @brief Sets the time where the use will occur to the given period.
	 *
	 * @param t 		Period of time of use
	 */
	void set_time(Period t) { time = t; }

	/**
	 * @brief Sets the paid status of the object.
	 *
	 * @param p 		Whether the use has been paid or not
	 */
	void set_paid(bool p) { paid = p; }

	virtual bool operator== (const Use & rhs) const;

	friend class Empresa;
};

//=================================================================================================================//

typedef int grade_t;

class Class_Attendance : public Use {
private:
	Class* class_;
	grade_t grade;

	string export_attributes() const override;

	string export_externals() const override;

public:

	Class_Attendance(User *u, Class *c);

	explicit Class_Attendance(istream& attributes);

	Class * get_class() const { return class_; }

	double get_cost() const override {
		return user->get_gold_card() ? (CLASS_PRICE*0.85) : CLASS_PRICE;
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

class Free_Use : public Use {
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
	double get_cost() const override { return FREE_PRICE * double(time.get_blocks()); }
};

//===================================================== TECHNICIAN =============================================================//

/**
 * @brief Classed used to store the attributes of a technician who are responsable for
 * doing court repairs for the company.
 * 
 */
class Technician {
private:
	static id_t largest_id;

	string name;
	id_t id;
	vector<pair<id_t, int>> jobs;
	int availability;
	int repairs;
public:
	/**
	 * @brief Constructs a new technician with a template name and unique id.
	 * 
	 */
	Technician();

	/**
	 * @brief Construct a new technician with the given name an a unique id.
	 * 
	 * @param name 		Name of the new technician
	 */
	Technician(string name);

	/**
	 * @brief Returns the technician's name.
	 * 
	 * @return string 	Name of the technician
	 */
	string get_name() const { return name; }

	/**
	 * @brief Returns the technician's id.
	 * 
	 * @return id_t 	Techinician's id
	 */
	id_t get_id() const { return id; }

	/**
	 * @brief Returns the technician's availability, i.e how many days until the
	 * technicians is free to do a new repair.
	 * 
	 * @return int 		Technician's availability
	 */
	int get_availability() const { return availability; }

	/**
	 * @brief Returns the number of repairs done by the technician so far.
	 * 
	 * @return int 		Number of repairs performed by the technician
	 */
	int get_repairs() const { return repairs; }

	/**
	 * @brief Assigns a repair to the technician. The repair is represented by a pair
	 * with the id of the court to be repaired and the duration of said repair.
	 * 
	 * @param court_id 	Id of the court that needsd repairing
	 * @param duration 	Duration in days of the given repair
	 */
	void assign_job(id_t court_id, int duration);

	/**
	 * @brief Decrements one day to the current repair if any are being done. If it
	 * was the last day it removes it from the jobs vector. Updates the availability
	 * accordingly.
	 * 
	 */
	void update_repair();

	/**
	 * @brief Cancels the repair that was being done by the technician returning the
	 * number of days that were missing for the repair to finish. If there was no job
	 * it returns 0.
	 * 
	 * @return int 		Number of days that were remaining to finish the repair
	 */
	int cancel_job();

	/**
	 * Cancels any jobs scheduled for the court in question
	 * 
	 * @param court_id ID of the court
	 */
	void cancel_job(id_t court_id);

	/**
	 * @brief Returns a string with information on the technician.
	 * 
	 * @return string 	Information about the technician
	 */
	string get_info();

	bool operator<(const Technician& tech) const;
	bool operator==(const Technician& tech) const;

	friend class Empresa;
};

#endif//OBJETOS_H
