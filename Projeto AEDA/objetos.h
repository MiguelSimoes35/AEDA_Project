#ifndef objetos_h
#define objetos_h

#include <iostream>
#include <vector>
#include "timing.h"

using namespace std;

						//   ----------------------------------   //
						//   -------- Class Prototypes --------   //
						//   ----------------------------------   //

class Utente;
class Professor;
class Campo;
class Uso;
class Aula;

						//   -----------------------------------   //
						//   --------- Global Variables --------   //
						//   -----------------------------------   //

double preco_livre = 3.0;
double preco_aula = 15.0;

						//   -----------------------------------   //
						//   -------- Class Definitions --------   //
						//   -----------------------------------   //


//=================================================================================================================//

class Utente {
private:
	static int maior_ID;
	int ID;
	int divida;
	string nome;
	bool cartao_gold;
	vector<Uso> utilizacoes;
public:
	Utente();
	Utente(string nome);

	int getID() const;
	string get_nome() const;
	bool get_gold() const;
	void gold_user(bool card);
	int get_debt() const;

	bool add_utilizacao(Uso &utilizacao);
	bool remove_utilizacao(Uso &utilizacao);

	void print_report(Month month) const;
	void print_bill(Month month) const;
	void pay_bill(Month month);

	bool  operator== (const Utente & u) const;
	bool  operator<  (const Utente & u) const;

	friend class Empresa;
};

//=================================================================================================================//

class Professor {
private:
	static int maior_ID;
	int ID;
	string nome;
	bool disponibilidade;

	vector<Aula> aulas;

public:
	Professor();
	Professor(string nome);

	int getID() const;
	string get_nome() const;
	bool available() const;
	void change_availability(bool change);
	bool add_class(Aula &utilizacao);
	bool remove_class(Aula &utilizacao);
	void print_schedule(Date inicio, Date fim) const;
	int num_classes(Date inicio, Date fim);
	bool  operator== (const Professor & p) const;
	bool  operator<  (const Professor & p) const;

	friend class Empresa;
};

//=================================================================================================================//

class Campo {
private:
	static int num_max;
	int number;

public:
	Campo();
	Campo(vector<Aula*> usos);
	int get_num() const;
	bool add_class(Aula &utilizacao);
	bool remove_class(Aula &utilizacao);
	bool add_freq(Uso &utilizacao);
	bool remove_freq(Uso &utilizacao);
	void list_classes(Date inicio, Date fim) const;
	void list_freq(Date inicio, Date fim) const;

	vector<Aula*> marcacoes;
	vector<Uso*> aulas_livres;


	friend class Empresa;
};

//=================================================================================================================//

class Uso {
private:
	static int maior_ID;
	Utente utente;
	Period period;
	Date date;
	string mode;
	double pagamento;

public:
	Uso(Date d, Period t, Utente u);
	Uso(Date d, Period t, Utente u, string mode);
	virtual int getID() const;
	virtual void get_utente(Utente *u) const;
	virtual bool change_utente(Utente *u);
	virtual void get_date(Date *d) const;
	virtual bool change_date(Date *d);
	virtual void get_period(Period *t) const;
	virtual bool change_period(Period *t);
	string get_mode() const;
	bool change_mode(string modo);
	double get_payment() const;
	bool payed() const;
	virtual bool operator== (const Uso & u) const;



	friend class Empresa;
};

//=================================================================================================================//

class Aula: public Uso {
private:
	static int maior_ID;
	Professor prof;

public:
	Aula(Utente u, Professor p, Date d, Period t);
	int getID();
	void get_aluno(Utente *u);
	bool change_aluno(Utente *u);
	void get_prof(Professor *p);
	bool change_prof(Professor *p);
	void get_date() const;
	bool change_date(Date *d);
	void get_period() const;
	bool change_period(Period *t);
	void print_class();
	bool operator== (const Aula & a) const;



	friend class Empresa;
};

#endif
