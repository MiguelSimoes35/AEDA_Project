#include "menu_functions.h"

using namespace std;

//=======================================================================================================================//

void setcolor(unsigned int color)
{
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hcon, color);
}

//=======================================================================================================================//

void setcolor(unsigned int color, unsigned int background_color)
{
	// Only changes to and from black to gray

	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	// 0 = BLACK
	if (background_color == 0)
		SetConsoleTextAttribute(hCon, color);
	else
		SetConsoleTextAttribute(hCon, color | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
}

//=======================================================================================================================//

void lineAcrossConsole(char lineChar)
{

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int columns;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;

	for (int i = 0; i < columns - 1; i++)
	{
		cout << lineChar;
	}

	cout << endl;
}

//=======================================================================================================================//

void centerWord(string title)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int columns, space;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;

	space = (columns - title.size()) / 2;

	for (int i = 0; i < space; i++)
	{
		cout << " ";
	}

	cout << title.c_str() << endl;
}

//=======================================================================================================================//

void clrscr(COORD coordScreen)
{
	//COORD coordScreen = { 0, 0 }; // upper left corner
	DWORD cCharsWritten;
	DWORD dwConSize;
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hCon, &csbi);
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
	// fill with spaces
	FillConsoleOutputCharacter(hCon, TEXT(' '), dwConSize, coordScreen, &cCharsWritten);
	GetConsoleScreenBufferInfo(hCon, &csbi);
	FillConsoleOutputAttribute(hCon, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
	// cursor to upper left corner
	SetConsoleCursorPosition(hCon, coordScreen);
}

//=======================================================================================================================//

COORD GetConsoleCursorPosition(HANDLE hConsoleOutput)
{
	CONSOLE_SCREEN_BUFFER_INFO cbsi;
	if (GetConsoleScreenBufferInfo(hConsoleOutput, &cbsi))
	{
		return cbsi.dwCursorPosition;
	}
	else
	{
		// The function failed. Call GetLastError() for details.
		COORD invalid = { 0, 0 };
		return invalid;
	}
}

//=======================================================================================================================//

void header(string header)
{
	cout << endl;
	setcolor(2);
	lineAcrossConsole('-');
	setcolor(14);
	cout << " " << header;
	cout << endl;
	setcolor(2);
	lineAcrossConsole('-');
	cout << endl;
	setcolor(15);
}

//=======================================================================================================================//

void header_date(string header, string date)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int columns;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	columns = csbi.srWindow.Right - csbi.srWindow.Left - 16 - header.size();

	cout << endl;
	setcolor(2);
	lineAcrossConsole('-');
	setcolor(14);
	cout << " " << header;
	for (int i = 0; i < columns - 1; i++)
	{
		cout << " ";
	}
	cout << "Date: " << setw(10) << date;
	cout << endl;
	setcolor(2);
	lineAcrossConsole('-');
	cout << endl;
	setcolor(15);
}

//=======================================================================================================================//

void main_header(string title) {
	setcolor(2);
	lineAcrossConsole('+');
	cout << endl;
	setcolor(14);
	centerWord(title);
	cout << endl;
	setcolor(2);
	lineAcrossConsole('+');
	cout << endl;

	setcolor(15);
}

//=======================================================================================================================//

int option_input(string question, int inferiorLimit, int superiorLimit)
{
	string option;
	bool ValidInput = false;
	int option_number;

	cout << question;

	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD currentPos = GetConsoleCursorPosition(hCon);

	while (!ValidInput)
	{
		cin.clear();

		bool ErrorFlag = false;

		getline(cin, option);


		if (cin.eof())
		{
			cin.clear();
		}
		if (cin.fail())
		{
			cin.clear();
			cin.ignore((numeric_limits<streamsize>::max)(), '\n');
			ErrorFlag = true;
		}
		if (option.length() > 1 || option == "")
		{
			ErrorFlag = true;
		}
		else
		{
			option_number = option.at(0) - '0';

			if (!ErrorFlag && !(option_number >= inferiorLimit && option_number <= superiorLimit))
			{
				ErrorFlag = true;
			}
		}

		ValidInput = !ErrorFlag;

		if (ErrorFlag)
		{

			clrscr(currentPos);
		}

	}


	return option_number;
}

//=======================================================================================================================//

bool choice_input(string question) {
	string choice;
	bool ValidInput = false;

	cout << question;

	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD currentPos = GetConsoleCursorPosition(hCon);

	while (!ValidInput)
	{
		cin.clear();

		bool ErrorFlag = false;

		getline(cin, choice);

		for (size_t i = 0; i < choice.size(); i++)
		{
			if (isalpha(choice.at(i)))
			{
				choice.at(i) = tolower(choice.at(i));
			}
			else {
				choice.erase(choice.begin() + i);
			}
		}

		if (cin.eof())
		{
			cin.clear();
		}
		if (cin.fail())
		{
			cin.clear();
			cin.ignore((numeric_limits<streamsize>::max)(), '\n');
			ErrorFlag = true;
		}

		if (choice == "yes") return true;
		else if (choice == "no") return false;
		else ErrorFlag = true;

		ValidInput = !ErrorFlag;

		if (ErrorFlag)
		{

			clrscr(currentPos);
		}

	}
}

//=======================================================================================================================//

string name_input(string question) {
	string name;

	bool ValidInput = false;

	cout << question;

	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD currentPos = GetConsoleCursorPosition(hCon);

	while (!ValidInput)
	{
		cin.clear();

		bool ErrorFlag = false;

		getline(cin, name);

		if (cin.eof())
		{
			cin.clear();
		}

		if (cin.fail())
		{
			cin.clear();
			cin.ignore((numeric_limits<streamsize>::max)(), '\n');
			ErrorFlag = true;
		}

		if (name.length() < 1 || name == "")
		{
			ErrorFlag = true;
		}
		else
		{
			for (size_t i = 0; i < name.length(); i++) {
				if (!isalpha(name.at(i)) && name.at(i) != ' ') {
					ErrorFlag = true;
					break;
				}
			}
		}

		ValidInput = !ErrorFlag;

		if (ErrorFlag)
		{
			clrscr(currentPos);
		}

	}

	return name;
}

//=======================================================================================================================//

id_t id_input(string question) {
	string id;

	bool ValidInput = false;

	cout << question;

	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD currentPos = GetConsoleCursorPosition(hCon);

	while (!ValidInput)
	{
		cin.clear();

		bool ErrorFlag = false;

		getline(cin, id);

		if (cin.eof())
		{
			cin.clear();
		}

		if (cin.fail())
		{
			cin.clear();
			cin.ignore((numeric_limits<streamsize>::max)(), '\n');
			ErrorFlag = true;
		}

		if (id.length() < 1 || id == "")
		{
			ErrorFlag = true;
		}
		else
		{
			for (size_t i = 0; i < id.length(); i++) {
				if (!isdigit(id.at(i))) {
					ErrorFlag = true;
					break;
				}
			}
		}

		if (stoul(id) == 0) {
			ErrorFlag = true;
		}

		ValidInput = !ErrorFlag;

		if (ErrorFlag)
		{
			clrscr(currentPos);
		}

	}

	return stoul(id);
}

//=======================================================================================================================//

size_t capacity_input(string question) {
	string input;
	int capacity;

	bool ValidInput = false;

	cout << question;

	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD currentPos = GetConsoleCursorPosition(hCon);

	while (!ValidInput)
	{
		cin.clear();

		bool ErrorFlag = false;

		getline(cin, input);

		if (cin.eof())
		{
			cin.clear();
		}

		if (cin.fail())
		{
			cin.clear();
			cin.ignore((numeric_limits<streamsize>::max)(), '\n');
			ErrorFlag = true;
		}

		if (input.length() < 1 || input == "")
		{
			ErrorFlag = true;
		}
		else
		{
			for (size_t i = 0; i < input.length(); i++) {
				if (!isdigit(input.at(i))) {
					ErrorFlag = true;
					break;
				}
			}

			if (!ErrorFlag) {
				capacity = stoi(input);
				if (capacity % 2 != 0 || capacity < 0) {
					ErrorFlag = true;
				}
			}
		}

		ValidInput = !ErrorFlag;

		if (ErrorFlag)
		{
			clrscr(currentPos);
		}

	}

	return capacity;
}

//=======================================================================================================================//

string get_filename(string question, bool file) {
	string name;

	bool ValidInput = false;

	cout << question;

	fs::path initial = fs::current_path();

	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD currentPos = GetConsoleCursorPosition(hCon);

	while (!ValidInput)
	{
		cin.clear();

		bool ErrorFlag = false;

		getline(cin, name);


		if (cin.eof())
		{
			cin.clear();
		}

		if (cin.fail())
		{
			cin.clear();
			cin.ignore((numeric_limits<streamsize>::max)(), '\n');
			ErrorFlag = true;
		}

		if (name.length() < 1 || name == "")
		{
			ErrorFlag = true;
		}
		else
		{
			name = name + ".txt";

			if (file) {

				if (file_exists(initial, name)) {
					return name;
				}
				else {
					ErrorFlag = true;
				}
			}
			else {
				if (file_exists(initial, name)) {
					ErrorFlag = true;

				}
				else {
					return name;
				}
			}
		}

		ValidInput = !ErrorFlag;

		if (ErrorFlag)
		{

			clrscr(currentPos);
		}

	}

}

//=======================================================================================================================//

Date get_date() {
	string input;
	string day, month, year;
	int d, m, y;
	bool got_day, got_month, got_year;

	bool ValidInput = false;

	cout << " Insert the date (day/month/year): ";

	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD currentPos = GetConsoleCursorPosition(hCon);

	while (!ValidInput)
	{
		cin.clear();

		bool ErrorFlag = false;

		getline(cin, input);

		got_day = false;
		got_month = false;
		got_year = false;

		day = "";
		month = "";
		year = "";

		
		for (size_t i = 0; i < input.size(); i++) {
			if (got_day && got_month) {
				got_year = true; // Insures that there is some character after the last '/'
				if (input.at(i) >= '0' && input.at(i) <= '9')
					year = year + input.at(i);
			}
			else if (!got_month && got_day) {
				if (input.at(i) >= '0' && input.at(i) <= '9')
					month = month + input.at(i);
				else if (input.at(i) == '/' && input.at(i-1) != '/') // Insures that there is some character between the '/'
					got_month = true;
			}
			else if (!got_month && !got_day) {
				if (input.at(i) >= '0' && input.at(i) <= '9')
					day = day + input.at(i);
				else if (input.at(i) == '/' && i != 0) // Insures that there is some character before the fisrt '/'
					got_day = true;
			}
		}



		if (cin.eof())
		{
			cin.clear();
		}

		if (cin.fail())
		{
			cin.clear();
			cin.ignore((numeric_limits<streamsize>::max)(), '\n');
			ErrorFlag = true;
		}

		// Converts strings of day, month and year to integers

		if (got_day && got_month && !day.empty() && !month.empty() && !year.empty()) {
			d = stoi(day);
			m = stoi(month);
			y = stoi(year);
		}
		else {
			d = -1;
			m = -1;
			y = -1;
		}

		// Checks if date is valid
		try {
			Date date(y, m, d);
			return date;
		}
		catch (...) {
			ErrorFlag = true;
		}

		ValidInput = !ErrorFlag;

		if (ErrorFlag)
		{
			clrscr(currentPos);
		}

	}

}

//=======================================================================================================================//

Period get_period() {
	string input;
	string minutes, hour, blocks;
	int m, h, b;
	bool got_minutes, got_hour;

	bool ValidInput = false;

	Date date = get_date();

	cout << endl << " Insert the time (hour:minutes): ";

	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD currentPos = GetConsoleCursorPosition(hCon);

	while (!ValidInput)
	{
		cin.clear();

		bool ErrorFlag = false;

		getline(cin, input);

		got_hour = false;
		got_minutes = false;

		hour = "";
		minutes = "";


		for (size_t i = 0; i < input.size(); i++) {
			if (got_hour) {
				got_minutes = true; // Insures that there is a character after the ':'
				if (input.at(i) >= '0' && input.at(i) <= '9')
					minutes = minutes + input.at(i);
			}
			else if (!got_hour) {
				if (input.at(i) >= '0' && input.at(i) <= '9')
					hour = hour + input.at(i);
				else if (input.at(i) == ':' && i != 0) // Insures that there is some character before the ':'
					got_hour = true;
			}
		}

		if (cin.eof())
		{
			cin.clear();
		}

		if (cin.fail())
		{
			cin.clear();
			cin.ignore((numeric_limits<streamsize>::max)(), '\n');
			ErrorFlag = true;
		}

		// Converts strings of minutes and days to integers

		if (got_minutes && got_hour && !hour.empty() && !minutes.empty()) {
			m = stoi(minutes);
			h = stoi(hour);
		}
		else {
			m = -1;
			h = -1;
		}

		// Checks if time is valid

		if (h < 0 || h > 23 || !(m == 0 || m == 30))
		{
			ErrorFlag = true;
		}

		ValidInput = !ErrorFlag;

		if (ErrorFlag)
		{
			clrscr(currentPos);
		}

	}

	cout << endl << " Duration in blocks (blocks = 30min): ";

	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	currentPos = GetConsoleCursorPosition(hCon);

	while (!ValidInput)
	{
		cin.clear();

		bool ErrorFlag = false;

		getline(cin, blocks);

		if (cin.eof())
		{
			cin.clear();
		}

		if (cin.fail())
		{
			cin.clear();
			cin.ignore((numeric_limits<streamsize>::max)(), '\n');
			ErrorFlag = true;
		}

		if (blocks.length() < 1 || blocks == "")
		{
			ErrorFlag = true;
		}
		else
		{
			for (size_t i = 0; i < blocks.length(); i++) {
				if (!isdigit(blocks.at(i))) {
					ErrorFlag = true;
					break;
				}
			}

			if (!ErrorFlag) {
				b = stoi(blocks);

				if (b < 1 || b > 4) {
					ErrorFlag = true;
				}
			}
		}

		ValidInput = !ErrorFlag;

		if (ErrorFlag)
		{
			clrscr(currentPos);
		}

	}

	return Period(date, h, m, b);

}

//=======================================================================================================================//

bool file_exists(const fs::path & dir_path, const string file_name) {
#ifdef FILESYSTEM_ON
	if (!exists(dir_path)) return false;
	fs::directory_iterator end_it;

	for (fs::directory_iterator it(dir_path); it != end_it; it++)
	{
		if (it->path().filename() == file_name)
		{
			return true;
		}
	}
#endif
	return false;
}

void sys_pause() {
	system("pause");
}

void sys_clear() {
	system("cls");
}

void print_option(int number, const string &label) {
	setcolor(10); cout << " [";
	setcolor(14); cout << number;
	setcolor(10); cout << "]";
	setcolor(15); cout << " - " << label << endl << endl;
}

void OptionMenu::run(Empresa &E) {
	sys_clear();

	main_header("TENNIS COURT MANAGEMENT");

	if(!initial) header_date(header, E.get_date());

	for (size_t i = 0; i < options.size(); i++) {
		print_option(i + 1, options[i].get_label());
	}
	print_option(0, back_option);

	int option = option_input(" Option: ", 0, options.size());

	sys_clear();

	main_header("TENNIS COURT MANAGEMENT");

	if (!initial) header_date(header, E.get_date());

	if (option != 0) {
		options[option - 1].execute(E);
		if (!initial) run(E);
	}
}

bool ui_get_user_id(Empresa &E, id_t &id_user) {
	bool exists = false;
	while (!exists) {
		try {
			string name = name_input(" What's the name of the user? ");
			cout << endl;

			id_user = E.find_user(name);
			exists = true;
		}
		catch (InexistentObject e) {
			cout << " There is no user with that name." << endl;
			return false;
		}
		catch (SameName e) {
			cout << " There are multiple users with that name." << endl;

			if (choice_input(" We will need the User's ID find them. Do you want a list of all users to get it?")) {
				cout << endl;

				E.list_utentes();

				cout << endl;

				id_user = id_input(" Insert the ID of the user: ");
				cout << endl;


				exists = true;
			}
			else if (choice_input(" Do want to insert the ID?")) {

				id_user = id_input(" Insert the ID of the user: ");

				exists = true;

			}
			else {

				cout << " Unable to find the user." << endl;
				return false;
			}
		}
	}
	return true;
}

void menu_exit() {
	cout << endl;
	sys_pause();
}

