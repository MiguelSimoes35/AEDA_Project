#include "empresa.h"


									//   -----------------------------------   //
									//   --- Member Function Definitions ---   //
									//   -----------------------------------   //


//==================================================== Empresa ============================================================//

//================== PRIVATE ==================//


void Empresa::import_user_uses(istream &line) {
	string temp;
	getline(line, temp, ';');
	User *u = find_user(temp).get_ptr();
	while (getline(line, temp, ';')) {
		u->add_use(usos[find_use(stoul(temp))]);
	}
}


void Empresa::import_teacher_classes(istream &line) {
	string temp;
	getline(line, temp, ';');
	Teacher *t = (*professores.find(dummie_teacher(temp))).get_ptr();
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
	c->set_teacher((*professores.find(dummie_teacher(temp))).get_ptr());
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
	u->set_user(find_user(temp).get_ptr());
	getline(line, temp, ';');
	u->set_court(&(campos[find_court(stoul(temp))]));
}


void Empresa::import_class_a_externals(istream &line) {
	string temp;
	getline(line, temp, ';');
	auto * u = dynamic_cast<Class_Attendance*>(usos[find_use(stoul(temp))]);
	getline(line, temp, ';');
	u->set_user(find_user(temp).get_ptr());
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
			//utentes.emplace(line); // TODO: Doesn't know hot to import from the given string
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
			break;
		case ATTRIBUTES:
			professores.emplace(TeacherPtr(&Teacher(line)));
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


UserPtr Empresa::dummie_user(string name) {
	User user(name);
	return UserPtr(&user);
}


TeacherPtr Empresa::dummie_teacher(string name) {
	Teacher teacher(name); // TODO : Possibily need to use <new>
	return TeacherPtr(&teacher);
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
	file << Court::export_globals() << "\n";
	file << Class::export_globals() << "\n";
	file << Use::export_globals() << "\n";
	for (auto it = utentes.begin(); it != utentes.end(); it++) {
		file << it->get_ptr()->export_attributes() << "\n";
	}
	for (auto it = professores.begin(); it != professores.end(); it++) {
		file << (*it).get_ptr()->export_attributes() << "\n";
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
		file << it->get_ptr()->export_uses() << "\n";
	}
	for (auto it = professores.begin(); it != professores.end(); it++) {
		file << (*it).get_ptr()->export_classes() << "\n";
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


void Empresa::add_utente(string nome, bool card, string address, unsigned NIF) {
	User* user = new User(nome, address, NIF, card);
	UserPtr U(user);
	utentes.insert(U);
}


void Empresa::remove_utente(string name) {

	if (exists_user(name)) {
		User* U = find_user(name).get_ptr();
		delete U;
		utentes.erase(find_user(name));
	}
	else {
		throw InexistentObject("User");
	}

}


void Empresa::print_bill(string name) const {

	if (exists_user(name)) {
		cout << find_user(name).get_ptr()->get_bill(date) << endl;
	}
	else {
		throw InexistentObject("User");
	}

	cout << endl << " Total Debt: " << to_string(find_user(name).get_ptr()->get_debt()) << "�" << endl;
}


double Empresa::get_debt(string name) const {
	if (exists_user(name)) {
		return (find_user(name).get_ptr()->get_debt());
	}
	else {
		throw InexistentObject("User");
	}
}


void Empresa::pay_debt(string name) {
	if (exists_user(name)) {
		UserPtr U = find_user(name);
		utentes.erase(find_user(name).get_ptr());
		U.get_ptr()->pay_debt();
		utentes.insert(U);
	}
	else {
		throw InexistentObject("User");
	}
}


void Empresa::change_card(string name, bool card) {
	if (exists_user(name)) {
		UserPtr U = find_user(name);
		utentes.erase(find_user(name).get_ptr());
		U.get_ptr()->set_gold_card(card);
		utentes.insert(U);
	}
	else {
		throw InexistentObject("User");
	}
}


void Empresa::change_address(string name, string address) {
	if (exists_user(name)) {
		UserPtr U = find_user(name);
		utentes.erase(find_user(name).get_ptr());
		U.get_ptr()->set_address(address);
		utentes.insert(U);
	}
	else {
		throw InexistentObject("User");
	}
}


bool Empresa::get_gold_card(string name) const {
	if (exists_user(name)) {
		return (find_user(name).get_ptr()->get_gold_card());
	}
	else {
		throw InexistentObject("User");
	}
}


UserPtr Empresa::find_user(string name) const {
	vector<User*> users;

	for (auto it = utentes.begin(); it != utentes.end(); it++) {
		if (it->get_name() == name) {
			users.push_back(it->get_ptr());
		}
	}

	if (users.size() == 0) {
		throw InexistentObject("User");
	}
	else if (users.size() > 1) {
		throw SameNameUser(name);
	}

	return UserPtr(users.at(0));
}


bool Empresa::exists_user(string name) const {

	for (auto it = utentes.begin(); it != utentes.end(); it++) {
		if (it->get_name() == name) {
			return true;
		}
	}

	return false;
}


void Empresa::print_user_info(string name) const {
	if (exists_user(name)) {
		cout << find_user(name).get_ptr()->get_info() << endl;
	}
	else {
		throw InexistentObject("User");
	}
}


void Empresa::print_user_schedule(string name) const {
	Date date_init = date;
	Date date_fin = date;
	for (int i = 0; i < 7; i++)
		date_fin++;

	if (exists_user(name)) {
		cout << find_user(name).get_ptr()->get_schedule(date_init, date_fin) << "\n";
	}
	else {
		throw InexistentObject("User");
	}
}


void Empresa::print_user_report(string name) const {
	Month month(date.get_month(), date.get_year());

	if (exists_user(name)) {
		cout << find_user(name).get_ptr()->get_report(month) << "\n";
	}
	else {
		throw InexistentObject("User");
	}
}


void Empresa::list_utentes() const {
	for (auto it = utentes.begin(); it != utentes.end(); it++)
		cout << it->get_ptr()->get_info() << '\n';
}


//==================================================== CLASSES ============================================================//


void Empresa::schedule_free_use(string user_name, id_t court_id, Period periodo) {
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
		else if (!exists_user(user_name)) {
			throw InexistentObject("User");
		}
		else {
			UserPtr U = find_user(user_name);
			utentes.erase(find_user(user_name).get_ptr());

			Free_Use F(U.get_ptr() , periodo, c);
			Free_Use* f;
			f = &F;

			U.get_ptr()->add_use(f);
			c->add_free_use(f);

			utentes.insert(U);
			usos.push_back(f);
			sort(usos.begin(), usos.end());
		}
	}
	else {
		throw InexistentObject("Court");
	}
}


void Empresa::schedule_class(string teacher_name, id_t court_id, Period periodo) {
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
			TeacherPtr T = *professores.find(dummie_teacher(teacher_name));

			bool scheduled = false;

			if (!scheduled) {
				Class CL(periodo, T.get_ptr(), c);
				Class* cl = &CL;
				c->add_class(cl);
				T.get_ptr()->add_class(cl);
				aulas.push_back(CL);
				//sort(aulas.begin(), aulas.end());     // TODO: FIX ERROR IN SORTING CLASSES
			}
		}
	}
	else {
		throw InexistentObject("Court");
	}
}


void Empresa::attend_class(string user_name, id_t class_id) {
	UserPtr u = find_user(user_name);
	utentes.erase(find_user(user_name).get_ptr());
	Class* cl = &aulas.at(find_class(class_id));

	Use * U = new Class_Attendance(u.get_ptr(), cl);
	u.get_ptr()->add_use(U);

	utentes.insert(u);
	usos.push_back(U);
}


void Empresa::give_class(string teacher_name, Class *a) {

	if (exists_teacher(teacher_name)) {
		TeacherPtr T = *professores.find(dummie_teacher(teacher_name));
		T.get_ptr()->add_class(a);
		a->set_teacher(T.get_ptr());
	}
	else {
		throw InexistentObject("Teacher");
	}
}


void Empresa::cancel_use(string user_name, id_t use_id) {
	bool exists = false;

	for (auto it = usos.begin(); it != usos.end(); it++) {
		if ((*it)->get_id() == use_id) {
			if ((*it)->get_user()->get_name() == user_name) {
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
			exists = true;
		}
	}

	if (!exists) {
		throw InexistentObject("Class");
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


void Empresa::add_prof(string name) {

	if (!exists_teacher(name)) {
		Teacher* teacher = new Teacher(name);
		TeacherPtr T(teacher);

		professores.insert(T);
	}
}


void Empresa::remove_prof(string name) {
	if (exists_teacher(name)) {
		TeacherPtr T = *professores.find(dummie_teacher(name));
		professores.erase(dummie_teacher(name));
		T.get_ptr()->change_status(false);
		professores.insert(T);
	}
	else {
		throw InexistentObject("Teacher");
	}
}


void Empresa::change_teacher(string name, id_t class_id) {
	for (auto it = aulas.begin(); it != aulas.end(); it++) {
		if (it->get_id() == class_id) {
			it->get_teacher()->rm_class(&(*it));

			TeacherPtr T = *professores.find(dummie_teacher(name));

			professores.erase(dummie_teacher(name));

			it->set_teacher(T.get_ptr());

			T.get_ptr()->add_class(&(*it));

			professores.insert(T);
		}
	}
}


void Empresa::list_profs() const {
	for (auto it = professores.begin(); it != professores.end(); it++)
		cout << it->get_ptr()->get_info() << '\n';
}


void Empresa::print_prof_schedule(string name) const {
	Date date_init = date;
	Date date_fin = date;
	for (int i = 0; i < 7; i++)
		date_fin++;

	if (exists_teacher(name)) {
		cout << (*professores.find(dummie_teacher(name))).get_ptr()->get_schedule(date_init, date_fin) << "\n";
	}
	else {
		throw InexistentObject("Teacher");
	}
}


bool Empresa::exists_teacher(string name) const {

	if (professores.find(dummie_teacher(name)) != professores.end()) {
		return true;
	}

	return false;
}


void Empresa::print_teacher_info(string name) const {
	if (exists_teacher(name)) {
		cout << (*professores.find(dummie_teacher(name))).get_ptr()->get_info() << "\n";
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


void Empresa::change_capacity(id_t id, size_t capacity) {
	if (exists_court(id)) {
		campos.at(find_court(id)).change_capacity(capacity);
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

	throw InexistentObject("Class");
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


bool Empresa::assign_technician(id_t court_id, int duration, unsigned max) {
	vector<Technician> auxiliar;
	bool assigned = false;
	Technician first = technicians.top();

	while (!technicians.empty() && !assigned){

		technicians.pop();

		if (first.get_repairs() < max){
			first.assign_job(court_id, duration);
			technicians.push(first);
			assigned = true;
			break;
		}

		auxiliar.push_back(first);
	}

	for (auto it = auxiliar.begin(); it != auxiliar.end(); it++)
		technicians.push(*it);

	return assigned;
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


id_t Empresa::find_technician(string name) {
	
	if (exists_teacher(name)) {
		vector<Technician> auxiliar;
		id_t technician_id = -1;

		while (!technicians.empty()) {
			if (technicians.top().get_name() == name)
				technician_id = technicians.top().get_id();

			auxiliar.push_back(technicians.top());

			technicians.pop();
		}

		for (auto it = auxiliar.begin(); it != auxiliar.end(); it++)
			technicians.push(*it);

		return technician_id;
	}
	else {
		throw InexistentObject("Technician");
	}
}

