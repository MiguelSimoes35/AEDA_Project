#ifndef objetos_h
#define objetos_h

#include <iostream>
#include <vector>
#include "timing.h"

using namespace std;

						//   ----------------------------------   //
						//   -------- Class Prototypes --------   //
						//   ----------------------------------   //

class User;
class Teacher;
class Court;
class Use;
class Class;

						//   -----------------------------------   //
						//   --------- Global Variables --------   //
						//   -----------------------------------   //

const double PRICE_FOR_FREE_USE = 3.0;
const double PRICE_FOR_CLASS = 15.0;

						//   -----------------------------------   //
						//   -------- Class Definitions --------   //
						//   -----------------------------------   //


//=================================================================================================================//

class User {
private:
	static int maior_ID;
	int ID;
	int divida;
	string nome;
	bool cartao_gold;
	vector<Use> utilizacoes;
public:
	User();
	User(string nome);

	int getID() const;
	string get_nome() const;
	bool get_gold() const;
	void gold_user(bool card);
	int get_debt() const;

	bool add_utilizacao(Use &utilizacao);
	bool remove_utilizacao(Use &utilizacao);

	void print_report(Month month) const;
	void print_bill(Month month) const;
	void pay_bill(Month month);

	bool  operator== (const User & u) const;
	bool  operator<  (const User & u) const;

	friend class Empresa;
};

//=================================================================================================================//

class Teacher {
private:
	static int maior_ID;
	int ID;
	string nome;
	bool disponibilidade;

	vector<Class> aulas;

public:
	Teacher();
	Teacher(string nome);

	int getID() const;
	string get_nome() const;
	bool available() const;
	void change_availability(bool change);
	bool add_class(Class &utilizacao);
	bool remove_class(Class &utilizacao);
	void print_schedule(Date inicio, Date fim) const;
	int num_classes(Date inicio, Date fim);
	bool  operator== (const Teacher & p) const;
	bool  operator<  (const Teacher & p) const;

	friend class Empresa;
};

//=================================================================================================================//

class Court {
private:
	static int num_max;
	int number;

public:
	Court();
	Court(vector<Class*> usos);
	int get_num() const;
	bool add_class(Class &utilizacao);
	bool remove_class(Class &utilizacao);
	bool add_freq(Use &utilizacao);
	bool remove_freq(Use &utilizacao);
	void list_classes(Date inicio, Date fim) const;
	void list_freq(Date inicio, Date fim) const;

	vector<Class*> marcacoes;
	vector<Use*> aulas_livres;


	friend class Empresa;
};

//=================================================================================================================//

class Use {
private:
	static int maior_ID;
	User utente;
	Period period;
	Date date;
	string mode;
	double pagamento;

public:
	Use(Date d, Period t, User u);
	Use(Date d, Period t, User u, string mode);
	virtual int getID() const;
	virtual void get_utente(User *u) const;
	virtual bool change_utente(User *u);
	virtual void get_date(Date *d) const;
	virtual bool change_date(Date *d);
	virtual void get_period(Period *t) const;
	virtual bool change_period(Period *t);
	string get_mode() const;
	bool change_mode(string modo);
	double get_payment() const;
	bool payed() const;
	virtual bool operator== (const Use & u) const;



	friend class Empresa;
};

//=================================================================================================================//

class Class: public Use {
private:
	static int maior_ID;
	Teacher prof;

public:
	Class(User u, Teacher p, Date d, Period t);
	int getID();
	void get_aluno(User *u);
	bool change_aluno(User *u);
	void get_prof(Teacher *p);
	bool change_prof(Teacher *p);
	void get_date() const;
	bool change_date(Date *d);
	void get_period() const;
	bool change_period(Period *t);
	void print_class();
	bool operator== (const Class & a) const;



	friend class Empresa;
};

#endif
