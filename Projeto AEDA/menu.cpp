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

	if (!ui_get_user_id(E, id_user)) {
		menu_exit();
		return;
	}

	setcolor(2);
	cout << " Here is the user's information:" << endl << endl;
	setcolor(15);
	try {
		E.print_user_info(id_user);
	}
	catch (InexistentObject e) {
		cout << " Error: the ID you provided doesn't refer to any user " << endl;
	}

	menu_exit();
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
	menu_exit();
}

void print_user_report(Empresa &E) {
	bool exists = false;
	id_t id_user = 0;
	string name;

	if (!ui_get_user_id(E, id_user)) {
		menu_exit();
		return;
	}

	try {
		E.print_user_report(id_user);
	}
	catch (InexistentObject e) {
		cout << "Didn't find any user, did you write the right ID?" << endl;
	}

	menu_exit();
}

void attend_class(Empresa &E) {
	bool exists = false;
	bool valid = false;
	id_t id_user = 0;
	id_t id_class = 0;
	string name;

	if (!ui_get_user_id(E, id_user)) {
		menu_exit();
		return;
	}

	exists = false;
	while (!exists) {
		try {
			id_class = E.find_class(get_period());
			exists = true;
		}
		catch (InexistentObject e) {
			cout << " Could not find a class at that time." << endl;
			if (!choice_input(" Do you want to search for a class at another time? ")) {
				menu_exit();
				return;
			}
		}
	}
	
	

	setcolor(2);
	try {
		E.attend_class(id_user, id_class);
		cout << " Successfully scheduled class attendance." << endl;
	}
	catch (InexistentObject e) {
		cout << "You input an id that doesn't correspond to any user. Could not schedule class attendance." << endl;
	}
	setcolor(15);

	menu_exit();
}

void schedule_free_use(Empresa &E) {
	bool exists = false;
	bool valid = false;
	string name;
	id_t id_user = 0;
	id_t id_court = 0;

	if (!ui_get_user_id(E, id_user)) {
		cout << endl;
		sys_pause();
		return;
	}

	exists = false;

	while (!exists) {
		try {
			id_court = id_input(" Insert the ID of the court: ");
			cout << endl;
			exists = true;

			while (!valid) {
				try {
					E.schedule_free_use(id_user, id_court, get_period());
					valid = true;
				}
				catch (InvalidPeriod e) {
					valid = false;
				}
				catch (CourtIsFull e) {
					valid = true;
					exists = false;

					cout << " Court is full. ";
					if (!choice_input("Do you want to try to schedule the use on another court? ")) {
						cout << endl;
						sys_pause();
						return;
					}
				}
			}
		}
		catch (InexistentObject e) {
			if (e.get_class() == "Court") {
				cout << " Did not find a court with that ID. ";
				if (!choice_input("Do you want to try again? ")) {
					cout << endl;
					sys_pause();
					return;
				}
				else {
					valid = false;
					exists = false;
				}
			}
			else {
				cout << "You input an user id that doesn't correspond to anyone in our records. Could not schedule free use" << endl;
				cout << endl;
				sys_pause();
				return;
			}
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
	id_t id_user = 0;

	while (!exists) {
		try {
			name = name_input(" What's the name of the user? ");
			cout << endl;

			id_user = E.find_user(name);
			exists = true;
		}
		catch (InexistentObject e) {
			cout << " There is no user with that name." << endl << endl;
			sys_pause();
			return;
		}
		catch (SameName e) {
			cout << " There are multiple users with that name." << endl;

			if (choice_input(" We will need the User's ID to fetch their record. Do you want a list of all users to get it?")) {
				cout << endl;

				E.list_utentes();

				cout << endl;

				id_user = id_input(" Insert the ID of the user: ");
				cout << endl;


				exists = true;
			}
			else if (choice_input(" Do want to insert the ID?")) {

				id_user = id_input(" Insert the ID of the user: ");

			}
			else {

				cout << " Unable to find the user." << endl << endl;
				cout << endl;
				sys_pause();
				return;
			}
		}
	}

	E.print_bill(id_user);

	cout << endl;
	sys_pause();
}

void pay_debt(Empresa& E) {
	id_t id = 0;
	if (!ui_get_user_id(E, id)) {
		menu_exit();
		return;
	}

	setcolor(2);
	try {
		E.pay_debt(id);
		cout << " Debt paid successfully." << endl;
	}
	catch (InexistentObject e) {
		cout << " Couldn't find a user with that ID." << endl;
	}
	setcolor(15);

	menu_exit();
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
	menu_exit();
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
	cout << " User added. " << endl;
	setcolor(15);
	menu_exit();
}

void remove_user(Empresa &E) {
	id_t id = 0;

	if (!ui_get_user_id(E, id)) {
		menu_exit();
		return;
	}

	
	setcolor(2);
	try {
		E.remove_utente(id);
		cout << " User removed successfully." << endl;
	}
	catch (InexistentObject e) {
		cout << " Couldn't find a user with that ID." << endl;
	}
	setcolor(15);
	menu_exit();
}

void update_gold_card(Empresa &E) {
	id_t id = 0;
	bool gold_card = false;

	if (!ui_get_user_id(E, id)) {
		menu_exit();
		return;
	}

	gold_card = choice_input(" Does the user want a gold card? ");
	cout << endl;

	setcolor(2);
	try {
		E.change_card(id, gold_card);
		cout << " Changed successfully." << endl;
	}
	catch (InexistentObject e) {
		cout << " Couldn't find a user with that ID." << endl;
	}
	setcolor(15);
	menu_exit();
}

//======================================================================================================================================================//

void add_teacher(Empresa &E) {
	string name = name_input(" What's the name of the teacher? ");

	cout << endl;

	E.add_prof(name);

	setcolor(2);
	cout << " Teacher added successfully." << endl;
	setcolor(15);
	menu_exit();
}

void remove_teacher(Empresa &E) {
	id_t id;
	ui_get_teacher_id(E, id);

	setcolor(2);
	try {
		E.remove_prof(id);
		cout << " Teacher removed successfully. " << endl;
	}
	catch (InexistentObject e) {
		cout << " Error: Could not find a teacher with that ID" << endl;
	}
	setcolor(15);

	menu_exit();
}

void search_teacher(Empresa &E) {
	id_t id;
	ui_get_teacher_id(E, id);

	setcolor(2);
	try {
		cout << " Here is the teacher's information:" << endl;
		setcolor(15);
		E.print_teacher_info(id);
	}
	catch (InexistentObject e) {
		setcolor(2);
		cout << " Error: Could not find a teacher with that ID" << endl;
	}
	setcolor(15);

	menu_exit();
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
	bool exit = false;
	while (!exit) {

		id_t id = id_input(" Insert the ID of the court: ");
		cout << endl;

		try {
			E.remove_court(id);
			setcolor(2);
			cout << " Court removed sucessfully" << endl;
			setcolor(15);
			exit = true;
		}
		catch (InexistentObject e) {
			setcolor(2);
			cout << " Error: there exists no court with that ID." << endl;
			setcolor(15);

			exit = !choice_input(" Do you want to try again with a diferent court ID?");
		}
	}
	
	menu_exit();
}

void change_court_capacity(Empresa &E) {
	bool exit = false;
	while (!exit) {

		id_t id = id_input(" Insert the ID of the court: ");
		cout << endl;

		int capacity = capacity_input(" Court's new capacity: ");
		cout << endl;

		try {
			//CHANGE COURT CAPACITY HERE
			setcolor(2);
			cout << " Sucessfully changed the court's capacity" << endl;
			setcolor(15);
			exit = true;
		}
		catch (InexistentObject e) {
			setcolor(2);
			cout << " Error: there exists no court with that ID." << endl;
			setcolor(15);

			exit = !choice_input(" Do you want to try again with a diferent court ID?");
		}
	}

	menu_exit();
}

void list_courts(Empresa &E) {
	E.list_courts();
	menu_exit();
}

//======================================================================================================================================================//

void search_class(Empresa &E) {
	id_t id_class = 0;
	bool valid = false;

	try {
		id_class = E.find_class(get_period());
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
	id_t id_class = 0;
	bool valid = false;

	try {
		id_class = E.find_class(get_period());
		valid = true;
	}
	catch (InexistentObject e) {
		valid = false;
	}

	if (valid) {
		setcolor(2);
		cout << " Here are the class details:" << endl;
		setcolor(15);
		E.print_class_info(id_class);
		cout << endl;

		if (choice_input(" Are you sure you want to cancel the class?")) {
			E.cancel_class(id_class);
			cout << " Class canceled successfully." << endl;
		}
	}
	else {
		setcolor(2);
		cout << " There is no class scheduled for that time." << endl;
		setcolor(15);
	}

	menu_exit();
}

void change_teacher(Empresa &E) {
	id_t id_class = 0;
	id_t id_teacher = 0;
	bool valid = false;

	ui_get_teacher_id(E, id_teacher);

	try {
		id_class = E.find_class(get_period());
		valid = true;
	}
	catch (InvalidPeriod e) {
		valid = false;
	}

	if (valid) {
		try {
			E.change_teacher(id_teacher, id_class);
			setcolor(2);
			cout << " The class's teacher was changed." << endl;
			setcolor(15);
		}
		catch (InexistentObject e) {
			setcolor(2);
			cout << " Error: found no teacher with that ID" << endl;
			setcolor(15);
		}
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
		id_class = E.find_class(get_period());
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

	try {
		id_use = E.find_use(get_period());
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
				id_use = E.find_use(get_period());

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

	E.print_court_schedule(id_court, get_date());

	cout << endl;
	sys_pause();
}

void print_day_schedule(Empresa &E) {
	E.print_day_schedule(get_date());
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

	header("CREATE COMPANY");
	string name = get_filename(" Name of the company: ", false);
	cout << endl;

	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD currentPos = GetConsoleCursorPosition(hCon);

	E = Empresa(get_date(), name);

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