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

bool Empresa::add_utente(User *u) {
	bool exists = false;
	int pos = -1;

	for (size_t t = 0; t < utentes.size(); t++) {
		if (utentes.at(t) == u) {
			exists = true;
		}
		else if (utentes.at(t) < u) {
			pos = t + 1;
		}
	}

	if (exists)
		return false;

	utentes.insert(utentes.begin() + pos, u);

	return true;
}

//=================================================================================================================//

bool Empresa::remove_utente(int id) {
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
		return true;
	}

	return false;
}

//=================================================================================================================//

bool Empresa::remove_utente(string nome) {
	bool exists = false;
	int pos = -1;

	for (size_t t = 0; t < utentes.size(); t++) {
		if (utentes.at(t).get_name == nome) {
			exists = true;
			pos = t;
		}
	}

	if (exists) {
		utentes.erase(utentes.begin() + pos);
		return true;
	}

	return false;
}

//=================================================================================================================//

bool Empresa::exists_utente(int id) {

	for (size_t t = 0; t < utentes.size(); t++) {
		if (utentes.at(t).get_id == id) {
			return true;
		}
	}

	return false;
}

//=================================================================================================================//

bool Empresa::exists_utente(string nome) {

	for (size_t t = 0; t < utentes.size(); t++) {
		if (utentes.at(t).get_name == nome) {
			return true;
		}
	}

	return false;
}

//=================================================================================================================//

void Empresa::list_utentes() {

}

//=================================================================================================================//

void Empresa::print_user_schedule(int id) {
	
}

//=================================================================================================================//

void Empresa::print_user_schedule(string nome) {

}

//=================================================================================================================//

void Empresa::print_bill(int id) {
	bool exists = false;
	int pos = -1;
	string bill;

	for (size_t t = 0; t < utentes.size(); t++) {
		if (utentes.at(t).get_id == id) {
			exists = true;
			pos = t;
		}
	}

	if (exists) {
		bill = utentes.at(pos).get_bill(date.get_month());
	}

}

//=================================================================================================================//

void Empresa::print_bill(string nome) {
	bool exists = false;
	int pos = -1;
	string bill;

	for (size_t t = 0; t < utentes.size(); t++) {
		if (utentes.at(t).get_name == nome) {
			exists = true;
			pos = t;
		}
	}

	if (exists) {
		bill = utentes.at(pos).get_bill(date.get_month());
	}

	// Função que imprime a string //
}

//=================================================================================================================//

int Empresa::get_debt(int id) {
	bool exists = false;
	int pos = -1;

	for (size_t t = 0; t < utentes.size(); t++) {
		if (utentes.at(t).get_id == id) {
			exists = true;
			pos = t;
		}
	}

	if (exists) {
		return utentes.at(pos).get_debt;
	}

	return -1;
}

//=================================================================================================================//

int Empresa::get_debt(string nome) {
	bool exists = false;
	int pos = -1;
	string bill;
	
	for (size_t t = 0; t < utentes.size(); t++) {
		if (utentes.at(t).get_name == nome) {
			exists = true;
			pos = t;
		}
	}

	if (exists) {
		return utentes.at(pos).get_debt;
	}

	return -1;
}

//=================================================================================================================//

bool Empresa::pay_debt(int id) {
	bool exists = false;
	int pos = -1;

	for (size_t t = 0; t < utentes.size(); t++) {
		if (utentes.at(t).get_id == id) {
			exists = true;
			pos = t;
		}
	}

	if (exists) {
		utentes.at(pos).pay_bill(date.get_month());
		return true;
	}

	return false;
}

//=================================================================================================================//

bool Empresa::pay_debt(string nome) {
	bool exists = false;
	int pos = -1;
	string bill;

	for (size_t t = 0; t < utentes.size(); t++) {
		if (utentes.at(t).get_name == nome) {
			exists = true;
			pos = t;
		}
	}

	if (exists) {
		utentes.at(pos).pay_bill(date.get_month());
		return true;
	}

	return false;
}

//=================================================================================================================//

bool Empresa::schedule_use() {

}

//=================================================================================================================//

bool Empresa::cancel_use() {

}

//=================================================================================================================//

bool Empresa::add_prof(Teacher *p) {
	bool exists = false;
	int pos = -1;

	for (size_t t = 0; t < professores.size(); t++) {
		if (professores.at(t) == p) {
			exists = true;
		}
		else if (professores.at(t) < p) {
			pos = t + 1;
		}
	}

	if (exists)
		return false;

	professores.insert(professores.begin() + pos, u);

	return true;
}

//=================================================================================================================//

bool Empresa::remove_prof(Teacher *p) {
	bool exists = false;
	int pos = -1;

	for (size_t t = 0; t < professores.size(); t++) {
		if (professores.at(t) == p) {
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

	for (size_t t = 0; t < professores.size(); t++) {
		if (professores.at(t) == p) {
			exists = true;
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
