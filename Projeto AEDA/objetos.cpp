#include "objetos.h"

										//   -----------------------------------   //
										//   --- Member Function Definitions ---   //
										//   -----------------------------------   //

//=================================================================================================================//
//==================================================== UTENTE ===========================================================//
//=================================================================================================================//

User::User() {
	ID = maior_ID++;
	divida = 0;
	nome = "utente" + ID;
	cartao_gold = false;
}

//=================================================================================================================//

User::User(string nome) {
	ID = maior_ID++;
	divida = 0;
	this->nome = nome;
	cartao_gold = false;
}

//=================================================================================================================//

int User::getID() const {
	return ID;
}

//=================================================================================================================//

string User::get_nome() const {
	return nome;
}

//=================================================================================================================//

bool User::get_gold() const {
	return cartao_gold;
}

//=================================================================================================================//

int User::get_debt() const{
	return divida;
}

//=================================================================================================================//

void User::gold_user(bool card) {
	cartao_gold = card;
}

//=================================================================================================================//

bool User::add_utilizacao(Use &utilizacao) {

	bool exists = false;
	
	for (size_t t = 0; t < utilizacoes.size(); t++) {
		if (utilizacoes.at(t) == utilizacao) {
			exists = true;
		}
	}

	if (exists)
		return false;
	
	utilizacoes.push_back(utilizacao);

	return true;
}

//=================================================================================================================//

bool User::remove_utilizacao(Use &utilizacao) {

	int pos = -1;

	for (size_t t = 0; t < utilizacoes.size(); t++) {
		if (utilizacoes.at(t) == utilizacao) {
			pos = t;
			break;
		}
	}

	if (pos != -1) {
		utilizacoes.erase(utilizacoes.begin() + pos);
		return true;
	}

	return false;
}

//=================================================================================================================//

void User::print_report(Month month) const{

}

//=================================================================================================================//

void User::print_bill(Month month) const{

}

//=================================================================================================================//

bool  User::operator== (const User & u) const {
	return (ID == u.getID() && nome == u.get_nome());
}

//=================================================================================================================//

bool  User::operator<  (const User & u) const {
	return (ID < u.getID());
}




//==========================================================================================================================//
//==================================================== PROFESSOR ===========================================================//
//==========================================================================================================================//

Teacher::Teacher() {
	ID = maior_ID++;
	nome = "professor" + ID;
	disponibilidade = true;
}

//=================================================================================================================//

Teacher::Teacher(string nome) {
	ID = maior_ID++;
	this->nome = nome;
	disponibilidade = true;
}

//=================================================================================================================//

int Teacher::getID() const{
	return ID;
}

//=================================================================================================================//

string Teacher::get_nome() const{
	return nome;
}

//=================================================================================================================//

bool Teacher::available() const{
	return disponibilidade;
}

//=================================================================================================================//

void Teacher::change_availability(bool change) {
	disponibilidade = change;
}

//=================================================================================================================//

bool Teacher::add_class(Class &aula) {

	bool exists = false;
	int pos = -1;

	for (size_t t = 0; t < aulas.size(); t++) {
		if (aulas.at(t) == aula) {
			exists = true;
		}
		else if (aulas.at(t).get_date() < aula.get_date()) {
			pos = t + 1;
		}
		else {
			pos = t;
			break;
		}
	}

	if (exists)
		return false;

	aulas.insert(aulas.begin() + pos, aula);

	return true;
}

//=================================================================================================================//

bool Teacher::remove_class(Class &aula) {
	int pos = -1;

	for (size_t t = 0; t < aulas.size(); t++) {
		if (aulas.at(t) == aula) {
			pos = t;
			break;
		}
	}

	if (pos != -1) {
		aulas.erase(aulas.begin() + pos);
		return true;
	}

	return false;
}

//=================================================================================================================//

void Teacher::print_schedule(Date inicio, Date fim) const{

}

//=================================================================================================================//

int Teacher::num_classes(Date inicio, Date fim) {

	int num = 0;

	for (size_t t = 0; t < aulas.size(); t++) {
		if (aulas.at(t).get_date() > inicio && aulas.at(t).get_date() < fim) {
			num++;
		}
	}

	return num;
}

//=================================================================================================================//

bool  Teacher::operator== (const Teacher & p) const {
	return (ID == p.getID() && nome == p.get_nome());
}

//=================================================================================================================//

bool  Teacher::operator<  (const Teacher & p) const {
	return (ID < p.getID());
}




//======================================================================================================================//
//==================================================== CAMPO ===========================================================//
//======================================================================================================================//

Court::Court() {
	number = num_max++;
}

//=================================================================================================================//

Court::Court(vector<Class*> usos) {
	number = num_max++;

	for (size_t t = 0; t < usos.size(); t++) {
		marcacoes.push_back(usos.at(t));

		if (usos.at(t)->get_mode == "livre") {
			aulas_livres.push_back(usos.at(t));
		}
	}
}

//=================================================================================================================//

int Court::get_num() const{
	return number;
}

//=================================================================================================================//

bool Court::add_class(Class &utilizacao) {

	bool exists = false;
	int pos = -1;

	for (size_t t = 0; t < marcacoes.size(); t++) {
		if (marcacoes.at(t) == utilizacao) {
			exists = true;
		}
		else if (marcacoes.at(t).get_date() < utilizacao.get_date()) {
			pos = t + 1;
		}
		else {
			pos = t;
			break;
		}
	}

	if (exists)
		return false;

	marcacoes.insert(marcacoes.begin() + pos, utilizacao);


	return true;
}

//=================================================================================================================//

bool Court::remove_class(Class &utilizacao) {

	int pos = -1;

	for (size_t t = 0; t < marcacoes.size(); t++) {
		if (marcacoes.at(t) == utilizacao) {
			pos = t;
			break;
		}
	}

	if (pos != -1) {
		marcacoes.erase(marcacoes.begin() + pos);
		return true;
	}

	return false;
}

//=================================================================================================================//

bool Court::add_freq(Use &utilizacao) {

	bool exists = false;
	int pos_marc = -1;
	int pos_freq = -1;

	for (size_t t = 0; t < marcacoes.size(); t++) {
		if (marcacoes.at(t) == utilizacao) {
			exists = true;
		}
		else if (marcacoes.at(t).get_date() < utilizacao.get_date()) {
			pos_marc = t + 1;
		}

		if (aulas_livres.at(t) == utilizacao) {
			exists = true;
		}
		else if (aulas_livres.at(t).get_date() < utilizacao.get_date()) {
			pos_freq = t + 1;
		}
	}

	if (exists)
		return false;

	marcacoes.insert(marcacoes.begin() + pos_marc, utilizacao);
	aulas_livres.insert(aulas_livres.begin() + pos_freq, utilizacao);

	return true;
}

//=================================================================================================================//

bool Court::remove_freq(Use &utilizacao) {
	int pos_marc = -1;
	int pos_freq = -1;

	for (size_t t = 0; t < marcacoes.size(); t++) {
		if (marcacoes.at(t) == utilizacao) {
			pos_marc = t;
			break;
		}

		if (aulas_livres.at(t) == utilizacao) {
			pos_freq = t;
		}
	}

	if (pos_marc != -1 && pos_freq != -1) {
		marcacoes.erase(marcacoes.begin() + pos_marc);
		aulas_livres.erase(aulas_livres.begin() + pos_freq);
		return true;
	}

	return false;
}

//=================================================================================================================//

void Court::list_classes(Date inicio, Date fim) const{

}

//=================================================================================================================//

void Court::list_freq(Date inicio, Date fim) const{

}




//====================================================================================================================//
//==================================================== USO ===========================================================//
//====================================================================================================================//

Use::Use(Date d, Period t, User u)
: date(d) , period(t) , utente(u){
	mode = "livre";
	pagamento = (t.get_blocks * PRICE_FOR_FREE_USE);
}

//=================================================================================================================//

Use::Use(Date d, Period t, User u, string mode)
: date(d), period(t), utente(u), mode(mode) {

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

int Use::getID() const{
	return utente.getID;
}

//=================================================================================================================//

void Use::get_utente(User *u) const{

}

//=================================================================================================================//

bool Use::change_utente(User *u) {
	if (utente == *u)
		return false;

	utente = *u;

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

void Use::get_period(Period *t) const{

}

//=================================================================================================================//

bool Use::change_period(Period *t) {
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

double Use::get_payment() const{
	return pagamento;
}

//=================================================================================================================//

bool Use::payed() const{
	return (pagamento == 0);
}

//=================================================================================================================//

bool Use::operator== (const Use & u) const {
	return (utente.getID() == u.getID() && period == u.get_period() && date == u.get_date() && mode == u.get_mode());
}



//=====================================================================================================================//
//==================================================== AULA ===========================================================//
//=====================================================================================================================//

Class::Class(User u, Teacher p, Date d, Period t)
: Use(d, t, u, "aula") , prof(p){
	
}

//=================================================================================================================//

int Class::getID() {
	return Use::getID();

}

//=================================================================================================================//

void Class::get_aluno(User *u) {
	Use::get_utente(u);
}

//=================================================================================================================//

bool Class::change_aluno(User *u) {
	Use::change_utente(u);
}

//=================================================================================================================//

void Class::get_prof(Teacher *p) {

}

//=================================================================================================================//

bool Class::change_prof(Teacher *p) {
	if (prof == *p)
		return false;

	prof = *p;

	return true;
}

//=================================================================================================================//

void Class::get_date(Date *d) const{
	Use::get_date(d);
}

//=================================================================================================================//

bool Class::change_date(Date *d) {
	Use::change_date(d);
}

//=================================================================================================================//

void Class::get_period(Period *t) const{
	Use::get_period(t);
}

//=================================================================================================================//

bool Class::change_period(Period *t){
	Use::change_period(t);
}

//=================================================================================================================//

void Class::print_class() {

}

//=================================================================================================================//

bool Class::operator== (const Class & a) const {
	return (Use::getID == a.getID() && Use::get_period == a.get_period() && Use::get_date() == a.get_date() && Use::get_mode() == a.get_mode() && prof == a.get_prof());
}

//=================================================================================================================//
