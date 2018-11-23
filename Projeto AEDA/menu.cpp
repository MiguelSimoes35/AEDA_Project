#include "menu.h"
#include <iostream>
#include <iomanip>
#include "empresa.h"

using namespace std;
							///////////////////////////////////////
							/////// Menu - Functions Design ///////
							///////////////////////////////////////

Date d = Date(cin);
Empresa e = Empresa(d);

bool clean_input() {
	while (!cin) {
		cin.clear();
		cin.ignore(100000, '\n');
		cout << "Input not valid" << endl;
		return true;
	}
	return false;
}

void classes() {
	int option;
	bool valid_input = false;
	//Selecionada a opção de aulas, podemos escolher duas açoes
	cout << " ______________________________________________________" << endl;
	cout << "|														                          |" << endl;
	cout << "|	Choose an option of the following:					        |" << endl;
	cout << "|													                          	|" << endl;
	cout << "|		1: Schedule Use									                  |" << endl;
	cout << "|		2: Cancel Use							                     		|" << endl;
	cout << "|		0: Back									                      		|" << endl;
	cout << "|______________________________________________________|" << endl << endl;

	while (!valid_input) {
		cout << "What you want to do? ";
		cin >> option;

		if (option == 1) {
			string choice;
			id_t user, coach, court;
			Period p = Period(cin);
			bool valido = false;
			cout << "Do you want a class or a free use? (write class or free) ";
			cin >> choice;
			while (clean_input()) {	//se o input for incorreto, limpa o buffer
				cout << "Write a valid capacity for the court! (Number) ";
				cin >> choice;
			}
			while (!valido) {
				if (choice == "class") { //lançar excecoes
					cout << "What is the user id? ";
					cin >> user;
					while (clean_input()) {	//se o input for incorreto, limpa o buffer
						cout << "Write a valid ID for the user! (just numbers) ";
						cin >> user;
					}
					cout << "What is the coach id? ";
					cin >> coach;
					while (clean_input()) {	//se o input for incorreto, limpa o buffer
						cout << "Write a valid ID for the teacher! (just numbers) ";
						cin >> coach;
					}
					cout << "What is the court id? ";
					cin >> court;
					while (clean_input()) {	//se o input for incorreto, limpa o buffer
						cout << "Write a valid ID for the court! (just numbers) ";
						cin >> court;
					}
					cout << "What day and hour you want? (Write year,month,day,hour,minutes,blocks) ";
					p;
					e.schedule_class(user, coach, court, p);
					cout << "The class is scheduled! " << endl;
					valido = true;
				}

				else if (choice == "free") { //lançar exceções
					cout << "What is the user id? ";
					cin >> user;
					while (clean_input()) {	//se o input for incorreto, limpa o buffer
						cout << "Write a valid ID for the user! (just numbers) ";
						cin >> user;
					}
					cout << endl << "What is the court id? ";
					cin >> court;
					while (clean_input()) {	//se o input for incorreto, limpa o buffer
						cout << "Write a valid ID for the court! (just numbers) ";
						cin >> court;
					}
					cout << endl << "What day and hour you want? (Write year,month,day,hour,minutes,blocks) ";
					p;
					e.schedule_free_use(user, court, p);
					cout << "The free use is scheduled! " << endl;
					valido = true;
				}

				else {
					clean_input();
					valido = false;
				}
			}
			valid_input = false;
		}

		else if (option == 2) {
			id_t user, cl;
			cout << "What is the user ID? ";
			cin >> user;
			while (clean_input()) {	//se o input for incorreto, limpa o buffer
				cout << "Write a valid ID for the user! (just numbers) ";
				cin >> user;
			}
			cout << "What is the class ID? ";
			cin >> cl;
			while (clean_input()) {	//se o input for incorreto, limpa o buffer
				cout << "Write a valid ID for the class! (just numbers) ";
				cin >> cl;
			}
			e.cancel_use(user, cl);
			cout << "The use is canceled! " << endl;
			valid_input = false;
		}

		else if (option == 0) {
			valid_input = true;
			manage_users();
		}

		else {
			clean_input();
			valid_input = false;
		}
	}
}

void expenses() {
	int option;
	bool valid_input = false;
	//Selecionada a opção de despesas, podemos escolher um conjunto de ações de 3
	cout << " ______________________________________________________" << endl;
	cout << "|														                          |" << endl;
	cout << "|	Choose an option of the following:			        		|" << endl;
	cout << "|													                           	|" << endl;
	cout << "|		1: Print bill						                    			|" << endl;
	cout << "|		2: Get debt							                     			|" << endl;
	cout << "|		3: Pay debt					                    					|" << endl;
	cout << "|		0: Back						                      					|" << endl;
	cout << "|______________________________________________________|" << endl << endl;

	while (!valid_input) {
		cout << "What you want to do? ";
		cin >> option;

		if (option == 1) {
			string name;
			cout << "What is the name of the user? ";
			cin >> name;
			while (clean_input()) {
				cout << "Write a valid name! (Just with letters) ";
				cin >> name;
			}
			try {
				e.print_bill(e.find_user(name), cout);
				valid_input = false;
			}
			catch (InexistentObject &exc1) {
				exc1.what();
			}
			catch (SameName &exc2) {
				exc2.what();
			}
		}

		else if (option == 2) {
			int ID;
			cout << "What is the ID of the user? ";
			cin >> ID;
			while (clean_input()) {
				cout << "Write a valid ID! (Just with numbers) ";
				cin >> ID;
			}
			e.get_debt(ID);
			valid_input = false;
		}

		else if (option == 3) {
			int ID;
			cout << "What is the ID of the user? ";
			cin >> ID;
			while (clean_input()) {
				cout << "Write a valid ID! (Just with numbers) ";
				cin >> ID;
			}
			e.pay_debt(ID);
			valid_input = false;
		}

		else if (option == 0) {
			valid_input = true;
			manage_users();
		}
	}
}

void edit_users() {
	int option;
	bool valid_input = false;
	//Selecionada a opção de gestão de utentes, podemos escolher um conjunto de ações de 3
	cout << " ______________________________________________________" << endl;
	cout << "|													                            |" << endl;
	cout << "|	Choose an option of the following:				        	|" << endl;
	cout << "|													                           	|" << endl;
	cout << "|		1: Add User									                    	|" << endl;
	cout << "|		2: Remove User						                  			|" << endl;
	cout << "|		3: Find User						                    			|" << endl;
	cout << "|		4: List of Users					                  			|" << endl;
	cout << "|		5: See User Schedule				                			|" << endl;
	cout << "|		0: Back											                      |" << endl;
	cout << "|______________________________________________________|" << endl << endl;
	
	while (!valid_input) {
		cout << "What you want to do? ";
		cin >> option;

		if (option == 1) {
			string name, gc;
			bool gold_card;
			cout << "Name of the new user: ";
			getline(cin, name);
			while (clean_input()) {	//se o input for incorreto, limpa o buffer
				cout << "Write a valid name for the user! (just letters and spaces) ";
				getline(cin, name);
			}
			cout << "Do you want to have a gold card? (yes or no in lower case) ";
			cin >> gc;
			while (clean_input()) {	//se o input for incorreto, limpa o buffer
				cout << "Write a valid ID for the user! (just letters) ";
				cin >> gc;
			}
			if (gc == "yes")
				gold_card = true;
			else if (gc == "no")
				gold_card = false;
			else {
				while (clean_input()) {
					cout << "Please read the question again!" << endl;
					cin >> gc;
				}
			}
			e.add_utente(name, gold_card);
			cout << "The user is created! " << endl;
			valid_input = false;
		}

		else if (option == 2) {
			int ID;
			cout << "What is the ID of the user? ";
			cin >> ID;
			while (clean_input()) {
				cout << "Write a valid ID! (Just with numbers) ";
				cin >> ID;
			}
			e.remove_utente(ID);
			cout << "The user is removed! " << endl;
			valid_input = false;
		}

		else if (option == 3) {
			string type, name;
			int ID;
			bool valido = false;
			cout << "What info do you have about the user, ID or Name? (Write ID or Name) ";
			getline(cin, type);
			//TO DO: Erros
			while (!valido) {
				if (type == "ID") {
					cout << "What is the ID? ";
					cin >> ID;
					while (clean_input()) {
						cout << "Write a valid ID! (Just with numbers) ";
						getline(cin, name);
					}
					e.find_user(ID);
					valido = true;
				}
				if (type == "Name") {
					cout << "What is the name? ";
					getline(cin, name);
					while (clean_input()) {
						cout << "Write a valid name! (Just with letters and blank spaces) ";
						getline(cin, name);
					}
					e.find_user(name);
					valido = true;
				}
				valid_input = false;
			}
		}

		else if (option == 4) {
			e.list_utentes(cout);
			valid_input = false;
		}

		else if (option == 5) {
			int ID;
			cout << "What is the ID? ";
			cin >> ID;
			while (clean_input()) {
				cout << "Write a valid ID! (Just with numbers) ";
				cin >> ID;
			}
			e.print_user_schedule(ID, cout);
			valid_input = false;
		}

		else if (option == 0) {
			valid_input = true;
			manage_users();
		}

		else {
			valid_input = false;
			clean_input();
		}
	}
}

void manage_users() {
	int option;
	bool valid_input = false;
	//Selecionada a opção de gestão de utentes, podemos escolher um conjunto de ações de 3
	cout << " ______________________________________________________" << endl;
	cout << "|														                          |" << endl;
	cout << "|	Choose an option of the following:			        		|" << endl;
	cout << "|												                          		|" << endl;
	cout << "|		1: Edit Users					                    				|" << endl;
	cout << "|		2: Expenses							                    			|" << endl;
	cout << "|		3: Classes								                    		|" << endl;
	cout << "|		0: Back										                      	|" << endl;
	cout << "|______________________________________________________|" << endl << endl;

	while (!valid_input) {
		cout << "What you want to do? ";
		cin >> option;

		if (option == 1) {
			edit_users();
			valid_input = true;
		}

		else if (option == 2) {
			expenses();
			valid_input = true;
		}

		else if (option == 3) {
			classes();
			valid_input = true;
		}

		else if (option == 0) {
			secondary_menu();
			valid_input = true;
		}

		else {
			clean_input();
			valid_input = false;
		}
	}
}

void manage_teachers() {
	int option;
	bool valid_input = false;
	//Selecionada a opção de gestão de professores, podemos escolher um conjunto de ações de 5
	cout << " ______________________________________________________" << endl;
	cout << "|													                          	|" << endl;
	cout << "|	Choose an option of the following:		        			|" << endl;
	cout << "|													                          	|" << endl;
	cout << "|		1: Add Teacher							                  		|" << endl;
	cout << "|		2: Remove Teacher						                  		|" << endl;
	cout << "|		3: Give Class								                    	|" << endl;
	cout << "|		4: See Teachers								                  	|" << endl;
	cout << "|		5: See Teacher Schedule					              		|" << endl;
	cout << "|		0: Back										                      	|" << endl;
	cout << "|______________________________________________________|" << endl << endl;

	while (!valid_input) {
		cout << "What you want to do? ";
		cin >> option;

		if (option == 1) {
			string name;
			cout << "What is the name of the teacher? ";
			cin >> name;
			while (clean_input()) {
				cout << "Write a valid name! (just letters and spaces) ";
				cin >> name;
			}
			e.add_prof(name);
			cout << "Teacher " << name << " added!" << endl;
			valid_input = false;
		}

		else if (option == 2) {
			id_t id;
			cout << "What is the ID of the teacher to remove? ";
			cin >> id;
			while (clean_input()) {
				cout << "Write a valid ID! (just numbers) ";
				cin >> id;
			}
			e.remove_prof(id);
			cout << "Teacher with ID = " << id << " removed!" << endl;
			valid_input = false;
		}

		else if (option == 3) {
			id_t id;
			cout << "What is the ID of the teacher to give the class? ";
			cin >> id;
			while (clean_input()) {
				cout << "Write a valid ID! (just numbers) ";
				cin >> id;
			}
			//TO DO
			//Onde está a classe class?????
			valid_input = false;
		}

		else if (option == 4) {
			e.list_profs(cout);
			valid_input = false;
		}

		else if (option == 5) {
			id_t id;
			cout << "What is the ID of the teacher to see the schedule? ";
			cin >> id;
			while (clean_input()) {
				cout << "Write a valid ID! (just numbers) ";
				cin >> id;
			}
			e.print_prof_schedule(id, cout);
			valid_input = false;
		}

		else if (option == 0) {
			secondary_menu();
			valid_input = true;
		}

		else {
			clean_input();
			valid_input = false;
		}
	}
}

void manage_courts() {
	int option;
	bool valid_input = false;
	//Selecionada a opção de gestão de campos, podemos escolher um conjunto de ações de 5
	cout << " ______________________________________________________" << endl;
	cout << "|														                          |" << endl;
	cout << "|	Choose an option of the following:				        	|" << endl;
	cout << "|													                          	|" << endl;
	cout << "|		1: Add Court						                    			|" << endl;
	cout << "|		2: Remove Court						                  			|" << endl;
	cout << "|		3: See Avalable Courts				              			|" << endl;
	cout << "|		4: See Court Schedule						                 	|" << endl;
	cout << "|		5: See Day Schedule				                				|" << endl;
	cout << "|		0: Back									                      		|" << endl;
	cout << "|______________________________________________________|" << endl << endl;

	while (!valid_input) {
		cout << "What you want to do? ";
		cin >> option;

		if (option == 1) {
			size_t cap;
			cout << "What is the capacity of the court? ";
			cin >> cap;
			while (clean_input()) {	//se o input for incorreto, limpa o buffer
				cout << "Write a valid capacity for the court! (Number) ";
				cin >> cap;
			}
			e.add_court(cap);
			cout << "Court added! " << endl;
			valid_input = false;
		}

		else if (option == 2) {
			id_t id;
			cout << "What is the ID of the court to remove? ";
			cin >> id;
			while (clean_input()) {
				cout << "Write a valid ID! (just numbers) ";
				cin >> id;
			}
			e.remove_court(id);
			cout << "Court removed!" << endl;
			valid_input = false;
		}

		else if (option == 3) {
			string type;
			bool valido = false;
			cout << "What is the date you want to see which courts are available? ";
			Date d1 = Date(cin);
			while (!valido) {
				cout << "You want to see a specific period of the day? (yes or no in lower case)" << endl;
				cin >> type;
				if (type == "yes") {
					valido = true;
					cout << "What is the period of the day? ";
					Period p1 = Period(cin);
					e.print_available_courts(p1);
				}
				else if (type == "no") {
					valido = true;
					e.print_available_courts(d1);
				}
				else
					valido = false;

				valid_input = false;
			}
		}

		else if (option == 4) {
			id_t id;
			cout << "What is the ID of the court to see the schedule? ";
			cin >> id;
			while (clean_input()) {
				cout << "Write a valid ID! (just numbers) ";
				cin >> id;
			}
			cout << "What is the date you want to see the court " << id << " schedule? ";
			Date d1 = Date(cin);
			e.print_court_schedule(id, d1);
			valid_input = false;
		}

		else if (option == 5) {
			cout << "What is the day you want to see the schedule? ";
			Date d1 = Date(cin);
			e.print_day_schedule(d1);
			valid_input = false;
		}

		else if (option == 0) {
			secondary_menu();
			valid_input = true;
		}

		else {
			clean_input();
			valid_input = false;
		}
	}
}

void save_company() {

}

void secondary_menu() {
	int option;
	bool valid_input = false;
	//Após ser criada a empresa podemos realizar várias ações sobre a mesma
	//Da mesma forma o podemos fazer caso a empresa já exista!
	cout << " ____________________________________________________" << endl;
	cout << "|                                                    |" << endl;
	cout << "|	Choose an option of the following:                |" << endl;
	cout << "|                                                    |" << endl;
  cout << "|		1: Manage Users	                                |" << endl;
  cout << "|		2: Manage teachers                              |" << endl;
	cout << "|		3: Manage courts                                |" << endl;
	cout << "|		4: Save company                                 |" << endl;
	cout << "|		0: Exit program                                 |" << endl;
	cout << "|____________________________________________________|" << endl << endl;

	while (!valid_input) {
		cout << "What you want to do? ";
		cin >> option;

		if (option == 1) {
			manage_users();
			valid_input = true;
		}

		else if (option == 2) {
			manage_teachers();
			valid_input = true;
		}

		else if (option == 3) {
			manage_courts();
			valid_input = true;
		}

		else if (option == 4) {
			save_company();
			valid_input = true;
		}

		else if (option == 0) {
			e.save_file();
		}

		else {
			clean_input();
			valid_input = false;
		}
	}
}

void MENU() {
	int option;
	bool valid_input;
	cout << "_____ _____               _____ _____     _____  _____         _____ _____ _____     _____  _____       _____  _____        " << endl;
	cout << "  |  |      |\   | |\   |   |  |         |      |     ||     ||     |  |  |         |     ||      |\   |  |   |     ||      " << endl;
	cout << "  |  |_____ | \  | | \  |   |  |_____    |      |     ||     ||_____|  |  |_____    |_____||_____ | \  |  |   |_____||      " << endl;
	cout << "  |  |      |  \ | |  \ |   |        |   |      |     ||     ||\       |        |   |\     |      |  \ |  |   |     ||      " << endl;
	cout << "  |  |_____ |   \| |   \| __|__ _____|   |_____ |_____||_____|| \      |   _____|   | \    |_____ |   \|  |   |     ||_____ " << endl;
	cout << " ____________________________________________________"  << endl;
	cout << "|                                                    |" << endl;
	cout << "|	Choose an option of the following:                |" << endl;
	cout << "|                                                    |" << endl;
	cout << "|		1: Create a new Company                         |" << endl;
	cout << "|		2: Use an existing Company                      |" << endl;
	cout << "|		0: Exit program                                 |" << endl;
	cout << "|____________________________________________________|" << endl << endl;

	while (valid_input) {
		cout << "What you want to do? ";
		cin >> option;

		if (option == 1) { // Criar empresa

			string name;
			int year, month, day;
			cout << "To create a company, you need to create some courts and hire some teachers..." << endl;
			cout << "But first, lets create the company with a name and a date" << endl;
			cout << "Enter the name ";
			cin >> name;
			while (clean_input())	//se o input for incorreto, limpa o buffer
				cin >> name;
			cout << "Enter the Date (day month year)";
			cin >> day >> month >> year;
			Date date(year, month, day);   //TO DO: lidar com exceções
			e.set_filename(name);

			//Criar os campos
			int courts;
			cout << "How many courts you want to create? ";
			cin >> courts;
			while (clean_input())	//se o input for incorreto, limpa o buffer
				cin >> courts;
			for (int i = 0; i < courts; i++) {
				size_t capacity;
				cout << "What capacity you want for court " << i + 1 << "?";
				cin >> capacity;
				e.add_court(capacity);
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
				e.add_prof(name);
				cin.clear();	//Limpar o buffer
				cin.ignore(1000, '\n');
			}
			e.save_file(name);  //Guardar a empresa
			cout << "New company saved! " << endl;
			valid_input = true;
			//Após ser criada a empresa podemos realizar várias ações sobre a mesma
			secondary_menu();
		}

		else if (option == 2) {
			string name;
			cout << "What is the name of the file to import? ";
			cin >> name;
			while (clean_input())
				cin >> name;
			e.import_file(name);
			valid_input = true;
			secondary_menu();
		}

		else if (option == 0) {

			valid_input = true;
		}

		else {
			clean_input();
			valid_input = false;
		}
	}
}
