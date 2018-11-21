#include "objetos.h"

										//   -----------------------------------   //
										//   --- Member Function Definitions ---   //
										//   -----------------------------------   //

//=================================================================================================================//
//==================================================== USER ===========================================================//
//=================================================================================================================//

User::User() {
	id = ++largest_id;
	debt = 0;
	name = DEFAULT_USER + to_string(id);
	gold_card = false;
}

User::User(string name, bool gold_card): name(move(name)), gold_card(gold_card) {
	id = ++largest_id;
	debt = 0;
}

string User::export_attributes() const {
	stringstream out;
	out << "user,attributes:" <<  id << ';' << name << ';' << (gold_card ? "true" : "false") << ';';
	return out.str();
}

string User::export_uses() const {
	stringstream out;
	out << "user,uses," << id << ':';
	for (auto it = uses.begin(); it != uses.end(); it++)
		out << (*it)->get_id() << ';';
	return out.str();
}

string User::get_info() const {
	stringstream out;
	out << INFO_USER << '\n';
	out << INFO_NAME << name << '\n';
	out << INFO_ID << id << '\n';
	out << INFO_CARD << gold_card ? " Yes" : " No";
	return out.str();
}

void User::pay_debt() {
	for (auto it = uses.begin(); it != uses.end(); it++) {
		(*it)->set_paid(true);
	}
	update_debt();
}

void User::add_use(Use* use) {



	bool exists = false;
	
	for (size_t t = 0; t < uses.size(); t++) {
		if (uses.at(t) == use) {
			exists = true;
		}
	}

	if (exists)
		throw RepeatedObject("Use*");
	
	uses.push_back(use);
}

void User::rm_use(Use *use) {

	int pos = -1;

	for (int t = 0; t < uses.size(); t++) {
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
	out << INFO_ID << id << '\n\n';

	for (auto it = uses.begin(); it != uses.end(); it++) {
		if (month == (*it)->get_time() && (*it)->get_type() == CLASS) {
			out << INFO_DATE << (*it)->get_time() << '\n';
			Class_Attendance* p = dynamic_cast <Class_Attendance*> (*it);
			if (p->get_grade() == -1) {
				out << INFO_GRADE << "Not graded" << '\n\n';
			}
			else {
				out << INFO_GRADE << p->get_grade() << '\n\n';
			}
		}
	}
}

string User::get_bill(Month month) const {
	stringstream out;

	out << INFO_USER << '\n';
	out << INFO_NAME << name << '\n';
	out << INFO_ID << id << '\n\n';

	for (auto it = uses.begin(); it != uses.end(); it++) {
		if (month == (*it)->get_time()) {
			if ((*it)->get_type() == CLASS) {
				out << DEFAULT_CLASS << '\n';
				out << INFO_DATE << (*it)->get_time() << '\n';
				Class_Attendance* p = dynamic_cast <Class_Attendance*> (*it);
				if (p->get_grade() == -1) {
					out << INFO_GRADE << "Not graded" << '\n\n';
				}
				else {
					out << INFO_GRADE << p->get_grade() << '\n\n';
				}
			}
			else if ((*it)->get_type() == FREE) {
				out << DEFAULT_FREE << '\n';
				out << INFO_DATE << (*it)->get_time() << '\n\n';
			}
		}
	}
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
}

bool  User::operator== (const User & u) const {
	Equal_ID<User> comp;
	return comp(*this,u);
}

bool  User::operator<  (const User & u) const {
	Sort_ID<User> comp;
	return comp(*this,u);
}

//==========================================================================================================================//
//==================================================== TEACHER ===========================================================//
//==========================================================================================================================//

Teacher::Teacher() {
	id = ++largest_id;
	name = DEFAULT_TEACHER + to_string(id);
}

Teacher::Teacher(string name): name(move(name)) {
	id = ++largest_id;
}

string Teacher::export_attributes() const {
	stringstream out;
	out << "teacher,attributes:" << id << "," << name << ";";
	return out.str();
}

string Teacher::export_classes() const {
	stringstream out;
	out << "teacher,classes," << id << ':';
	for (auto it = classes.begin(); it != classes.end(); it++)
		out << (*it)->get_id() << ';';
	return out.str();
}

void Teacher::add_class(Class *class_) {
    POINTER_OP(Class,Sort_Time) comp;
	bool exists = false;
	int pos = -1;

	for (size_t t = 0; t < classes.size(); t++) {
		if (classes.at(t) == class_) {
			exists = true;
		}
		else if (comp(classes.at(t),class_)) {
			pos = t + 1;
		}
		else {
			pos = t;
			break;
		}
	}

	if (exists)
		throw RepeatedObject("Class*");

	classes.insert(classes.begin() + pos, class_);
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

string Teacher::get_schedule(Date from, Date to) const{
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
	Date temp(1,1,1);
	for (size_t t = 0; t < classes.size(); t++) {
		temp = classes.at(t)->get_time();
		if ( !(temp < from) && temp < to ) {
			num++;
		}
	}

	return num;
}

bool  Teacher::operator== (const Teacher & p) const {
	Equal_ID<Teacher> comp;
	return comp(*this,p);
}

bool  Teacher::operator<  (const Teacher & p) const {
	Sort_ID<Teacher> comp;
	return comp(*this,p);
}

//======================================================================================================================//
//==================================================== COURT ===========================================================//
//======================================================================================================================//

Court::Court() {
	id = ++largest_id;
	capacity = 0;
}

Court::Court(size_t max_capacity) {
	id = ++largest_id;
	capacity = max_capacity;
}

string Court::export_attributes() const {
	stringstream out;
	out << "court,attributes:" << id << ';' << capacity << ';';
	return out.str();
}

string Court::export_classes() const {
	stringstream out;
	out << "court,classes," << id << ':';
	for (auto it = classes.begin(); it != classes.end(); it++)
		out << (*it)->get_id() << ';';
	return out.str();
}

string Court::export_free_uses() const {
	stringstream out;
	out << "court,free_uses," << id << ':';
	for (auto it = free_uses.begin(); it != free_uses.end(); it++)
		out << (*it)->get_id() << ';';
	return out.str();
}

void Court::add_class(Class *class_ {
	POINTER_OP(Class,Sort_Time) comp;
	bool exists = false;
	int pos = -1;

	for (size_t t = 0; t < classes.size(); t++) {
		if (classes.at(t) == class_) {
			exists = true;
		}
		else if (comp(classes.at(t),class_)) {
			pos = t + 1;
		}
		else {
			pos = t;
			break;
		}
	}

	if (!exists) {

	}
		throw RepeatedObject("Class");

	classes.insert(classes.begin() + pos, class_);
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
	POINTER_OP(Free_Use,Sort_Time) comp;
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
		else if (comp(free_uses.at(t),use)) {
			pos = t + 1;
		}
	}

	if (exists)
		throw RepeatedObject("Use");

	free_uses.insert(free_uses.begin() + pos, use);
}

void Court::rm_free_use(Free_Use *use) {
	int pos = -1;

	for (size_t t = 0; t < classes.size(); t++) {
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

string Court::list_classes(Date from, Date to) const{

}

string Court::list_free_uses(Date from, Date to) const{

}

bool  Court::operator== (const Court & p) const {
	return (id == p.get_id() && capacity == p.get_capacity());
}

bool  Court::operator<  (const Court & p) const {
	return (id < p.get_id());
}



//====================================================================================================================//
//==================================================== USE ===========================================================//
//====================================================================================================================//

string Use::get_enum_string(use_t use) {
	switch(use) {
		case ABSTRACT:
			return "ABSTRACT";
		case CLASS:
			return "CLASS";
		case FREE:
			return "FREE";
		default:
			return "ERROR";
	}
}

string Use::export_attributes() const {
	stringstream out;
	out << "use,attributes:" << id << ';' << get_enum_string(type) << ';' << time.get_export() << ";" << (paid ? "true" : "false") << ';';
	return out.str();
}

string Use::export_externals() const {
	stringstream out;
	out << "use,externals," << id << ':' << user->get_id() << ';';
}

Use::Use(User* user, Period time, Court *court): user(user), time(time), court(court) {
	id = ++largest_id;
	paid = false;
	type = ABSTRACT;
}

bool Use::operator== (const Use & u) const {
	Equal_ID<Use> comp;
	return comp(*this,u);
}

//=================================================================================================================//

string Class_Attendance::export_externals() const {
	stringstream out;
	out << Use::export_externals() << class_->get_id() << ';';
	return out.str();
}

string Class_Attendance::export_attributes() const {
	stringstream out;
	out << Use::export_attributes() << ";" << grade << ";";
	return out.str();
}

Class_Attendance::Class_Attendance(User *u, Class *c): Use(u,c->get_time(),c->get_court) {
	grade = -1;
	class_ = c;
	type = CLASS;
}

bool Class_Attendance::operator==(const Class_Attendance &rhs) const {
	Equal_ID<Class_Attendance> comp;
	return comp(*this,rhs);
}

//=================================================================================================================//

string Free_Use::export_attributes() const {
	return Use::export_attributes();
}

string Free_Use::export_externals() const {
	stringstream out;
	out << Use::export_externals() << court->get_id() << ';';
	return out.str();
}

Free_Use::Free_Use(User *u, Period p, Court *court): Use(u,move(p),court) {
	type = FREE;
}

//=====================================================================================================================//
//==================================================== CLASS ===========================================================//
//=====================================================================================================================//

string Class::export_attributes() const {
	stringstream out;
	out << "class,attributes:" << id << ';' << time.get_export() << ';';
	return out.str();
}

string Class::export_externals() const {
	stringstream out;
	out << "class,externals," << id << ':' << court->get_id() << ';' << teacher->get_id() << ';';
	return out.str();
}

string Class::export_attendances() const {
	stringstream out;
	out << "class,attendances," << id << ':';
	for (auto it = attendances.begin(); it != attendances.end(); it++)
		out << (*it)->get_id() << ';';
	return out.str();
}
