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
		oss << "Company" << setw(4) << number;
		name = oss.str();
	}

	filename = name;
	date = Date();
}

//=================================================================================================================//

Empresa::Empresa(string file) {
	fs::path initial = fs::current_path();

	if (!file_exists(initial, file)) {
		cout << "File name already used!" << endl;
	}
	else {
		filename = file;
		date = Date();
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
		oss << setfill('0') << setw(4) << number;
		name = oss.str();
	}

	filename = name;
	this->date = date;
}

//=================================================================================================================//

Empresa::Empresa(Date date, string file) {
	fs::path initial = fs::current_path();

	if (!file_exists(initial, file)) {
		cout << "File name already used!" << endl;
	}
	else {
		filename = file;
		this->date = date;
	}
}

//=================================================================================================================//

void Empresa::set_filename(string filename) {
	fs::path initial = fs::current_path();

	if (!file_exists(initial, filename)) {
		cout << "File name already used!" << endl;
	}
	else {
		this->filename = filename;
	}
}

//=================================================================================================================//

int Empresa::find_user(id_t id) const {
	if (exists_user(id)) {
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

	if (ids.size() == 0) {
		throw InexistentObject("User");
	} else if (ids.size() > 1) {
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

	if (ids.size() == 0) {
		throw InexistentObject("User");
	} else if (ids.size() > 1) {
		throw SameName(nome, ids);
	}

	return ids.at(0);
}

//=================================================================================================================//

int Empresa::find_court(id_t id) const {
	if (exists_court(id)) {
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

bool Empresa::exists_user(id_t id) const {

	for (size_t t = 0; t < utentes.size(); t++) {
		if (utentes.at(t).get_id == id) {
			return true;
		}
	}

	return false;
}

//=================================================================================================================//
	
bool Empresa::exists_user(string nome) const {

	for (size_t t = 0; t < utentes.size(); t++) {
		if (utentes.at(t).get_name == nome) {
			return true;
		}
	}

	return false;
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
	for (size_t t = 0; t < professores.size(); t++) {
		if (professores.at(t).get_name == nome) {
			return true;
		}
	}

	return false;
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

void Empresa::add_utente(string nome, bool card){
	int pos = -1;
	User u(nome, card);

	for (size_t t = 0; t < utentes.size(); t++) {
		 if (utentes.at(t) < u) {
			pos = t + 1;
			}
	}
	

	utentes.insert(utentes.begin() + pos, u);
}

//=================================================================================================================//

void Empresa::remove_utente(int id) {

	if (exists_user(id)) {
		utentes.erase(utentes.begin() + find_user(id));
	}

	throw InexistentObject("User");
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

	if (exists_user(id)) {
		out << (utentes.at(find_user(id))).get_schedule(date_init, date_fin) << "\n";
	}
	else {
		throw InexistentObject("User");
	}	
}

//=================================================================================================================//

void Empresa::print_bill(int id, ostream& out) const{

	if (exists_user(id)) {
		out << (utentes.at(find_user(id))).get_bill(date) << "\n";
	}
	else {
		throw InexistentObject("User");
	}
}

//=================================================================================================================//

int Empresa::get_debt(int id) const{
	if (exists_user(id)) {
		return (utentes.at(find_user(id))).get_debt();
	}
	else {
		throw InexistentObject("User");
	}
}

//=================================================================================================================//

void Empresa::pay_debt(int id) {
	if (exists_user(id)) {
		(utentes.at(find_user(id))).pay_debt();
	}
	else {
		throw InexistentObject("User");
	}
}

//=================================================================================================================//

void Empresa::schedule_free_use(id_t user_id, id_t court_id, Period periodo, Date data){



}

//=================================================================================================================//

void Empresa::schedule_class(id_t user_id, id_t teacher_id, id_t court_id, Period periodo, Date data) {

}

//=================================================================================================================//

void Empresa::attend_class(id_t user_id, id_t class_id) {

}

//=================================================================================================================//

void Empresa::cancel_use(id_t user_id, id_t class_id) {

}

//=================================================================================================================//

void Empresa::add_prof(string nome) {
	int pos = -1;
	Teacher T(nome);

	for (size_t t = 0; t < professores.size(); t++) {
		if (professores.at(t) < T) {
			pos = t + 1;
		}
	}

	professores.insert(professores.begin() + pos, T);
}

//=================================================================================================================//

void Empresa::remove_prof(id_t id) {
	if (exists_teacher(id)) {
		utentes.erase(utentes.begin() + find_teacher(id));
	}

	throw InexistentObject("Teacher");
}

//=================================================================================================================//

void Empresa::give_class(id_t id, Class *a) {

	if (exists_teacher(id)) {
		professores.at(find_teacher(id)).add_class(a);
	}
	else {
		throw InexistentObject("Teacher");
	}
}

//=================================================================================================================//

void Empresa::list_profs(ostream& out) const{
	for (auto it = professores.begin(); it != professores.end(); it++)
		out << it->get_info() << '\n';
}

//=================================================================================================================//

void Empresa::print_prof_schedule(int id, ostream& out) const{
	Date date_init = date;
	Date date_fin = date;
	for (int i = 0; i < 7; i++)
		date_fin++;

	if (exists_teacher(id)) {
		out << (professores.at(find_user(id))).get_schedule(date_init, date_fin) << "\n";
	}
	else {
		throw InexistentObject("Teacher");
	}
}

//=================================================================================================================//

void Empresa::add_court(size_t capacity) {
	int pos = -1;
	Court C(capacity);

	for (size_t t = 0; t < professores.size(); t++) {
		if (campos.at(t) < C) {
			pos = t + 1;
		}
	}
	
	campos.insert(campos.begin() + pos, C);
}

//=================================================================================================================//

void Empresa::remove_court(id_t id) {
	if (exists_court(id)) {
		campos.erase(campos.begin() + find_court(id));
	}

	throw InexistentObject("Court");
}

//=================================================================================================================//

void Empresa::print_available_courts(Date d) {

}

//=================================================================================================================//

void Empresa::print_available_courts(Date d, Period p) {

}

//=================================================================================================================//

void Empresa::print_court_schedule(id_t id, Date d) {

}

//=================================================================================================================//

void Empresa::print_day_schedule(Date d) {

}

//=================================================================================================================//

void Empresa::import_file(string filename) {

}

//=================================================================================================================//

void Empresa::save_file() {

}

//=================================================================================================================//

void Empresa::save_file(string filename) {

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
