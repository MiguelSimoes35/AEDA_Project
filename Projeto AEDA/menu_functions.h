#ifndef MENU_FUNCTIONS_H
#define MENU_FUNCTIONS_H

#include <windows.h>
#include <iostream>
#include <string>
#include "empresa.h"

using namespace std;

/**
 * @defgroup menu_functions
 * Helper functions to implement the UI
 * @{
 */

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

/**
 * Prints out formatted sub-header for the UI
 * 
 *  @param header Text to display
 */
void header(string header);

/**
 * Prints out formatted sub-header for the UI, addicionally displaying a date
 * 
 * @param header Text to display
 * @param date Date to display
 */
void header_date(string header, string date);

/**
 * Prints out the formatted header for the UI
 * 
 * @param title Text to display in the title
 */
void main_header(string title);

/**
 * Allows the user to input a number corresponding to an option in a menu, within specified bounds
 * 
 * @param question Question to place before the prompt
 * @param inferiorLimit Lowest option number able to be input
 * @param superiorLimit Highest option number able to be input
 * @return The option that was input
 */
int option_input(string question, int inferiorLimit, int superiorLimit);

/**
 * Lets the user do a yes/no choice
 * 
 * @param question Question to place before the prompt
 * @return True if "yes" is input, false if "no" is input
 */
bool choice_input(string question);

/**
 * Lets the user input a name
 * 
 * @param question Question to place before the prompt
 * @return A string only composed of letters in the alphabet
 */
string name_input(string question);

/**
 * Lets the user input a string
 * 
 * @param question Question to place before the prompt
 * @return A non empty string
 */
string string_input(string question);

/**
 * Lets the user input an ID
 * 
 * @param question Question to place before the prompt
 * @return A positive integer
 */
id_t id_input(string question);

/**
 * Lets the user input a court capacity
 * 
 * @param question Question to place before the prompt
 * @return An even positive integer
 */
size_t capacity_input(string question);

/**
 * Lets the user input an ammount of days for repairs
 * 
 * @param question Question to place before the prompt
 * @return A positive integer
 */
int days_input(string question);

/**
 * Lets the user input a file name
 * 
 * @param question Question to place before the prompt
 * @param file True for reading mode, false for writing mode
 * @return An existing .txt file name for read mode, a free .txt file name for write mode
 */
string get_filename(string question, bool file);

/**
 * Lets the user input a date
 * 
 * @return Valid date
 */
Date get_date();

/**
 * Lets the user input a time period
 * 
 * @return Valid time period
 */
Period get_period();

/**
 * Pauses the application using the Windows API
 */
void sys_pause();

/**
 * Clears the screen using the Windows API
 */
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

/**
 * Implements a simple bean with a label and an action, to represent a Menu item
 */
class MenuOption {
private:
	string label; /// Label of the item
	void(*function)(Empresa &); /// Function to execute when selected
public:
	/**
	 * Constructor for a MenuOption object
	 * 
	 * @param label Label of the menu item
	 * @param function Function to execute when selected
	 */
	MenuOption(string label, void(*function)(Empresa &)) : label(move(label)) { this->function = function; }
	/**
	 * Returns option label
	 * @return Label
	 */
	string get_label() { return label; }
	/**
	 * Executes the correspondent UI function
	 * 
	 * @param E Company to manage
	 */
	void execute(Empresa &E) { function(E); }
};

/**
 * Prints a menu item
 * @param number Option number that corresponds to the item
 * @param label Label of the item
 */
void print_option(int number, const string &label);

/**
 * Introduces a line break and pauses the system, usually executed at the end of an operation
 */
void menu_exit();

/**
 * Class used to declaratively generate menus that associate labels and option numbers to certain actions
 */
class OptionMenu {
private:
	vector<MenuOption> options; /// Options that will be shown
	string header; /// Title of the menu
	string back_option; /// Label for the back option
	bool initial; /// If true, the menu will not appear again when returning from executing one of the menu items
public:
	/**
	 * Constructor for an OptionMenu object
	 * 
	 * @param options Options to be shown in the menu
	 * @param header Title of the menu
	 * @param back_option Label for the back option, default 'Back'
	 * @param initial If true the menu will not be shown after an option is executed, default false
	 */
	OptionMenu(vector<MenuOption> options, string header, string back_option = "Back", bool initial = false):
		options(move(options)), header(move(header)), back_option(move(back_option)) { this->initial = initial; }
	/**
	 * Generates and shows the menu
	 * @param E Company to manage
	 */
	void run(Empresa &E);
};

/**
 * Searches for an user in the company and stores their name in the parameter name
 * @param E Company to manage
 * @param name Variable in which the name will be stored
 * @return Whether the operation was successful
 */
bool ui_get_user_name(Empresa &E, string &name);

/**
 * Searches for a teacher in the company and stores their name in the parameter name
 * @param E Company to manage
 * @param name Variable in which the name will be stored
 * @return Whether the operation was successful
 */
bool ui_get_teacher_name(Empresa &E, string &name);

/**
 * Searches for a technician in the company and stores their ID in the parameter name
 * @param E Company to manage
 * @param name Variable in which the ID will be stored
 * @return Whether the operation was successful
 */
bool ui_get_technician_id(Empresa &E, id_t &id);

/**
 * Searches for a class in the company and stores their ID in the parameter name
 * @param E Company to manage
 * @param name Variable in which the ID will be stored
 * @return Whether the operation was successful
 */
bool ui_find_class(Empresa &E, id_t id);

/**
 * Searches for a use in the company and stores their ID in the parameter name
 * @param E Company to manage
 * @param name Variable in which the ID will be stored
 * @return Whether the operation was successful
 */
bool ui_find_use(Empresa &E, id_t id);

/**
 * @}
 */
#endif//MENU_FUNCTIONS_H
