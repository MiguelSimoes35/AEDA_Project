#include "menu.h"

using namespace std;

//======================================================================================================================================================//

void user_menu(Empresa &E) {
	vector<MenuOption> options = {
		MenuOption("Search User",search_user),
		MenuOption("Manage Payment",payments_menu),
		MenuOption("Print User Report",print_user_report),
		MenuOption("List Users",list_users),
		MenuOption("Schedules",schedules_menu),
		MenuOption("Attend Class",attend_class),
		MenuOption("Schedule Free Use",schedules_menu)
	};
	string header = "User Menu";
	OptionMenu(options,header).run(E);
}

void search_user(Empresa& E) {
	bool exists = false;
	id_t id_user = 0;
	string name;

	try {
		name = name_input(" What's the name of the user? ");
		cout << endl;
		id_user = E.find_user(name);
		exists = true;
	}
	catch (InexistentObject e) {
		exists = false;
	}
	catch (SameName e) {
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
	sys_pause();
}

void payments_menu(Empresa &E) {
	vector<MenuOption> options = {
		MenuOption("Print Bill",print_bill),
		MenuOption("Pay Debt",pay_debt)
	};
	string header = "PAYMENTS MENU";
	OptionMenu(options, header).run(E);
}

void list_users(Empresa &E) {
	E.list_utentes();
	cout << endl;
	sys_pause();
}

void print_user_report(Empresa &E) {
	bool exists = false;
	id_t id_user = 0;
	string name;

	while (!exists) {
		try {
			name = name_input(" What's the name of the user? ");
			cout << endl;

			id_user = E.find_user(name);
			exists = true;
		}
		catch (InexistentObject e) {
			exists = false;
		}
		catch (SameName e) {
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
	sys_pause();
}

void attend_class(Empresa &E) {
	bool exists = false;
	bool valid = false;
	id_t id_user = 0;
	id_t id_class = 0;
	string name;
	vector<int> periodo = { 0,0,0,0,0,0 };

	while (!exists) {
		try {
			name = name_input(" What's the name of the user? ");
			cout << endl;

			id_user = E.find_user(name);
			exists = true;
		}
		catch (InexistentObject e) {
			exists = false;
		}
		catch (SameName e) {
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
	catch (InvalidPeriod e) {
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
	sys_pause();
}

void schedule_free_use(Empresa &E) {
	bool exists = false;
	bool valid = false;
	string name;
	id_t id_user = 0;
	id_t id_court = 0;
	vector<int> periodo = { 0,0,0,0,0,0 };

	while (!exists) {
		try {
			name = name_input(" What's the name of the user? ");
			cout << endl;

			id_user = E.find_user(name);
			exists = true;
		}
		catch (InexistentObject e) {
			exists = false;
		}
		catch (SameName e) {
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
				catch (InvalidPeriod e) {
					valid = false;
				}
				catch (CourtIsFull e) {
					valid = true;
					exists = false;

					cout << " Court is full. Pick a different court or period." << endl << endl;
				}
			}
		}
		catch (InexistentObject e) {
			exists = false;
		}
	}


	setcolor(2);
	cout << endl << " Free use scheduled." << endl;
	setcolor(15);

	cout << endl;
	sys_pause();
}

void print_bill(Empresa &E) {
	string name;
	bool exists = false;
	id_t id = 0;

	while (!exists) {
		try {
			name = name_input(" What's the name of the user? ");
			cout << endl;

			id = E.find_user(name);
			exists = true;
		}
		catch (InexistentObject e) {
			exists = false;
		}
		catch (SameName e) {
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
	sys_pause();
}

void pay_debt(Empresa& E) {
	bool exists = false;
	id_t id = 0;
	string name;

	while (!exists) {
		try {
			name = name_input(" What's the name of the user? ");
			cout << endl;

			id = E.find_user(name);
			exists = true;
		}
		catch (InexistentObject e) {
			exists = false;
		}
		catch (SameName e) {
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
	cout << " Debt paid successfully." << endl;
	setcolor(15);
	sys_pause();
}

//======================================================================================================================================================//

void teacher_menu(Empresa &E) {
	vector<MenuOption> options = {
		MenuOption("Search Teacher",search_teacher),
		MenuOption("List Teachers",list_teachers),
		MenuOption("Schedules",schedules_menu)
	};
	string header = "TEACHER MENU";
	OptionMenu(options, header).run(E);
}

void list_teachers(Empresa &E) {
	E.list_profs();
	cout << endl;
	sys_pause();
}

//======================================================================================================================================================//

void company_menu(Empresa &E) {
	string header = "COMPANY MENU";
	vector<MenuOption> options = {
		MenuOption("Manage Users",manage_users),
		MenuOption("Manage Teacher",manage_teachers),
		MenuOption("Manage Courts",manage_courts),
		MenuOption("Manage Uses",manage_uses),
		MenuOption("End Day",end_day)
	};
	OptionMenu(options, header).run(E);
}

void manage_users(Empresa &E) {
	vector<MenuOption> options = {
		MenuOption("Add User",add_user),
		MenuOption("Remove User",remove_user),
		MenuOption("Update Gold Card",update_gold_card),
		MenuOption("Search User",search_user),
		MenuOption("List Users",list_users)
	};
	string header = "USER MANAGEMENT";
	OptionMenu(options, header).run(E);
}

void manage_teachers(Empresa &E) {
	vector<MenuOption> options = {
		MenuOption("Add Teacher",add_teacher),
		MenuOption("Remove Teacher",remove_teacher),
		MenuOption("Search Teacher",search_teacher),
		MenuOption("List Teachers",list_teachers)
	};
	string header = "TEACHER MANAGEMENT";
	OptionMenu(options, header).run(E);
}

void manage_courts(Empresa &E) {
	vector<MenuOption> options = {
		MenuOption("Add Court",add_court),
		MenuOption("Remove Court",remove_court),
		MenuOption("Change Court Capacity",change_court_capacity),
		MenuOption("List Courts",list_courts)
	};
	string header = "COURT MANAGEMENT";
	OptionMenu(options, header).run(E);
}

void manage_classes(Empresa &E) {
	vector<MenuOption> options = {
		MenuOption("Search Class",search_class),
		MenuOption("List Classes",list_classes),
		MenuOption("Cancel Class",cancel_class),
		MenuOption("Change Teacher",change_teacher),
		MenuOption("Change Court",change_court)
	};
	string header = "CLASSES_MANAGEMENT";
	OptionMenu(options, header).run(E);
}

void manage_uses(Empresa &E) {
	vector<MenuOption> options = {
		MenuOption("Search Use",search_use),
		MenuOption("List Uses",list_uses),
		MenuOption("Cancel Use",cancel_use)
	};
	string header = "USES MANAGEMENT";
	OptionMenu(options, header).run(E);
}

void end_day(Empresa &E) {
	E.increment_date();
}

//======================================================================================================================================================//

void add_user(Empresa &E) {
	string name = name_input(" What's the name of the user? ");

	cout << endl;

	bool gold_card = choice_input(" Acquire gold card?(yes/no) ");

	cout << endl;

	E.add_utente(name, gold_card);

	setcolor(2);
	cout << " User added. " << endl << endl;
	setcolor(15);
	sys_pause();
}

void remove_user(Empresa &E) {
	bool exists = false;
	id_t id = 0;
	string name;

	while (!exists) {
		try {
			name = name_input(" What's the name of the user? ");
			cout << endl;

			id = E.find_user(name);
			exists = true;
		}
		catch (InexistentObject e) {
			exists = false;
		}
		catch (SameName e) {
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
	sys_pause();
}

void update_gold_card(Empresa &E) {
	bool exists = false;
	id_t id = 0;
	bool gold_card = false;
	string name;

	while (!exists) {
		try {
			name = name_input(" What's the name of the user? ");
			cout << endl;

			id = E.find_user(name);
			exists = true;
		}
		catch (InexistentObject e) {
			exists = false;
		}
		catch (SameName e) {
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
	sys_pause();
}

//======================================================================================================================================================//

void add_teacher(Empresa &E) {
	string name = name_input(" What's the name of the teacher? ");

	cout << endl;

	E.add_prof(name);

	setcolor(2);
	cout << " Teacher added." << endl << endl;
	setcolor(15);
	sys_pause();
}

void remove_teacher(Empresa &E) {
	bool exists = false;
	id_t id = 0;
	string name;

	while (!exists) {
		try {
			name = name_input(" What's the name of the teacher? ");
			cout << endl;

			id = E.find_teacher(name);
			exists = true;
		}
		catch (InexistentObject e) {
			exists = false;
		}
		catch (SameName e) {
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
	sys_pause();
}

void search_teacher(Empresa &E) {
	bool exists = false;
	id_t id = 0;
	string name;

	try {
		name = name_input(" What's the name of the teacher? ");
		id = E.find_teacher(name);
		exists = true;
	}
	catch (InexistentObject e) {
		exists = false;
	}
	catch (SameName e) {
		cout << " There are multiple teachers with that name.";

		if (choice_input(" Would you like a list of all teachers? ")) {
			cout << endl;

			E.list_profs();
			return;
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
	sys_pause();
}

//======================================================================================================================================================//

void add_court(Empresa &E) {
	int capacity = 0;

	capacity = capacity_input(" New court capacity: ");

	E.add_court(capacity);

	setcolor(2);
	cout << " Court added." << endl << endl;
	setcolor(15);
	sys_pause();
}

void remove_court(Empresa &E) {
	bool exists = false;
	id_t id = id_input(" Insert the ID of the court: ");
	cout << endl;

	try {
		E.remove_court(id);
	}
	catch (InexistentObject e) {
		cout << " Error: there exists no court with that ID." << endl << endl;
		sys_pause();
		return;
	}

	setcolor(2);
	cout << " Court removed" << endl << endl;
	setcolor(15);
	sys_pause();
}

void change_court_capacity(Empresa &E) {
	bool exists = false;
	id_t id = 0;
	int capacity = 0;


	while (!exists) {
		try {
			id = id_input(" Insert the ID of the court: ");
			cout << endl;
			exists = true;
		}
		catch (InexistentObject e) {
			exists = false;
		}
	}


	capacity = capacity_input(" Court's new capacity: ");

	setcolor(2);
	cout << " Court's capacity changed." << endl << endl;
	setcolor(15);
	sys_pause();
}

void list_courts(Empresa &E) {
	E.list_courts();
	cout << endl;
	sys_pause();
}

//======================================================================================================================================================//

void search_class(Empresa &E) {
	vector<int> periodo = { 0,0,0,0,0,0 };
	id_t id_class = 0;
	bool valid = false;

	try {
		get_period(periodo);
		id_class = E.find_class(Period(periodo[0], periodo[1], periodo[2], periodo[3], periodo[4], periodo[5]));
		valid = true;
	}
	catch (InvalidPeriod e) {
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
	sys_pause();
}

void cancel_class(Empresa &E) {
	vector<int> periodo = { 0,0,0,0,0,0 };
	id_t id_class = 0;
	bool valid = false;

	try {
		get_period(periodo);
		id_class = E.find_class(Period(periodo[0], periodo[1], periodo[2], periodo[3], periodo[4], periodo[5]));
		valid = true;
	}
	catch (InvalidPeriod e) {
		cout << "Error: you input an invalid period" << endl;
		sys_pause();
		return;
	}
	catch (InexistentObject e) {
		valid = false;
	}

	if (valid) {
		setcolor(2);
		cout << " The class exists. Here is the information:" << endl;
		setcolor(15);

		E.cancel_class(id_class);
		cout << " Class canceled successfully." << endl;
	}
	else {
		setcolor(2);
		cout << " There is no class scheduled for that time." << endl;
		setcolor(15);
	}

	cout << endl;
	sys_pause();
}

void change_teacher(Empresa &E) {
	id_t id_class = 0;
	id_t id_teacher = 0;
	vector<int> periodo = { 0,0,0,0,0,0 };
	bool valid = false;
	bool exists = false;
	string name;

	while (!exists) {
		try {
			name = name_input(" What's the name of the teacher? ");
			id_teacher = E.find_teacher(name);
			exists = true;
		}
		catch (InexistentObject e) {
			exists = false;
		}
		catch (SameName e) {
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
	catch (InvalidPeriod e) {
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

}

void change_court(Empresa &E) {
	id_t id_class = 0;
	id_t id_court = 0;
	vector<int> periodo = { 0,0,0,0,0,0 };
	bool exists = false;
	bool valid = false;

	while (!exists) {
		try {
			id_court = id_input(" Insert the ID of the court: ");
			cout << endl;
			exists = true;
		}
		catch (InexistentObject e) {
			exists = false;
		}
	}

	try {
		get_period(periodo);
		id_class = E.find_class(Period(periodo[0], periodo[1], periodo[2], periodo[3], periodo[4], periodo[5]));
		valid = true;
	}
	catch (InvalidPeriod e) {
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

}

void list_classes(Empresa &E) {
	E.list_classes();
	cout << endl;
	sys_pause();
}

//======================================================================================================================================================//

void search_use(Empresa &E) {
	id_t id_use = 0;
	bool valid = false;
	vector<int> periodo = { 0,0,0,0,0,0 };

	try {
		get_period(periodo);
		id_use = E.find_use(Period(periodo[0], periodo[1], periodo[2], periodo[3], periodo[4], periodo[5]));
		valid = true;
	}
	catch (InvalidPeriod e) {
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
	sys_pause();
}

void list_uses(Empresa &E) {
	E.list_uses();
	cout << endl;
	sys_pause();
}

void cancel_use(Empresa &E) {
	vector<int> periodo = { 0,0,0,0,0,0 };
	id_t id_use = 0;
	id_t id_user = 0;
	bool exists = false;
	bool valid = false;
	string name;

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
				catch (InexistentObject e) {
					exists = false;
				}

				valid = true;
			}
			catch (InvalidPeriod e) {
				valid = false;
			}
		}

		catch (InexistentObject e) {
			exists = false;
		}
		catch (SameName e) {
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
	sys_pause();
}

//======================================================================================================================================================//

void schedules_menu(Empresa &E) {
	vector<MenuOption> options = {
		MenuOption("Print User Schedule",print_user_schedule),
		MenuOption("Print Teacher Schedule",print_teacher_schedule),
		MenuOption("Print Court Schedule",print_court_schedule),
		MenuOption("Print the Schedule of a Day",print_day_schedule)
	};
	string header = "SCHEDULES MENU";
	OptionMenu(options, header).run(E);
}

void print_user_schedule(Empresa &E) {
	bool exists = false;
	id_t id_user = 0;
	string name;

	while (!exists) {
		try {
			name = name_input(" What's the name of the user? ");
			cout << endl;

			id_user = E.find_user(name);
			exists = true;
		}
		catch (InexistentObject e) {
			exists = false;
		}
		catch (SameName e) {
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
	sys_pause();
}

void print_teacher_schedule(Empresa &E) {
	bool exists = false;
	id_t id_teacher = 0;
	string name;

	while (!exists) {
		try {
			name = name_input(" What's the name of the teacher? ");
			cout << endl;

			id_teacher = E.find_teacher(name);
			exists = true;
		}
		catch (InexistentObject e) {
			exists = false;
		}
		catch (SameName e) {
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
	sys_pause();
}

void print_court_schedule(Empresa &E) {
	bool exists = false;
	id_t id_court = 0;
	vector<int> date = { 0,0,0 };

	while (!exists) {
		try {
			id_court = id_input(" Insert the ID of the court: ");
			cout << endl;
			exists = true;
		}
		catch (InexistentObject e) {
			exists = false;
		}
	}

	get_date(date);

	E.print_court_schedule(id_court, Date(date.at(2), date.at(1), date.at(0)));

	cout << endl;
	sys_pause();
}

void print_day_schedule(Empresa &E) {
	vector<int> date = { 0,0,0 };
	get_date(date);
	E.print_day_schedule(Date(date.at(2), date.at(1), date.at(0)));
	sys_pause();
}

//======================================================================================================================================================//

void main_menu(Empresa &E) {
	vector<MenuOption> options = {
		MenuOption("User Menu",user_menu),
		MenuOption("Teacher Menu",teacher_menu),
		MenuOption("Company Menu",company_menu)
	};
	string header = "MAIN MENU";
	OptionMenu(options, header, "Exit").run(E);
}

void exit_menu(Empresa &E) {
	sys_clear();

	main_header("TENNIS COURT MANAGEMENT");

	header(" EXIT ");

	if (choice_input(" Would you like to save changes?(yes/no) ")) {
		E.save_file();
	}

	sys_clear();
}

void new_company(Empresa &E) {
	int option;
	bool success = false;
	vector <int> date = { 0,0,0 };
	Date D;

	header("CREATE COMPANY");
	string name = get_filename(" Name of the company: ", false);
	cout << endl;

	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD currentPos = GetConsoleCursorPosition(hCon);

	while (!success) {

		get_date(date);

		try {
			D.set_date(date.at(2), date.at(1), date.at(0));
			success = true;
		}
		catch (InvalidDate e) {
			clrscr(currentPos);
			success = false;
		}
	}

	E = Empresa(D, name);

	main_menu(E);

	exit_menu(E);
}

void load_company(Empresa &E) {
	header("UPLOAD COMPANY");
	string name = get_filename(" Name of the file: ", true);
	E = Empresa(name);
	main_menu(E);
	exit_menu(E);
}

void start_menu() {
	Empresa E = Empresa();
	vector<MenuOption> options = {
		MenuOption("Create New Company",new_company),
		MenuOption("Use existing company",load_company)
	};
	string header = "TENNIS MANAGEMENT SYSTEM";
	OptionMenu(options, header, "Exit", true).run(E);
}