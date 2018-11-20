#ifndef empresa.h
#define empresa_h

#include <iostream>
#include <iomanip>
#include <vector>
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
	 * @param out 	Ostream where the information will be outputted
	 */
	void list_utentes(ostream& out) const;

	/**
	 * @brief Displays the schedule, of the user with the given id, for the
	 * 6 following days.
	 * 
	 * @param id 	Id of the user whos' schedule will be printed
	 * @param out 	Ostream where the information will be outputted
	 */
	void print_user_schedule(int id, ostream& out) const;

	/**
	 * @brief Displays the bill describing the expenses due for the current
	 * month.
	 * 
	 * @param id 	Id of the user whos' bill will be printed
	 * @param out 	Ostream where the information will be outputted
	 */
	void print_bill(int id, ostream& out) const;

	/**
	 * @brief Return the debt of the user with the given id.
	 * 
	 * @param id 	Id of the user whos' debt will be returned
	 *
	 * @return int 	Debt of the user with the given id
	 */
	int get_debt(int id) const;

	/**
	 * @brief Pays all debt of the user with the given id.
	 * 
	 * @param id 	Id of the user whos' debt will be payed
	 */
	void pay_debt(int id);

	/**
	 * @brief Creates a free use class and adds it to the vector usos.
	 * 
	 * @param user_id 		Id of the user that will be use the court
	 * @param court_id 		Court where the free use class will take place
	 * @param periodo 		Time period in the day where the free use class will occur
	 * @param data			Date where the class will occur
	 */
	void schedule_free_use(id_t user_id, id_t court_id, Period periodo, Date data);

	/**
	 * @brief Creates a class with the given user and teacher, in the given
	 * court and adds it to the vector aulas and usos.
	 * 
	 * @param user_id 		Id of the user that will be attending the class
	 * @param teacher_id 	Id of the teacher that will be giving the class
	 * @param court_id 		Court where the class will take place
	 * @param periodo 		Time period in the day where the class will occur
	 * @param data			Date where the class will occur 
	 */
	void schedule_class(id_t user_id, id_t teacher_id, id_t court_id, Period periodol, Date data);

	/**.
	 * @brief Removes the class with the given class_id from the vector aulas.
	 * 
	 * @param user_id 		Id of the user that attended the class
	 * @param class_id 		Id of the class that happend
	 */
	void attend_class(id_t user_id, id_t class_id);

	/**
	 * @brief Removes the class with the given class_id from the vector aulas and
	 * usos.
	 * 
	 * @param user_id 		Id of the user that would attend the class
	 * @param class_id	 	Id of the class that would occur
	 */
	void cancel_use(id_t user_id, id_t class_id);

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
	 * @param out 	Ostream where the information will be outputted
	 */
	void list_profs(ostream& out) const;

	/**
	 * @brief Displays the schedule, of the teacher with the given id, for the
	 * 6 following days.
	 * 
	 * @param id 	Id of the teacher whos' schedule will be printed
	 * @param out 	Ostream where the information will be outputted
	 */
	void print_prof_schedule(int id, ostream& out) const;

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
	void print_available_courts(Date d, Period p);

	/**
	 * @brief Prints the schedule of the court on the day given by the date.
	 * 
	 * @param id 	Id of the court whos' schedule will be displayed
	 * @param d 	Date of the day where the schedule will be displayed
	 */
	void print_court_schedule(id_t id, Date d);

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
	void save_file();

	/**
	 * @brief Saves all information to a file, with the name given by filename, of 
	 * type .txt.
	 * 
	 * @param filename		Name of the file where the information will be stored
	 */
	void save_file(string file);

protected:

	/**
	* @brief Given the path and file_name it checks the folder of the given path if
	* there is a file of the same name, return true if there is, false otherwise.
	* 
	* @param dir_path		Path of the folder that will be checked
	* @param file_name		Name of the file that will be checked if it exists
	*
	* @return true			The path folder has a file with the same name of the given string 
	* @return false			The path folder doesn't have a file with the same name of the given string 
	*/
	bool file_exists(const fs::path & dir_path, const string file_name);
};

#endif

