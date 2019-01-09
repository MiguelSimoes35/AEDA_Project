#include "empresa.h"


									//   -----------------------------------   //
									//   --- Member Function Definitions ---   //
									//   -----------------------------------   //


//==================================================== Empresa ============================================================//

//================== PRIVATE ==================//


UserPtr Empresa::dummie_user(string name) {
	User* u = new User(name);
	return UserPtr(u);
}


TeacherPtr Empresa::dummie_teacher(string name) {
	Teacher* t = new Teacher(name);
	return TeacherPtr(t);
}

void Empresa::remove_dependent_objects(Court *court) {
	id_t court_id = court->get_id();
	vector<Technician> tech_aux;
	while (!technicians.empty()) {
		Technician technician = technicians.top();
		technicians.pop();
		technician.cancel_job(court_id);
		tech_aux.push_back(technician);
	}
	technicians = priority_queue<Technician>(tech_aux.begin(), tech_aux.end());

	vector<id_t> class_aux;
	for (auto it = court->classes.begin(); it != court->classes.end(); it++) {
		class_aux.push_back((*it)->get_id());
	}
	for (auto it = class_aux.begin(); it != class_aux.end(); it++) {
		cancel_class(*it);
	}

	for (auto it = court->free_uses.begin(); it != court->free_uses.end(); it++) {
		Free_Use *use = *it;
		use->get_user()->rm_use(use);
		usos.erase(find(usos.begin(), usos.end(), use));
		delete use;
		court->free_uses.erase(it);
	}
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
	cout << "Not implemented" << endl;
}


void Empresa::save_file() const {
	save_file(filename);
}


void Empresa::save_file(string filename) const {
	ofstream file;
	file.open(filename);
	file << "Not implemented" << endl << endl;
	file.close();
}


void Empresa::print_day_schedule(Date d) {

	for (auto it = campos.begin(); it != campos.end(); it++) {
		if ((*it)->check_on_day(d)) {
			cout << (*it)->get_info();
			cout << (*it)->list_classes(d, ++d);
		}
	}
}


string Empresa::get_date() {
	string data = to_string(date.get_day()) + '/' + to_string(date.get_month()) + '/' + to_string(date.get_year());

	return data;
}


void Empresa::increment_date() {
	date++;
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
		utentes.erase(find_user(name));
		delete U;

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
	bool full = false;

	auto it = campos.begin();
	for (; it != campos.end(); it++) {
		if ((*it)->get_id() == court_id) {
			if ((*it)->check_on_going(periodo) && (*it)->get_available_capacity(periodo) == 0) {
				full = true;
			}
			break;
		}
	}

	if (it != campos.end()) {
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
			UserPtr user = find_user(user_name);
			utentes.erase(find_user(user_name).get_ptr());

			Free_Use *use = new Free_Use(user.get_ptr(), periodo, *it);
			user.get_ptr()->add_use(use);
			(*it)->add_free_use(use);

			utentes.insert(user);
			usos.push_back(use);			
		}
	}
	else {
		throw InexistentObject("Court");
	}
}


void Empresa::schedule_class(string teacher_name, id_t court_id, Period periodo) {
	bool full = false;

	auto it = campos.begin();
	for (; it != campos.end(); it++) {
		if ((*it)->get_id() == court_id) {
			if ((*it)->check_on_going(periodo) && (*it)->get_available_capacity(periodo) == 0) {
				full = true;
			}
			break;
		}
	}

	if (it != campos.end()) {
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
				Class *CL = new Class(periodo, T.get_ptr(), *it);
				aulas.push_back(CL);
				(*it)->add_class(CL);
				T.get_ptr()->add_class(CL);
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
	Class* cl = aulas.at(find_class(class_id));

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
	for (auto it = usos.begin(); it != usos.end(); it++) {
		if ((*it)->get_id() == use_id) {
			if ((*it)->get_user()->get_name() == user_name) {
				Use *use = *it;
				use->get_user()->rm_use(use);
				if (use->get_type() == CLASS) {
					Class_Attendance *p = dynamic_cast<Class_Attendance*>(use);
					p->get_class()->rm_attendance(p);
				}
				else if (use->get_type() == FREE) {
					Free_Use *p = dynamic_cast<Free_Use*>(use);
					p->get_court()->rm_free_use(p);
				}
				usos.erase(it);
				delete use;
				return;
			}
			throw InexistentObject("User");
		}
	}
	throw InexistentObject("Use");
}


void Empresa::cancel_class(id_t class_id) {
	for (auto it = aulas.begin(); it != aulas.end(); it++) {
		if ((*it)->get_id() == class_id) {
			Class *c = *it;
			vector<Class_Attendance*> attendances = c->get_attendances();
			for (auto i = attendances.begin(); i != attendances.end(); i++) {
				Class_Attendance *a = *i;
				a->get_user()->rm_use(a);
				delete a;
			}
			c->get_teacher()->rm_class(c);
			c->get_court()->rm_class(c);
			delete c;
			aulas.erase(it);
			return;
		}
	}
	throw InexistentObject("Class");
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
		if (aulas.at(t)->get_id() == id) {
			return true;
		}
	}
	return false;
}


id_t Empresa::find_class(Period periodo) const {
	for (auto it = aulas.begin(); it != aulas.end(); it++) {
		if ((*it)->get_time() == periodo) {
			return (*it)->get_id();
		}
	}
	throw(InexistentObject("Class"));
}


int Empresa::find_class(id_t id) const {
	for (size_t t = 0; t < aulas.size(); t++) {
		if (aulas.at(t)->get_id() == id) {
			return t;
		}
	}
	throw InexistentObject("Class");
}


id_t Empresa::find_use(Period periodo) const {
	for (auto it = usos.begin(); it != usos.end(); it++) {
		if ((*it)->get_time() == periodo) {
			return (*it)->get_id();
		}
	}
	throw(InexistentObject("Use"));
}


int Empresa::find_use(id_t id) const {
	for (size_t t = 0; t < usos.size(); t++) {
		if (usos.at(t)->get_id() == id) {
			return t;
		}
	}
	throw InexistentObject("Use");
}


void Empresa::print_use_info(id_t id) const {
	try {
		cout << usos.at(find_use(id))->get_info() << endl;
	}
	catch (InexistentObject e) {
		throw e;
	}
}


void Empresa::print_class_info(id_t id) const {
	try {
		cout << aulas.at(find_class(id))->get_info() << endl;
	}
	catch (InexistentObject e) {
		throw e;
	}
}


void Empresa::list_uses() const {
	for (auto it = usos.begin(); it != usos.end(); it++) {
		cout << (*it)->get_info() << endl;
	}
}


void Empresa::list_classes() const {
	for (auto it = aulas.begin(); it != aulas.end(); it++) {
		cout << (*it)->get_info() << endl;
	}
}


//==================================================== TEACHER ============================================================//


void Empresa::add_prof(string name) {

	TeacherPtr dummy = dummie_teacher(name);
	
	if (professores.find(dummy) != professores.end()) {
		dummy = *professores.find(dummy);
		dummy.get_ptr()->change_status(true);
	}
	else
		professores.insert(TeacherPtr(new Teacher(name)));
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
		Class *c = *it;
		if (c->get_id() == class_id) {
			c->get_teacher()->rm_class(c);

			TeacherPtr T = *professores.find(dummie_teacher(name));

			professores.erase(dummie_teacher(name));

			c->set_teacher(T.get_ptr());

			T.get_ptr()->add_class(c);

			professores.insert(T);
		}
	}
}


void Empresa::list_profs() const {
	for (auto it = professores.begin(); it != professores.end(); it++)
		cout << it->get_ptr()->get_info() << endl;
}


void Empresa::print_prof_schedule(string name) const {
	auto it = professores.find(dummie_teacher(name));
	if (it == professores.end()) {
		throw InexistentObject("Teacher");
	}

	Date end = date;
	for (int i = 0; i < 7; i++) {
		end++;
	}

	cout << it->get_ptr()->get_schedule(date, end) << endl;
}


bool Empresa::exists_teacher(string name) const {
	auto it = professores.find(dummie_teacher(name));
	return (it != professores.end()) && (it->get_ptr()->get_status());
}


void Empresa::print_teacher_info(string name) const {
	auto it = professores.find(dummie_teacher(name));
	if (it == professores.end()) {
		throw InexistentObject("Teacher");
	}
	cout << it->get_ptr()->get_info() << endl;
}


//===================================================== COURT =============================================================//


void Empresa::add_court(size_t capacity) {
	Court *C = new Court(capacity);
	campos.push_back(C);
}


void Empresa::remove_court(id_t id) {
	for (auto it = campos.begin(); it != campos.end(); it++) {
		Court *court = *it;
		if (court->get_id() == id) {
			remove_dependent_objects(court);
			campos.erase(it);
			delete court;
			return;
		}
	}
	throw InexistentObject("Court");
}


void Empresa::change_capacity(id_t id, size_t capacity) {
	for (auto it = campos.begin(); it != campos.end(); it++) {
		Court *court = *it;
		if (court->get_id() == id) {
			court->change_capacity(capacity);
			return;
		}
	}
	throw InexistentObject("Court");
}

void Empresa::change_court(id_t court_id, id_t class_id) {
	Class *c = aulas[find_class(class_id)];
	Court *new_court = campos[find_court(court_id)];
	c->get_court()->rm_class(c);
	c->set_court(new_court);
	new_court->add_class(c);
}


void Empresa::list_courts() const {
	for (auto it = campos.begin(); it != campos.end(); it++) {
		cout << (*it)->get_info() << endl;
	}
}


void Empresa::print_available_courts(Date d) {
	int num = 0;
	Period p(d, 0, 0, 48);

	for (auto it = campos.begin(); it != campos.end(); it++) {
		if (!(*it)->check_on_day(d) || (*it)->get_available_capacity(p) > 0) {
			cout << (*it)->get_info();
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
		if (!(*it)->check_on_going(p) || (*it)->get_available_capacity(p) > 0) {
			cout << (*it)->get_info();
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
		if ((*it)->get_id() == id) {
			cout << (*it)->list_classes(d, ++d) << endl;
			return;
		}
	}
	throw InexistentObject("Court");
}


int Empresa::find_court(id_t id) const {
	for (int i = 0; i < campos.size(); i++) {
		if (campos[i]->get_id() == id) {
			return i;
		}
	}
	throw InexistentObject("Court");
}


bool Empresa::exists_court(id_t id) const {
	for (size_t t = 0; t < campos.size(); t++) {
		if (campos.at(t)->get_id() == id) {
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
		id_t technician_id = 0;

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

