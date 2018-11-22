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

void Empresa::schedule_free_use(id_t user_id, id_t court_id, Period periodo){
	bool exists = false;
	bool full = false;
	Court* c;

	for (auto it = campos.begin(); it != campos.end(); it++) {
		if (it->get_id() == court_id) {
			exists = true;
			*c = (*it);
			if (it->check_on_going(periodo)) {
				full = true;
				break;
			}
			else {
				break;
			}
		}
	}

	if (exists) {
		if (full) {
			throw CourtIsFull(court_id, periodo);
		}
		else if (periodo.get_blocks() < 1 || periodo.get_blocks() > 4) {
			throw InvalidPeriod(periodo.get_hour(), periodo.get_min(), periodo.get_blocks());
		}
		else if(!exists_user(user_id)){
			throw InexistentObject("User");
		}
		else {
			User* u;
			*u = utentes.at(find_user(user_id));
			Free_Use F(u, periodo, c);
			Free_Use* f;
			*f = F;
			u->add_use(f);
			c->add_free_use(f);
			usos.push_back(f);
			sort(usos.begin(), usos.end());
		}
	}
	else {
		throw InexistentObject("Court");
	}
}

//=================================================================================================================//

void Empresa::schedule_class(id_t user_id, id_t teacher_id, id_t court_id, Period periodo) {
	bool exists = false;
	bool full = false;
	Court* c;

	for (auto it = campos.begin(); it != campos.end(); it++) {
		if (it->get_id() == court_id) {
			exists = true;
			*c = (*it);
			if (it->check_on_going(periodo) && it->get_available_capacity(periodo) == 0) {
				full = true;
				break;
			}
			else {
				break;
			}
		}
	}

	if (exists) {
		if (full) {
			throw CourtIsFull(court_id, periodo);
		}
		else if (periodo.get_blocks() < 1 || periodo.get_blocks() > 4) {
			throw InvalidPeriod(periodo.get_hour(), periodo.get_min(), periodo.get_blocks());
		}
		else if (!exists_user(user_id)) {
			throw InexistentObject("User");
		}
		else {
			User* u;
			*u = utentes.at(find_user(user_id));
			Teacher* t;
			*t = professores.at(find_teacher(teacher_id));
			Class C(t, periodo, c);
			Class* cl;
			*cl = C;
			Class_Attendance CA(u, cl);
			Class_Attendance* ca;
			*ca = CA;
			cl->add_attendance(ca);
			u->add_use(ca);
			c->add_class(cl);
			usos.push_back(ca);
			sort(usos.begin(), usos.end());
		}
	}
	else {
		throw InexistentObject("Court");
	}
}

//=================================================================================================================//

void Empresa::attend_class(id_t user_id, id_t class_id) {
	bool exists = false;
	Class_Attendance* ca;

	for (auto it = usos.begin(); it != usos.end(); it++) {
		if ((*it)->get_id() == class_id) {
			exists = true;
			ca = dynamic_cast <Class_Attendance*> (*it);
		}
	}

	if (exists) {
		(ca->get_class())->rm_attendance(ca);
		ca->set_grade(rand() % 100 + 1);
	}
}

//=================================================================================================================//

void Empresa::cancel_use(id_t user_id, id_t class_id) {
	bool exists = false;
	Class_Attendance* ca;
	vector<Use*>::iterator rem;

	for (auto it = usos.begin(); it != usos.end(); it++) {
		if ((*it)->get_id() == class_id) {
			exists = true;
			ca = dynamic_cast <Class_Attendance*> (*it);
			rem = it;
		}
	}

	if (exists) {
		(ca->get_class())->rm_attendance(ca);
		User* u;
		*u = utentes.at(find_user(user_id));
		u->rm_use(ca);
		usos.erase(rem);
	}
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
	int num = 0;
	Period p(d, 0, 0, 48);

	for (auto it = campos.begin(); it != campos.end(); it++) {
		if (!it->check_on_day(d) || it->get_available_capacity(p) > 0) {
			cout << it->get_info();
			num++;
		}
	}

	if (num == 1) {
		cout << " There is " << num << " available court.\n\n";
	}
	else if (num > 1) {
		cout << " There are " << num << " available courts.\n\n";
	}
	else {
		cout << " There are no available courts...\n\n";
	}
}

//=================================================================================================================//

void Empresa::print_available_courts(Period p) {
	int num = 0;

	for (auto it = campos.begin(); it != campos.end(); it++) {
		if (!it->check_on_going(p) || it->get_available_capacity(p) > 0) {
			cout << it->get_info();
			num++;
		}
	}

	if (num == 1) {
		cout << " There is " << num << " available court.\n\n";
	}
	else if (num > 1) {
		cout << " There are " << num << " available courts.\n\n";
	}
	else {
		cout << " There are no available courts...\n\n";
	}
}

//=================================================================================================================//

void Empresa::print_court_schedule(id_t id, Date d) {
	bool exists = false;

	for (auto it = campos.begin(); it != campos.end(); it++) {
		if (it->get_id() == id) {
			cout << it->list_classes(d, d++);
			cout << it->list_free_uses(d, d++);
			exists = true;
			break;
		}
	}

	if (!exists) {
		throw InexistentObject("Court");
	}
}

//=================================================================================================================//

void Empresa::print_day_schedule(Date d) {

	for (auto it = campos.begin(); it != campos.end(); it++) {
		if (it->check_on_day(d)) {
			cout << it->get_info();
			cout << it->list_classes(d, d++);
			cout << it->list_free_uses(d, d++);
		}
	}
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
