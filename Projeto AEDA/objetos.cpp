/*
 * (c) 2018 Griné, Matos, and Simões
 * This software is provided under the MIT License.
 * To obtain a copy of this license, please read the file LICENSE at the root of the repository, or visit
 * https://opensource.org/licenses/MIT
 */

#include "objetos.h"

id_t User::largest_id = 0;
id_t Court::largest_id = 0;
id_t Class::largest_id = 0;
id_t Use::largest_id = 0;
id_t Technician::largest_id = 0;

									//   -----------------------------------   //
									//   --- Member Function Definitions ---   //
									//   -----------------------------------   //

//==================================================== USER ===========================================================//

User::User(string name, string address, unsigned NIF, bool gold_card) 
	: name(move(name)), gold_card(gold_card), address(address), NIF(NIF) {
	id = ++largest_id;
	debt = 0;
}

User::User(string name) 
: name(name) {
	// Used only for dummie_users
}

string User::get_info() const {
	stringstream out;
	out << INFO_USER << '\n';
	out << INFO_NAME << name << '\n';
	out << INFO_ID << id << '\n';
	out << INFO_ADDESS << address << '\n';
	out << INFO_NIF << NIF << '\n';
	out << INFO_CARD << (gold_card ? " Yes" : " No");
	out << "\n\n";
	return out.str();
}

void User::update_debt() {
	double new_debt = 0;

	new_debt += gold_card ? CARD_FEE : 0;

	for (auto it = uses.begin(); it != uses.end(); it++) {
		if (!((*it)->get_paid_status())) {
			if ((*it)->get_type() == CLASS) {
				Class_Attendance* c = dynamic_cast <Class_Attendance*> (*it);
				new_debt += c->get_cost();
			}
			else if ((*it)->get_type() == FREE) {
				auto p = dynamic_cast <Free_Use*> (*it);
				new_debt += p->get_cost();
			}
		}
	}

	debt = new_debt;
}

void User::pay_debt() {
	for (auto it = uses.begin(); it != uses.end(); it++) {
		(*it)->set_paid(true);
	}

	update_debt();
}

void User::add_use(Use* use) {
	bool exists = false;
	POINTER_OP(Use, Sort_Time) comp;

	for (size_t t = 0; t < uses.size(); t++) {
		if (uses.at(t) == use) {
			exists = true;
		}
	}

	if (exists)
		throw RepeatedObject("Use*");

	uses.push_back(use);

	sort(uses.begin(), uses.end(), comp);
}

void User::rm_use(Use *use) {

	int pos = -1;

	for (size_t t = 0; t < uses.size(); t++) {
		if (uses.at(t) == use) {
			pos = t;
			break;
		}
	}

	if (pos != -1) {
		uses.erase(uses.begin() + pos);
		return;
	}

	throw InexistentObject("Use*");
}

string User::get_report(Month month) const {
	stringstream out;

	out << INFO_USER << '\n';
	out << INFO_NAME << name << '\n';
	out << INFO_ID << id << "\n";
	out << INFO_NIF << NIF << '\n\n';

	for (auto it = uses.begin(); it != uses.end(); it++) {
		if (month == (*it)->get_time() && (*it)->get_type() == CLASS) {
			out << INFO_DATE << (*it)->get_time().display_period() << '\n';
			Class_Attendance* p = dynamic_cast <Class_Attendance*> (*it);
			if (p->get_grade() == -1) {
				out << INFO_GRADE << "Not graded" << "\n\n";
			}
			else {
				out << INFO_GRADE << p->get_grade() << "\n\n";
			}
		}
	}
	return out.str();
}

string User::get_bill(Month month) const {
	stringstream out;

	out << INFO_USER << '\n';
	out << INFO_NAME << name << '\n';
	out << INFO_ID << id << "\n";
	out << INFO_NIF << NIF << '\n\n';

	for (auto it = uses.begin(); it != uses.end(); it++) {
		if (month == (*it)->get_time()) {
			if ((*it)->get_type() == CLASS) {
				out << DEFAULT_CLASS << '\n';
				out << INFO_DATE << (*it)->get_time().display_period() << '\n';
				Class_Attendance* p = dynamic_cast <Class_Attendance*> (*it);
				if (p->get_grade() == -1) {
					out << INFO_GRADE << "Not graded" << "\n\n";
				}
				else {
					out << INFO_GRADE << p->get_grade() << "\n\n";
				}
			}
			else if ((*it)->get_type() == FREE) {
				out << DEFAULT_FREE << '\n';
				out << INFO_DATE << (*it)->get_time().display_period() << "\n\n";
			}
		}
	}

	return out.str();
}

string User::get_schedule(Date from, Date to) const {
	stringstream out;
	Use* c = nullptr;
	out << "Schedule for user " << name << " from " << from.get_year() << '.' << from.get_month() << '.' << from.get_day()
		<< " to " << to.get_year() << '.' << to.get_month() << '.' << to.get_day() << ':';
	for (auto it = uses.begin(); it != uses.end(); it++) {
		c = (*it);
		Period time = c->get_time();
		Date temp = time;
		if (!(temp < from) && temp < to)
			out << "\nClass " << c->get_id() << " on court " << c->get_court()->get_id() << ", on " << time.get_year()
			<< '.' << time.get_month() << '.' << time.get_day() << ", at " << time.get_hour() << ':' << setfill('0')
			<< setw(2) << time.get_min() << ";";
	}
	return out.str();
}

void User::pay_bill(Month month) {
	for (auto it = uses.begin(); it != uses.end(); it++) {
		if (month == (*it)->get_time())
			(*it)->set_paid(true);
	}

	update_debt();
}

bool  User::operator== (const User & u) const {
	return (id == u.get_id() && address == u.get_address() && NIF == u.get_NIF());
}

bool  User::operator<  (const User & u) const {
	if (name == u.get_name()) {
		if (address == u.get_address()) {
			if (NIF == u.get_NIF()) {
				return (id < u.get_id());
			}
			else
				return (NIF < u.get_NIF());
		}
		else
			return (address < u.get_address());
	}
	else
		return (name < u.get_name());
	
}

//======================================================================================================================//

UserPtr::UserPtr(User* user) {
	this->user = user;
}

string UserPtr::get_name() const {
	return this->user->get_name();
}

id_t UserPtr::get_id() const {
	return this->user->get_id();
}

unsigned UserPtr::get_frequency() const {
	return this->user->get_frequency();
}

string UserPtr::get_address() const {
	return this->user->get_address();
}

unsigned UserPtr::get_NIF() const {
	return this->user->get_NIF();
}

//=================================================== TEACHER ==========================================================//

Teacher::Teacher(string name) : name(move(name)) {
	this->id = calculate_id(this->name);
	active = true;
}

string Teacher::get_info() const {
	stringstream out;
	out << INFO_TEACHER << '\n';
	out << INFO_NAME << name << '\n';
	out << " Currently " << (active ? "employed." : "unemployed.") << endl;
	return out.str();
}

id_t Teacher::get_id(string name) const {
	return calculate_id(name);
}

id_t Teacher::calculate_id(string name) const{
	id_t result = 0;

	for (auto it = name.begin(); it != name.end(); it++)
		result += 13 * ((*it) + 103);

	return (result % 9887 + 1);
}

void Teacher::add_class(Class *class_) {
	POINTER_OP(Class, Sort_Time) comp;
	bool exists = false;
	int pos = -1;

	for (size_t t = 0; t < classes.size(); t++) {
		if (classes.at(t) == class_) {
			exists = true;
		}
		else if (comp(classes.at(t), class_)) {
			pos = t + 1;
		}
		else {
			pos = t;
			break;
		}
	}

	if (exists)
		throw RepeatedObject("Class*");

	classes.push_back(class_);
}

void Teacher::rm_class(Class *class_) {
	int pos = -1;

	for (size_t t = 0; t < classes.size(); t++) {
		if (classes.at(t) == class_) {
			pos = t;
			break;
		}
	}

	if (pos != -1) {
		classes.erase(classes.begin() + pos);
		return;
	}

	throw InexistentObject("Class");
}

string Teacher::get_schedule(Date from, Date to) const {
	stringstream out;
	Class* c = nullptr;
	out << "Schedule for teacher " << name << " from " << from.get_year() << '.' << from.get_month() << '.' << from.get_day()
		<< " to " << to.get_year() << '.' << to.get_month() << '.' << to.get_day() << ':';
	for (auto it = classes.begin(); it != classes.end(); it++) {
		c = (*it);
		Period time = c->get_time();
		Date temp = time;
		if (!(temp < from) && temp < to)
			out << "\nClass " << c->get_id() << " on court " << c->get_court()->get_id() << ", on " << time.get_year()
			<< '.' << time.get_month() << '.' << time.get_day() << ", at " << time.get_hour() << ':' << setfill('0')
			<< setw(2) << time.get_min() << ";";
	}
	return out.str();
}

size_t Teacher::get_num_classes(Date from, Date to) const {
	size_t num = 0;
	Date temp(1, 1, 1);
	for (size_t t = 0; t < classes.size(); t++) {
		temp = classes.at(t)->get_time();
		if (!(temp < from) && temp < to) {
			num++;
		}
	}

	return num;
}

bool  Teacher::operator== (const Teacher & p) const {
	Equal_ID<Teacher> comp;
	return comp(*this, p);
}

bool  Teacher::operator<  (const Teacher & p) const {
	Sort_ID<Teacher> comp;
	return comp(*this, p);
}

//======================================================================================================================//

TeacherPtr::TeacherPtr(Teacher* teacher) {
	this->teacher = teacher;
}

string TeacherPtr::get_name() const {
	return this->teacher->get_name();
}

id_t TeacherPtr::get_id() const {
	return this->teacher->get_id();
}

//==================================================== COURT ===========================================================//

Court::Court() {
	id = ++largest_id;
	capacity = 0;
}

Court::Court(size_t max_capacity) {
	id = ++largest_id;
	capacity = max_capacity;
}

string Court::get_info() const {
	stringstream out;
	out << INFO_COURT << '\n';
	out << " Court" << INFO_ID << id << "\n";
	out << " Capacity: " << capacity << "\n\n";

	return out.str();
}

size_t Court::get_available_capacity(Period time) const {
	size_t users = 0;

	for (auto it = classes.begin(); it != classes.end(); it++) {
		if ((*it)->get_time() == time) {
			users += (*it)->get_num_attendants();
		}
	}

	for (auto it = free_uses.begin(); it != free_uses.end(); it++) {
		if ((*it)->get_time() == time) {
			users++;
		}
	}

	return (capacity - users);
}

bool Court::check_on_going(Period time) const {
	bool ocupied = false;

	for (auto it = classes.begin(); it != classes.end(); it++) {
		if ((*it)->get_time() == time) {
			ocupied = true;
		}
	}

	for (auto it = free_uses.begin(); it != free_uses.end(); it++) {
		if ((*it)->get_time() == time) {
			ocupied = true;
		}
	}

	return ocupied;
}

bool Court::check_on_day(Date time) const {
	bool ocupied = false;

	Period periodo(time, 0, 0, 48);

	for (auto it = classes.begin(); it != classes.end(); it++) {
		if ((*it)->get_time() == periodo) {
			ocupied = true;
		}
	}

	return ocupied;
}

void Court::add_class(Class *class_) {
	POINTER_OP(Class, Sort_Time) comp;
	bool exists = false;
	int pos = -1;

	for (size_t t = 0; t < classes.size(); t++) {
		if (classes.at(t) == class_) {
			exists = true;
		}
		else if (comp(classes.at(t), class_)) {
			pos = t + 1;
		}
		else {
			pos = t;
			break;
		}
	}

	if (exists) {
		throw RepeatedObject("Class");
	}
	
	
	classes.push_back(class_);
}

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
		return;
	}

	throw InexistentObject("Class");
}

void Court::add_free_use(Free_Use *use) {
	POINTER_OP(Free_Use, Sort_Time) comp;
	if (use->get_type() != FREE)
		throw WrongUseType();
	if (get_available_capacity(use->get_time()))
		throw CourtIsFull(id, use->get_time());

	bool exists = false;
	int pos = -1;

	for (size_t t = 0; t < free_uses.size(); t++) {
		if (free_uses.at(t) == use) {
			exists = true;
		}
		else if (comp(free_uses.at(t), use)) {
			pos = t + 1;
		}
	}

	if (exists)
		throw RepeatedObject("Use");

	free_uses.insert(free_uses.begin() + pos, use);
}

void Court::rm_free_use(Free_Use *use) {
	int pos = -1;

	for (size_t t = 0; t < free_uses.size(); t++) {
		if (free_uses.at(t) == use) {
			pos = t;
		}
	}

	if (pos != -1) {
		free_uses.erase(free_uses.begin() + pos);
		return;
	}

	throw InexistentObject("Free_Use");
}

string Court::list_classes(Date from, Date to) const {
	stringstream out;
	out << INFO_COURT << '\n';
	out << " Court" << INFO_ID << id << "\n\n";
	out << DEFAULT_CLASS << "\n\n";
	out << INFO_DATE << from.display_month() << " to " << to.display_month() << "\n\n";

	for (size_t i = 0; i < classes.size(); i++) {
		if (!(static_cast<Date>(classes.at(i)->get_time()) < from) && static_cast<Date>(classes.at(i)->get_time()) < to) {
			out << classes.at(i)->get_info() << '\n';
		}
	}

	return out.str();
}

string Court::list_free_uses(Date from, Date to) const {
	stringstream out;
	out << INFO_COURT << '\n';
	out << " Court" << INFO_ID << id << "\n\n";
	out << DEFAULT_FREE << "\n\n";
	out << INFO_DATE << from.display_month() << " to " << to.display_month() << "\n\n";

	for (size_t i = 0; i < free_uses.size(); i++) {
		if (!(static_cast<Date>(classes.at(i)->get_time()) < from) && static_cast<Date>(classes.at(i)->get_time()) < to) {
			out << free_uses.at(i)->get_info() << '\n';
		}
	}

	return out.str();
}

bool  Court::operator== (const Court & p) const {
	return (id == p.get_id() && capacity == p.get_capacity());
}

bool  Court::operator<  (const Court & p) const {
	return (id < p.get_id());
}

//==================================================== USE ===========================================================//

string Use::get_enum_string(use_t use) {
	switch (use) {
	case ABSTRACT:
		return "ABSTRACT";
	case CLASS:
		return "CLASS";
	case FREE:
		return "FREE";
	default:
		throw WrongUseType();
	}
}

use_t Use::get_enum(const string& use) {
	if (use == "ABSTRACT")
		return ABSTRACT;
	if (use == "CLASS")
		return CLASS;
	if (use == "FREE")
		return FREE;

	throw WrongUseType();
}

Use::Use(User* user, Period time, Court* court) : user(user), time(move(time)), court(court) {
	id = ++largest_id;
	paid = false;
	type = ABSTRACT;
}

bool Use::operator== (const Use & u) const {
	Equal_ID<Use> comp;
	return comp(*this, u);
}

//=================================================================================================================//

Class_Attendance::Class_Attendance(User *u, Class *c) : Use(u, c->get_time(), c->get_court()) {
	grade = -1;
	class_ = c;
	type = CLASS;
}

bool Class_Attendance::operator==(const Class_Attendance &rhs) const {
	Equal_ID<Class_Attendance> comp;
	return comp(*this, rhs);
}

string Class_Attendance::get_info() const {
	stringstream out;

	out << INFO_DATE << time.display_period() << '\n';
	out << " Class attendance" << INFO_ID << id << '\n';
	out << " Court" << INFO_ID << court->get_id() << '\n';
	out << INFO_USER << user->get_name() << ' ' << user->get_id() << "\n\n";

	return out.str();
}

//=================================================================================================================//

Free_Use::Free_Use(User *user, Period p, Court* court) : Use(user, move(p), court) {
	type = FREE;
}

string Free_Use::get_info() const {
	stringstream out;

	out << INFO_DATE << time.display_period() << '\n';
	out << " Free Use" << INFO_ID << id << '\n';
	out << INFO_USER << user->get_name() << ' ' << user->get_id() << "\n\n";

	return out.str();
}

//==================================================== CLASS ===========================================================//

Class::Class(Period time, Teacher* teacher, Court *court) : time(move(time)), teacher(teacher), court(court) {
	id = ++largest_id;
}

string Class::get_info() const {
	stringstream out;

	out << INFO_DATE << time.display_period() << '\n';
	out << " Class" << INFO_ID << id << '\n';
	out << INFO_TEACHER << teacher->get_name() << ' ' << teacher->get_id() << '\n';
	for (auto it = attendances.begin(); it != attendances.end(); it++) {
		out << INFO_USER << (*it)->get_user()->get_name() << ' ' << (*it)->get_user()->get_id() << '\n';
	}

	return out.str();
}

void Class::add_attendance(Class_Attendance* attendance) {
	POINTER_OP(Class_Attendance, Sort_Time) comp;

	if (court->get_available_capacity(time) > 0) {
		attendances.push_back(attendance);
		sort(attendances.begin(), attendances.end(), comp);
	}
	else {
		throw CourtIsFull(court->get_id(), time);
	}
}

void Class::rm_attendance(Class_Attendance* attendance) {
	int pos = -1;

	for (size_t t = 0; t < attendances.size(); t++) {
		if (attendances.at(t) == attendance) {
			pos = t;
		}
	}

	if (pos != -1) {
		attendances.erase(attendances.begin() + pos);
		return;
	}

	throw InexistentObject("Free_Use");
}

//=================================================== TECHNICIAN ===========================================================//

Technician::Technician() {
	id = ++largest_id;
	name = "Technician " + to_string(id);
}

Technician::Technician(string name): name(name) {
	id = ++largest_id;
}

void Technician::assign_job(id_t court_id, int duration) {
	this->availability += duration;
	pair<id_t, int> job = { court_id, duration };
	jobs.push_back(job);
}

void Technician::update_repair() {
	if (availability > 0) {
		availability--;
		jobs.at(0).second--;
		if (jobs.at(0).second == 0) {
			jobs.erase(jobs.begin());
			repairs++;
		}
	}
}

int Technician::cancel_job() {
	if (this->availability == 0)
		return 0;

	int days_remaining = jobs.at(0).second;
	this->availability -= days_remaining;

	jobs.erase(jobs.begin());

	return days_remaining;
}

void Technician::cancel_job(id_t court_id) {
	for (auto it = jobs.begin(); it != jobs.end(); it++) {
		if (it->first == court_id) {
			availability -= it->second;
			jobs.erase(it);
		}
	}
}

string Technician::get_info() {
	stringstream out;

	out << INFO_USER << '\n';
	out << INFO_NAME << name << '\n';
	out << INFO_ID << id << '\n';
	out << INFO_AVL << availability << '\n';
	out << INFO_REPAIR << repairs << '\n';
	out << "\n\n";

	return out.str();
}

bool Technician::operator<(const Technician& tech) const {
	return (this->availability < tech.get_availability());
}

bool Technician::operator==(const Technician& tech) const {
	Equal_ID<Technician> comp;
	return comp(*this, tech);
}

