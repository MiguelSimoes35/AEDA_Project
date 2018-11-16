#include "objetos.h"

										//   -----------------------------------   //
										//   --- Member Function Definitions ---   //
										//   -----------------------------------   //

//=================================================================================================================//
//==================================================== UTENTE ===========================================================//
//=================================================================================================================//

User::User() {
	id = ++largest_id;
	debt = 0;
	name = DEFAULT_USER + to_string(id);
	gold_card = false;
}

//=================================================================================================================//

User::User(string name, bool gold_card): name(move(name)), gold_card(gold_card) {
	id = ++largest_id;
	debt = 0;
}

//=================================================================================================================//

void User::add_use(Use* use) {

	bool exists = false;
	
	for (size_t t = 0; t < uses.size(); t++) {
		if (uses.at(t) == use) {
			exists = true;
		}
	}

	if (exists)
		return false;
	
	uses.push_back(use);

	return true;
}

//=================================================================================================================//

void User::remove_use(Use* use) {

	int pos = -1;

	for (int t = 0; t < uses.size(); t++) {
		if (uses.at(t) == use) {
			pos = t;
			break;
		}
	}

	if (pos != -1) {
		uses.erase(uses.begin() + pos);
		return true;
	}

	return false;
}

//=================================================================================================================//

string User::get_report(Month month) const{

}

//=================================================================================================================//

string User::get_bill(Month month) const{

}

//=================================================================================================================//

bool  User::operator== (const User & u) const {
	return (id == u.getID() && name == u.get_nome());
}

//=================================================================================================================//

bool  User::operator<  (const User & u) const {
	return (id < u.getID());
}




//==========================================================================================================================//
//==================================================== PROFESSOR ===========================================================//
//==========================================================================================================================//

Teacher::Teacher() {
	id = greatest_id++;
	name = "professor" + id;
	availability = true;
}

//=================================================================================================================//

Teacher::Teacher(string name) {
	move()
	id = greatest_id++;
	this->name = move(name);
	availability = true;
}

//=================================================================================================================//

id_t Teacher::get_id() const{
	return id;
}

//=================================================================================================================//

string Teacher::get_name() const{
	return name;
}

//=================================================================================================================//

void Teacher::add_class(Class *aula) {

	bool exists = false;
	int pos = -1;

	for (size_t t = 0; t < classes.size(); t++) {
		if (classes.at(t) == aula) {
			exists = true;
		}
		else if (classes.at(t).get_date() < aula.get_date()) {
			pos = t + 1;
		}
		else {
			pos = t;
			break;
		}
	}

	if (exists)
		return false;

	classes.insert(classes.begin() + pos, aula);

	return true;
}

//=================================================================================================================//

void Teacher::rm_class(Class *aula) {
	int pos = -1;

	for (size_t t = 0; t < classes.size(); t++) {
		if (classes.at(t) == aula) {
			pos = t;
			break;
		}
	}

	if (pos != -1) {
		classes.erase(classes.begin() + pos);
		return true;
	}

	return false;
}

//=================================================================================================================//

string Teacher::get_schedule(Date from, Date to) const{

}

//=================================================================================================================//

size_t Teacher::get_num_classes(Date from, Date to) const {

	size_t num = 0;

	for (size_t t = 0; t < classes.size(); t++) {
		if (classes.at(t).get_date() > from && classes.at(t).get_date() < to) {
			num++;
		}
	}

	return num;
}

//=================================================================================================================//

bool  Teacher::operator== (const Teacher & p) const {
	return (id == p.get_id() && name == p.get_name());
}

//=================================================================================================================//

bool  Teacher::operator<  (const Teacher & p) const {
	return (id < p.get_id());
}




//======================================================================================================================//
//==================================================== CAMPO ===========================================================//
//======================================================================================================================//

Court::Court() {
	id = ++largest_id;
	capacity = 0;
}

//=================================================================================================================//

Court::Court(vector<ClassAtendance*> usos) {
	id = largest_id++;

	for (size_t t = 0; t < usos.size(); t++) {
		classes.push_back(usos.at(t));

		if (usos.at(t)->get_mode == "livre") {
			free_uses.push_back(usos.at(t));
		}
	}
}

//=================================================================================================================//

void Court::add_class(Class *class_) {

	bool exists = false;
	int pos = -1;

	for (size_t t = 0; t < classes.size(); t++) {
		if (classes.at(t) == class_) {
			exists = true;
		}
		else if (classes.at(t).get_date() < class_.get_date()) {
			pos = t + 1;
		}
		else {
			pos = t;
			break;
		}
	}

	if (exists)
		return false;

	classes.insert(classes.begin() + pos, class_);


	return true;
}

//=================================================================================================================//

void Court::rm_class(Class *class_) {

	int pos = -1;

	for (size_t t = 0; t < classes.size(); t++) {
		if (classes.at(t) == class_) {
			pos = t;
			break;
		}
	}

	if (pos != -1) {
		classes.erase(classes.begin() + pos);
		return true;
	}

	return false;
}

//=================================================================================================================//

void Court::add_free_use(Use *use) {

	bool exists = false;
	int pos_marc = -1;
	int pos_freq = -1;

	for (size_t t = 0; t < classes.size(); t++) {
		if (classes.at(t) == use) {
			exists = true;
		}
		else if (classes.at(t).get_date() < use.get_date()) {
			pos_marc = t + 1;
		}

		if (free_uses.at(t) == use) {
			exists = true;
		}
		else if (free_uses.at(t).get_date() < use.get_date()) {
			pos_freq = t + 1;
		}
	}

	if (exists)
		return false;

	classes.insert(classes.begin() + pos_marc, use);
	free_uses.insert(free_uses.begin() + pos_freq, use);

	return true;
}

//=================================================================================================================//

void Court::rm_free_use(Use *use) {
	int pos_marc = -1;
	int pos_freq = -1;

	for (size_t t = 0; t < classes.size(); t++) {
		if (classes.at(t) == use) {
			pos_marc = t;
			break;
		}

		if (free_uses.at(t) == use) {
			pos_freq = t;
		}
	}

	if (pos_marc != -1 && pos_freq != -1) {
		classes.erase(classes.begin() + pos_marc);
		free_uses.erase(free_uses.begin() + pos_freq);
		return true;
	}

	return false;
}

//=================================================================================================================//

string Court::list_classes(Date from, Date to) const{

}

//=================================================================================================================//

string Court::list_free_uses(Date from, Date to) const{

}




//====================================================================================================================//
//==================================================== USO ===========================================================//
//====================================================================================================================//

Use::Use(Date d, Period t, User u)
: date(d) , period(t) , user(u){
	mode = "livre";
	pagamento = (t.get_blocks * PRICE_FOR_FREE_USE);
}

//=================================================================================================================//

Use::Use(Date d, Period t, User u, string mode)
: date(d), period(t), user(u), mode(mode) {

	if (this->mode == "livre") {
		pagamento = (t.get_blocks * PRICE_FOR_FREE_USE);
	}
	else {
		if (u.get_gold) {
			pagamento = PRICE_FOR_CLASS * 0.85;
		}
		else {
			pagamento = PRICE_FOR_CLASS;
		}
	}
}

//=================================================================================================================//

id_t Use::get_id() const{
	return user.getID;
}

//=================================================================================================================//

User * Use::get_user() const{

}

//=================================================================================================================//

void Use::set_user(User *u) {
	if (user == *u)
		return false;

	user = *u;

	return true;
}

//=================================================================================================================//

void Use::get_date(Date *d) const{
	
}

//=================================================================================================================//

bool Use::change_date(Date *d) {
	if (date == *d)
		return false;

	date = *d;

	return true;
}

//=================================================================================================================//

Period Use::get_time() const{

}

//=================================================================================================================//

void Use::set_time(Period *t) {
	if (period == *t)
		return false;

	period = *t;

	return true;
}

//=================================================================================================================//

string Use::get_mode() const{
	return mode;
}

//=================================================================================================================//

bool Use::change_mode(string modo) {
	mode = modo;
}

//=================================================================================================================//

double Use::get_cost() const{
	return pagamento;
}

//=================================================================================================================//

bool Use::get_paid_status() const{
	return (pagamento == 0);
}

//=================================================================================================================//

bool Use::operator== (const Use & u) const {
	return (user.getID() == u.get_id() && period == u.get_time() && date == u.get_date() && mode == u.get_mode());
}



//=====================================================================================================================//
//==================================================== AULA ===========================================================//
//=====================================================================================================================//

ClassAtendance::ClassAtendance(User u, Teacher p, Date d, Period t)
: Use(d, t, u, "aula") , prof(p){
	
}

//=================================================================================================================//

id_t ClassAtendance::get_id() {
	return Use::get_id();

}

//=================================================================================================================//

void ClassAtendance::get_aluno(User *u) {
	Use::get_user();
}

//=================================================================================================================//

bool ClassAtendance::change_aluno(User *u) {
	Use::set_user(u);
}

//=================================================================================================================//

void ClassAtendance::get_prof(Teacher *p) {

}

//=================================================================================================================//

bool ClassAtendance::change_prof(Teacher *p) {
	if (prof == *p)
		return false;

	prof = *p;

	return true;
}

//=================================================================================================================//

void ClassAtendance::get_date(Date *d) const{
	Use::get_date(d);
}

//=================================================================================================================//

bool ClassAtendance::change_date(Date *d) {
	Use::change_date(d);
}

//=================================================================================================================//

void ClassAtendance::get_period(Period *t) const{
	Use::get_time();
}

//=================================================================================================================//

bool ClassAtendance::change_period(Period *t){
	Use::set_time(t);
}

//=================================================================================================================//

void ClassAtendance::print_class() {

}

//=================================================================================================================//

bool ClassAtendance::operator== (const ClassAtendance & a) const {
	return (Use::get_id == a.get_id() && Use::get_period == a.get_period() && Use::get_date() == a.get_date() && Use::get_mode() == a.get_mode() && prof == a.get_prof());
}

//=================================================================================================================//
