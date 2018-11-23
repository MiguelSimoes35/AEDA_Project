#include "menu.h"


using namespace std;
							///////////////////////////////////////
							/////// Menu - Functions Design ///////
							///////////////////////////////////////

Date d = Date(1,1,1);
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

	while (!valid_input) {
		cin.clear();
		cout << " ______________________________________________________" << endl;
		cout << "|                                                      |" << endl;
		cout << "|   Choose an option of the following:                 |" << endl;
		cout << "|                                                      |" << endl;
		cout << "|      1: Schedule Use                                 |" << endl;
		cout << "|      2: Cancel Use                                   |" << endl;
		cout << "|      3: Attend class                                 |" << endl;
		cout << "|      4: User report                                  |" << endl;
		cout << "|      0: Back                                         |" << endl;
		cout << "|______________________________________________________|" << endl << endl;


		cout << " What do you want to do? ";
		cin >> option;

		if (option == 1) {
			string choice, user, coach;
			id_t court;
			Period p(1,1,1,1,1,1);
			bool valido = false;
			cout << "Do you want a class or a free use? (write class or free) ";
			cin >> choice;
			while (clean_input()) {	//se o input for incorreto, limpa o buffer
				cout << "Write a valid choice! (class or free use) ";
				cin >> choice;
			}
			while (!valido) {
				if (choice == "class") { //lançar excecoes
					cout << "What is the user name? ";
					cin >> user;
					while (clean_input()) {	//se o input for incorreto, limpa o buffer
						cout << "Write a valid name for the user! (just letters) ";
						cin >> user;
					}
					cout << "What is the coach name? ";
					cin >> coach;
					while (clean_input()) {	//se o input for incorreto, limpa o buffer
						cout << "Write a valid name for the teacher! (just letters) ";
						cin >> coach;
					}
					cout << "What is the court number? ";
					cin >> court;
					while (clean_input()) {	//se o input for incorreto, limpa o buffer
						cout << "Write a valid number for the court! (just numbers) ";
						cin >> court;
					}
					cout << "What day and hour you want? (Write year,month,day,hour,minutes,blocks) ";
					int year, month, day, hour, minutes, blocks;
					cin >> year >> month >> day >> hour >> minutes >> blocks;
					p = Period(year, month, day, hour, minutes, blocks);
					try {
						e.schedule_class(e.find_user(user), e.find_teacher(coach), court, p);
						cout << "The class is scheduled! " << endl;
						valido = true;
					}
					catch (InexistentObject &exc1) {
						exc1.what();
					}
					catch (SameName &exc2) {
						exc2.what();
					}
				}

				else if (choice == "free") { //lançar exceções
					cout << "What is the user name? ";
					cin >> user;
					while (clean_input()) {	//se o input for incorreto, limpa o buffer
						cout << "Write a valid name for the user! (just letters) ";
						cin >> user;
					}
					cout << endl << "What is the court number? ";
					cin >> court;
					while (clean_input()) {	//se o input for incorreto, limpa o buffer
						cout << "Write a valid ID for the court! (just numbers) ";
						cin >> court;
					}
					cout << endl << " What day and hour do you want? (Write year,month,day,hour,minutes,blocks) ";
					int year, month, day, hour, minutes, blocks;
					cin >> year >> month >> day >> hour >> minutes >> blocks;
					p = Period(year,month,day,hour,minutes,blocks);
					try {
						e.schedule_free_use(e.find_user(user), court, p);
						cout << " The free use is scheduled! " << endl;
						valido = true;
					}
					catch (InexistentObject &exc1) {
						exc1.what();
					}
					catch (SameName &exc2) {
						exc2.what();
					}
				}

				else {
					clean_input();
					valido = false;
				}
			}
			valid_input = false;
		}

		else if (option == 2) {
			string user;
			id_t cl;
			cout << " What is the user name? ";
			cin >> user;
			while (clean_input()) {	//se o input for incorreto, limpa o buffer
				cout << " Write a valid name for the user! (just letters) ";
				cin >> user;
			}
			cout << " What is the class number? ";
			cin >> cl;
			while (clean_input()) {	//se o input for incorreto, limpa o buffer
				cout << " Write a valid number for the class! (just numbers) ";
				cin >> cl;
			}
			try {
				e.cancel_use(e.find_user(user), cl);
				cout << " The use is canceled! " << endl;
				valid_input = false;
			}
			catch (InexistentObject &exc1) {
				exc1.what();
			}
			catch (SameName &exc2) {
				exc2.what();
			}
		}

		else if (option == 3) {
			string name;
			cout << " What is the name of the user? ";
			cin >> name;
			while (clean_input()) {
				cout << " Write a valid name! (just letters) ";
				cin >> name;
			}
			try {
				e.print_user_schedule(e.find_user(name));
				int id;
				cout << " What is the number of the class? ";
				cin >> id;
				while (clean_input()) {
					cout << " Write a valid number!";
					cin >> id;
				}
				e.attend_class(e.find_user(name), id);
				cout << " Completed classes and assignments!" << endl;
				valid_input = false;
			}
			catch (InexistentObject &exc1) {
				exc1.what();
			}
			catch (SameName &exc2) {
				exc2.what();
			}
		}

		else if (option == 4) {
		string name;
		cout << " What is the name of the user? ";
		cin >> name;
		while (clean_input()) {
			cout << " Write a valid name! (just letters) ";
			cin >> name;
		}
		try {
			e.print_user_report(e.find_user(name));
			valid_input = false;
		}
		catch (InexistentObject &exc1) {
			exc1.what();
		}
		catch (SameName &exc2) {
			exc2.what();
		}
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

	while (!valid_input) {
		cin.clear();
		cout << "  ______________________________________________________" << endl;
		cout << " |                                                      |" << endl;
		cout << " |   Choose an option of the following:                 |" << endl;
		cout << " |                                                      |" << endl;
		cout << " |      1: Print bill                                   |" << endl;
		cout << " |      2: Get debt                                     |" << endl;
		cout << " |      3: Pay debt                                     |" << endl;
		cout << " |      0: Back                                         |" << endl;
		cout << " |______________________________________________________|" << endl << endl;


		cout << " What do you want to do? ";
		cin >> option;

		if (option == 1) {
			string name;
			cout << " What is the name of the user? ";
			cin >> name;
			while (clean_input()) {
				cout << " Write a valid name! (Just with letters) ";
				cin >> name;
			}
			try {
				e.print_bill(e.find_user(name));
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
			string name;
			cout << " What is the name of the user? ";
			cin >> name;
			while (clean_input()) {
				cout << " Write a valid name! (Just with letters) ";
				cin >> name;
			}
			cout << " Your debt: " << endl;
			try {
				e.get_debt(e.find_user(name));
				valid_input = false;
			}
			catch (InexistentObject &exc1) {
				exc1.what();
			}
			catch (SameName &exc2) {
				exc2.what();
			}
		}

		else if (option == 3) {
			string name;
			cout << " What is the name of the user? ";
			cin >> name;
			while (clean_input()) {
				cout << " Write a valid name! (Just with letters) ";
				cin >> name;
			}
			try {
				e.pay_debt(e.find_user(name));
				cout << " Everything is paid!" << endl;
				valid_input = false;
			}
			catch (InexistentObject &exc1) {
				exc1.what();
			}
			catch (SameName &exc2) {
				exc2.what();
			}
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

	while (!valid_input) {

		cin.clear();

		cout << "  ______________________________________________________" << endl;
		cout << " |                                                      |" << endl;
		cout << " |   Choose an option of the following:                 |" << endl;
		cout << " |                                                      |" << endl;
		cout << " |      1: Add User                                     |" << endl;
		cout << " |      2: Remove User                                  |" << endl;
		cout << " |      3: List of Users                                |" << endl;
		cout << " |      4: See User Schedule                            |" << endl;
		cout << " |      0: Back                                         |" << endl;
		cout << " |______________________________________________________|" << endl << endl;


		cout << " What do you want to do? ";
		cin >> option;

		if (option == 1) {
			string name, gc;
			bool gold_card;
			cout << "Name of the new user: ";
			cin >> name;
			while (clean_input()) {	//se o input for incorreto, limpa o buffer
				cout << " Write a valid name for the user! (just letters) ";
				cin >> name;
			}
			cout << " Do you want to have a gold card? (yes or no in lower case) ";
			cin >> gc;
			while (clean_input()) {	//se o input for incorreto, limpa o buffer
				cout << " Write a valid ID for the user! (just letters) ";
				cin >> gc;
			}
			if (gc == "yes")
				gold_card = true;
			else if (gc == "no")
				gold_card = false;
			else {
				while (clean_input()) {
					cout << " Please read the question again!" << endl;
					cin >> gc;
				}
			}
			e.add_utente(name, gold_card);
			cout << " The user is created! " << endl;
			valid_input = false;
		}

		else if (option == 2) {
			string name;
			cout << " What is the name of the user? ";
			cin >> name;
			while (clean_input()) {
				cout << " Write a valid name! (Just with letters) ";
				cin >> name;
			}
			try {
				e.remove_utente(e.find_user(name));
				cout << " The user is removed! " << endl;
				valid_input = false;
			}
			catch (InexistentObject &exc1) {
				exc1.what();
			}
			catch (SameName &exc2) {
				exc2.what();
			}
		}

		else if (option == 3) {
			e.list_utentes();
			valid_input = false;
		}

		else if (option == 4) {
			string name;
			cout << " What is the name of the user? ";
			cin >> name;
			while (clean_input()) {
				cout << " Write a valid name! (Just with letters) ";
				cin >> name;
			}
			try {
				e.print_user_schedule(e.find_user(name));
				valid_input = false;
			}
			catch (InexistentObject &exc1) {
				exc1.what();
			}
			catch (SameName &exc2) {
				exc2.what();
			}

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

	while (!valid_input) {
		cin.clear();

		cout << "  ______________________________________________________" << endl;
		cout << " |                                                      |" << endl;
		cout << " |   Choose an option of the following:                 |" << endl;
		cout << " |                                                      |" << endl;
		cout << " |      1: Edit Users                                   |" << endl;
		cout << " |      2: Expenses                                     |" << endl;
		cout << " |      3: Classes                                      |" << endl;
		cout << " |      0: Back                                         |" << endl;
		cout << " |______________________________________________________|" << endl << endl;


		cout << "What do you want to do? ";
		cin >> option;

		if (option == 1) {
			valid_input = true;
			edit_users();
		}

		else if (option == 2) {
			valid_input = true;
			expenses();
		}

		else if (option == 3) {
			valid_input = true;
			classes();
		}

		else if (option == 0) {
			valid_input = true;
			secondary_menu();
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

	while (!valid_input) {
		cin.clear();
		cout << "  ______________________________________________________" << endl;
		cout << " |                                                      |" << endl;
		cout << " |   Choose an option of the following:                 |" << endl;
		cout << " |                                                      |" << endl;
		cout << " |      1: Add Teacher                                  |" << endl;
		cout << " |      2: Remove Teacher                               |" << endl;
		cout << " |      3: Give Class                                   |" << endl;
		cout << " |      4: See Teachers                                 |" << endl;
		cout << " |      5: See Teacher Schedule                         |" << endl;
		cout << " |      0: Back                                         |" << endl;
		cout << " |______________________________________________________|" << endl << endl;


		cout << " What do you want to do? ";
		cin >> option;

		if (option == 1) {
			string name;
			cout << " What is the name of the teacher? ";
			cin >> name;
			while (clean_input()) {
				cout << " Write a valid name! (just letters) ";
				cin >> name;
			}
			e.add_prof(name);
			cout << " Teacher " << name << " added!" << endl;
			valid_input = false;
		}

		else if (option == 2) {
			string name;
			cout << " What is the name of the teacher? ";
			cin >> name;
			while (clean_input()) {
				cout << " Write a valid name! (just letters) ";
				cin >> name;
			}
			try {
				e.remove_prof(e.find_teacher(name));
				cout << " Teacher removed!" << endl;
				valid_input = false;
			}
			catch (InexistentObject &exc1) {
				exc1.what();
			}
			catch (SameName &exc2) {
				exc2.what();
			}
		}

		else if (option == 3) {
			string name;
			Period p (1,1,1,1,1,1);
			Teacher T = Teacher(name);
			Teacher *t = &T;
			cout << " What is the name of the teacher? ";
			cin >> name;
			while (clean_input()) {
				cout << " Write a valid name! (just letters) ";
				cin >> name;
			}
			try {
				e.print_prof_schedule(e.find_teacher(name));
				Court C(0);
				Court *c = &C;
				Class CL(p, t, c);
				Class *a = &CL;
				e.give_class(e.find_teacher(name), a);
				cout << " Class gived!" << endl;
				valid_input = false;
			}
			catch (InexistentObject &exc1) {
				exc1.what();
			}
			catch (SameName &exc2) {
				exc2.what();
			}
		}

		else if (option == 4) {
			e.list_profs();
			valid_input = false;
		}

		else if (option == 5) {
			string name;
			cout << " What is the name of the teacher? ";
			cin >> name;
			while (clean_input()) {
				cout << " Write a valid name! (just letters) ";
				cin >> name;
			}
			try {
				e.print_prof_schedule(e.find_teacher(name));
				valid_input = false;
			}
			catch (InexistentObject &exc1) {
				exc1.what();
			}
			catch (SameName &exc2) {
				exc2.what();
			}
		}

		else if (option == 0) {
			valid_input = true;
			secondary_menu();
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

	while (!valid_input) {
		cin.clear();

		cout << "  ______________________________________________________" << endl;
		cout << " |                                                      |" << endl;
		cout << " |   Choose an option of the following:                 |" << endl;
		cout << " |                                                      |" << endl;
		cout << " |      1: Add Court                                    |" << endl;
		cout << " |      2: Remove Court                                 |" << endl;
		cout << " |      3: See Available Courts                         |" << endl;
		cout << " |      4: See Court Schedule                           |" << endl;
		cout << " |      5: See Day Schedule                             |" << endl;
		cout << " |      0: Back                                         |" << endl;
		cout << " |______________________________________________________|" << endl << endl;

		cout << " What do you want to do? ";
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
			cout << " Court added! " << endl;
			valid_input = false;
		}

		else if (option == 2) {
			id_t id;
			cout << " What is the number of the court to remove? ";
			cin >> id;
			while (clean_input()) {
				cout << " Write a valid number! (just numbers) ";
				cin >> id;
			}
			e.remove_court(id);
			cout << " Court removed!" << endl;
			valid_input = false;
		}

		else if (option == 3) {
			string type;
			bool valido = false;
			cout << " What is the date you want to see which courts are available? ";
			Date d1 = Date(cin);
			while (!valido) {
				cout << " You want to see a specific period of the day? (yes or no in lower case)" << endl;
				cin >> type;
				if (type == "yes") {
					valido = true;
					cout << " What is the period of the day? ";
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
			cout << " What is the number of the court to see the schedule? ";
			cin >> id;
			while (clean_input()) {
				cout << " Write a valid number! (just numbers) ";
				cin >> id;
			}
			cout << " What is the date you want to see the court " << id << " schedule? ";
			Date d1 = Date(cin);
			e.print_court_schedule(id, d1);
			valid_input = false;
		}

		else if (option == 5) {
			cout << " What is the day you want to see the schedule? ";
			Date d1 = Date(cin);
			e.print_day_schedule(d1);
			valid_input = false;
		}

		else if (option == 0) {
			valid_input = true;
			secondary_menu();
		}

		else {
			clean_input();
			valid_input = false;
		}
	}
}

void secondary_menu() {
	int option;
	bool valid_input = false;
	//Após ser criada a empresa podemos realizar várias ações sobre a mesma
	//Da mesma forma o podemos fazer caso a empresa já exista!

	while (!valid_input) {
		cin.clear();
		cout << "  ____________________________________________________" << endl;
		cout << " |                                                    |" << endl;
		cout << " |   Choose an option of the following:               |" << endl;
		cout << " |                                                    |" << endl;
		cout << " |      1: Manage Users                               |" << endl;
		cout << " |      2: Manage teachers                            |" << endl;
		cout << " |      3: Manage courts                              |" << endl;
		cout << " |      4: Save company                               |" << endl;
		cout << " |      0: Exit program                               |" << endl;
		cout << " |____________________________________________________|" << endl << endl;


		cout << " What do you want to do? ";
		cin >> option;

		if (option == 1) {
			valid_input = true;
			manage_users();
		}

		else if (option == 2) {
			valid_input = true;
			manage_teachers();
		}

		else if (option == 3) {
			valid_input = true;
			manage_courts();
		}

		else if (option == 4) {
			e.save_file();
			valid_input = false;
			cout << " Company saved! " << endl;
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

void MENU() {
	int option;
	bool valid_input = true;
	bool exit = false;

	while (valid_input && !exit) {
		cin.clear();

		cout << endl;
		cout << setw(40) << " _____  _____                  _____  _____           _____   ____            _____  _____  _____          _____   _____         _____   _____         " << endl;
		cout << setw(40) << "   |   |       ||   |  ||   |    |   |               |       |     | |     | |     |   |   |              |     | |       ||   |   |    |     | |      " << endl;
		cout << setw(40) << "   |   |_____  | |  |  | |  |    |   |_____          |       |     | |     | |_____|   |   |_____         |_____| |_____  | |  |   |    |_____| |      " << endl;
		cout << setw(40) << "   |   |       |  | |  |  | |    |         |         |       |     | |     | |  |      |         |        |  |    |       |  | |   |    |     | |      " << endl;
		cout << setw(40) << "   |   |_____  |   ||  |   ||  __|__  _____|         |_____  |_____| |_____| |   |     |    _____|        |   |   |_____  |   ||   |    |     | |_____ " << endl << endl;
		cout << "  ____________________________________________________" << endl;
		cout << " |                                                    |" << endl;
		cout << " |   Choose an option of the following:               |" << endl;
		cout << " |                                                    |" << endl;
		cout << " |      1: Create a new Company                       |" << endl;
		cout << " |      2: Use an existing Company                    |" << endl;
		cout << " |      0: Exit program                               |" << endl;
		cout << " |____________________________________________________|" << endl << endl;


		cout << " What you want to do? ";
		cin >> option;

		if (option == 1) { // Criar empresa

			string name;
			int year, month, day;
			cout << endl;
			cout << " Important: To create a company, you need to build some courts and hire some teachers..." << endl << endl;
			cout << " But first, lets name the company." << endl;
			cout << " Enter the name: ";
			cin >> name;
			while (clean_input())	//se o input for incorreto, limpa o buffer
				cin >> name;
			cout << endl << " Enter the date (day month year): ";
			cin >> day >> month >> year;
			try {
				Date date(year, month, day);
			}
			catch(InvalidDate &exc1){
				exc1.what();
			}

			e.set_filename(name);

			//Criar os campos
			int courts;
			cout << endl << " How many courts do you want to create? ";
			cin >> courts;
			while (clean_input())	//se o input for incorreto, limpa o buffer
				cin >> courts;
			for (int i = 0; i < courts; i++) {
				size_t capacity;
				cout << endl << " What capacity does the court " << i + 1 << " hold? ";
				cin >> capacity;
				e.add_court(capacity);
				cin.clear();	//Limpar o buffer
				cin.ignore(1000, '\n');
			}

			//Criar os professores
			int teachers;
			cout << endl << " How many teachers does your company employ? ";
			cin >> teachers;
			while (clean_input())	//se o input for incorreto, limpa o buffer
				cin >> teachers;
			for (size_t i = 0; i < teachers; i++) {
				string name;
				cout << " Name of teacher " << i + 1 << ": ";
				cin >> name;
				e.add_prof(name);
				cin.clear();	//Limpar o buffer
				cin.ignore(1000, '\n');
			}

			e.save_file(name);  //Guardar a empresa
			cout << " New company saved! " << endl;
			valid_input = true;
			//Após ser criada a empresa podemos realizar várias ações sobre a mesma
			secondary_menu();
		}

		else if (option == 2) {
			string name;
			cout << " Name of the file to import: ";
			cin >> name;
			while (clean_input())
				cin >> name;
			e.import_file(name);
			valid_input = true;
			secondary_menu();
		}

		else if (option == 0) {
			cout << endl;
			valid_input = true;
			exit = true;
		}

		else {
			clean_input();
			valid_input = false;
		}
	}
}
