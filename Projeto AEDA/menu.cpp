#include "menu.h"

using namespace std;

//======================================================================================================================================================//

void user_menu(Empresa &E) {
	int option;
	id_t id_user, id_court, id_teacher, id_class;
	bool exists, valid;
	string name;
	vector<int> periodo = { 0,0,0,0,0,0 }; // Period of type {year, month, day, hour, minutes, blocks}

	system("cls");

	main_header("TENNIS COURT MANAGEMENT");

	header_date("USER MENU ", E.get_date());

	setcolor(10); cout << " ["; setcolor(14); cout << "1"; setcolor(10); cout << "]"; setcolor(15); cout << " - Search User" << endl << endl;
	setcolor(10); cout << " ["; setcolor(14); cout << "2"; setcolor(10); cout << "]"; setcolor(15); cout << " - Manage Payments" << endl << endl;
	setcolor(10); cout << " ["; setcolor(14); cout << "3"; setcolor(10); cout << "]"; setcolor(15); cout << " - Print User Report" << endl << endl;
	setcolor(10); cout << " ["; setcolor(14); cout << "4"; setcolor(10); cout << "]"; setcolor(15); cout << " - List Users" << endl << endl;
	setcolor(10); cout << " ["; setcolor(14); cout << "5"; setcolor(10); cout << "]"; setcolor(15); cout << " - Schedules" << endl << endl;
	setcolor(10); cout << " ["; setcolor(14); cout << "6"; setcolor(10); cout << "]"; setcolor(15); cout << " - Attend Class" << endl << endl;
	setcolor(10); cout << " ["; setcolor(14); cout << "7"; setcolor(10); cout << "]"; setcolor(15); cout << " - Schedule Free Use" << endl << endl;
	setcolor(10); cout << " ["; setcolor(14); cout << "0"; setcolor(10); cout << "]"; setcolor(15); cout << " - Back" << endl << endl;

	option = option_input(" Option: ", 0, 7);

	system("cls");

	main_header("TENNIS COURT MANAGEMENT");

	header_date("USER MENU ", E.get_date());

	switch (option) {
	case 1:
		exists = false;
		id_user = -1;

		try {
			name = name_input(" What's the name of the user? ");
			cout << endl;
			id_user = E.find_user(name);
			exists = true;
		}
		catch (InexistentObject &exc) {
			exists = false;
		}
		catch (SameName &exc) {
			cout << " There are multiple users with that name.";

			if (choice_input(" Would you like a list of all users? ")) {
				cout << endl;
				E.list_utentes();
			}
			else {
				exists = false;
			}

		}

		if (exists) {
			setcolor(2);
			cout << " The user exists. Here is the information:" << endl << endl;
			setcolor(15);

			E.print_user_info(id_user);
		}
		else {
			setcolor(2);
			cout << " The user doesn't exist." << endl;
			setcolor(15);
		}

		cout << endl;
		system("pause");

		user_menu(E);
		break;
	case 2:
		payments_menu(E);

		user_menu(E);
		break;
	case 3:
		exists = false;
		id_user = -1;

		while (!exists) {
			try {
				name = name_input(" What's the name of the user? ");
				cout << endl;

				id_user = E.find_user(name);
				exists = true;
			}
			catch (InexistentObject &exc) {
				exists = false;
			}
			catch (SameName &exc) {
				cout << " There are multiple users with that name.";

				if (choice_input(" Would you like a list of all users? ")) {
					cout << endl;

					E.list_utentes();

					cout << endl;

					id_user = id_input(" Insert the ID of the user: ");
					cout << endl;


					exists = true;
				}
				else {
					exists = false;
				}
			}
		}

		E.print_user_report(id_user);

		cout << endl;
		system("pause");

		user_menu(E);
		break;
	case 4:
		E.list_utentes();

		cout << endl;
		system("pause");

		user_menu(E);
		break;
	case 5:
		schedules_menu(E);

		user_menu(E);
		break;
	case 6:
		exists = false;
		valid = false;

		id_user = -1;
		id_class = -1;

		while (!exists) {
			try {
				name = name_input(" What's the name of the user? ");
				cout << endl;

				id_user = E.find_user(name);
				exists = true;
			}
			catch (InexistentObject &exc) {
				exists = false;
			}
			catch (SameName &exc) {
				cout << " There are multiple users with that name.";

				if (choice_input(" Would you like a list of all users? ")) {
					cout << endl;

					E.list_utentes();

					cout << endl;

					id_user = id_input(" Insert the ID of the user: ");
					cout << endl;


					exists = true;
				}
				else {
					exists = false;
				}
			}
		}

		valid = false;

		try {
			get_period(periodo);
			id_class = E.find_class(Period(periodo[0], periodo[1], periodo[2], periodo[3], periodo[4], periodo[5]));
			valid = true;
		}
		catch (InvalidPeriod &exc) {
			valid = false;
		}

		setcolor(2);
		if (valid) {
			E.attend_class(id_user, id_class);

			cout << " Class attendance successful." << endl;
		}
		else {
			cout << " There is no class scheduled for that time." << endl;
		}
		setcolor(15);

		cout << endl;
		user_menu(E);
		break;
	case 7:
		exists = false;
		valid = false;

		id_user = -1;
		id_court = -1;

		while (!exists) {
			try {
				name = name_input(" What's the name of the user? ");
				cout << endl;

				id_user = E.find_user(name);
				exists = true;
			}
			catch (InexistentObject &exc) {
				exists = false;
			}
			catch (SameName &exc) {
				cout << " There are multiple users with that name.";

				if (choice_input(" Would you like a list of all users? ")) {
					cout << endl;

					E.list_utentes();

					cout << endl;

					id_user = id_input(" Insert the ID of the user: ");
					cout << endl;


					exists = true;
				}
				else {
					exists = false;
				}
			}
		}

		exists = false;

		while (!exists) {
			try {
				id_court = id_input(" Insert the ID of the court: ");
				cout << endl;
				exists = true;

				while (!valid) {
					try {
						get_period(periodo);
						E.schedule_free_use(id_user, id_court, Period(periodo[0], periodo[1], periodo[2], periodo[3], periodo[4], periodo[5]));
						valid = true;
					}
					catch (InvalidPeriod &exc) {
						valid = false;
					}
					catch (CourtIsFull &exc) {
						valid = true;
						exists = false;

						cout << " Court is full. Pick a different court or period." << endl << endl;
					}
				}
			}
			catch (InexistentObject &exception) {
				exists = false;
			}
		}


		setcolor(2);
		cout << endl << " Free use scheduled." << endl;
		setcolor(15);

		cout << endl;
		user_menu(E);
		break;
	case 0:
		break;
	}
}

void payments_menu(Empresa &E) {
	int option;
	int id;
	bool exists, gold_card;
	string name;

	system("cls");

	main_header("TENNIS COURT MANAGEMENT");

	header_date("PAYMENTS MENU ", E.get_date());

	setcolor(10); cout << " ["; setcolor(14); cout << "1"; setcolor(10); cout << "]"; setcolor(15); cout << " - Print Bill" << endl << endl;
	setcolor(10); cout << " ["; setcolor(14); cout << "2"; setcolor(10); cout << "]"; setcolor(15); cout << " - Pay Debt" << endl << endl;
	setcolor(10); cout << " ["; setcolor(14); cout << "0"; setcolor(10); cout << "]"; setcolor(15); cout << " - Back" << endl << endl;

	option = option_input(" Option: ", 0, 2);

	system("cls");

	main_header("TENNIS COURT MANAGEMENT");

	header_date("PAYMENTS MENU ", E.get_date());

	switch (option) {
	case 1:
		exists = false;
		id = -1;

		while (!exists) {
			try {
				name = name_input(" What's the name of the user? ");
				cout << endl;

				id = E.find_user(name);
				exists = true;
			}
			catch (InexistentObject &exc) {
				exists = false;
			}
			catch (SameName &exc) {
				cout << " There are multiple users with that name.";

				if (choice_input(" Would you like a list of all users? ")) {
					cout << endl;

					E.list_utentes();

					cout << endl;

					id = id_input(" Insert the ID of the user: ");
					cout << endl;


					exists = true;
				}
				else {
					exists = false;
				}
			}
		}

		E.print_bill(id);

		cout << endl;
		system("pause");

		break;
	case 2:
		exists = false;
		id = -1;

		while (!exists) {
			try {
				name = name_input(" What's the name of the user? ");
				cout << endl;

				id = E.find_user(name);
				exists = true;
			}
			catch (InexistentObject &exc) {
				exists = false;
			}
			catch (SameName &exc) {
				cout << " There are multiple users with that name.";

				if (choice_input(" Would you like a list of all users? ")) {
					cout << endl;

					E.list_utentes();

					cout << endl;

					id = id_input(" Insert the ID of the user: ");
					cout << endl;


					exists = true;
				}
				else {
					exists = false;
				}
			}
		}

		E.pay_debt(id);

		setcolor(2);
		cout << " Debt payed successfully." << endl;
		setcolor(15);
		system("pause");

		break;
	case 0:

		break;
	}
}

//======================================================================================================================================================//

void teacher_menu(Empresa &E) {
	int option;
	int id;
	bool exists;
	string name;

	system("cls");

	main_header("TENNIS COURT MANAGEMENT");

	header_date("TEACHER MENU ", E.get_date());

	setcolor(10); cout << " ["; setcolor(14); cout << "1"; setcolor(10); cout << "]"; setcolor(15); cout << " - Search Teacher" << endl << endl;
	setcolor(10); cout << " ["; setcolor(14); cout << "2"; setcolor(10); cout << "]"; setcolor(15); cout << " - List Teachers" << endl << endl;
	setcolor(10); cout << " ["; setcolor(14); cout << "3"; setcolor(10); cout << "]"; setcolor(15); cout << " - Schedules" << endl << endl;
	setcolor(10); cout << " ["; setcolor(14); cout << "0"; setcolor(10); cout << "]"; setcolor(15); cout << " - Back" << endl << endl;

	option = option_input(" Option: ", 0, 3);

	system("cls");

	main_header("TENNIS COURT MANAGEMENT");

	header_date("TEACHER MENU ", E.get_date());

	switch (option) {
	case 1:
		exists = false;
		id = -1;

		try {
			name = name_input(" What's the name of the teacher? ");
			id = E.find_teacher(name);
			exists = true;
		}
		catch (InexistentObject &exc) {
			exists = false;
		}
		catch (SameName &exc) {
			cout << " There are multiple teachers with that name.";

			if (choice_input(" Would you like a list of all teachers? ")) {
				cout << endl;

				E.list_profs();
				break;
			}
			else {
				exists = false;
			}

		}

		if (exists) {
			setcolor(2);
			cout << " The teacher exists. Here is the information:" << endl;
			setcolor(15);
			E.print_teacher_info(id);
		}
		else {
			setcolor(2);
			cout << " The teacher doesn't exist." << endl;
			setcolor(15);
		}

		cout << endl;
		system("pause");

		teacher_menu(E);
		break;
	case 2:
		E.list_profs();

		cout << endl;
		system("pause");

		teacher_menu(E);
		break;
	case 3:
		schedules_menu(E);

		teacher_menu(E);
		break;
	case 0:
		break;
	}
}

//======================================================================================================================================================//

void company_menu(Empresa &E) {
	int option;

	system("cls");

	main_header("TENNIS COURT MANAGEMENT");

	header_date("COMPANY MENU ", E.get_date());

	setcolor(10); cout << " ["; setcolor(14); cout << "1"; setcolor(10); cout << "]"; setcolor(15); cout << " - Manage Users" << endl << endl;
	setcolor(10); cout << " ["; setcolor(14); cout << "2"; setcolor(10); cout << "]"; setcolor(15); cout << " - Manage Teachers" << endl << endl;
	setcolor(10); cout << " ["; setcolor(14); cout << "3"; setcolor(10); cout << "]"; setcolor(15); cout << " - Manage Courts" << endl << endl;
	setcolor(10); cout << " ["; setcolor(14); cout << "4"; setcolor(10); cout << "]"; setcolor(15); cout << " - Manage Classes" << endl << endl;
	setcolor(10); cout << " ["; setcolor(14); cout << "5"; setcolor(10); cout << "]"; setcolor(15); cout << " - Manage Uses" << endl << endl;
	setcolor(10); cout << " ["; setcolor(14); cout << "6"; setcolor(10); cout << "]"; setcolor(15); cout << " - End Day" << endl << endl;
	setcolor(10); cout << " ["; setcolor(14); cout << "0"; setcolor(10); cout << "]"; setcolor(15); cout << " - Back" << endl << endl;

	option = option_input(" Option: ", 0, 6);

	switch (option) {
	case 1:
		manage_users(E);
		company_menu(E);
		break;
	case 2:
		manage_teachers(E);
		company_menu(E);
		break;
	case 3:
		manage_courts(E);
		company_menu(E);
		break;
	case 4:
		manage_classes(E);
		company_menu(E);
		break;
	case 5:
		manage_uses(E);
		company_menu(E);
		break;
	case 6:
		E.increment_date();
		company_menu(E);
		break;
	case 0:
		break;
	}
}

void manage_users(Empresa &E) {
	int option;
	int id;
	bool exists, gold_card;
	string name;

	system("cls");

	main_header("TENNIS COURT MANAGEMENT");

	header_date("USER MANAGEMENT ", E.get_date());

	setcolor(10); cout << " ["; setcolor(14); cout << "1"; setcolor(10); cout << "]"; setcolor(15); cout << " - Add User" << endl << endl;
	setcolor(10); cout << " ["; setcolor(14); cout << "2"; setcolor(10); cout << "]"; setcolor(15); cout << " - Remove User" << endl << endl;
	setcolor(10); cout << " ["; setcolor(14); cout << "3"; setcolor(10); cout << "]"; setcolor(15); cout << " - Update Gold Card" << endl << endl;
	setcolor(10); cout << " ["; setcolor(14); cout << "4"; setcolor(10); cout << "]"; setcolor(15); cout << " - Search User" << endl << endl;
	setcolor(10); cout << " ["; setcolor(14); cout << "5"; setcolor(10); cout << "]"; setcolor(15); cout << " - List Users" << endl << endl;
	setcolor(10); cout << " ["; setcolor(14); cout << "0"; setcolor(10); cout << "]"; setcolor(15); cout << " - Back" << endl << endl;

	option = option_input(" Option: ", 0, 5);

	system("cls");

	main_header("TENNIS COURT MANAGEMENT");

	header_date("USER MANAGEMENT ", E.get_date());

	switch (option) {
	case 1:
		name = name_input(" What's the name of the user? ");

		cout << endl;

		gold_card = choice_input(" Acquire gold card?(yes/no) ");

		cout << endl;

		E.add_utente(name, gold_card);

		setcolor(2);
		cout << " User added. " << endl << endl;
		setcolor(15);
		system("pause");

		company_menu(E);

		break;
	case 2:
		exists = false;
		id = -1;

		while (!exists) {
			try {
				name = name_input(" What's the name of the user? ");
				cout << endl;

				id = E.find_user(name);
				exists = true;
			}
			catch (InexistentObject &exc) {
				exists = false;
			}
			catch (SameName &exc) {
				cout << " There are multiple users with that name.";

				if (choice_input(" Would you like a list of all users? ")) {
					cout << endl;

					E.list_utentes();

					cout << endl;

					id = id_input(" Insert the ID of the user: ");
					cout << endl;


					exists = true;
				}
				else {
					exists = false;
				}
			}
		}

		E.remove_utente(id);
		setcolor(2);
		cout << " User removed." << endl << endl;
		setcolor(15);
		system("pause");

		company_menu(E);

		break;
	case 3:
		exists = false;
		id = -1;
		gold_card = false;

		while (!exists) {
			try {
				name = name_input(" What's the name of the user? ");
				cout << endl;

				id = E.find_user(name);
				exists = true;
			}
			catch (InexistentObject &exc) {
				exists = false;
			}
			catch (SameName &exc) {
				cout << " There are multiple users with that name.";

				if (choice_input(" Would you like a list of all users? ")) {
					cout << endl;

					E.list_utentes();

					cout << endl;

					id = id_input(" Insert the ID of the user: ");
					cout << endl;


					exists = true;
				}
				else {
					exists = false;
				}
			}
		}

		gold_card = choice_input(" Does the user want a gold card? ");
		cout << endl;


		E.change_card(id, gold_card);

		setcolor(2);
		cout << " Changed successfully." << endl << endl;
		setcolor(15);
		system("pause");

		company_menu(E);

		break;
	case 4:
		exists = false;
		id = -1;

		try {
			name = name_input(" What's the name of the user? ");
			cout << endl;
			id = E.find_user(name);
			exists = true;
		}
		catch (InexistentObject &exc) {
			exists = false;
		}
		catch (SameName &exc) {
			cout << " There are multiple users with that name.";

			if (choice_input(" Would you like a list of all users? ")) {
				cout << endl;
				E.list_utentes();
			}
			else {
				exists = false;
			}

		}

		if (exists) {
			setcolor(2);
			cout << " The user exists. Here is the information:" << endl << endl;
			setcolor(15);

			E.print_user_info(id);
		}
		else {
			setcolor(2);
			cout << " The user doesn't exist." << endl;
			setcolor(15);
		}

		cout << endl;
		system("pause");

		company_menu(E);

		break;
	case 5:
		E.list_utentes();

		cout << endl;
		system("pause");

		company_menu(E);

		break;

	case 0:
		break;
	}
}

void manage_teachers(Empresa &E) {
	int option;
	int id;
	bool exists;
	string name;

	system("cls");

	main_header("TENNIS COURT MANAGEMENT");

	header_date("TEACHER MANAGEMENT ", E.get_date());

	setcolor(10); cout << " ["; setcolor(14); cout << "1"; setcolor(10); cout << "]"; setcolor(15); cout << " - Add Teacher" << endl << endl;
	setcolor(10); cout << " ["; setcolor(14); cout << "2"; setcolor(10); cout << "]"; setcolor(15); cout << " - Remove Teacher" << endl << endl;
	setcolor(10); cout << " ["; setcolor(14); cout << "3"; setcolor(10); cout << "]"; setcolor(15); cout << " - Search Teacher" << endl << endl;
	setcolor(10); cout << " ["; setcolor(14); cout << "4"; setcolor(10); cout << "]"; setcolor(15); cout << " - List Teachers" << endl << endl;
	setcolor(10); cout << " ["; setcolor(14); cout << "0"; setcolor(10); cout << "]"; setcolor(15); cout << " - Back" << endl << endl;

	option = option_input(" Option: ", 0, 4);

	system("cls");

	main_header("TENNIS COURT MANAGEMENT");

	header_date("TEACHER MANAGEMENT ", E.get_date());

	switch (option) {
	case 1:
		name = name_input(" What's the name of the teacher? ");

		cout << endl;

		E.add_prof(name);

		setcolor(2);
		cout << " Teacher added." << endl << endl;
		setcolor(15);
		system("pause");

		company_menu(E);

		break;
	case 2:
		exists = false;
		id = -1;

		while (!exists) {
			try {
				name = name_input(" What's the name of the teacher? ");
				cout << endl;

				id = E.find_teacher(name);
				exists = true;
			}
			catch (InexistentObject &exc) {
				exists = false;
			}
			catch (SameName &exc) {
				cout << " There are multiple teachers with that name.";

				if (choice_input(" Would you like a list of all teachers? ")) {
					cout << endl;

					E.list_profs();

					cout << endl;

					id = id_input(" Insert the ID of the teacher: ");
					cout << endl;


					exists = true;
				}
				else {
					exists = false;
				}
			}
		}

		E.remove_prof(id);

		setcolor(2);
		cout << " Teacher removed. " << endl << endl;
		setcolor(15);
		system("pause");

		company_menu(E);

		break;

	case 3:
		exists = false;
		id = -1;

		try {
			name = name_input(" What's the name of the teacher? ");
			id = E.find_teacher(name);
			exists = true;
		}
		catch (InexistentObject &exc) {
			exists = false;
		}
		catch (SameName &exc) {
			cout << " There are multiple teachers with that name.";

			if (choice_input(" Would you like a list of all teachers? ")) {
				cout << endl;

				E.list_profs();
				break;
			}
			else {
				exists = false;
			}

		}

		if (exists) {
			setcolor(2);
			cout << " The teacher exists. Here is the information:" << endl;
			setcolor(15);

			E.print_teacher_info(id);
		}
		else {
			setcolor(2);
			cout << " The teacher doesn't exist." << endl;
			setcolor(15);
		}

		cout << endl;
		system("pause");

		company_menu(E);

		break;
	case 4:
		E.list_profs();

		cout << endl;
		system("pause");

		company_menu(E);

		break;

	case 0:
		break;
	}
}

void manage_courts(Empresa &E) {
	int option;
	int id;
	size_t capacity;
	bool exists;

	system("cls");

	main_header("TENNIS COURT MANAGEMENT");

	header_date("COURT MANAGEMENT ", E.get_date());

	setcolor(10); cout << " ["; setcolor(14); cout << "1"; setcolor(10); cout << "]"; setcolor(15); cout << " - Add Court" << endl << endl;
	setcolor(10); cout << " ["; setcolor(14); cout << "2"; setcolor(10); cout << "]"; setcolor(15); cout << " - Remove Court" << endl << endl;
	setcolor(10); cout << " ["; setcolor(14); cout << "3"; setcolor(10); cout << "]"; setcolor(15); cout << " - Change Court Capacity" << endl << endl;
	setcolor(10); cout << " ["; setcolor(14); cout << "4"; setcolor(10); cout << "]"; setcolor(15); cout << " - List Court" << endl << endl;
	setcolor(10); cout << " ["; setcolor(14); cout << "0"; setcolor(10); cout << "]"; setcolor(15); cout << " - Back" << endl << endl;

	option = option_input(" Option: ", 0, 4);

	system("cls");

	main_header("TENNIS COURT MANAGEMENT");

	header_date("COURT MANAGEMENT ", E.get_date());

	switch (option) {
	case 1:
		capacity = 0;

		capacity = capacity_input(" New court capacity: ");

		E.add_court(capacity);

		setcolor(2);
		cout << " Court added." << endl << endl;
		setcolor(15);
		system("pause");

		company_menu(E);

		break;
	case 2:
		exists = false;
		id = -1;

		while (!exists) {
			try {
				id = id_input(" Insert the ID of the court: ");
				cout << endl;
				exists = true;
			}
			catch (InexistentObject &exc) {
				exists = false;
			}
		}

		E.remove_court(id);

		setcolor(2);
		cout << " Court removed" << endl << endl;
		setcolor(15);
		system("pause");

		company_menu(E);

		break;

	case 3:
		exists = false;
		id = -1;
		capacity = 0;


		while (!exists) {
			try {
				id = id_input(" Insert the ID of the court: ");
				cout << endl;
				exists = true;
			}
			catch (InexistentObject &exc) {
				exists = false;
			}
		}


		capacity = capacity_input(" Court's new capacity: ");

		setcolor(2);
		cout << " Court's capacity changed." << endl << endl;
		setcolor(15);
		system("pause");

		company_menu(E);

		break;
	case 4:
		E.list_courts();

		cout << endl;
		system("pause");

		company_menu(E);

		break;

	case 0:
		break;
	}
}

void manage_classes(Empresa &E) {
	int option;
	id_t id_user, id_court, id_teacher, id_class;
	bool exists, valid;
	string name;
	vector<int> periodo = { 0,0,0,0,0,0 }; // Period of type {year, month, day, hour, minutes, blocks}

	system("cls");

	main_header("TENNIS COURT MANAGEMENT");

	header_date("CLASSES MANAGEMENT ", E.get_date());

	setcolor(10); cout << " ["; setcolor(14); cout << "1"; setcolor(10); cout << "]"; setcolor(15); cout << " - Search Class" << endl << endl;
	setcolor(10); cout << " ["; setcolor(14); cout << "2"; setcolor(10); cout << "]"; setcolor(15); cout << " - List Classess" << endl << endl;
	setcolor(10); cout << " ["; setcolor(14); cout << "3"; setcolor(10); cout << "]"; setcolor(15); cout << " - Cancel Class" << endl << endl;
	setcolor(10); cout << " ["; setcolor(14); cout << "4"; setcolor(10); cout << "]"; setcolor(15); cout << " - Change Teacher" << endl << endl;
	setcolor(10); cout << " ["; setcolor(14); cout << "5"; setcolor(10); cout << "]"; setcolor(15); cout << " - Change Court" << endl << endl;
	setcolor(10); cout << " ["; setcolor(14); cout << "0"; setcolor(10); cout << "]"; setcolor(15); cout << " - Back" << endl << endl;

	option = option_input(" Option: ", 0, 5);

	system("cls");

	main_header("TENNIS COURT MANAGEMENT");

	header_date("CLASSES MANAGEMENT ", E.get_date());

	switch (option) {
	case 1:
		id_class = -1;
		valid = false;

		try {
			get_period(periodo);
			id_class = E.find_class(Period(periodo[0], periodo[1], periodo[2], periodo[3], periodo[4], periodo[5]));
			valid = true;
		}
		catch (InvalidPeriod &exc) {
			valid = false;
		}

		if (valid) {
			setcolor(2);
			cout << " The class exists. Here is the information:" << endl;
			setcolor(15);

			E.print_class_info(id_class);
		}
		else {
			setcolor(2);
			cout << " There is no class scheduled for that time." << endl;
			setcolor(15);
		}

		cout << endl;
		system("pause");
		break;
	case 2:
		E.list_classes();

		cout << endl;
		system("pause");
		break;
	case 3:
		id_class = -1;
		valid = false;

		try {
			get_period(periodo);
			id_class = E.find_class(Period(periodo[0], periodo[1], periodo[2], periodo[3], periodo[4], periodo[5]));
			valid = true;
		}
		catch (InvalidPeriod &exc) {
			valid = false;
		}

		if (valid) {
			setcolor(2);
			cout << " The class exists. Here is the information:" << endl;
			setcolor(15);

			E.cancel_class(id_class);
		}
		else {
			setcolor(2);
			cout << " There is no class scheduled for that time." << endl;
			setcolor(15);
		}

		cout << endl;
		system("pause");
		break;
	case 4:
		id_class = -1;
		id_teacher = -1;

		valid = false;
		exists = false;

		while (!exists) {
			try {
				name = name_input(" What's the name of the teacher? ");
				id_teacher = E.find_teacher(name);
				exists = true;
			}
			catch (InexistentObject &exc) {
				exists = false;
			}
			catch (SameName &exc) {
				cout << " There are multiple teachers with that name.";

				if (choice_input(" Would you like a list of all teachers? ")) {
					cout << endl;

					E.list_profs();
					break;
				}
				else {
					exists = false;
				}

			}
		}

		try {
			get_period(periodo);
			id_class = E.find_class(Period(periodo[0], periodo[1], periodo[2], periodo[3], periodo[4], periodo[5]));
			valid = true;
		}
		catch (InvalidPeriod &exc) {
			valid = false;
		}

		if (valid) {
			E.change_teacher(id_teacher, id_class);

			setcolor(2);
			cout << " The class's teacher was changed." << endl;
			setcolor(15);
		}
		else {
			setcolor(2);
			cout << " There is no class scheduled for that time." << endl;
			setcolor(15);
		}

		break;
	case 5:
		id_class = -1;
		id_court = -1;

		exists = false;
		valid = false;

		while (!exists) {
			try {
				id_court = id_input(" Insert the ID of the court: ");
				cout << endl;
				exists = true;
			}
			catch (InexistentObject &exc) {
				exists = false;
			}
		}

		try {
			get_period(periodo);
			id_class = E.find_class(Period(periodo[0], periodo[1], periodo[2], periodo[3], periodo[4], periodo[5]));
			valid = true;
		}
		catch (InvalidPeriod &exc) {
			valid = false;
		}

		if (valid) {
			E.change_court(id_court, id_class);

			setcolor(2);
			cout << " The class's court was changed." << endl;
			setcolor(15);
		}
		else {
			setcolor(2);
			cout << " There is no class scheduled for that time." << endl;
			setcolor(15);
		}

		break;
	case 0:

		break;
	}
}

void manage_uses(Empresa &E) {
	int option;
	id_t id_user, id_court, id_use;
	bool exists, valid;
	string name;
	vector<int> periodo = { 0,0,0,0,0,0 }; // Period of type {year, month, day, hour, minutes, blocks}

	system("cls");

	main_header("TENNIS COURT MANAGEMENT");

	header_date("USES MANAGEMENT ", E.get_date());

	setcolor(10); cout << " ["; setcolor(14); cout << "1"; setcolor(10); cout << "]"; setcolor(15); cout << " - Search Use" << endl << endl;
	setcolor(10); cout << " ["; setcolor(14); cout << "2"; setcolor(10); cout << "]"; setcolor(15); cout << " - List Uses" << endl << endl;
	setcolor(10); cout << " ["; setcolor(14); cout << "3"; setcolor(10); cout << "]"; setcolor(15); cout << " - Cancel Use" << endl << endl;
	setcolor(10); cout << " ["; setcolor(14); cout << "0"; setcolor(10); cout << "]"; setcolor(15); cout << " - Back" << endl << endl;

	option = option_input(" Option: ", 0, 3);

	system("cls");

	main_header("TENNIS COURT MANAGEMENT");

	header_date("USES MANAGEMENT ", E.get_date());

	switch (option) {
	case 1:
		id_use = -1;
		valid = false;

		try {
			get_period(periodo);
			id_use = E.find_use(Period(periodo[0], periodo[1], periodo[2], periodo[3], periodo[4], periodo[5]));
			valid = true;
		}
		catch (InvalidPeriod &exc) {
			valid = false;
		}

		if (valid) {
			setcolor(2);
			cout << " There is a usage scheduled. Here is the information:" << endl;
			setcolor(15);

			E.print_use_info(id_use);
		}
		else {
			setcolor(2);
			cout << " There is no usage scheduled for that time." << endl;
			setcolor(15);
		}

		cout << endl;
		system("pause");
		break;
	case 2:
		E.list_uses();

		cout << endl;
		system("pause");
		break;
	case 3:
		id_use = -1;
		id_user = -1;

		exists = false;
		valid = false;

		while (!exists) {
			try {
				name = name_input(" What's the name of the user? ");
				cout << endl;

				id_user = E.find_user(name);
				exists = true;

				try {
					get_period(periodo);
					id_use = E.find_use(Period(periodo[0], periodo[1], periodo[2], periodo[3], periodo[4], periodo[5]));

					try {
						E.cancel_use(id_user, id_use);
					}
					catch (InexistentObject &exc) {
						exists = false;
					}

					valid = true;
				}
				catch (InvalidPeriod &exc) {
					valid = false;
				}
			}

			catch (InexistentObject &exc) {
				exists = false;
			}
			catch (SameName &exc) {
				cout << " There are multiple users with that name.";

				if (choice_input(" Would you like a list of all users? ")) {
					cout << endl;

					E.list_utentes();

					cout << endl;

					id_user = id_input(" Insert the ID of the user: ");
					cout << endl;


					exists = true;
				}
				else {
					exists = false;
				}
			}
		}

		if (valid) {
			setcolor(2);
			cout << " Use canceled." << endl;
			setcolor(15);

		}
		else {
			setcolor(2);
			cout << " There is no usage scheduled for that time." << endl;
			setcolor(15);
		}


		cout << endl;
		system("pause");
		break;
	case 0:

		break;
	}
}

//======================================================================================================================================================//

void schedules_menu(Empresa &E) {
	int option;
	id_t id_user, id_teacher, id_court;
	bool exists, valid;
	string name;

	vector<int> date = { 0,0,0 }; // Date in the form {day, month, year}

	system("cls");

	main_header("TENNIS COURT MANAGEMENT");

	header_date("SCHEDULES MENU ", E.get_date());

	setcolor(10); cout << " ["; setcolor(14); cout << "1"; setcolor(10); cout << "]"; setcolor(15); cout << " - Print User's Schedule" << endl << endl;
	setcolor(10); cout << " ["; setcolor(14); cout << "2"; setcolor(10); cout << "]"; setcolor(15); cout << " - Print Teacher's Schedule" << endl << endl;
	setcolor(10); cout << " ["; setcolor(14); cout << "3"; setcolor(10); cout << "]"; setcolor(15); cout << " - Print Court's Schedule" << endl << endl;
	setcolor(10); cout << " ["; setcolor(14); cout << "4"; setcolor(10); cout << "]"; setcolor(15); cout << " - Print Day's Schedule" << endl << endl;
	setcolor(10); cout << " ["; setcolor(14); cout << "0"; setcolor(10); cout << "]"; setcolor(15); cout << " - Back" << endl << endl;

	option = option_input(" Option: ", 0, 4);

	system("cls");

	main_header("TENNIS COURT MANAGEMENT");

	header_date("SCHEDULES MENU ", E.get_date());

	switch (option) {
	case 1:

		exists = false;
		id_user = -1;

		while (!exists) {
			try {
				name = name_input(" What's the name of the user? ");
				cout << endl;

				id_user = E.find_user(name);
				exists = true;
			}
			catch (InexistentObject &exc) {
				exists = false;
			}
			catch (SameName &exc) {
				cout << " There are multiple users with that name.";

				if (choice_input(" Would you like a list of all users? ")) {
					cout << endl;

					E.list_utentes();

					cout << endl;

					id_user = id_input(" Insert the ID of the user: ");
					cout << endl;


					exists = true;
				}
				else {
					exists = false;
				}
			}
		}

		E.print_user_schedule(id_user);

		cout << endl;
		system("pause");
		break;
	case 2:

		exists = false;
		id_teacher = -1;

		while (!exists) {
			try {
				name = name_input(" What's the name of the teacher? ");
				cout << endl;

				id_teacher = E.find_teacher(name);
				exists = true;
			}
			catch (InexistentObject &exc) {
				exists = false;
			}
			catch (SameName &exc) {
				cout << " There are multiple teachers with that name.";

				if (choice_input(" Would you like a list of all teachers? ")) {
					cout << endl;

					E.list_profs();

					cout << endl;

					id_teacher = id_input(" Insert the ID of the teacher: ");
					cout << endl;


					exists = true;
				}
				else {
					exists = false;
				}
			}
		}

		E.print_prof_schedule(id_teacher);

		cout << endl;
		system("pause");
		break;
	case 3:
		exists = false;
		id_court = -1;

		while (!exists) {
			try {
				id_court = id_input(" Insert the ID of the court: ");
				cout << endl;
				exists = true;
			}
			catch (InexistentObject &exc) {
				exists = false;
			}
		}

		get_date(date);

		E.print_court_schedule(id_court, Date(date.at(2), date.at(1), date.at(0)));

		cout << endl;
		system("pause");
		break;
	case 4:

		get_date(date);

		E.print_day_schedule(Date(date.at(2), date.at(1), date.at(0)));

		break;
	case 0:

		break;

	}
}

//======================================================================================================================================================//

void main_menu(Empresa &E) {
	int option;

	system("cls");

	main_header("TENNIS COURT MANAGEMENT");

	header_date("MAIN MENU ", E.get_date());

	setcolor(10); cout << " ["; setcolor(14); cout << "1"; setcolor(10); cout << "]"; setcolor(15); cout << " - User Menu" << endl << endl;
	setcolor(10); cout << " ["; setcolor(14); cout << "2"; setcolor(10); cout << "]"; setcolor(15); cout << " - Teacher Menu" << endl << endl;
	setcolor(10); cout << " ["; setcolor(14); cout << "3"; setcolor(10); cout << "]"; setcolor(15); cout << " - Company Menu" << endl << endl;
	setcolor(10); cout << " ["; setcolor(14); cout << "0"; setcolor(10); cout << "]"; setcolor(15); cout << " - Exit" << endl << endl;

	option = option_input(" Option: ", 0, 3);

	switch (option) {
	case 1:
		user_menu(E);
		main_menu(E);
		break;
	case 2:
		teacher_menu(E);
		main_menu(E);
		break;
	case 3:
		company_menu(E);
		main_menu(E);
		break;
	case 0:
		system("cls");

		main_header("TENNIS COURT MANAGEMENT");

		header(" EXIT ");

		if (choice_input(" Would you like to save changes?(yes/no) ")) {
			E.save_file();
		}

		system("cls");

		break;
	}

}

void start_menu() {
	int option;
	bool success = false;
	vector <int> date = { 0,0,0 }; // Vector cointainig {day, month, year}
	string name;
	Empresa E = Empresa();
	Date D = Date();

	HANDLE hCon;
	COORD currentPos;

	setcolor(10); cout << " ["; setcolor(14); cout << "1"; setcolor(10);  cout << "]"; setcolor(15); cout << " - Create New Company" << endl << endl;
	setcolor(10); cout << " ["; setcolor(14); cout << "2"; setcolor(10); cout << "]"; setcolor(15); cout << " - Use Existing Company" << endl << endl;
	setcolor(10); cout << " ["; setcolor(14); cout << "0"; setcolor(10); cout << "]"; setcolor(15); cout << " - Exit" << endl << endl;

	option = option_input(" Option: ", 0, 2);

	switch (option) {
	case 1:
		header("CREATE COMPANY");
		name = get_filename(" Name of the company: ", false);
		cout << endl;

		hCon = GetStdHandle(STD_OUTPUT_HANDLE);
		currentPos = GetConsoleCursorPosition(hCon);

		while (!success) {

			get_date(date);

			try {
				D.set_date(date.at(2), date.at(1), date.at(0));
				success = true;
			}
			catch (InvalidDate &exc) {
				clrscr(currentPos);
				success = false;
			}
		}

		E = Empresa(D, name);

		main_menu(E);

		break;

	case 2:
		header("UPLOAD COMPANY");
		name = get_filename(" Name of the file: ", true);

		E.import_file(name);

		main_menu(E);
		break;

	case 0:
		system("cls");
		break;
	}

}