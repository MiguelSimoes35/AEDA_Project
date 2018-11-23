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

	throw InexistentObject("User");
	
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
	
	throw InexistentObject("Teacher");
	
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
	
	throw InexistentObject("Court");
	
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
		utentes.at(id).dec_largestID();
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

double Empresa::get_debt(int id) const{
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
	Court C(0);
	C.dec_largestID();
	Court *c = &C;

	for (auto it = campos.begin(); it != campos.end(); it++) {
		if (it->get_id() == court_id) {
			exists = true;
			*c = *it;
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
			User U("Error");
			U.dec_largestID();
			User* u = &U;
			u = &utentes.at(find_user(user_id));

			Free_Use F(u, periodo, c);
			Free_Use* f;
			f = &F;

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
	Court C(0);
	C.dec_largestID();
	Court *c = &C;

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
			User U("Error");
			U.dec_largestID();
			User* u = &U;
			*u = utentes.at(find_user(user_id));

			Teacher T("Error");
			T.dec_largestID();
			Teacher* t = &T;
			*t = professores.at(find_teacher(teacher_id));

			Class CL(t, periodo, c);
			Class* cl = &CL;

			Class_Attendance CA(u, cl);
			Class_Attendance* ca = &CA;

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
	Class_Attendance* ca;

	for (auto it = usos.begin(); it != usos.end(); it++) {
		if ((*it)->get_id() == class_id) {
			ca = dynamic_cast <Class_Attendance*> (*it);
			ca->dec_largestID();
			(ca->get_class())->rm_attendance(ca);
			ca->set_grade(rand() % 100 + 1);
			break;
		}
	}
}

//=================================================================================================================//

void Empresa::cancel_use(id_t user_id, id_t class_id) {
	Class_Attendance* ca;

	for (auto it = usos.begin(); it != usos.end(); it++) {
		if ((*it)->get_id() == class_id) {
			ca = dynamic_cast <Class_Attendance*> (*it);
			(ca->get_class())->rm_attendance(ca);
			User* u;
			u = &utentes.at(find_user(user_id));
			u->dec_largestID();
			u->rm_use(ca);
			usos.erase(it);
		}
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
		professores.at(id).dec_largestID();
		professores.erase(professores.begin() + find_teacher(id));
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

	for (size_t t = 0; t < campos.size(); t++) {
		if (campos.at(t) < C) {
			pos = t + 1;
		}
	}
	
	campos.insert(campos.begin() + pos, C);
}

//=================================================================================================================//

void Empresa::remove_court(id_t id) {
	if (exists_court(id)) {
		campos.at(id).dec_largestID();
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
