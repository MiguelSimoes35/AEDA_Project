#include "empresa.h"


//   -----------------------------------   //
//   --- Member Function Definitions ---   //
//   -----------------------------------   //


//==================================================== Empresa ============================================================//

//================== PRIVATE ==================//

void Empresa::import_user_uses(istream &line) {
	string temp;
	getline(line, temp, ';');
	User *u = &(utentes[find_user(stoul(temp))]);
	while (getline(line, temp, ';')) {
		u->add_use(usos[find_use(stoul(temp))]);
	}
}


void Empresa::import_teacher_classes(istream &line) {
	string temp;
	getline(line, temp, ';');
	Teacher *t = &(professores[find_teacher(stoul(temp))]);
	while (getline(line, temp, ';')) {
		t->add_class(&(aulas[find_class(stoul(temp))]));
	}
}


void Empresa::import_court_free_uses(istream &line) {
	string temp;
	getline(line, temp, ';');
	Court *c = &(campos[find_court(stoul(temp))]);
	while (getline(line, temp, ';')) {
		c->add_free_use(dynamic_cast<Free_Use*>(usos[find_use(stoul(temp))]));
	}
}


void Empresa::import_class_externals(istream &line) {
	string temp;
	getline(line, temp, ';');
	Class *c = &(aulas[find_class(stoul(temp))]);
	getline(line, temp, ';');
	c->set_court(&(campos[find_court(stoul(temp))]));
	getline(line, temp, ';');
	c->set_teacher(&(professores[find_teacher(stoul(temp))]));
}


void Empresa::import_class_attendances(istream &line) {

	string temp;
	getline(line, temp, ';');
	Class *c = &(aulas[find_class(stoul(temp))]);
	while (getline(line, temp, ';')) {
		c->add_attendance(dynamic_cast<Class_Attendance*>(usos[find_use(stoul(temp))]));
	}
}


void Empresa::import_free_use_externals(istream &line) {
	string temp;
	getline(line, temp, ';');
	auto * u = dynamic_cast<Free_Use*>(usos[find_use(stoul(temp))]);
	getline(line, temp, ';');
	u->set_user(&(utentes[find_user(stoul(temp))]));
	getline(line, temp, ';');
	u->set_court(&(campos[find_court(stoul(temp))]));
}


void Empresa::import_class_a_externals(istream &line) {
	string temp;
	getline(line, temp, ';');
	auto * u = dynamic_cast<Class_Attendance*>(usos[find_use(stoul(temp))]);
	getline(line, temp, ';');
	u->set_user(&(utentes[find_user(stoul(temp))]));
	getline(line, temp, ';');
	u->set_court(&(campos[find_court(stoul(temp))]));
	getline(line, temp, ';');
	u->set_class(&(aulas[find_class(stoul(temp))]));
}


void Empresa::import_line(istream &line) {
	string head;
	getline(line, head, ':');
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
	getline(s, temp, ',');
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
		getline(s, temp, ',');
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
	getline(s, temp, ',');
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


//================== PUBLIC ==================//


Empresa::Empresa() {
	filename = "empresa_sem_nome.company";
	date = Date();
}


Empresa::Empresa(string file) {
	filename = file;
	date = Date();
}


Empresa::Empresa(Date date) {
	filename = "empresa_sem_nome.company";
	this->date.set_date(date.get_year(), date.get_month(), date.get_day());
}


Empresa::Empresa(Date date, string file) {
	filename = file;
	this->date.set_date(date.get_year(), date.get_month(), date.get_day());
}


void Empresa::set_filename(string filename) {
	this->filename = filename;
}


void Empresa::import_file(string filename) {
	ifstream file(filename);
	string temp;
	stringstream s;
	getline(file, temp); s = stringstream(temp);
	getline(s, temp, ':'); date = Date(s);
	while (getline(file, temp)) {
		cout << temp << endl;
		s = stringstream(temp);
		import_line(s);
	}
}


void Empresa::save_file() const {
	save_file(filename);
}


void Empresa::save_file(string filename) const {
	ofstream file;
	file.open(filename);
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


void Empresa::print_day_schedule(Date d) {

	for (auto it = campos.begin(); it != campos.end(); it++) {
		if (it->check_on_day(d)) {
			cout << it->get_info();
			cout << it->list_classes(d, d++);
			cout << it->list_free_uses(d, d++);
		}
	}
}


string Empresa::get_date() {
	string data = to_string(date.get_day()) + '/' + to_string(date.get_month()) + '/' + to_string(date.get_year());


	return data;
}


void Empresa::increment_date() {
	date = date++;
	update_repairs();
}


//====================================================== USER =============================================================//


void Empresa::add_utente(string nome, bool card) {
	int pos = -1;
	User u(nome, card);

	utentes.push_back(u);

	sort(utentes.begin(), utentes.end());
}


void Empresa::remove_utente(int id) {

	if (exists_user(id)) {
		utentes.erase(utentes.begin() + find_user(id));
	}
	else {
		throw InexistentObject("User");
	}

}


void Empresa::print_bill(int id) const {

	if (exists_user(id)) {
		cout << (utentes.at(find_user(id))).get_bill(date) << endl;
	}
	else {
		throw InexistentObject("User");
	}

	cout << endl << " Total Debt: " << to_string((utentes.at(find_user(id))).get_debt()) << "€" << endl;
}


double Empresa::get_debt(int id) const {
	if (exists_user(id)) {
		return (utentes.at(find_user(id))).get_debt();
	}
	else {
		throw InexistentObject("User");
	}
}


void Empresa::pay_debt(int id) {
	if (exists_user(id)) {
		(utentes.at(find_user(id))).pay_debt();
	}
	else {
		throw InexistentObject("User");
	}
}


void Empresa::change_card(id_t id, bool card) {
	if (exists_user(id)) {
		(utentes.at(find_user(id))).set_gold_card(card);
	}
	else {
		throw InexistentObject("User");
	}
}


bool Empresa::get_gold_card(id_t id) {
	if (exists_user(id)) {
		return (utentes.at(find_user(id))).get_gold_card();
	}
	else {
		throw InexistentObject("User");
	}
}


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


id_t Empresa::find_user(string nome) const {
	vector<id_t> ids;

	for (size_t t = 0; t < utentes.size(); t++) {
		if (utentes.at(t).get_name() == nome) {
			ids.push_back(utentes.at(t).get_id());
		}
	}

	if (ids.size() == 0) {
		throw InexistentObject("User");
	}
	else if (ids.size() > 1) {
		throw SameName(nome, ids);
	}

	return ids.at(0);
}


bool Empresa::exists_user(id_t id) const {

	for (size_t t = 0; t < utentes.size(); t++) {
		if (utentes.at(t).get_id() == id) {
			return true;
		}
	}

	return false;
}


bool Empresa::exists_user(string nome) const {

	for (size_t t = 0; t < utentes.size(); t++) {
		if (utentes.at(t).get_name() == nome) {
			return true;
		}
	}

	return false;
}


void Empresa::print_user_info(id_t id) const {
	if (exists_user(id)) {
		cout << utentes.at(find_user(id)).get_info() << endl;
	}
	else {
		throw InexistentObject("User");
	}
}


void Empresa::print_user_schedule(int id) const {
	Date date_init = date;
	Date date_fin = date;
	for (int i = 0; i < 7; i++)
		date_fin++;

	if (exists_user(id)) {
		cout << (utentes.at(find_user(id))).get_schedule(date_init, date_fin) << "\n";
	}
	else {
		throw InexistentObject("User");
	}
}


void Empresa::print_user_report(int id) const {
	Month month(date.get_month(), date.get_year());

	if (exists_user(id)) {
		cout << (utentes.at(find_user(id))).get_report(month) << "\n";
	}
	else {
		throw InexistentObject("User");
	}
}


void Empresa::list_utentes() const {
	for (auto it = utentes.begin(); it != utentes.end(); it++)
		cout << it->get_info() << '\n';
}

//==================================================== CLASSES ============================================================//


void Empresa::schedule_free_use(id_t user_id, id_t court_id, Period periodo) {
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
		else if (!exists_user(user_id)) {
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


void Empresa::schedule_class(id_t teacher_id, id_t court_id, Period periodo) {
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
		else {
			Teacher T("Error");
			T.dec_largestID();
			Teacher* t = &T;
			*t = professores.at(find_teacher(teacher_id));

			bool scheduled = false;

			if (!scheduled) {
				Class CL(periodo, t, c);
				Class* cl = &CL;
				c->add_class(cl);
				t->add_class(cl);
				aulas.push_back(CL);
				//sort(aulas.begin(), aulas.end());     // TODO: FIX ERROR IN SORTING CLASSES
			}
		}
	}
	else {
		throw InexistentObject("Court");
	}
}


void Empresa::attend_class(id_t user_id, id_t class_id) {
	User* us = &utentes.at(find_user(user_id));
	Class* cl = &aulas.at(find_class(class_id));

	Use * U = new Class_Attendance(us, cl);

	usos.push_back(U);
}


void Empresa::give_class(id_t id, Class *a) {

	if (exists_teacher(id)) {
		professores.at(find_teacher(id)).add_class(a);
	}
	else {
		throw InexistentObject("Teacher");
	}
}


void Empresa::cancel_use(id_t user_id, id_t use_id) {
	bool exists = false;

	for (auto it = usos.begin(); it != usos.end(); it++) {
		if ((*it)->get_id() == use_id) {
			if ((*it)->get_user()->get_id() == user_id) {
				(*it)->get_user()->rm_use(*it);
				usos.erase(it);
				exists = true;
			}
		}
	}

	if (!exists) {
		throw InexistentObject("User");
	}
}


void Empresa::cancel_class(id_t class_id) {
	bool exists = false;

	for (auto it = aulas.begin(); it != aulas.end(); it++) {
		if (it->get_id() == class_id) {
			(it->get_teacher())->rm_class(&(*it));
			aulas.erase(it);
		}
	}

	if (!exists) {
		throw InexistentObject("User");
	}
}


bool Empresa::exists_use(id_t id) const {
	for (size_t t = 0; t < usos.size(); t++) {
		if (usos.at(t)->get_id() == id) {
			return true;
		}
	}

	return false;
}


bool Empresa::exists_class(id_t id) const {
	for (size_t t = 0; t < aulas.size(); t++) {
		if (aulas.at(t).get_id() == id) {
			return true;
		}
	}

	return false;
}


id_t Empresa::find_class(Period periodo) const {

	for (auto it = aulas.begin(); it != aulas.end(); it++) {
		if (it->get_time() == periodo) {
			return it->get_id();
		}
	}

	throw(InexistentObject("Class"));
}


int Empresa::find_class(id_t id) const {
	if (exists_class(id)) {
		for (size_t t = 0; t < aulas.size(); t++) {
			if (aulas.at(t).get_id() == id) {
				return t;
			}
		}
	}
	else {
		throw InexistentObject("Class");
	}
}


id_t Empresa::find_use(Period periodo) const {
	for (auto it = usos.begin(); it != usos.end(); it++) {
		if ((*it)->get_type() == CLASS) {
			Class_Attendance* ca = dynamic_cast <Class_Attendance*> (*it);

			if (ca->get_time() == periodo) {
				return ca->get_id();
			}

		}
		else if ((*it)->get_type() == FREE) {
			Free_Use* fe = dynamic_cast <Free_Use*> (*it);

			if (fe->get_time() == periodo) {
				return fe->get_id();
			}

		}


	}

	throw(InexistentObject("Class"));
}


int Empresa::find_use(id_t id) const {
	if (exists_use(id)) {
		for (size_t t = 0; t < usos.size(); t++) {
			if (usos.at(t)->get_id() == id) {
				return t;
			}
		}
	}
	else {
		throw InexistentObject("Use");
	}
}


void Empresa::print_use_info(id_t id) const {
	if (exists_use(id)) {
		cout << (*usos.at(find_use(id))).get_info() << endl;
	}
	else {
		throw InexistentObject("Use");
	}
}


void Empresa::print_class_info(id_t id) const {
	if (exists_class(id)) {
		cout << aulas.at(find_class(id)).get_info() << endl;
	}
	else {
		throw InexistentObject("Class");
	}
}


void Empresa::list_uses() const {
	for (auto it = usos.begin(); it != usos.end(); it++) {
		if ((*it)->get_type() == CLASS) {
			Class_Attendance* ca = dynamic_cast <Class_Attendance*> (*it);
			cout << ca->get_info() << endl;
		}
		else if ((*it)->get_type() == FREE) {
			Free_Use* fe = dynamic_cast <Free_Use*> (*it);
			cout << fe->get_info() << endl;
		}
	}
}


void Empresa::list_classes() const {
	for (auto it = aulas.begin(); it != aulas.end(); it++) {
		cout << it->get_info() << endl;
	}
}


//==================================================== TEACHER ============================================================//


void Empresa::add_prof(string nome) {
	int pos = -1;
	Teacher T(nome);

	professores.push_back(T);

	sort(professores.begin(), professores.end());
}


void Empresa::remove_prof(id_t id) {
	if (exists_teacher(id)) {
		professores.erase(professores.begin() + find_teacher(id));
	}
	else {
		throw InexistentObject("Teacher");
	}
}


void Empresa::change_teacher(id_t teacher_id, id_t class_id) {
	for (auto it = aulas.begin(); it != aulas.end(); it++) {
		if (it->get_id() == class_id) {
			it->get_teacher()->rm_class(&(*it));

			it->set_teacher(&(professores.at(find_teacher(teacher_id))));

			professores.at(find_teacher(teacher_id)).rm_class(&(*it));
		}
	}
}


void Empresa::list_profs() const {
	for (auto it = professores.begin(); it != professores.end(); it++)
		cout << it->get_info() << '\n';
}


void Empresa::print_prof_schedule(int id) const {
	Date date_init = date;
	Date date_fin = date;
	for (int i = 0; i < 7; i++)
		date_fin++;

	if (exists_teacher(id)) {
		cout << (professores.at(find_user(id))).get_schedule(date_init, date_fin) << "\n";
	}
	else {
		throw InexistentObject("Teacher");
	}
}


bool Empresa::exists_teacher(id_t id) const {
	for (size_t t = 0; t < professores.size(); t++) {
		if (professores.at(t).get_id() == id) {
			return true;
		}
	}

	return false;
}


bool Empresa::exists_teacher(string nome) const {
	for (size_t t = 0; t < professores.size(); t++) {
		if (professores.at(t).get_name() == nome) {
			return true;
		}
	}

	return false;
}


int Empresa::find_teacher(id_t id) const {
	if (exists_teacher(id)) {
		for (size_t t = 0; t < professores.size(); t++) {
			if (professores.at(t).get_id() == id) {
				return t;
			}
		}
	}
	else {
		throw InexistentObject("Teacher");
	}
}


id_t Empresa::find_teacher(string nome) const {
	vector<id_t> ids;

	for (size_t t = 0; t < professores.size(); t++) {
		if (professores.at(t).get_name() == nome) {
			ids.push_back(professores.at(t).get_id());
		}
	}

	if (ids.size() == 0) {
		throw InexistentObject("User");
	}
	else if (ids.size() > 1) {
		throw SameName(nome, ids);
	}

	return ids.at(0);
}


void Empresa::print_teacher_info(id_t id) const {
	if (exists_teacher(id)) {
		cout << professores.at(find_teacher(id)).get_info() << endl;
	}
	else {
		throw InexistentObject("Teacher");
	}
}


//===================================================== COURT =============================================================//


void Empresa::add_court(size_t capacity) {
	int pos = -1;
	Court C(capacity);

	campos.push_back(C);

	sort(campos.begin(), campos.end());
}


void Empresa::remove_court(id_t id) {
	if (exists_court(id)) {
		campos.erase(campos.begin() + find_court(id));
	}
	else {
		throw InexistentObject("Court");
	}
}


void Empresa::change_court(id_t court_id, id_t class_id) {
	for (auto it = aulas.begin(); it != aulas.end(); it++) {
		if (it->get_id() == class_id) {
			it->get_court()->rm_class(&(*it));

			it->set_court(&(campos.at(find_court(court_id))));

			campos.at(find_court(court_id)).rm_class(&(*it));
		}
	}
}


void Empresa::list_courts() const {
	for (auto it = campos.begin(); it != campos.end(); it++) {
		cout << it->get_info() << endl;
	}
}


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


bool Empresa::exists_court(id_t id) const {
	for (size_t t = 0; t < campos.size(); t++) {
		if (campos.at(t).get_id() == id) {
			return true;
		}
	}

	return false;
}

//=================================================== TECHNICIAN ==========================================================//


void Empresa::add_technician(string name) {
	Technician T(name);

	technicians.push(T);
}


void Empresa::remove_technician(id_t id) {
	vector<Technician> auxiliar;

	while (!technicians.empty()) {
		if (technicians.top().get_id() != id)
			auxiliar.push_back(technicians.top());

		technicians.pop();
	}

	for (auto it = auxiliar.begin(); it != auxiliar.end(); it++)
		technicians.push(*it);
}


void Empresa::assign_technician(id_t court_id, int duration) {
	Technician first = technicians.top();

	technicians.pop();

	first.assign_job(court_id, duration);

	technicians.push(first);
}


void Empresa::update_repairs() {
	vector<Technician> auxiliar;
	Technician T;

	while (!technicians.empty()) {
		T = technicians.top();
		T.update_repair();

		auxiliar.push_back(T);

		technicians.pop();
	}

	for (auto it = auxiliar.begin(); it != auxiliar.end(); it++)
		technicians.push(*it);
}


void Empresa::list_technicians() {
	vector<Technician> auxiliar;
	Technician T;

	while (!technicians.empty()) {
		auxiliar.push_back(technicians.top());
		T = technicians.top();

		cout << T.get_info() << endl;
		technicians.pop();
	}

	for (auto it = auxiliar.begin(); it != auxiliar.end(); it++)
		technicians.push(*it);
}


bool Empresa::exists_technician(string name) {
	vector<Technician> auxiliar;
	bool exists;

	while (!technicians.empty()) {
		if (technicians.top().get_name() == name)
			exists = true;

		auxiliar.push_back(technicians.top());

		technicians.pop();
	}

	for (auto it = auxiliar.begin(); it != auxiliar.end(); it++)
		technicians.push(*it);

	return exists;
}


/**
* @brief Searches the priority queue technicians for the technician,
* if it finds it, it returns true, false otherwise.
*
* @param id  	Id of the technician to be found
*
* @return bool  Boolean indicating if it found it or not
*/
bool Empresa::exists_technician(id_t id) {
	vector<Technician> auxiliar;
	bool exists;

	while (!technicians.empty()) {
		if (technicians.top().get_id() == id)
			exists = true;

		auxiliar.push_back(technicians.top());

		technicians.pop();
	}

	for (auto it = auxiliar.begin(); it != auxiliar.end(); it++)
		technicians.push(*it);

	return exists;
}
