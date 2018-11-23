#ifndef MENU_H
#define MENU_H

#include "timing.h"

/**
 * @brief It checks if the input was correct,
 * if not, cit cleans the buffer and return false, otherwise returns false
 *
 * @return true 	The input was correct
 * @return false 	The input was incorrect
 */
bool clean_input();

//Secondary Menu Functions

/**
 * @brief It shows a sub-menu with options about the classes
 * to manage the users
 */
void classes();

/**
 * @brief It shows a sub-menu with options about the expenses
 * to manage the users
 */
void expenses();

/**
 * @brief It shows a sub-menu with options to edit the users
 */
void edit_users();

/**
 * @brief It shows a menu with options to manage the users:
 * edit_users(), expenses(), classes()
 */
void manage_users();

/**
 * @brief It shows a menu with options to manage the teachers
 */
void manage_teachers();

/**
 * @brief It shows a menu with options to manage the courts
 */
void manage_courts();

/**
 * @brief It shows a menu with options to choose between
 * manage the users, the teachers, the courts, to save the company
 * and to exit the program
 */
void secondary_menu();

//Main Menu

/**
 * @brief It shows a menu with options to create a new company,
 * to choose a company already created and to exit the program
 */
void MENU();
#endif
