#ifndef MENU_FUNCTIONS_H
#define MENU_FUNCTIONS_H

#include <windows.h>
#include <iostream>
#include <string>
#include "empresa.h"

using namespace std;

/**
* Sets the Color of the console Text
*
* @param    color              Unsigned integer code of the desired color
*/
void setcolor(unsigned int color);

/**
* Sets the Color of the console Text and its background
* Background color it's only possible to change from black to gray and back
*
* @param   color               Unsigned integer code of the desired text color
* @param   background_color    Unsigned integer code correspondent to any color
*/
void setcolor(unsigned int color, unsigned int background_color);

/**
* Gets the width of the console and makes a line all the way across it with a certain character
*
* @param   lineChar            Character you want to write across the console
*/
void lineAcrossConsole(char lineChar);

/**
* Writes a certain word in the center of the console
*
* @param   title               String to be written centered in the console
*/
void centerWord(string title);

/**
* Clears the console screen from a certain point forward
*
* @param   coordScreen         Coordinates from where you want to begin erasing the screen
*/
void clrscr(COORD coordScreen);

/**
* Gets the coordinates of the current position of the cursor in the console
*
* @param   hConsoleOutput      Handle for the Console
*
* @return  COORD               Returns the position of the cursor in the console
*/
COORD GetConsoleCursorPosition(HANDLE hConsoleOutput);


void header(string header);

void header_date(string header, string date);

void main_header(string title);

int option_input(string question, int inferiorLimit, int superiorLimit);

bool choice_input(string question);

string name_input(string question);

string string_input(string question);

id_t id_input(string question);

size_t capacity_input(string question);

int days_input(string question);

string get_filename(string question, bool file);

Date get_date();

Period get_period();

void sys_pause();

void sys_clear();


/**
* @brief Given the path and file_name it checks the folder of the given path if
* there is a file of the same name, return true if there is, false otherwise.
*
* @param dir_path		Path of the folder that will be checked
* @param file_name		Name of the file that will be checked if it exists
*
* @return true			The path folder has a file with the same name of the given string
* @return false			The path folder doesn't have a file with the same name of the given string
*/
bool file_exists(const fs::path & dir_path, const string file_name);

class MenuOption {
private:
	string label;
	void(*function)(Empresa &);
public:
	MenuOption(string label, void(*function)(Empresa &)) : label(move(label)) { this->function = function; }
	string get_label() { return label; }
	void execute(Empresa &E) { function(E); }
};

void print_option(int number, const string &label);

void menu_exit();

class OptionMenu {
private:
	vector<MenuOption> options;
	string header;
	string back_option;
	bool initial;
public:
	OptionMenu(vector<MenuOption> options, string header, string back_option = "Back", bool initial = false):
		options(move(options)), header(move(header)), back_option(move(back_option)) { this->initial = initial; }
	void run(Empresa &E);
};

bool ui_get_user_name(Empresa &E, string &name);

bool ui_get_teacher_name(Empresa &E, string &name);

bool ui_get_technician_id(Empresa &E, id_t &id);

bool ui_find_class(Empresa &E, id_t id);

bool ui_find_use(Empresa &E, id_t id);

#endif//MENU_FUNCTIONS_H

