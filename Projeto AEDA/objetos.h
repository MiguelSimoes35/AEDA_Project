#ifndef objetos.h
#define objetos_h

#include <iostream>
#include <vector>

using namespace std;

						//   ----------------------------------   //
						//   -------- Class Prototypes --------   //
						//   ----------------------------------   //

class Mes;
class Data;
class Periodo;
class Utente;
class Professor;
class Campo;
class Uso;
class Aula;

						//   -----------------------------------   //
						//   -------- Class Definitions --------   //
						//   -----------------------------------   //

class Mes {
protected:
	int mes;
	int ano;

public:
	Mes();
	Mes(int mes, int ano);
	virtual int get_mes();
	virtual int get_ano();
	Mes & operator++ () const;
	Mes & operator-- () const;
	bool & operator== (Mes & m) const;
	bool & operator<  (Mes & m) const;

};

//=======================================================================================================================//

class Data: public Mes{
private:
	int dia;

public:
	Data();
	Data(int d, int m, int a);
	int get_dia();
	int get_mes();
	int get_ano();
	Data  operator++ () const;
	Data  operator-- () const;
	bool  operator== (const Data & d) const;
	bool  operator<  (const Data & d) const;
};

//=======================================================================================================================//

class  Periodo{
private:
	int hora0, hora1;
	int minutos0, minutos1;
	int duracao;

public:
	Periodo();
	Periodo(int h0, int m0, int h1, int min1);
	int get_duracao();
	bool  operator== (const Periodo & p) const;
};

//=======================================================================================================================//

class Utente {
private:
	static int maior_ID;
	int ID;
	int divida;
	string nome;
	bool cartao_gold;

public:
	Utente();
	Utente(string nome);
	int getID();
	string get_nome();
	bool gold_user();
	bool add_utilizacao(Uso &utilizacao);
	bool remove_utilizacao(Uso &utilizacao);
	void print_report(int mes);
	void print_bill(int mes);
	int get_debt();
	bool  operator== (const Utente & u) const;
	bool  operator<  (const Utente & u) const;

	vector<Uso*> utilizacoes;



	friend class Empresa;
};

//=======================================================================================================================//

class Professor {
private:
	static int maior_ID;
	int ID;
	string nome;
	bool disponibilidade;

public:
	Professor();
	Professor(string nome);
	int getID();
	string get_nome();
	bool available();
	void change_availability();
	bool add_class(Uso &utilizacao);
	bool remove_class(Uso &utilizacao);
	void print_schedule(Data inicio, Data fim);
	int num_classes(Data inicio, Data fim);
	bool  operator== (const Professor & p) const;
	bool  operator<  (const Professor & p) const;

	vector<Aula*> aulas;



	friend class Empresa;
};

//=======================================================================================================================//

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
	void list_classes(Data inicio, Data fim);
	void list_freq(Data inicio, Data fim);

	vector<Aula*> marcacoes;
	vector<Aula*> aulas_livres;



	friend class Empresa;
};

//=======================================================================================================================//

class Uso {
private:
	static int maior_ID;
	Utente aluno;
	Periodo period;
	Data date;
	string mode;
	bool pagamento;

public:
	Uso();
	Uso(Data d, Periodo t, Utente u);
	virtual int getID();
	virtual void get_aluno(Utente *u);
	virtual bool change_aluno(Utente *u);
	virtual void get_data(Data *d);
	virtual bool change_data(Data *d);
	virtual void get_periodo(Periodo *t);
	virtual bool change_periodo(Periodo *t);
	string get_mode();
	bool change_mode(string modo);
	bool payment();
	virtual bool operator== (const Uso & u) const;



	friend class Empresa;
};

//=======================================================================================================================//

class Aula: public Uso {
private:
	static int maior_ID;
	Professor prof;

public:
	Aula(Utente u, Professor p, Data d, Periodo t);
	int getID();
	void get_aluno(Utente *u);
	bool change_aluno(Utente *u);
	void get_prof(Professor *p);
	bool change_prof(Professor *p);
	void get_data(Data *d);
	bool change_data(Data *d);
	void get_periodo(Periodo *t);
	bool change_periodo(Periodo *t);
	void print_class();
	bool operator== (const Aula & a) const;



	friend class Empresa;
};

#endif
