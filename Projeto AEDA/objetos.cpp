#include "objetos.h"

										//   -----------------------------------   //
										//   --- Member Function Definitions ---   //
										//   -----------------------------------   //

//=================================================================================================================//
//==================================================== UTENTE ===========================================================//
//=================================================================================================================//

Utente::Utente() {
	ID = maior_ID++;
	divida = 0;
	nome = "utente" + ID;
	cartao_gold = false;
}

//=================================================================================================================//

Utente::Utente(string nome) {
	ID = maior_ID++;
	divida = 0;
	this->nome = nome;
	cartao_gold = false;
}

//=================================================================================================================//

int Utente::getID() const {
	return ID;
}

//=================================================================================================================//

string Utente::get_nome() const {
	return nome;
}

//=================================================================================================================//

bool Utente::get_gold() const {
	return cartao_gold;
}

//=================================================================================================================//

int Utente::get_debt() const{
	return divida;
}

//=================================================================================================================//

void Utente::gold_user(bool card) {
	cartao_gold = card;
}

//=================================================================================================================//

bool Utente::add_utilizacao(Uso &utilizacao) {

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

bool Utente::remove_utilizacao(Uso &utilizacao) {

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

void Utente::print_report(Month month) const{

}

//=================================================================================================================//

void Utente::print_bill(Month month) const{

}

//=================================================================================================================//

bool  Utente::operator== (const Utente & u) const {
	return (ID == u.getID() && nome == u.get_nome());
}

//=================================================================================================================//

bool  Utente::operator<  (const Utente & u) const {
	return (ID < u.getID());
}




//==========================================================================================================================//
//==================================================== PROFESSOR ===========================================================//
//==========================================================================================================================//

Professor::Professor() {
	ID = maior_ID++;
	nome = "professor" + ID;
	disponibilidade = true;
}

//=================================================================================================================//

Professor::Professor(string nome) {
	ID = maior_ID++;
	this->nome = nome;
	disponibilidade = true;
}

//=================================================================================================================//

int Professor::getID() const{
	return ID;
}

//=================================================================================================================//

string Professor::get_nome() const{
	return nome;
}

//=================================================================================================================//

bool Professor::available() const{
	return disponibilidade;
}

//=================================================================================================================//

void Professor::change_availability(bool change) {
	disponibilidade = change;
}

//=================================================================================================================//

bool Professor::add_class(Aula &aula) {

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

bool Professor::remove_class(Aula &aula) {
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

void Professor::print_schedule(Date inicio, Date fim) const{

}

//=================================================================================================================//

int Professor::num_classes(Date inicio, Date fim) {

	int num = 0;

	for (size_t t = 0; t < aulas.size(); t++) {
		if (aulas.at(t).get_date() > inicio && aulas.at(t).get_date() < fim) {
			num++;
		}
	}

	return num;
}

//=================================================================================================================//

bool  Professor::operator== (const Professor & p) const {
	return (ID == p.getID() && nome == p.get_nome());
}

//=================================================================================================================//

bool  Professor::operator<  (const Professor & p) const {
	return (ID < p.getID());
}




//======================================================================================================================//
//==================================================== CAMPO ===========================================================//
//======================================================================================================================//

Campo::Campo() {
	number = num_max++;
}

//=================================================================================================================//

Campo::Campo(vector<Aula*> usos) {
	number = num_max++;

	for (size_t t = 0; t < usos.size(); t++) {
		marcacoes.push_back(usos.at(t));

		if (usos.at(t)->get_mode == "livre") {
			aulas_livres.push_back(usos.at(t));
		}
	}
}

//=================================================================================================================//

int Campo::get_num() const{
	return number;
}

//=================================================================================================================//

bool Campo::add_class(Aula &utilizacao) {

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

bool Campo::remove_class(Aula &utilizacao) {

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

bool Campo::add_freq(Uso &utilizacao) {

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

bool Campo::remove_freq(Uso &utilizacao) {
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

void Campo::list_classes(Date inicio, Date fim) const{

}

//=================================================================================================================//

void Campo::list_freq(Date inicio, Date fim) const{

}




//====================================================================================================================//
//==================================================== USO ===========================================================//
//====================================================================================================================//

Uso::Uso(Date d, Period t, Utente u) 
: date(d) , period(t) , utente(u){
	mode = "livre";
	pagamento = (t.get_blocks * preco_livre);
}

//=================================================================================================================//

Uso::Uso(Date d, Period t, Utente u, string mode) 
: date(d), period(t), utente(u), mode(mode) {

	if (this->mode == "livre") {
		pagamento = (t.get_blocks * preco_livre);
	}
	else {
		if (u.get_gold) {
			pagamento = preco_aula * 0.85;
		}
		else {
			pagamento = preco_aula;
		}
	}
}

//=================================================================================================================//

int Uso::getID() const{
	return utente.getID;
}

//=================================================================================================================//

void Uso::get_utente(Utente *u) const{

}

//=================================================================================================================//

bool Uso::change_utente(Utente *u) {
	if (utente == *u)
		return false;

	utente = *u;

	return true;
}

//=================================================================================================================//

void Uso::get_date(Date *d) const{
	
}

//=================================================================================================================//

bool Uso::change_date(Date *d) {
	if (date == *d)
		return false;

	date = *d;

	return true;
}

//=================================================================================================================//

void Uso::get_period(Period *t) const{

}

//=================================================================================================================//

bool Uso::change_period(Period *t) {
	if (period == *t)
		return false;

	period = *t;

	return true;
}

//=================================================================================================================//

string Uso::get_mode() const{
	return mode;
}

//=================================================================================================================//

bool Uso::change_mode(string modo) {
	mode = modo;
}

//=================================================================================================================//

double Uso::get_payment() const{
	return pagamento;
}

//=================================================================================================================//

bool Uso::payed() const{
	return (pagamento == 0);
}

//=================================================================================================================//

bool Uso::operator== (const Uso & u) const {
	return (utente.getID() == u.getID() && period == u.get_period() && date == u.get_date() && mode == u.get_mode());
}



//=====================================================================================================================//
//==================================================== AULA ===========================================================//
//=====================================================================================================================//

Aula::Aula(Utente u, Professor p, Date d, Period t)
: Uso(d, t, u, "aula") , prof(p){
	
}

//=================================================================================================================//

int Aula::getID() {
	return Uso::getID();

}

//=================================================================================================================//

void Aula::get_aluno(Utente *u) {
	Uso::get_utente(u);
}

//=================================================================================================================//

bool Aula::change_aluno(Utente *u) {
	Uso::change_utente(u);
}

//=================================================================================================================//

void Aula::get_prof(Professor *p) {

}

//=================================================================================================================//

bool Aula::change_prof(Professor *p) {
	if (prof == *p)
		return false;

	prof = *p;

	return true;
}

//=================================================================================================================//

void Aula::get_date(Date *d) const{
	Uso::get_date(d);
}

//=================================================================================================================//

bool Aula::change_date(Date *d) {
	Uso::change_date(d);
}

//=================================================================================================================//

void Aula::get_period(Period *t) const{
	Uso::get_period(t);
}

//=================================================================================================================//

bool Aula::change_period(Period *t){
	Uso::change_period(t);
}

//=================================================================================================================//

void Aula::print_class() {

}

//=================================================================================================================//

bool Aula::operator== (const Aula & a) const {
	return (Uso::getID == a.getID() && Uso::get_period == a.get_period() && Uso::get_date() == a.get_date() && Uso::get_mode() == a.get_mode() && prof == a.get_prof());
}

//=================================================================================================================//
