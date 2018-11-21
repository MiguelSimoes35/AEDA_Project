#include <iostream>
#include "empresa.h"
#define LOCALE_PT
using namespace std;

void MENU() {
	int option;

	cout << "Tennis Courts Rental" << endl; //Melhorar intro
	cout << " ____________________________________________________" << endl;
	cout << "|                                                    |" << endl;
	cout << "|	Choose an option of the following:                |" << endl;
	cout << "|                                                    |" << endl;
	cout << "|		1: Create a new Company                       |" << endl;
	cout << "|		2: Use an existing Company                    |" << endl;
	cout << "|		0: Exit program                               |" << endl;
	cout << "|____________________________________________________|" << endl << endl;

	cout << "What you want to do? ";
	cin >> option;

	if (option == 1) { // Criar empresa

		string name;
		int year, month, day;
		cout << "To create a company, you need to create some courts and hire some teachers..." << endl;
		cout << "But first, lets create the company with a name and a date" << endl;
		cout << "Enter the name ";
		cin >> name;	//TO DO: limpar o buffer
		cout << "Enter the Date (day month year)";
		cin >> day >> month >> year;
		Date date(year, month, day);   //TO DO: lidar com exceções
		Empresa(date, name);

		//Criar os campos
		int courts;
		cout << "How many courts you want to create? ";
		cin >> courts;
		while (clean_input())	//se o input for incorreto, limpa o buffer
			cin >> courts;
		for (size_t i = 0; i < courts; i++) {
			int capacity;
			cout << "What capacity you want for court " << i + 1 << "?";
			cin >> capacity;
			add_court(capacity);
			cin.clear();	//Limpar o buffer
			cin.ignore(1000, '\n');
		}

		//Criar os professores
		int teachers;
		cout << "How many teachers you want for your company? ";
		cin >> teachers;
		while (clean_input())	//se o input for incorreto, limpa o buffer
			cin >> teachers;
		for (size_t i = 0; i < teachers; i++) {
			string name;
			cout << "What is the name of the teacher " << i + 1 << "?";
			cin >> name;
			add_prof(name);
			cin.clear();	//Limpar o buffer
			cin.ignore(1000, '\n');
		}

		//Após ser criada a empresa podemos realizar várias ações sobre a mesma
		secondary_menu();
	}

	else if (option == 2) {
		//TO DO: Importar ficheiro de empresa existente
		secondary_menu();
	}

	else if (option == 0) {

	}

	else {
		clean_input();
		cout << "What you want to do? (Choose one of the available options)";
		cin >> option;
	}
}

void secondary_menu() {

	int option;

	//Após ser criada a empresa podemos realizar várias ações sobre a mesma
	cout << " ____________________________________________________" << endl;
	cout << "|                                                    |" << endl;
	cout << "|	Choose an option of the following:                |" << endl;
	cout << "|                                                    |" << endl;
	cout << "|		1: Manage Users	                              |" << endl;
	cout << "|		2: Manage teachers                            |" << endl;
	cout << "|		3: Manage courts                              |" << endl;
	cout << "|		4: Save company                               |" << endl;
	cout << "|		0: Exit program                               |" << endl;
	cout << "|____________________________________________________|" << endl << endl;

	cout << "What you want to do? ";
	cin >> option;

	if (option == 1) {
		manage_users();
	}

	else if (option == 2) {

	}

	else if (option == 3) {

	}

	else if (option == 4) {

	}

	else if (option == 0) {

	}

	else {
		clean_input();
		cout << "What you want to do? (Choose one of the available options)";
		cin >> option;
	}

}

void manage_users() {

	int option;

	//Selecionada a opção de gestão de utentes, podemos escolher um conjunto de ações de 3
	cout << " ____________________________________________________" << endl;
	cout << "|                                                    |" << endl;
	cout << "|	Choose an option of the following:                |" << endl;
	cout << "|                                                    |" << endl;
	cout << "|		1: Edit Users                                 |" << endl;
	cout << "|		2: Expenses                                   |" << endl;
	cout << "|		3: Classes                                    |" << endl;
	cout << "|		0: Back                                       |" << endl;
	cout << "|____________________________________________________|" << endl << endl;

	cout << "What you want to do? ";
	cin >> option;

	if (option == 1) {
		edit_users();
	}

	else if (option == 2) {

	}

	else if (option == 3) {

	}

	else if (option == 0) {
		secondary_menu();
	}

	else {
		clean_input();
		cout << "What you want to do? (Choose one of the available options)";
		cin >> option;
	}
}

void edit_users() {
	int option;

	//Selecionada a opção de gestão de utentes, podemos escolher um conjunto de ações de 3
	cout << " ____________________________________________________" << endl;
	cout << "|                                                    |" << endl;
	cout << "|	Choose an option of the following:                |" << endl;
	cout << "|                                                    |" << endl;
	cout << "|		1: Add User                                   |" << endl;
	cout << "|		2: Remove User                                |" << endl;
	cout << "|		3: Find User                                  |" << endl;
	cout << "|		4: List of Users                              |" << endl;
	cout << "|		5: See User Schedule                          |" << endl;
	cout << "|		0: Back                                       |" << endl;
	cout << "|____________________________________________________|" << endl << endl;

	cout << "What you want to do? ";
	cin >> option;

	if (option == 1) {
		string name, gc;
		bool gold_card;
		cout << "Name of the new user: ";
		getline(cin, name);
		//TO DO: See exceptions
		cout << "Do you want to have a gold card? (yes or no in lower case) ";
		cin >> gc;
		if (gc == "yes")
			gold_card = true;
		else if (gc == "no")
			gold card = false;
		else {
			while (clean_input()) {
				cout << "Please read the question again!" << endl;
				cin >> gc;
			}
		}

		add_utente(name, gold_card);
	}

	else if (option == 2) {
		string type, name;
		int ID;
		cout << "What info do you have about the user, ID or Name? (Write ID or Name) ";
		//TO DO: Erros
		getline(cin, type);
		if (type == "ID") {
			cout << "What is the ID? ";
			cin >> ID;
			while (clean_input()) {
				cout << "Write a valid ID! (Just with numbers) ";
				getline(cin, name);
				remove_utente(ID);
			}
		}
		if (type == "Name") {
			cout "What is the name? ";
			getline(cin, name);
			while (clean_input()) {
				cout << "Write a valid name! (Just with letters and blank spaces) ";
				getline(cin, name);
			}
			remove_utente(name);
		}
	}

	else if (option == 3) {
		string type, name;
		int ID;
		cout << "What info do you have about the user, ID or Name? (Write ID or Name) ";
		getline(cin, type);
		//TO DO: Erros
		if (type == "ID") {
			cout << "What is the ID? ";
			cin >> ID;
			while (clean_input()) {
				cout << "Write a valid ID! (Just with numbers) ";
				getline(cin, name);
				exists_utente(ID);
			}
		}
		if (type == "Name") {
			cout << "What is the name? ";
			getline(cin, name);
			while (clean_input()) {
				cout << "Write a valid name! (Just with letters and blank spaces) ";
				getline(cin, name);
			}
			exists_utente(name);
		}
	}

	else if (option == 4) {
		//VER NOVA FUNÇÃO
		list_utentes();
	}

	else if (option == 5) {
		string type, name;
		int ID;
		cout << "What info do you have about the user, ID or Name? (Write ID or Name) ";
		getline(cin, type);
		//TO DO: Erros
		if (type == "ID") {
			cout << "What is the ID? ";
			cin >> ID;
			while (clean_input()) {
				cout << "Write a valid ID! (Just with numbers) ";
				getline(cin, name);
			}
			print_user_schedule(ID);
		}
		if (type == "Name") {
			cout << "What is the name? ";
			getline(cin, name);
			while (clean_input()) {
				cout << "Write a valid name! (Just with letters and blank spaces) ";
				getline(cin, name);
			}
			print_user_schedule(name);
		}
	}

	else if (option == 0) {
		manage_users();
	}

	else {
		clean_input();
		cout << "What you want to do? (Choose one of the available options)";
		cin >> option;
	}
}

void expenses() {
	//Selecionada a opção de despesas, podemos escolher um conjunto de ações de 3
	cout << " ____________________________________________________" << endl;
	cout << "|                                                    |" << endl;
	cout << "|	Choose an option of the following:                |" << endl;
	cout << "|                                                    |" << endl;
	cout << "|		1: Print bill                                 |" << endl;
	cout << "|		2: Get debt                                   |" << endl;
	cout << "|		3: Pay debt                                   |" << endl;
	cout << "|		0: Back                                       |" << endl;
	cout << "|____________________________________________________|" << endl << endl;

	cout << "What you want to do? ";
	cin >> option;

	if (option == 1) {
		string type, name;
		int ID;
		cout << "What info do you have about the user, ID or Name? (Write ID or Name) ";
		getline(cin, type);
		//TO DO: Erros
		if (type == "ID") {
			cout << "What is the ID? ";
			cin >> ID;
			while (clean_input()) {
				cout << "Write a valid ID! (Just with numbers) ";
				getline(cin, name);
			}
			pay_debt(ID);
		}
		if (type == "Name") {
			cout << "What is the name? ";
			getline(cin, name);
			while (clean_input()) {
				cout << "Write a valid name! (Just with letters and blank spaces) ";
				getline(cin, name);
			}
			pay_debt(name);
		}

	}

	if (option == 2) {
		string type, name;
		int ID;
		cout << "What info do you have about the user, ID or Name? (Write ID or Name) ";
		getline(cin, type);
		//TO DO: Erros
		if (type == "ID") {
			cout << "What is the ID? ";
			cin >> ID;
			while (clean_input()) {
				cout << "Write a valid ID! (Just with numbers) ";
				getline(cin, name);
			}
			get_debt(ID);
		}
		if (type == "Name") {
			cout << "What is the name? ";
			getline(cin, name);
			while (clean_input()) {
				cout << "Write a valid name! (Just with letters and blank spaces) ";
				getline(cin, name);
			}
			get_debt(name);
		}

	}

	if (option == 3) {
		string type, name;
		int ID;
		cout << "What info do you have about the user, ID or Name? (Write ID or Name) ";
		getline(cin, type);
		//TO DO: Erros
		if (type == "ID") {
			cout << "What is the ID? ";
			cin >> ID;
			while (clean_input()) {
				cout << "Write a valid ID! (Just with numbers) ";
				getline(cin, name);
			}
			pay_debt(ID);
		}
		if (type == "Name") {
			cout << "What is the name? ";
			getline(cin, name);
			while (clean_input()) {
				cout << "Write a valid name! (Just with letters and blank spaces) ";
				getline(cin, name);
			}
			pay_debt(name);
		}

	}

	if (option == 0) {
		manage_users();
	}
}

bool clean_input() {
	while (!cin) {
		cin.clear();
		cin.ignore(100000, '\n');
		cout << "Input not valid" << endl;
		return true;
	}
	return false;
}

int main() {
	cout << "HI!" << endl;

	system("pause");

	return 0;
}