#include "empresa.h"


//==================================================== Empresa ===========================================================//

									//   -----------------------------------   //
									//   --- Member Function Definitions ---   //
									//   -----------------------------------   //



void Empresa::import_line(istream &line) { //TODO
	string head;
	getline(line,head,':');
	header h = parse_header(head);
	switch (h.c) {
		case USER:
			switch (h.l) {
				case GLOBALS:
					User::set_globals(line);
				case ATTRIBUTES:
					utentes.emplace_back(line);
					break;
				case USES:
					import_user_uses(line);
					break;
				default:
					throw "Not implemented";
			}
			break;
		case TEACHER:
			switch (h.l) {
				case GLOBALS:
					Teacher::set_globals(line);
					break;
				case ATTRIBUTES:
					professores.emplace_back(line);
					break;
				case CLASSES:
					import_teacher_classes(line);
					break;
				default:
					throw "Not implemented";
			}
			break;
		case COURT:
			switch (h.l) {
				case GLOBALS:
					Court::set_globals(line);
					break;
				case ATTRIBUTES:
					campos.emplace_back(line);
					break;
				case CLASSES:
					import_court_free_uses(line);
					break;
				case FREE_USES:
					break;
				default:
					throw "Not implemented";
			}
			break;
		case CLASS:
			switch (h.l) {
				case GLOBALS:
					Class::set_globals(line);
					break;
				case ATTRIBUTES:
					aulas.emplace_back(line);
					break;
				case EXTERNALS:
					import_class_externals(line);
					break;
				case ATTENDANCES:
					import_class_attendances(line);
					break;
				default:
					throw "Not implemented";
			}
			break;
		case USE:
			if (h.l == GLOBALS) {
				Use::set_globals(line);
			}
			else {
				switch (h.u) {
					case ABSTRACT:
						throw "An object of abstract type use is being instantiated";
					case FREE:
						switch (h.l) {
							case ATTRIBUTES:
								usos.push_back(new Free_Use(line));
								break;
							case EXTERNALS:
								import_free_use_externals(line);
								break;
							default:
								throw "Not implemented";
						}
						break;
					case CLASS_A:
						switch (h.l) {
							case ATTRIBUTES:
								usos.push_back(new Class_Attendance(line));
								break;
							case EXTERNALS:
								import_class_a_externals(line);
								break;
							default:
								throw "Not implemented";
						}
						break;
					default:
						throw "Not implemented";
				}
			}
			break;
		default:
			throw "Something went wrong";
	}

}

Empresa::header Empresa::parse_header(const string &h) {
	stringstream s(h);
	string temp;
	Empresa::header out;
	getline(s,temp,',');
	out.u = NOT;
	if (temp == "user") {
		out.c = USER;
	}
	else if (temp == "teacher") {
		out.c = TEACHER;
	}
	else if (temp == "court") {
		out.c = COURT;
	}
	else if (temp == "class") {
		out.c = CLASS;
	}
	else {
		out.c = USE;
		getline(s,temp,',');
		if (temp == "ABSTRACT") {
			out.u = ABSTRACT;
		}
		else if (temp == "FREE") {
			out.u = FREE;
		}
		else if (temp == "CLASS") {
			out.u = CLASS_A;
		}
	}
	getline(s,temp,',');
	if (temp == "globals") {
		out.l = GLOBALS;
	}
	else if (temp == "attributes") {
		out.l = ATTRIBUTES;
	}
	else if (temp == "externals") {
		out.l = EXTERNALS;
	}
	else if (temp == "uses") {
		out.l = USES;
	}
	else if (temp == "classes") {
		out.l = CLASSES;
	}
	else if (temp == "free_uses") {
		out.l = FREE_USES;
	}
	else {
		out.l = ATTENDANCES;
	}
	return out;
}

void Empresa::import_file(string filename) {
	ifstream file(filename);
	string temp;
	stringstream s;
	while(getline(file,temp)) {
		s = stringstream(temp);
		import_line(s);
	}
}

void Empresa::save_file() const {
	ofstream file(filename);
	file << "date:" << date.get_export() << ";\n";
	file << User::export_globals() << "\n";
	file << Teacher::export_globals() << "\n";
	file << Court::export_globals() << "\n";
	file << Class::export_globals() << "\n";
	file << Use::export_globals() << "\n";
	for (auto it = utentes.begin(); it != utentes.end(); it++) {
		file << it->export_attributes() << "\n";
	}
	for (auto it = professores.begin(); it != professores.end(); it++) {
		file << it->export_attributes() << "\n";
	}
	for (auto it = campos.begin(); it != campos.end(); it++) {
		file << it->export_attributes() << "\n";
	}
	for (auto it = aulas.begin(); it != aulas.end(); it++) {
		file << it->export_attributes() << "\n";
	}
	for (auto it = usos.begin(); it != usos.end(); it++) {
		file << (*it)->export_attributes() << "\n";
	}
	for (auto it = utentes.begin(); it != utentes.end(); it++) {
		file << it->export_uses() << "\n";
	}
	for (auto it = professores.begin(); it != professores.end(); it++) {
		file << it->export_classes() << "\n";
	}
	for (auto it = campos.begin(); it != campos.end(); it++) {
		file << it->export_classes() << "\n";
		file << it->export_free_uses() << "\n";

	}
	for (auto it = aulas.begin(); it != aulas.end(); it++) {
		file << it->export_externals() << "\n";
		file << it->export_attendances() << "\n";
	}
	for (auto it = usos.begin(); it != usos.end(); it++) {
		file << (*it)->export_externals() << "\n";
	}
}

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
		if (utentes.at(t).get_name() == nome) {
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
		if (professores.at(t).get_name() == nome) {
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
		if (utentes.at(t).get_id() == id) {
			return true;
		}
	}

	return false;
}

//=================================================================================================================//
	
bool Empresa::exists_user(string nome) const {

	for (size_t t = 0; t < utentes.size(); t++) {
		if (utentes.at(t).get_name() == nome) {
			return true;
		}
	}

	return false;
}

//=================================================================================================================//

bool Empresa::exists_teacher(id_t id) const {
	for (size_t t = 0; t < professores.size(); t++) {
		if (professores.at(t).get_id() == id) {
			return true;
		}
	}

	return false;
}

//=================================================================================================================//

bool Empresa::exists_teacher(string nome) const {
	for (size_t t = 0; t < professores.size(); t++) {
		if (professores.at(t).get_name() == nome) {
			return true;
		}
	}

	return false;
}

//=================================================================================================================//

bool Empresa::exists_court(id_t id) const {
	for (size_t t = 0; t < campos.size(); t++) {
		if (campos.at(t).get_id() == id) {
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

void Empresa::save_file() {
	save_file(filename);
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
