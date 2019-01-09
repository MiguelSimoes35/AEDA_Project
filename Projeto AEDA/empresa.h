#ifndef empresa_h
#define empresa_h

#define FILESYSTEM_ON

#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <experimental/filesystem>
#include <set>
#include <unordered_set>
#include <queue>

#include "objetos.h"

using namespace std;

namespace fs = experimental::filesystem;

/**
 * @brief Struct used for defining operator to be used in the data structure set, used to
 * store User information, encapsulated in a class UserPtr. A user is lesser then another if
 * it has less classes/free uses attended, or if this number is the same, then lesser in
 * alphabetical order. 
 * 
 */
struct UserPtrBST {
	bool operator() (const UserPtr user1, const UserPtr user2) const {
		if (user1.get_frequency() == user2.get_frequency()) 
			return (user1.get_name() < user2.get_name());
		else
			return (user1.get_frequency() < user2.get_frequency());
	}
};

/**
 * @brief Struct used to define the hash function and operator for the unordered set that will
 * store Teacher Information, encapsulated in a class TeacherPtr. Two teachers are the same if
 * they have the same id.
 * 
 */
struct TeacherPtrHash
{
	int operator() (const TeacherPtr teacher) const {
		int hash_code =  teacher.get_id();

		hash_code = (hash_code ^ 61) ^ (hash_code >> 16);
		hash_code = hash_code + (hash_code << 3);
		hash_code = hash_code ^ (hash_code >> 4);
		hash_code = hash_code * 0x27d4eb2d;
		hash_code = hash_code ^ (hash_code >> 15);

		return (hash_code % 131);
	}

	bool operator() (const TeacherPtr teach1, const TeacherPtr teach2) const {
		return (teach1.get_id() == teach2.get_id());
	}
};

/**
 * @brief Set (Binary Search Tree) structure to store information about the company's users
 * through a class UserPtr that has a pointer to a user and functions to access important 
 * information.
 * 
 */
typedef set<UserPtr, UserPtrBST> BST;

/**
 * @brief Unordered set (Hash Table) structure used to store information about the company's
 * teachers using a class TeacherPtr that has a pointer to a teacher and necessary function to
 * access relevant information
 * 
 */
typedef unordered_set<TeacherPtr, TeacherPtrHash, TeacherPtrHash> HashTable;

/**
 * @brief Manages tennis courts, namely adding or removing courts, teachers and user, plus managing their attributes. Adds and removes
 * classes and free uses of the courts. Displays information about users, teacher and courts and respective schedules. Displays and
 * manages bills. Imports and saves information in a .txt file.
 */
class Empresa {
private:

	Date date;
	string filename;
	BST utentes;
	HashTable professores;
	priority_queue<Technician> technicians;
	vector<Court> campos;
	vector<Class> aulas;
	vector<Use*> usos;

	/**
	 * @brief Used to create a fake user, used only temporarily to facilitate
	 * handling the users on functionalities like searching, where the name of
	 * a user is known but not any other information.
	 * 
	 * @param name 		Name of the user
	 * @return UserPtr 	A fake UserPtr used to search the set structure for 
	 * 					actual user
	 */
	static UserPtr dummie_user(string name);
	
	/**
	 * @brief Used to create a fake teacher, used only temporarily to facilitate
	 * handling the teachers on functionalities like searching, where the name of
	 * a teacher is known but not any other information.
	 * 
	 * @param name 			Name of the teacher
	 * @return TeacherPtr 	A fake TeacherPtr used to search the set structure for 
	 * 						actual teacher
	 */
	static TeacherPtr dummie_teacher(string name);

public:

	//==================================================== Empresa ============================================================//

	/**
	* @brief Default constructor for the Empresa. Generates a file, that will
	* store all information from Empresa, with an available filename and
	* sets the date to 0-0-0.
	*
	*/
	Empresa();

	/**
	 * @brief Constructs a new Empresa object, creating a file, that will
	 * store all information from Empresa, with the name given by file, if
	 * not already used, and sets the date to 0-0-0.
	 *
	 * @param file 		Name of the file to create
	 */
	Empresa(string file);

	/**
	 * @brief Constructs a new Empresa object, creating a file, that will
	 * store all information from Empresa, with an available name and sets
	 * the date to be the given date.
	 *
	 * @param date 		Date that will be set to be the current one
	 */
	Empresa(Date date);

	/**
	 * @brief Constructs a new Empresa object, creating a file, that will
	 * store all information from Empresa, with the name given by file, if
	 * not already used, and sets the date to be the given date.
	 *
	 * @param date  	Name of the file to create
	 * @param file 		Date that will be set to be the current one
	 */
	Empresa(Date date, string file);

	/**
	 * @brief return the filename of the file that stores information.
	 *
	 * @return string 	Name of the file that stores information
	 */
	string get_filename() const { return filename; }

	/**
	 * @brief Checks if a file with new_filename already exist, if it doesn't
	 * it sets filename to new_filename.
	 *
	 * @param new_filename 		New name for the file that stores the information
	 */
	void set_filename(string new_filename);

	/**
	 * @brief Imports information from the file, with the name given by filename, of
	 * type .txt.
	 *
	 * @param filename		Name of the file with the information to import
	 */
	void import_file(string filename);

	/**
	 * @brief Saves all information to a file, with an available name, of type .txt.
	 *
	 */
	void save_file() const;

	/**
	 * @brief Saves all information to a file, with the name given by filename, of
	 * type .txt.
	 *
	 * @param filename		Name of the file where the information will be stored
	 */
	void save_file(string file) const;

	/**
	 * @brief Prints the schedule of all courts on the day given by the date.
	 *
	 * @param d 	Date of the day where the schedule will be displayed
	 */
	void print_day_schedule(Date d);

	/**
	 * @brief Return the current date in the format dd/mm/yyyy
	 * 
	 * @return string 	String containing current date (dd/mm/yyyy)
	 */
	string get_date();

	/**
	 * @brief Increments current date an updates job rapairs that might be
	 * ongoing
	 * 
	 */
	void increment_date();

	//====================================================== USER ==============================================================//

	/**
	 * @brief Creates a user with the given name, card option, address and NIF.
	 * Inserts the user in the correct position in the BST utentes.
	 *
	 * @param nome 		Name of the new user
	 * @param card 		Golden card (true == owns it; false == doesn't have it)
	 * @param address 	Address of the new user
	 * @param NIF		NIF of the new user
	 */
	void add_utente(string nome, bool card, string address, unsigned NIF);

	/**
	 * @brief First it checks if there is a user with the given name. If there is
	 * it removes it from the BST utentes. Otherwise it throws an exception
	 * of type InexistingObject.
	 *
	 * @param nome 		Name of the user
	 */
	void remove_utente(string name);

	/**
	 * @brief Return the debt of the user with the given name.
	 *
	 * @param nome 		Name of the user
	 *
	 * @return int 	Debt of the user with the given name
	 */
	double get_debt(string name) const;

	/**
	 * @brief Pays all debt of the user with the given name.
	 *
	 * @param nome 		Name of the user
	 */
	void pay_debt(string name);

	/**
	 * @brief Finds user with the given name and if succeded changes the
	 * golden card to according to the argument card, if not throws
	 * exception of type InexistentObject
	 * 
	 * @param name 		Name of the user to change gold card
	 * @param card 		Desired status for gold card
	 */
	void change_card(string name, bool card);

	/**
	 * @brief Trys to find user with the given name. If found, changes it's
	 * address to the one passed as argument, otherwise it thorws an exception´
	 * of type InexistentObject
	 * 
	 * @param name 			Name of the user whos address is to be changed
	 * @param address 		New user address
	 */
	void change_address(string name, string address);

	/**
	 * @brief Trys to find user with the given name. If found return it's 
	 * current gold card status
	 * 
	 * @param name 		Name of the user to be found
	 * @return true 	Given user owns a gold card
	 * @return false 	Given user doens't have a gold card
	 */
	bool get_gold_card(string name) const;

	/**
	 * @brief Searches the utentes BST for the user with the name, if it
	 * finds him and there is only one user, it returns a UserPtr of that user,
	 * if there are multiple users with that name it throws an exception,
	 * if there is no user with that name it throws an InexistentObject 
	 * exception.
	 *
	 * @param nome 		Name of the user to be found
	 *
	 * @return UserPtr	UserPtr with a pointer to the user with the given name
	 */
	UserPtr find_user(string name) const;

	/**
	 * @brief It checks if the BST utentes has a user with the given name,
	 * return true if it does, false otherwise. If there are multiple users
	 * with the given name it still returns true.
	 *
	 * @param nome 		Name of the user to check if it exists
	 *
	 * @return true 	A user with the given name exists
	 * @return false 	No user with the given name exists
	 */
	bool exists_user(string name) const;

	/**
	 * @brief If a user with the given name is found it displays it's info
	 * in a user friendly way, otherwise it trows an InexistentObject 
	 * exception
	 * 
	 * @param name 	Name of the user whos information is to be displayed
	 */
	void print_user_info(string name) const;

	/**
	 * @brief Displays the schedule, of the user with the given name, for the
	 * 6 following days.
	 *
	 * @param nome 		Name of the user
	 */
	void print_user_schedule(string name) const;

	/**
	 * @brief Displays the bill describing the expenses due for the current
	 * month, of the given user.
	 *
	 * @param nome 		Name of the user
	 */
	void print_bill(string name) const;

	/**
	 * @brief Displays the report giving the classes and grades of the use
	 * with the given name.
	 *
	 * @param nome 		Name of the user
	 */
	void print_user_report(string name) const;

	/**
	 * @brief Displays the information about each user in the BST utentes
	 * by the order they appear in the BSt.
	 *
	 */
	void list_utentes() const;

	//==================================================== CLASSES ============================================================//

	/**
	 * @brief Creates a free use class and adds it to the vector usos.
	 *
	 * @param user_name		Name of the user that will be use the court
	 * @param court_id 		Court where the free use class will take place
	 * @param periodo 		Time period in the day where the free use class will occur
	 */
	void schedule_free_use(string user_name, id_t court_id, Period periodo);

	/**
	 * @brief Creates a class with the given user and teacher, in the given
	 * court and adds it to the vector aulas and usos.
	 *
	 * @param teacher_name 	Name of the teacher that will be giving the class
	 * @param court_id 		Court where the class will take place
	 * @param periodo 		Time period in the day where the class will occur
	 */
	void schedule_class(string teacher_name, id_t court_id, Period periodol);

	/**.
	 * @brief Removes the class with the given class_id from the vector aulas.
	 *
	 * @param user_name		Name of the user that attended the class
	 * @param class_id 		Id of the class that happend
	 */
	void attend_class(string user_name, id_t class_id);

	/**
	 * @brief Checks if there is a teacher with the given id. If there is then it
	 * atributes the given class to the teacher. Otherwise it throws an exception
	 * of type InexistingObject.
	 *
	 * @param teacher_name 	Name of the teacher that will have the class
	 * @param a 				Class that will be taught by the teacher
	 */
	void give_class(string teacher_name, Class *a);

	/**
	 * @brief Removes the class with the given class_id from the vector aulas and
	 * usos.
	 *
	 * @param user_name		Name of the user that would attend the class
	 * @param class_id	 	Id of the class that would occur
	 */
	void cancel_use(string user_name, id_t use_id);

	/**
	 * @brief Cancels the class with the given id if it exists, making the
	 * necessary changes
	 * 
	 * @param class_id 	Id of the class to be canceled
	 */
	void cancel_class(id_t class_id);

	/**
	 * @brief It checks if the vector usos has the use with the given
	 * id, returns true if it does, false otherwise.
 	 *
	 * @param id 		Id of the use to check if it exists
	 *
	 * @return true 		The use with the given id was found
	 * @return false 	The use with the given id was not found
	 */
	bool exists_use(id_t id) const;

	/**
	 * @brief It checks if the vector aulas has the class with the given
	 * id, returns true if it does, false otherwise.
	 *
	 * @param id 		Id of the class to check if it exists
	 *
	 * @return true		The class with the given id was found
	 * @return false 	The class with the given id was not found
	 */
	bool exists_class(id_t id) const;

	/**
	 * @brief Trys to find an existing class during the given period. If it
	 * finds it it return the id of that class, otherwise it throwns an
	 * InexistentObject exception
	 * 
	 * @param periodo 	Period to be checked for a class
	 * @return id_t 	Id of the class that occurs during the given period
	 */
	id_t find_class(Period periodo) const;

	/**
	 * @brief Searches the vector aulas for the class, if it finds it,
	 * it returns the index of the class in the vector, otherwise it
	 * throws an exception of type InexistingObject.
	 *
	 * @param id  	Id of the class to be found
	 *
	 * @return int 	Index of the class with the given id in vector aulas
	 */
	int find_class(id_t id) const;

	/**
	 * @brief Trys to find an existing use during the given period. If it
	 * finds it it return the id of that use, otherwise it throwns an
	 * InexistentObject exception
	 * 
	 * @param periodo 	Period to be checked for a use
	 * @return id_t 	Id of the use that occurs during the given period
	 */
	id_t find_use(Period periodo) const;

	/**
	 * @brief Searches the vector usos for the use, if it finds it,
	 * it returns the index of the use in the vector, otherwise it
	 * throws an exception of type InexistingObject.
	 *
	 * @param id  	Id of the use to be found
	 *
	 * @return int 	Index of the use with the given id in vector usos
	 */
	int find_use(id_t id) const;

	/**
	 * @brief If it finds a use with the given id, it return the info of that
	 * use 
	 * 
	 * @param id 	Id of the use which info is to be printed
	 */
	void print_use_info(id_t id) const;

	/**
	 * @brief If it finds a class with the given id, it return the info of that
	 * class 
	 * 
	 * @param id 	Id of the class which info is to be printed
	 */
	void print_class_info(id_t id) const;

	/**
	 * @brief Lists the information about all uses that exist in the
	 * vector usos
	 * 
	 */
	void list_uses() const;

	/**
	 * @brief Lists the information about all classes that exist in the
	 * vector aulas
	 * 
	 */
	void list_classes() const;

	//==================================================== TEACHER ============================================================//

	/**
	 * @brief Creates a teacher with the given name. Inserts the teacher in the
	 * correct position in the hash table professores.
	 *
	 * @param name 		Name of the new teacher
	 */
	void add_prof(string name);

	/**
	 * @brief First it checks if there is a teacher with the given name. If there is
	 * it sets the current state of that teacher to inactive. Otherwise it throws an 
	 * exception of type InexistingObject.
	 *
	 * @param name 		Name of the teacher
	 */
	void remove_prof(string name);

	/**
	 * @brief If there is a class with the given id, it changes the teacher of that
	 * class to the teacher with the given name
	 * 
	 * @param name 			Name of the new teacher for the class
	 * @param class_id 		Id of the class to be changed
	 */
	void change_teacher(string name, id_t class_id);

	/**
	 * @brief Displays the information about each teacher in the hash table professores
	 * by the order which they appear in the hash table.
	 *
	 */
	void list_profs() const;

	/**
	 * @brief Displays the schedule, of the teacher with the given name, for the
	 * 6 following days.
	 *
	 * @param name 		Name of the teacher
	 */
	void print_prof_schedule(string name) const;

	/**
	 * @brief It checks the hash table professores for a teacher with the given
	 * name, return true if it does, false otherwise. If there are multiple
	 * teachers with the given name it still returns true.
	 *
	 * @param name 		Name of the teacher to check if it exists
	 *
	 * @return true 		A teacher with the given name exists
	 * @return false 	No teacher with the given name exists
	 */
	bool exists_teacher(string name) const;

	/**
	 * @brief If there is a teacher in the hash table professores with the given
	 * name it displays the informations about that teacher. Otherwise it throws
	 * an InexistentObject exception
	 * 
	 * @param name 		Name of the teacher
	 */
	void print_teacher_info(string name) const;

	//===================================================== COURT =============================================================//

	/**
	 * @brief It creates a Court with the given capacity. It adds the new court
	 * to the vector campos.
	 *
	 * @param capacity 	Capacity that the new court will widstand
	 */
	void add_court(size_t capacity);

	/**
	 * @brief Removes the court with the given id from the vector campos.
	 *
	 * @param id 	Id of the court that will be removed
	 */
	void remove_court(id_t id);

	/**
	 * @brief Changes the capacity of the court with the given id to the
	 * capacity given as an argument. If it doesn't find the given court
	 * it throws an exception of type InexistentObject
	 * 
	 * @param id 			Id of the court which capacity is to be changed
	 * @param capacity 		New court capacity
	 */
	void change_capacity(id_t id, size_t capacity);

	/**
	 * @brief If there is a class with the given id in the vector aulas, it
	 * changes the schedule court to be instead the one passed as argument.
	 * If there isn't an exception of type InexistentObject is thrown.
	 * 
	 * @param court_id 
	 * @param class_id 
	 */
	void change_court(id_t court_id, id_t class_id);

	/**
	 * @brief Displays the information about all courts that exist in
	 * the vector campos.
	 * 
	 */
	void list_courts() const;

	/**
	 * @brief Prints the courts that are available in the given date.
	 *
	 * @param d 	Date where the court availability will be displayed
	 */
	void print_available_courts(Date d);

	/**
	 * @brief Prints the courts that are available in the given date on the
	 * given period.
	 *
	 * @param p 	Period of the day where the court availability will be displayed
	 */
	void print_available_courts(Period p);

	/**
	 * @brief Prints the schedule of the court on the day given by the date.
	 *
	 * @param id 	Id of the court whos' schedule will be displayed
	 * @param d 	Date of the day where the schedule will be displayed
	 */
	void print_court_schedule(id_t id, Date d);

	/**
	 * @brief Searches the vector campos for the court, if it finds it,
	 * it returns the index of the court in the vector, otherwise it
	 * throws an exception of type InexistingObject.
	 *
	 * @param id  	Id of the court to be found
	 *
	 * @return int 	Index of the court with the given id in vector campos
	 */
	int find_court(id_t id) const;

	/**
	 * @brief It checks if the vector campos has the court with the given
	 * id, returns true if it does, false otherwise.
	 *
	 * @param id 		Id of the court to check if it exists
	 *
	 * @return true 	The court with the given id was found
	 * @return false 	The court with the given id was not found
	 */
	bool exists_court(id_t id) const;
	
	//=================================================== TECHNICIAN ==========================================================//

	/**
	 * @brief Adds a new technician to the priority queue technicians, with
	 * the given name.
	 * 
	 * @param name 	Name of the new technician
	 */
	void add_technician(string name);

	/**
	 * @brief Removes from the priority queue technicians the technician with
	 * the given id. If there isn't one the priority queue remains the same.
	 * 
	 * @param id 	Id of the technician to be removed
	 */
	void remove_technician(id_t id);

	/**
	 * @brief If the priority queue technicians is not empty it assigns the
	 * first technician in the queue with less then the maximum amount od repairs,
	 * to repair the court with the given id, that will last the given amount of
	 * days. If there is no technician that fills these requirements the function
	 * returns false.
	 * 
	 * @param court_id 			Id of the court to be repaired
	 * @param duration 			Duration in days of the repair
	 * @param max 				Max number of repairs a technician can have to be assigned the job
	 * 
	 * @return true 			The repair was assigned to a technician
	 * @return false 			There was no technician that could be assigned the given repair
	 */
	bool assign_technician(id_t court_id, int duration, unsigned max);

	/**
	 * @brief Updates all current repairs being made by the technicians in
	 * the priority queue technicians, i.e subtracts one day off all repairs
	 * and if any have finished then the next one (if exists) is started
	 * 
	 */
	void update_repairs();

	/**
	 * @brief List the information about all technicians that exist in the
	 * priority queue technicians.
	 * 
	 */
	void list_technicians();

	/**
	 * @brief Searches the priority queue technicians for a technician with
	 * the given name. If it finds it, return true, false otherwise.
	 * 
	 * @param name 		Name of the technician to be found
	 * @return true 	There is a technician with the given name
	 * @return false 	A technician with the given name does not exist
	 */
	bool exists_technician(string name);

	/**
	 * @brief Searches the priority queue technicians for the technician with
	 * the given id, if it finds it, it returns true, false otherwise.
	 *
	 * @param id  	Id of the technician to be found
	 *
	 * @return true  There is a technician with the given id
	 * @return false  There isn't a technician with the given id
	 */
	bool exists_technician(id_t id);

	/**
	 * @brief Searches the priority queue for a technician with the given name.
	 * If it finds it, returns their id, otherwise it throws an InexistentObject
	 * exception.
	 * 
	 * @param name 
	 * @return id_t 
	 */
	id_t find_technician(string name);
};

#endif//empresa_h

