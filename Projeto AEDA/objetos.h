#ifndef objetos_h
#define objetos_h

#include <iostream>
#include <vector>

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
	vector<int> utilizacoes;
public:
	Utente();
	Utente(string nome);

	int getID() const;
	string get_nome() const;
	bool gold_user() const;

	bool add_utilizacao(Uso &utilizacao);
	bool remove_utilizacao(Uso &utilizacao);

	void print_report(Month month) const;
	void print_bill(Month month) const;
	void pay_bill(Month month);
	int get_debt() const;

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

	vector<int> aulas;

public:
	Professor();
	Professor(string nome);

	int getID();
	string get_nome();
	bool available();
	void change_availability();
	bool add_class(Uso &utilizacao);
	bool remove_class(Uso &utilizacao);
	void print_schedule(Date inicio, Date fim);
	int num_classes(Date inicio, Date fim);
	bool  operator== (const Professor & p) const;
	bool  operator<  (const Professor & p) const;

	friend class Empresa;
};

//=================================================================================================================//

class Campo {
private:
	static int num;

public:
	Campo();
	Campo(vector<Aula*> aulas);
	int get_num();
	bool add_class(Uso &utilizacao);
	bool remove_class(Uso &utilizacao);
	bool add_freq(Uso &utilizacao);
	bool add_freq(Uso &utilizacao);
	void list_classes(Date inicio, Date fim);
	void list_freq(Date inicio, Date fim);

	vector<Aula*> marcacoes;
	vector<Aula*> aulas_livres;



	friend class Empresa;
};

//=================================================================================================================//

class Uso {
private:
	static int maior_ID;
	Utente aluno;
	Period period;
	Date date;
	string mode;
	bool pagamento;

public:
	Uso();
	Uso(Date d, Period t, Utente u);
	virtual int getID();
	virtual void get_aluno(Utente *u);
	virtual bool change_aluno(Utente *u);
	virtual void get_date(Date *d);
	virtual bool change_date(Date *d);
	virtual void get_period(Period *t);
	virtual bool change_period(Period *t);
	string get_mode();
	bool change_mode(string modo);
	bool payment();
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
	void get_date(Date *d);
	bool change_date(Date *d);
	void get_period(Period *t);
	bool change_period(Period *t);
	void print_class();
	bool operator== (const Aula & a) const;



	friend class Empresa;
};

#endif
