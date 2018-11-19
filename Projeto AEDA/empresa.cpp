#include "empresa.h"

//==================================================== Empresa ===========================================================//

									//   -----------------------------------   //
									//   --- Member Function Definitions ---   //
									//   -----------------------------------   //






Empresa::Empresa() {
	fs::path initial = fs::current_path();
	string name = "0";
	int number = 0;

	while (file_exists(initial, name) && number < 9999) {
		number++;
		ostringstream oss;
		oss << setfill('0') << setw(3) << number;
		name = oss.str();
	}

	filename = name;
	date = Date(0, 0, 0);
}

//=================================================================================================================//

Empresa::Empresa(string file) {
	fs::path initial = fs::current_path();

	if (!file_exists(initial, file) {
		cout << "File name already used!" << endl;
	}
	else {
		filename = file;
		date = Date(0, 0, 0);
	}
}

//=================================================================================================================//

Empresa::Empresa(Date date) {
	fs::path initial = fs::current_path();
	string name = "0";
	int number = 0;
	
	while (file_exists(initial, name) && number < 9999) {
		number++;
		ostringstream oss;
		oss << setfill('0') << setw(3) << number;
		name = oss.str();
	}

	filename = name;
	this->date = date;
}

//=================================================================================================================//

Empresa::Empresa(Date date, string file) {
	fs::path initial = fs::current_path();

	if (!file_exists(initial, file) {
		cout << "File name already used!" << endl;
	}
	else {
		filename = file;
		this->date = date;
	}
}

//=================================================================================================================//

string Empresa::get_filename() const{
	return filename;
}

//=================================================================================================================//

void Empresa::set_filename(string filename) {
	fs::path initial = fs::current_path();

	if (!file_exists(initial, file) {
		cout << "File name already used!" << endl;
	}
	else {
		this->filename = filename;
	}
}

//=================================================================================================================//

int Empresa::find_user(id_t id) const {
	if (exists_utente(id)) {
		for (size_t t = 0; t < utentes.size(); t++) {
			if (utentes.at(t).get_id() == id) {
				return t;
			}
		}
	}
	else {
		throw InexistentObject("User");
	}
}

//=================================================================================================================//

id_t Empresa::find_user(string nome) const{
	vector<id_t> ids;

	for (size_t t = 0; t < utentes.size(); t++) {
		if (utentes.at(t).get_name == nome) {
			ids.push_back(utentes.at(t).get_id());
		}
	}

	if (ids.size() != 1) {
		throw SameName(nome, ids);
	}
	
	return ids.at(0);
}

//=================================================================================================================//

int Empresa::find_teacher(id_t id) const{
	if (exists_teacher(id)) {
		for (size_t t = 0; t < professores.size(); t++){
			if (professores.at(t).get_id() == id) {
				return t;
			}
		}
	}
	else {
		throw InexistentObject("Teacher");
	}
}

//=================================================================================================================//

id_t Empresa::find_teacher(string nome) const {
	vector<id_t> ids;

	for (size_t t = 0; t < professores.size(); t++) {
		if (professores.at(t).get_name == nome) {
			ids.push_back(professores.at(t).get_id());
		}
	}

	if (ids.size() != 1) {
		throw SameName(nome, ids);
	}

	return ids.at(0);
}

//=================================================================================================================//

int Empresa::find_court(id_t id) const {
	if (exists_campo(id)) {
		for (size_t t = 0; t < campos.size(); t++) {
			if (campos.at(t).get_id() == id) {
				return t;
			}
		}
	}
	else {
		throw InexistentObject("Court");
	}
}

//=================================================================================================================//

void Empresa::add_utente(string nome, bool card){
	bool exists = false;
	int pos = -1;
	User u(nome, card);

	for (size_t t = 0; t < utentes.size(); t++) {
		if (utentes.at(t) == u) {
			exists = true;
		}
		else if (utentes.at(t) < u) {
			pos = t + 1;
		}
	}

	if (exists_utente(nome))
		throw RepeatedObject("User");

	utentes.insert(utentes.begin() + pos, u);
}

//=================================================================================================================//

void Empresa::remove_utente(int id) {
	bool exists = false;
	int pos = -1;

	for (size_t t = 0; t < utentes.size(); t++) {
		if (utentes.at(t).get_id == id) {
			exists = true;
			pos = t;
		}
	}

	if (exists) {
		utentes.erase(utentes.begin() + pos);
	}

	throw InexistentObject("User");
}

//=================================================================================================================//

bool Empresa::exists_utente(id_t id) const {

	for (size_t t = 0; t < utentes.size(); t++) {
		if (utentes.at(t).get_id == id) {
			return true;
		}
	}

	return false;
}

//=================================================================================================================//
	
bool Empresa::exists_utente(string nome) const {

	id_t id = find_user(nome);

	return exists_utente(id);
}

//=================================================================================================================//

bool Empresa::exists_teacher(id_t id) const {
	for (size_t t = 0; t < professores.size(); t++) {
		if (professores.at(t).get_id == id) {
			return true;
		}
	}

	return false;
}

//=================================================================================================================//

bool Empresa::exists_teacher(string nome) const {
	id_t id = find_teacher(nome);

	return exists_teacher(id);
}

//=================================================================================================================//

bool Empresa::exists_court(id_t id) const {
	for (size_t t = 0; t < campos.size(); t++) {
		if (campos.at(t).get_id == id) {
			return true;
		}
	}

	return false;
}

//=================================================================================================================//

void Empresa::list_utentes(ostream& out) const {
	for (auto it = utentes.begin(); it != utentes.end(); it++)
		out << it->get_info() << '\n';
}

//=================================================================================================================//

void Empresa::print_user_schedule(int id, ostream& out) const {
	Date date_init = date;
	Date date_fin = date;
	for (int i = 0; i < 7; i++) 
		date_fin++;

	if (exists_utente(id)) {
		out << (utentes.at(find_user(id))).get_schedule(date_init, date_fin) << "\n";
	}
	else {
		throw InexistentObject("User");
	}	
}

//=================================================================================================================//

void Empresa::print_bill(int id, ostream& out) const{

	if (exists_utente(id)) {
		out << (utentes.at(find_user(id))).get_bill(date) << "\n";
	}
	else {
		throw InexistentObject("User");
	}
}

//=================================================================================================================//

int Empresa::get_debt(int id) const{
	if (exists_utente(id)) {
		return (utentes.at(find_user(id))).get_debt();
	}
	else {
		throw InexistentObject("User");
	}
}

//=================================================================================================================//

void Empresa::pay_debt(int id) {
	if (exists_utente(id)) {
		(utentes.at(find_user(id))).pay_debt();
	}
	else {
		throw InexistentObject("User");
	}
}

//=================================================================================================================//

void schedule_free_use(id_t user_id, id_t court_id, Date data){



}

//=================================================================================================================//

void schedule_class(id_t user_id, id_t teacher_id, id_t court_id, Date data) {

}

//=================================================================================================================//

void attend_class(id_t user_id, id_t class_id) {

}

//=================================================================================================================//

bool Empresa::cancel_use() {

}

//=================================================================================================================//

bool Empresa::add_prof(Teacher *p) {
	bool exists = false;
	int pos = -1;

	for (size_t t = 0; t < professores.size(); t++) {
		if (professores.at(t) == *p) {
			exists = true;
		}
		else if (professores.at(t) < *p) {
			pos = t + 1;
		}
	}

	if (exists)
		return false;

	professores.insert(professores.begin() + pos, *p);

	return true;
}

//=================================================================================================================//

bool Empresa::remove_prof(Teacher *p) {
	bool exists = false;
	int pos = -1;

	for (size_t t = 0; t < professores.size(); t++) {
		if (professores.at(t) == *p) {
			exists = true;
			pos = t;
		}
	}

	if (exists) {
		professores.erase(professores.begin() + pos);
		return true;
	}

	return false;
}

//=================================================================================================================//

bool Empresa::give_class(Teacher *p, ClassAtendance *a) {
	bool exists = false;
	int pos = -1;

	for (size_t t = 0; t < professores.size(); t++) {
		if (professores.at(t) == *a) {
			exists = true;
			pos = t;
		}
	}

	if (exists) {
		professores.at(pos).add_class(a);
		return true;
	}

	return false;
}

//=================================================================================================================//

void Empresa::print_profs() {

}

//=================================================================================================================//

void Empresa::print_prof_schedule(int id) {

}

//=================================================================================================================//

void Empresa::print_prof_schedule(string nome) {

}

//=================================================================================================================//

bool Empresa::add_court(Court *c) {
	bool exists = false;
	int pos = -1;

	for (size_t t = 0; t < campos.size(); t++) {
		if (campos.at(t).get_id == c->get_id) {
			exists = true;
		}
		else if (campos.at(t).get_id < c->get_id) {
			pos = t + 1;
		}
	}

	if (exists)
		return false;

	campos.insert(campos.begin() + pos, u);

	return true;
}

//=================================================================================================================//

bool Empresa::remove_court(int num) {
	bool exists = false;
	int pos = -1;

	for (size_t t = 0; t < professores.size(); t++) {
		if (campos.at(t).get_id == c->get_id) {
			exists = true;
			pos = t;
		}

	if (exists) {
		campos.erase(campos.begin() + pos);
	}
		return true;
	}

	return false;
}

//=================================================================================================================//

void Empresa::print_available_courts(Date d) {

}

//=================================================================================================================//

void Empresa::print_available_courts(Date d, Period p) {

}

//=================================================================================================================//

void Empresa::print_court_schedule(int court, Date d) {

}

//=================================================================================================================//

void Empresa::print_day_schedule(Date d) {

}

//=================================================================================================================//

void Empresa::import_file() {

}

//=================================================================================================================//

void Empresa::import_file(string file) {

}

//=================================================================================================================//

void Empresa::save_file() {

}

//=================================================================================================================//

void Empresa::save_file(string file) {

}

//=================================================================================================================//

bool Empresa::file_exists(const fs::path & dir_path, const string file_name){
	if (!exists(dir_path)) return false;
	fs::directory_iterator end_it;

	for (fs::directory_iterator it(dir_path); it != end_it; it++)
	{
		if (it->path().filename() == file_name)
		{
			return true;
		}
	}
	return false;
}

//=================================================================================================================//
