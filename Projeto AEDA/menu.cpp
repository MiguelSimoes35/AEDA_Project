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
		cout << "Input not valid" << '\n';
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
		cout << " ______________________________________________________" << '\n';
		cout << "|                                                      |" << '\n';
		cout << "|   Choose an option of the following:                 |" << '\n';
		cout << "|                                                      |" << '\n';
		cout << "|      1: Schedule Use                                 |" << '\n';
		cout << "|      2: Cancel Use                                   |" << '\n';
		cout << "|      3: Attend class                                 |" << '\n';
		cout << "|      4: User report                                  |" << '\n';
		cout << "|      0: Back                                         |" << '\n';
		cout << "|______________________________________________________|" << '\n' << '\n';


		cout << " What do you want to do? ";
		cin >> option;

		if (option == 1) {
			string choice, user, coach;
			id_t court;
			Period p(1,1,1,1,0,1);
			bool valido = false;
			bool sucesso = false;
			cout << '\n' << "Do you want a class or a free use? (write class or free) ";
			cin >> choice;
			while (clean_input()) {	//se o input for incorreto, limpa o buffer
				cout << '\n' << "Write a valid choice! (class or free) ";
				cin >> choice;
			}
			while (!valido) {
				if (choice == "class") { //lançar excecoes
					cout << '\n' << "What is the user name? ";
					cin >> user;
					while (clean_input()) {	//se o input for incorreto, limpa o buffer
						cout << '\n' << "Write a valid name for the user! (just letters) ";
						cin >> user;
					}
					cout << '\n' << "What is the teacher name? ";
					cin >> coach;
					while (clean_input()) {	//se o input for incorreto, limpa o buffer
						cout << '\n' << "Write a valid name for the teacher! (just letters) ";
						cin >> coach;
					}
					cout << '\n' << "What is the court number? ";
					cin >> court;
					while (clean_input()) {	//se o input for incorreto, limpa o buffer
						cout << '\n' << "Write a valid number for the court! (just numbers) ";
						cin >> court;
					}
					while (!sucesso) {
						cout << '\n' << "What day and hour you want? (Write year,month,day,hour,minutes,blocks) ";
						int year, month, day, hour, minutes, blocks;
						cin >> year >> month >> day >> hour >> minutes >> blocks;
						try {
							p = Period(year, month, day, hour, minutes, blocks);
							e.schedule_class(e.find_user(user), e.find_teacher(coach), court, p);
							cout  << '\n' << "The class is scheduled! " << '\n';
							valido = true;
							sucesso = true;
						}
						catch (InvalidPeriod &exc1) {
							cout << '\n' << exc1.what();
							sucesso = false;
						}
						catch (InexistentObject &exc2) {
							cout << '\n' << exc2.what();
							sucesso = false;
						}
						catch (SameName &exc3) {
							cout << '\n' << exc3.what();
							sucesso = false;
						}
					}
				}
				else if (choice == "free") { //lançar exceções
					cout << '\n' << "What is the user name? ";
					cin >> user;
					while (clean_input()) {	//se o input for incorreto, limpa o buffer
						cout << '\n' << "Write a valid name for the user! (just letters) ";
						cin >> user;
					}
					cout << '\n' << "What is the court number? ";
					cin >> court;
					while (clean_input()) {	//se o input for incorreto, limpa o buffer
						cout << '\n' << "Write a valid ID for the court! (just numbers) ";
						cin >> court;
					}
					while (!sucesso) {
						cout << '\n' << "What day and hour you want? (Write year,month,day,hour,minutes,blocks) ";
						int year, month, day, hour, minutes, blocks;
						cin >> year >> month >> day >> hour >> minutes >> blocks;
						try {
							p = Period(year, month, day, hour, minutes, blocks);
							e.schedule_class(e.find_user(user), e.find_teacher(coach), court, p);
							cout << '\n' << "The class is scheduled! " << '\n';
							valido = true;
							sucesso = true;
						}
						catch (InvalidPeriod &exc1) {
							cout << '\n' << exc1.what();
							sucesso = false;
						}
						catch (InexistentObject &exc2) {
							cout << '\n' << exc2.what();
							sucesso = false;
						}
						catch (SameName &exc3) {
							cout << '\n' << exc3.what();
							sucesso = false;
						}
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
			cout << '\n' << " What is the user name? ";
			cin >> user;
			while (clean_input()) {	//se o input for incorreto, limpa o buffer
				cout << '\n' << " Write a valid name for the user! (just letters) ";
				cin >> user;
			}
			cout << '\n' << " What is the class number? ";
			cin >> cl;
			while (clean_input()) {	//se o input for incorreto, limpa o buffer
				cout << '\n' << " Write a valid number for the class! (just numbers) ";
				cin >> cl;
			}
			try {
				e.cancel_use(e.find_user(user), cl);
				cout << '\n' << " The use is canceled! " << '\n';
				valid_input = false;
			}
			catch (InexistentObject &exc1) {
				cout << '\n' << exc1.what();
			}
			catch (SameName &exc2) {
				cout << '\n' << exc2.what();
			}
		}

		else if (option == 3) {
			string name;
			cout << '\n' << " What is the name of the user? ";
			cin >> name;
			while (clean_input()) {
				cout << '\n' << " Write a valid name! (just letters) ";
				cin >> name;
			}
			try {
				e.print_user_schedule(e.find_user(name));
				int id;
				cout << '\n' << " What is the number of the class? ";
				cin >> id;
				while (clean_input()) {
					cout << '\n' << " Write a valid number!";
					cin >> id;
				}
				e.attend_class(e.find_user(name), id);
				cout << '\n' << " Completed classes and assignments!" << '\n';
				valid_input = false;
			}
			catch (InexistentObject &exc1) {
				cout << '\n' << exc1.what();
			}
			catch (SameName &exc2) {
				cout << '\n' << exc2.what();
			}
		}

		else if (option == 4) {
		string name;
		cout << '\n' << " What is the name of the user? ";
		cin >> name;
		while (clean_input()) {
			cout << '\n' << " Write a valid name! (just letters) ";
			cin >> name;
		}
		try {
			e.print_user_report(e.find_user(name));
			valid_input = false;
		}
		catch (InexistentObject &exc1) {
			cout << '\n' << exc1.what();
		}
		catch (SameName &exc2) {
			cout << '\n' << exc2.what();
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
		cout << "  ______________________________________________________" << '\n';
		cout << " |                                                      |" << '\n';
		cout << " |   Choose an option of the following:                 |" << '\n';
		cout << " |                                                      |" << '\n';
		cout << " |      1: Print bill                                   |" << '\n';
		cout << " |      2: Get debt                                     |" << '\n';
		cout << " |      3: Pay debt                                     |" << '\n';
		cout << " |      0: Back                                         |" << '\n';
		cout << " |______________________________________________________|" << '\n' << '\n';


		cout << '\n' << " What do you want to do? ";
		cin >> option;

		if (option == 1) {
			string name;
			cout << '\n' << " What is the name of the user? ";
			cin >> name;
			while (clean_input()) {
				cout << '\n' << " Write a valid name! (Just with letters) ";
				cin >> name;
			}
			try {
				e.print_bill(e.find_user(name));
				valid_input = false;
			}
			catch (InexistentObject &exc1) {
				cout << '\n' << exc1.what();
			}
			catch (SameName &exc2) {
				cout << '\n' << exc2.what();
			}
		}

		else if (option == 2) {
			string name;
			cout << '\n' << " What is the name of the user? ";
			cin >> name;
			while (clean_input()) {
				cout << '\n' << " Write a valid name! (Just with letters) ";
				cin >> name;
			}
			cout << '\n' << " Your debt: " << '\n';
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
			cout << '\n' << " What is the name of the user? ";
			cin >> name;
			while (clean_input()) {
				cout << '\n' << " Write a valid name! (Just with letters) ";
				cin >> name;
			}
			try {
				e.pay_debt(e.find_user(name));
				cout << '\n' << " Everything is paid!" << '\n';
				valid_input = false;
			}
			catch (InexistentObject &exc1) {
				cout << '\n' << exc1.what();
			}
			catch (SameName &exc2) {
				cout << '\n' << exc2.what();
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

		cout << "  ______________________________________________________" << '\n';
		cout << " |                                                      |" << '\n';
		cout << " |   Choose an option of the following:                 |" << '\n';
		cout << " |                                                      |" << '\n';
		cout << " |      1: Add User                                     |" << '\n';
		cout << " |      2: Remove User                                  |" << '\n';
		cout << " |      3: List of Users                                |" << '\n';
		cout << " |      4: See User Schedule                            |" << '\n';
		cout << " |      0: Back                                         |" << '\n';
		cout << " |______________________________________________________|" << '\n' << '\n';


		cout << '\n' << " What do you want to do? ";
		cin >> option;

		if (option == 1) {
			string name, gc;
			bool gold_card;
			cout << '\n' << "Name of the new user: ";
			cin >> name;
			while (clean_input()) {	//se o input for incorreto, limpa o buffer
				cout << '\n' << " Write a valid name for the user! (just letters) ";
				cin >> name;
			}
			cout << '\n' << " Do you want to have a gold card? (yes or no in lower case) ";
			cin >> gc;
			while (clean_input()) {	//se o input for incorreto, limpa o buffer
				cout << '\n' << " Write a valid ID for the user! (just letters) ";
				cin >> gc;
			}
			if (gc == "yes")
				gold_card = true;
			else if (gc == "no")
				gold_card = false;
			else {
				while (clean_input()) {
					cout << '\n' << " Please read the question again!";
					cin >> gc;
				}
			}
			e.add_utente(name, gold_card);
			cout << '\n' << " The user is created! " << '\n';
			valid_input = false;
		}

		else if (option == 2) {
			string name;
			cout << '\n' << " What is the name of the user? ";
			cin >> name;
			while (clean_input()) {
				cout << '\n' << " Write a valid name! (Just with letters) ";
				cin >> name;
			}
			try {
				e.remove_utente(e.find_user(name));
				cout << '\n' << " The user is removed! " << '\n';
				valid_input = false;
			}
			catch (InexistentObject &exc1) {
				cout << '\n' << exc1.what();
			}
			catch (SameName &exc2) {
				cout << '\n' << exc2.what();
			}
		}

		else if (option == 3) {
			e.list_utentes();
			valid_input = false;
		}

		else if (option == 4) {
			string name;
			cout << '\n' << " What is the name of the user? ";
			cin >> name;
			while (clean_input()) {
				cout << '\n' << " Write a valid name! (Just with letters) ";
				cin >> name;
			}
			try {
				e.print_user_schedule(e.find_user(name));
				valid_input = false;
			}
			catch (InexistentObject &exc1) {
				cout << '\n' << exc1.what();
			}
			catch (SameName &exc2) {
				cout << '\n' << exc2.what();
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

		cout << "  ______________________________________________________" << '\n';
		cout << " |                                                      |" << '\n';
		cout << " |   Choose an option of the following:                 |" << '\n';
		cout << " |                                                      |" << '\n';
		cout << " |      1: Edit Users                                   |" << '\n';
		cout << " |      2: Expenses                                     |" << '\n';
		cout << " |      3: Classes                                      |" << '\n';
		cout << " |      0: Back                                         |" << '\n';
		cout << " |______________________________________________________|" << '\n' << '\n';


		cout << '\n' << "What do you want to do? ";
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
		cout << "  ______________________________________________________" << '\n';
		cout << " |                                                      |" << '\n';
		cout << " |   Choose an option of the following:                 |" << '\n';
		cout << " |                                                      |" << '\n';
		cout << " |      1: Add Teacher                                  |" << '\n';
		cout << " |      2: Remove Teacher                               |" << '\n';
		cout << " |      3: Give Class                                   |" << '\n';
		cout << " |      4: See Teachers                                 |" << '\n';
		cout << " |      5: See Teacher Schedule                         |" << '\n';
		cout << " |      0: Back                                         |" << '\n';
		cout << " |______________________________________________________|" << '\n' << '\n';


		cout << '\n' << " What do you want to do? ";
		cin >> option;

		if (option == 1) {
			string name;
			cout << '\n' << " What is the name of the teacher? ";
			cin >> name;
			while (clean_input()) {
				cout << '\n' << " Write a valid name! (just letters) ";
				cin >> name;
			}
			e.add_prof(name);
			cout << '\n' << " Teacher " << name << " added!" << '\n';
			valid_input = false;
		}

		else if (option == 2) {
			string name;
			cout << '\n' << " What is the name of the teacher? ";
			cin >> name;
			while (clean_input()) {
				cout << '\n' << " Write a valid name! (just letters) ";
				cin >> name;
			}
			try {
				e.remove_prof(e.find_teacher(name));
				cout << '\n' << " Teacher removed!" << '\n';
				valid_input = false;
			}
			catch (InexistentObject &exc1) {
				cout << '\n' << exc1.what();
			}
			catch (SameName &exc2) {
				cout << '\n' << exc2.what();
			}
		}

		else if (option == 3) {
			string name;
			Period p (1,1,1,1,1,1);
			Teacher T = Teacher(name);
			Teacher *t = &T;
			cout << '\n' << " What is the name of the teacher? ";
			cin >> name;
			while (clean_input()) {
				cout << '\n' << " Write a valid name! (just letters) ";
				cin >> name;
			}
			try {
				e.print_prof_schedule(e.find_teacher(name));
				Court C(0);
				Court *c = &C;
				Class CL(p, t, c);
				Class *a = &CL;
				e.give_class(e.find_teacher(name), a);
				cout << '\n' << " Class gived!" << '\n';
				valid_input = false;
			}
			catch (InexistentObject &exc1) {
				cout << '\n' << exc1.what();
			}
			catch (SameName &exc2) {
				cout << '\n' << exc2.what();
			}
		}

		else if (option == 4) {
			e.list_profs();
			valid_input = false;
		}

		else if (option == 5) {
			string name;
			cout << '\n' << " What is the name of the teacher? ";
			cin >> name;
			while (clean_input()) {
				cout << '\n' << " Write a valid name! (just letters) ";
				cin >> name;
			}
			try {
				e.print_prof_schedule(e.find_teacher(name));
				valid_input = false;
			}
			catch (InexistentObject &exc1) {
				cout << '\n' << exc1.what();
			}
			catch (SameName &exc2) {
				cout << '\n' << exc2.what();
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

		cout << "  ______________________________________________________" << '\n';
		cout << " |                                                      |" << '\n';
		cout << " |   Choose an option of the following:                 |" << '\n';
		cout << " |                                                      |" << '\n';
		cout << " |      1: Add Court                                    |" << '\n';
		cout << " |      2: Remove Court                                 |" << '\n';
		cout << " |      3: See Available Courts                         |" << '\n';
		cout << " |      4: See Court Schedule                           |" << '\n';
		cout << " |      5: See Day Schedule                             |" << '\n';
		cout << " |      0: Back                                         |" << '\n';
		cout << " |______________________________________________________|" << '\n' << '\n';

		cout << '\n' << " What do you want to do? ";
		cin >> option;

		if (option == 1) {
			size_t cap;
			cout << '\n' << "What is the capacity of the court? ";
			cin >> cap;
			while (clean_input()) {	//se o input for incorreto, limpa o buffer
				cout << '\n' << "Write a valid capacity for the court! (Number) ";
				cin >> cap;
			}
			e.add_court(cap);
			cout << '\n' << " Court added! " << '\n';
			valid_input = false;
		}

		else if (option == 2) {
			id_t id;
			cout << '\n' << " What is the number of the court to remove? ";
			cin >> id;
			while (clean_input()) {
				cout << '\n' << " Write a valid number! (just numbers) ";
				cin >> id;
			}
			e.remove_court(id);
			cout << '\n' << " Court removed!" << '\n';
			valid_input = false;
		}

		else if (option == 3) {
			string type;
			int y, m, d;
			Date d1(1, 1, 1);
			bool valido = false;
			cout << '\n' << " What is the date you want to see which courts are available? ";
			cin >> y >> m >> d;
			try {
				d1 = Date(y, m, d);
			}
			catch (InvalidDate &exc1) {
				cout << '\n' << exc1.what();
			}
			while (!valido) {
				cout << '\n' << " You want to see a specific period of the day? (yes or no in lower case)" << '\n';
				cin >> type;
				if (type == "yes") {
					valido = true;
					cout << '\n' << " What is the period of the day? ";
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
			cout << '\n' << " What is the number of the court to see the schedule? ";
			cin >> id;
			while (clean_input()) {
				cout << '\n' << " Write a valid number! (just numbers) ";
				cin >> id;
			}
			cout << '\n' << " What is the date you want to see the court " << id << " schedule? ";
			Date d1 = Date(cin);
			e.print_court_schedule(id, d1);
			valid_input = false;
		}

		else if (option == 5) {
			cout << '\n' << " What is the day you want to see the schedule? ";
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
		cout << "  ____________________________________________________" << '\n';
		cout << " |                                                    |" << '\n';
		cout << " |   Choose an option of the following:               |" << '\n';
		cout << " |                                                    |" << '\n';
		cout << " |      1: Manage Users                               |" << '\n';
		cout << " |      2: Manage teachers                            |" << '\n';
		cout << " |      3: Manage courts                              |" << '\n';
		cout << " |      4: Save company                               |" << '\n';
		cout << " |      0: Exit program                               |" << '\n';
		cout << " |____________________________________________________|" << '\n' << '\n';


		cout << '\n' << " What do you want to do? ";
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
			cout << '\n' << " Company saved! ";
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
	bool valid_input = false;
	bool exit = false;

	while (!valid_input && !exit) {
		cin.clear();

		cout << '\n';
		cout << setw(40) << " _____  _____                  _____  _____           _____   ____            _____  _____  _____          _____   _____         _____   _____         " << '\n';
		cout << setw(40) << "   |   |       ||   |  ||   |    |   |               |       |     | |     | |     |   |   |              |     | |       ||   |   |    |     | |      " << '\n';
		cout << setw(40) << "   |   |_____  | |  |  | |  |    |   |_____          |       |     | |     | |_____|   |   |_____         |_____| |_____  | |  |   |    |_____| |      " << '\n';
		cout << setw(40) << "   |   |       |  | |  |  | |    |         |         |       |     | |     | |  |      |         |        |  |    |       |  | |   |    |     | |      " << '\n';
		cout << setw(40) << "   |   |_____  |   ||  |   ||  __|__  _____|         |_____  |_____| |_____| |   |     |    _____|        |   |   |_____  |   ||   |    |     | |_____ " << '\n' << '\n';
		cout << "  ____________________________________________________" << '\n';
		cout << " |                                                    |" << '\n';
		cout << " |   Choose an option of the following:               |" << '\n';
		cout << " |                                                    |" << '\n';
		cout << " |      1: Create a new Company                       |" << '\n';
		cout << " |      2: Use an existing Company                    |" << '\n';
		cout << " |      0: Exit program                               |" << '\n';
		cout << " |____________________________________________________|" << '\n' << '\n';


		cout << '\n' << " What you want to do? ";
		cin >> option;

		if (option == 1) { // Criar empresa

			string name;
			int year, month, day;
			cout << '\n' << " Important: To create a company, you need to build some courts and hire some teachers..." << '\n';
			cout << '\n' << " But first, lets name the company." << '\n';
			cout << " \t Enter the name: ";
			cin >> name;
			while (clean_input()) {	//se o input for incorreto, limpa o buffer
				cout << '\n' << " Name not valid! Please write a valid name! ";
				cin >> name;
			}
			cout << '\n' << " Enter the date (day month year): ";
			cin >> day >> month >> year;
			try {
				Date date(year, month, day);
			}
			catch(InvalidDate &exc1){
				cout << '\n' << exc1.what();
			}

			e.set_filename(name);

			//Criar os campos
			int courts;
			cout << '\n' << " How many courts do you want to create? ";
			cin >> courts;
			while (clean_input()) {	//se o input for incorreto, limpa o buffer
				cout << '\n' << "Please write a number! ";
				cin >> courts;
			}
			for (int i = 0; i < courts; i++) {
				size_t capacity;
				cout << '\n' << " What capacity does the court " << i + 1 << " hold? ";
				cin >> capacity;
				e.add_court(capacity);
				cin.clear();	//Limpar o buffer
				cin.ignore(1000, '\n');
			}

			//Criar os professores
			int teachers;
			cout << '\n' << " How many teachers does your company employ? ";
			cin >> teachers;
			while (clean_input()) {	//se o input for incorreto, limpa o buffer
				cout << '\n' << "Please write a number! ";
				cin >> teachers;
			}
			for (size_t i = 0; i < teachers; i++) {
				string name;
				cout << '\n' << " Name of teacher " << i + 1 << ": ";
				cin >> name;
				e.add_prof(name);
				cin.clear();	//Limpar o buffer
				cin.ignore(1000, '\n');
			}

			e.save_file(name);  //Guardar a empresa
			cout << '\n' << " New company saved! " << '\n';
			valid_input = true;
			//Após ser criada a empresa podemos realizar várias ações sobre a mesma
			secondary_menu();
		}

		else if (option == 2) {
            string name;
            cout << '\n' << " Name of the file to import: ";
            cin >> name;
            while (clean_input()) {
                cout << '\n' << "Invalid name. Please write a valid name! ";
                cin >> name;
                e.import_file(name);
                valid_input = true;
                secondary_menu();
            }
        }

		else if (option == 0) {
			cout << '\n';
			valid_input = true;
			exit = true;
		}

		else {
			clean_input();
			valid_input = false;
		}
	}
}
