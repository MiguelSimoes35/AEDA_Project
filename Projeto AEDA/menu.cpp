/*
 * (c) 2018 Griné, Matos, and Simões
 * This software is provided under the MIT License.
 * To obtain a copy of this license, please read the file LICENSE at the root of the repository, or visit
 * https://opensource.org/licenses/MIT
 */

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
	string name;
	if (ui_get_user_name(E, name)) {
		setcolor(2);
		cout << " Here is the user's information:" << endl;
		setcolor(15);
		cout << endl;
		E.print_user_info(name);
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
	string name;
	if (ui_get_user_name(E, name)) {
		E.print_user_report(name);
	}
	menu_exit();
}

void attend_class(Empresa &E) {
	bool exists = false;
	bool valid = false;
	id_t id_class = 0;
	string name;

	if (!ui_get_user_name(E, name)) {
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
			if (!choice_input(" Do you want to search for a class at another time? (yes/no) ")) {
				menu_exit();
				return;
			}
		}
	}
	
	
	E.attend_class(name, id_class);
	setcolor(2);
	cout << " Done." << endl;
	setcolor(15);

	menu_exit();
}

void schedule_free_use(Empresa &E) {
	bool exists = false;
	bool valid = false;
	string name;
	id_t id_court = 0;

	if (!ui_get_user_name(E, name)) {
		menu_exit();
		return;
	}

	Period time = get_period();

	exists = false;

	while (!exists) {
		try {
			id_court = id_input(" Insert the ID of the court: ");
			cout << endl;
			exists = true;

			while (!valid) {
				try {
					E.schedule_free_use(name, id_court, time);
					valid = true;
				}
				catch (InvalidPeriod e) {
					valid = false;
				}
				catch (CourtIsFull e) {
					valid = true;
					exists = false;

					cout << " Court is full. ";
					if (!choice_input(" Do you want to try to schedule the use on another court? (yes/no) ")) {
						cout << endl;
						sys_pause();
						return;
					}
				}
			}
		}
		catch (InexistentObject e) {
			cout << " Did not find a court with that ID. ";
			if (!choice_input(" Do you want to try again? (yes/no) ")) {
				menu_exit();
				return;
			}
			else {
				valid = false;
				exists = false;
			}
		}
	}


	setcolor(2);
	cout << endl << " Done." << endl;
	setcolor(15);

	cout << endl;
	sys_pause();
}

void print_bill(Empresa &E) {
	string name;
	if (ui_get_user_name(E, name)) {
		E.print_bill(name);
	}
	menu_exit();
}

void pay_debt(Empresa& E) {
	string name;
	if (ui_get_user_name(E, name)) {
		E.pay_debt(name);
		setcolor(2);
		cout << " Done." << endl;
		setcolor(15);
	}
	menu_exit();
}

void schedule_class(Empresa &E) {
	string name;
	if (!ui_get_teacher_name(E, name)) {
		menu_exit();
		return;
	}

	id_t court_id = id_input(" Input the court's ID. ");

	Period period = get_period();
	setcolor(2);
	try {
		E.schedule_class(name, court_id, period);
		cout << " Done." << endl;
	}
	catch (CourtIsFull e) {
		cout << " The court is full, please schedule on another court or another time." << endl;
	}
	catch (InexistentObject e) {
		cout << " " << e.get_class() << " ID does not correspond to an existent court. Please try another one." << endl;
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
		MenuOption("Manage Technicians",manage_technicians),
		MenuOption("Manage Courts",manage_courts),
		MenuOption("Manage Classes",manage_classes),
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
		MenuOption("Schedule Class",schedule_class),
		MenuOption("Search Class",search_class),
		MenuOption("List Classes",list_classes),
		MenuOption("Cancel Class",cancel_class),
		MenuOption("Change Teacher",change_teacher),
		MenuOption("Change Court",change_court),
	};
	string header = "CLASS MANAGEMENT";
	OptionMenu(options, header).run(E);
}

void manage_uses(Empresa &E) {
	vector<MenuOption> options = {
		MenuOption("Search Use",search_use),
		MenuOption("List Uses",list_uses),
		MenuOption("Cancel Use",cancel_use)
	};
	string header = "USE MANAGEMENT";
	OptionMenu(options, header).run(E);
}

void end_day(Empresa &E) {
	E.increment_date();
}

//======================================================================================================================================================//

void add_user(Empresa &E) {
	string name = name_input(" What's the name of the user? ");

	cout << endl;

	bool gold_card = choice_input(" Acquire gold card? (yes/no) ");

	cout << endl;

	string address = string_input(" What is the user's adress? ");

	cout << endl;

	unsigned tax_no = id_input(" What is the user's tax number (NIF)? ");

	cout << endl;

	E.add_utente(name, gold_card, address, tax_no);

	setcolor(2);
	cout << " Done. " << endl;
	setcolor(15);
	menu_exit();
}

void remove_user(Empresa &E) {
	string name;
	if (ui_get_user_name(E, name)) {
		cout << endl;
		E.remove_utente(name);
		setcolor(2);
		cout << " Done." << endl;
		setcolor(15);
	}
	menu_exit();
}

void update_gold_card(Empresa &E) {
	string name;
	if (ui_get_user_name(E, name)) {
		bool gold_card = choice_input(" Does the user want a gold card? (yes/no) ");
		cout << endl;
		E.change_card(name, gold_card);
		setcolor(2);
		cout << " Done." << endl;
		setcolor(15);
	}
	menu_exit();
}

//======================================================================================================================================================//

void add_teacher(Empresa &E) {
	string name = name_input(" What's the name of the teacher? ");
	cout << endl;
	E.add_prof(name);
	setcolor(2);
	cout << endl << " Done." << endl;
	setcolor(15);
	menu_exit();
}

void remove_teacher(Empresa &E) {
	string name;
	if (ui_get_teacher_name(E, name)) {
		E.remove_prof(name);
		setcolor(2);
		cout << " Done." << endl;
		setcolor(15);
	}
	menu_exit();
}

void search_teacher(Empresa &E) {
	string name;
	if (ui_get_teacher_name(E, name)) {
		setcolor(2);
		cout << " Here is the teacher's information:" << endl;
		setcolor(15);
		E.print_teacher_info(name);
	}
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

			exit = !choice_input(" Do you want to try again with a diferent court ID? (yes/no) ");
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
			E.change_capacity(id, capacity); //CHANGE COURT CAPACITY HERE
			setcolor(2);
			cout << " Sucessfully changed the court's capacity" << endl;
			setcolor(15);
			exit = true;
		}
		catch (InexistentObject e) {
			setcolor(2);
			cout << " Error: there exists no court with that ID." << endl;
			setcolor(15);

			exit = !choice_input(" Do you want to try again with a diferent court ID? (yes/no) ");
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
		cout << " Here are the class details: " << endl;
		setcolor(15);
		E.print_class_info(id_class);
		cout << endl;

		if (choice_input(" Are you sure you want to cancel the class? (yes/no) ")) {
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
	string teacher_name;
	bool valid = false;

	if (!ui_get_teacher_name(E, teacher_name)) {
		menu_exit();
		return;
	}

	try {
		id_class = E.find_class(get_period());
		valid = true;
	}
	catch (InexistentObject e) {
		valid = false;
	}

	if (valid) {
		E.change_teacher(teacher_name, id_class);
		setcolor(2);
		cout << " Done." << endl;
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
	if (!ui_find_class(E, id_class)) {
		menu_exit();
		return;
	}

	id_t id_court = 0;
	while (true) {
		id_court = id_input(" Insert the ID of the desired court ");

		try {
			E.change_court(id_court, id_class);
			setcolor(2);
			cout << " The court was successfully changed." << endl;
			setcolor(15);
			menu_exit();
			return;
		}
		catch (InexistentObject e) {
			cout << "Error: there is no court with that ID." << endl;
			if (!choice_input(" Do you want to try a different court? ")) {
				menu_exit();
				return;
			}
		}
		catch (CourtIsFull e) {
			cout << "Error: the court you selected is full" << endl;
			if (!choice_input(" Do you want to try a different court? (yes/no) ")) {
				menu_exit();
				return;
			}
		}
	}
}

void list_classes(Empresa &E) {
	E.list_classes();
	menu_exit();
}

//======================================================================================================================================================//

void search_use(Empresa &E) {
	id_t id_use = 0;
	bool valid = false;

	try {
		id_use = E.find_use(get_period());
		valid = true;
	}
	catch (InexistentObject e) {
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

	menu_exit();
}

void list_uses(Empresa &E) {
	E.list_uses();
	menu_exit();
}

void cancel_use(Empresa &E) {
	id_t id_use = 0;
	string name;

	if (!ui_get_user_name(E, name)) {
		menu_exit();
		return;
	}

	if (!ui_find_use(E, id_use)) {
		menu_exit();
		return;
	}

	setcolor(2);
	try {
		E.cancel_use(name,id_use);
		cout << " Free use cancelled successfully." << endl;
	}
	catch (InexistentObject e) {
		cout << " Error: Did not find a use to remove. Perhaps the use you found does not correspond to the user." << endl;
	}
	setcolor(15);

	menu_exit();
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
	string name;
	if (ui_get_user_name(E, name)) {
		E.print_user_schedule(name);
	}
	menu_exit();
}

void print_teacher_schedule(Empresa &E) {
	string name;
	if (ui_get_teacher_name(E, name)) {
		E.print_prof_schedule(name);
	}	
	menu_exit();
}

void print_court_schedule(Empresa &E) {
	id_t id_court = id_input(" Insert the ID of the court: ");
	cout << endl;
	
	try {
		E.print_court_schedule(id_court, get_date());
	}
	catch (InexistentObject e) {
		setcolor(2);
		cout << " The ID provided doesn't correspond to any court." << endl;
	}

	cout << endl;
	sys_pause();
}

void print_day_schedule(Empresa &E) {
	E.print_day_schedule(get_date());
	sys_pause();
}

//======================================================================================================================================================//

void manage_technicians(Empresa &E) {
	vector<MenuOption> options = {
		MenuOption("Add Technician",add_technician),
		MenuOption("Remove Technician",remove_technician),
		MenuOption("Assign Technician",assign_technician),
		MenuOption("List Technicians",list_technicians)
	};
	string header = "MANAGE TECHNICIANS";
	OptionMenu(options, header).run(E);
}

void add_technician(Empresa &E) {
	string name = name_input(" What's the name of the technician? ");

	cout << endl;

	E.add_technician(name);

	setcolor(2);
	cout << " Technician added successfully." << endl;
	setcolor(15);
	menu_exit();
}

void remove_technician(Empresa &E) {
	id_t id;
	if (ui_get_technician_id(E, id)) {
		E.remove_technician(id);
		setcolor(2);
		cout << " Done." << endl;
		setcolor(15);
	}
	else {
		setcolor(2);
		cout << " Cannot proceed with the operation." << endl;
		setcolor(15);
	}
	menu_exit();
}

void assign_technician(Empresa &E) {
	id_t id = id_input(" Insert the name of the court on which to perform maintenance: ");
	int days = days_input(" Insert how many days maintenance will take: ");
	unsigned max = id_input(" What is the maximum number of assignments the technicians can take? ");
	cout << endl;

	E.assign_technician(id, days, max);

	setcolor(2);
	cout << " Done" << endl;
	setcolor(15);
	menu_exit();
}

void list_technicians(Empresa &E) {
	setcolor(2);
	cout << " Here is the list of the company's technicians: " << endl;
	setcolor(15);
	cout << endl;
	E.list_technicians();
	menu_exit();
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

/**
 * Optionally saves the company to a file
 * @param E Company to manage
 */
void exit_menu(Empresa &E) {
	sys_clear();

	main_header("TENNIS COURT MANAGEMENT");

	header(" EXIT ");

	if (choice_input(" Would you like to save changes? (yes/no) ")) {
		E.save_file();
	}

	sys_clear();
}

/**
 * @addtogroup menu
 * Initializes the company as a new one
 * @param E Company to manage
 */
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

/**
 * @addtogroup menu
 * Imports the company from a file
 * @param E Company to manage
 */
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