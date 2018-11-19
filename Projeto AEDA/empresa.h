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
	vector<Class> aulas;
	vector<Use*> usos;

public:
	Empresa(string file);
	Empresa(Date date);

	int find_user(id_t id) const;
	id_t find_user(string nome) const;
	int find_teacher(id_t id) const;
	id_t find_teacher(string nome) const;
	int find_court(id_t id) const;
	string get_filename() const { return filename; }
	void set_filename(string new_filename) { filename = move(new_filename); }
	void add_utente(string nome, bool card);
	void remove_utente(int id);
	bool exists_utente(id_t id) const;
	bool exists_utente(string nome) const;
	bool exists_teacher(id_t id) const;
	bool exists_teacher(string nome) const;
	bool exists_court(id_t id) const;
	void list_utentes(ostream& out) const;
	void print_user_schedule(int id, ostream& out) const;
	void print_bill(int id, ostream& out) const;
	int get_debt(int id) const;
	void pay_debt(int id);
	void schedule_free_use(id_t user_id, id_t court_id, Period periodo);
	void schedule_class(id_t user_id, id_t teacher_id, id_t court_id, Date data);
	void attend_class(id_t user_id, id_t class_id);
	void cancel_use();
	void add_prof(Teacher *p);
	void remove_prof(Teacher *p);
	void give_class(Teacher *p, Class *a);
	void print_profs();
	void print_prof_schedule(int id);
	void print_prof_schedule(string nome);
	void add_court(size_t capacity);
	void remove_court(int num);
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

