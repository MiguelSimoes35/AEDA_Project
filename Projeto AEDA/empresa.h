#ifndef empresa_h
#define empresa_h

#define FILESYSTEM_ON

#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <experimental/filesystem>

#include "objetos.h"

using namespace std;
namespace fs = experimental::filesystem;

/**
 * @brief Manages tennis courts, namely adding or removing courts, teachers and user, plus managing their attributes. Adds and removes 
 * classes and free uses of the courts. Displays information about users, teacher and courts and respective schedules. Displays and 
 * manages bills. Imports and saves information in a .txt file.
 */
class Empresa {
private:
	
	Date date;
	string filename;
	vector<User> utentes;
	vector<Teacher> professores;
	vector<Court> campos;
	vector<Class> aulas;
	vector<Use*> usos;

	void import_line(istream& line);
	enum class_type { USER, TEACHER, COURT, CLASS, USE };
	enum use_type { NOT, ABSTRACT, CLASS_A, FREE };
	enum line_type { GLOBALS, ATTRIBUTES, EXTERNALS, USES, CLASSES, FREE_USES, ATTENDANCES};

	struct header {
		class_type c;
		use_type u;
		line_type l;
	};

	static header parse_header(const string &h);

	void import_user_uses(istream& line);
	void import_teacher_classes(istream& line);
	void import_court_free_uses(istream& line);
	void import_class_externals(istream& line);
	void import_class_attendances(istream& line);
	void import_free_use_externals(istream& line);
	void import_class_a_externals(istream& line);

public:


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

	string get_date();

	void increment_date() { date = date++; }

	/**
	 * @brief Searches the utentes vector for the user, if it finds him it 
	 * returns the index of the user in the vector, otherwise it throws an
	 * exception of type InexistingObject.
	 * 
	 * @param id 		Id of user to be found
	 *
	 * @return int 		Index of user in vector utentes
	 */
	int find_user(id_t id) const;

	/**
	 * @brief Searches the utentes vector for the user with the name, if it
	 * finds him and there is only one user, it returns the id of that user,
	 * if there are multiple user with that name it throws an exception that
	 * displays all ids of users with the given name, if there is no user
	 * with that name it throws an InexistentObject exception.
	 * 
	 * @param nome 		Name of the user to be found
	 *
	 * @return id_t 	Id of the user with the given name
	 */
	id_t find_user(string nome) const;

	/**
	 * @brief Searches the vector professores for the teacher, if it finds
	 * him it returns the index of the teacher in the vector, otherwise it 
	 * throws an exception of type InexistingObject.
	 * 
	 * @param id 		Id of the theacher to be found
	 *
	 * @return int  	Index of teacher in vector professores
	 */
	int find_teacher(id_t id) const;

	/**
	 * @brief Searches the vector professores for the teacher with the name, if it
	 * finds him and there is only one teacher, it returns the id of that teacher,
	 * if there are multiple teacher with that name it throws an exception that
	 * displays all ids of teachers with the given name, if there is no teacher
	 * with that name it throws an InexistentObject exception.
	 * 
	 * @param nome 		Name of the teacher to be found
	 *
	 * @return id_t 	Id of the teacher with the given name
	 */
	id_t find_teacher(string nome) const;

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
	* @brief Searches the vector usos for the use, if it finds it,
	* it returns the index of the use in the vector, otherwise it
	* throws an exception of type InexistingObject.
	*
	* @param id  	Id of the use to be found
	*
	* @return int 	Index of the use with the given id in vector usos
	*/
	int find_use(id_t id) const;

	id_t find_class(Period periodo) const;

	id_t find_use(Period periodo) const;

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
	 * @brief It checks if the vector utentes has a user with the given id,
	 * returns true if it does, false otherwise.
	 * 
	 * @param id 		Id of the user to check if it exists
	 *
	 * @return true 	The user with the given id was found
	 * @return false 	The user with the given id was not found
	 */
	bool exists_user(id_t id) const;

	/**
	 * @brief It checks the vector utentes has a user with the given name, 
	 * return true if it does, false otherwise. If there are multiple users
	 * with the given name it still returns true.
	 * 
	 * @param nome 		Name of the user to check if it exists
	 *
	 * @return true 	A user with the given name exists
	 * @return false 	No user with the given name exists
	 */
	bool exists_user(string nome) const;

	/**
	 * @brief It checks if the vector professores has the teacher with the given 
	 * id, returns true if it does, false otherwise.
	 * 
	 * @param id 		Id of the teacher to check if it exists
	 *
	 * @return true 	The teacher with the given id was found
	 * @return false 	The teacher with the given id was not found
	 */
	bool exists_teacher(id_t id) const;

	/**
	 * @brief It checks the vector professores has a teacher with the given 
	 * name, return true if it does, false otherwise. If there are multiple 
	 * teachers with the given name it still returns true.
	 * 
	 * @param nome 		Name of the teacher to check if it exists
	 *
	 * @return true 	A teacher with the given name exists
	 * @return false 	No teacher with the given name exists
	 */
	bool exists_teacher(string nome) const;

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
	 * @brief Creates a user with the given name and card option. Inserts the
	 * user in the correct position in the vector utentes.
	 * 
	 * @param nome 		Name of the new user
	 * @param card 		Golden card (true == owns it; false == doesn't have it)	
	 */
	void add_utente(string nome, bool card);

	/**
	 * @brief First it checks if there is a user with the given id. If there is
	 * it removes it from the vector utentes. Otherwise it throws an exception
	 * of type InexistingObject.
	 * 
	 * @param id 	Id of the user that will be removed
	 */
	void remove_utente(int id);

	/**
	 * @brief Displays the information about each user in the vector utentes
	 * by the order they appear in the vector.
	 * 
	 */
	void list_utentes() const;

	void print_user_info(id_t id) const;

	void print_teacher_info(id_t id) const;

	void print_class_info(id_t id) const;

	void print_use_info(id_t id) const;


	/**
	 * @brief Displays the schedule, of the user with the given id, for the
	 * 6 following days.
	 * 
	 * @param id 	Id of the user whos' schedule will be printed
	 */
	void print_user_schedule(int id) const;

	/**
	 * @brief Displays the bill describing the expenses due for the current
	 * month.
	 * 
	 * @param id 	Id of the user whos' bill will be printed
	 */
	void print_bill(int id) const;

	/**
	* @brief Displays the report giving the classes and grades of the use
	* with the given id.
	*
	* @param id 	Id of the user whos' report will be printed
	*/
	void print_user_report(int id) const;

	/**
	 * @brief Return the debt of the user with the given id.
	 * 
	 * @param id 	Id of the user whos' debt will be returned
	 *
	 * @return int 	Debt of the user with the given id
	 */
	double get_debt(int id) const;

	/**
	 * @brief Pays all debt of the user with the given id.
	 * 
	 * @param id 	Id of the user whos' debt will be payed
	 */
	void pay_debt(int id);

	void change_card(id_t id, bool card);

	bool get_gold_card(id_t id);

	/**
	 * @brief Creates a free use class and adds it to the vector usos.
	 * 
	 * @param user_id 		Id of the user that will be use the court
	 * @param court_id 		Court where the free use class will take place
	 * @param periodo 		Time period in the day where the free use class will occur
	 */
	void schedule_free_use(id_t user_id, id_t court_id, Period periodo);

	/**
	 * @brief Creates a class with the given user and teacher, in the given
	 * court and adds it to the vector aulas and usos.
	 * 
	 * @param user_id 		Id of the user that will be attending the class
	 * @param teacher_id 	Id of the teacher that will be giving the class
	 * @param court_id 		Court where the class will take place
	 * @param periodo 		Time period in the day where the class will occur
	 */
	void schedule_class(id_t teacher_id, id_t court_id, Period periodol);

	/**.
	 * @brief Removes the class with the given class_id from the vector aulas.
	 * 
	 * @param user_id 		Id of the user that attended the class
	 * @param class_id 		Id of the class that happend
	 */
	void attend_class(id_t user_id, id_t class_id);

	void change_teacher(id_t teacher_id, id_t class_id);

	void change_court(id_t court_id, id_t class_id);

	/**
	 * @brief Removes the class with the given class_id from the vector aulas and
	 * usos.
	 * 
	 * @param user_id 		Id of the user that would attend the class
	 * @param class_id	 	Id of the class that would occur
	 */
	void cancel_use(id_t user_id, id_t use_id);

	void cancel_class(id_t class_id);

	/**
	 * @brief Creates a teacher with the given name. Inserts the teacher in the
	 * correct position in the vector professores.
	 * 
	 * @param nome 		Name of the new teacher
	 */
	void add_prof(string nome);

	/**
	 * @brief First it checks if there is a teacher with the given id. If there is
	 * it removes it from the vector professores. Otherwise it throws an exception
	 * of type InexistingObject. 
	 * 
	 * @param id 	Id of the teacher that will be removed
	 */
	void remove_prof(id_t id);

	/**
	 * @brief Checks if there is a teacher with the given id. If there is then it
	 * atributes the given class to the teacher. Otherwise it throws an exception 
	 * of type InexistingObject.
	 * 
	 * @param id 	Id of the teacher that will have the class
	 * @param a 	Class that will be taught by the teacher
	 */
	void give_class(id_t id, Class *a);

	/**
	 * @brief Displays the information about each teacher in the vector professores
	 * by the order which they appear in the vector.
	 * 
	 */
	void list_profs() const;

	/**
	 * @brief Displays the schedule, of the teacher with the given id, for the
	 * 6 following days.
	 * 
	 * @param id 	Id of the teacher whos' schedule will be printed
	 */
	void print_prof_schedule(int id) const;

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
	 * @param d 	Date where the court availability will be displayed
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

	void list_uses() const;

	void list_classes() const;

	/**
	 * @brief Prints the schedule of all courts on the day given by the date.
	 * 
	 * @param d 	Date of the day where the schedule will be displayed
	 */
	void print_day_schedule(Date d);

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
};

#endif//empresa_h

