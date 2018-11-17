#ifndef empresa.h
#define empresa_h

#include <iostream>
#include <vector>
#include "objetos.h"

using namespace std;

/**
 * @brief gere os conjuntos de dados, as relacoes entre eles e as operacoes
 * @
 *
 */
class Empresa {
private:
	Date date;
	string filename;
	vector<User> utentes;
	vector<Teacher> professores;
	vector<Court> campos;
	vector<ClassAtendance> aulas;
	vector<Use*> usos;

public:
	Empresa(string file);
	Empresa(Date date);
	
	string get_filename() const { return filename; }
	void set_filename(string new_filename) { filename = move(new_filename); }
	
	bool add_utente(User *u);
	bool remove_utente(int id);
	bool remove_utente(string nome);
	bool exists_utente(int id);
	bool exists_utente(string nome);
	void list_utentes();
	void print_user_schedule(int id);
	void print_user_schedule(string nome);
	void print_bill(int id);
	void print_bill(string nome);
	int get_debt(int id);
	int get_debt(string nome);
	bool pay_debt(int id);
	bool pay_debt(string nome);
	bool schedule_use();
	bool cancel_use();
	bool add_prof(Teacher *p);
	bool remove_prof(Teacher *p);
	bool give_class(Teacher *p, ClassAtendance *a);
	void print_profs();
	void print_prof_schedule(int id);
	void print_prof_schedule(string nome);
	bool add_court(Court *c);
	bool remove_court(int num);
	void print_available_courts(Date d);
	void print_available_courts(Date d, Period p);
	void print_court_schedule(int court, Date d);
	void print_day_schedule(Date d);
	void import_file();
	void import_file(string file);
	void save_file();
	void save_file(string file);

protected:
	bool file_exists(const fs::path & dir_path, const string file_name);
};

#endif

