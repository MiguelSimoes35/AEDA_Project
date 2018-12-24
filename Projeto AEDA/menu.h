#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <iomanip>
#include "empresa.h"
#include "menu_functions.h"

//======================================================================================================================================================//

/**
 * @brief It shows a menu with options to manage the users:
 * edit_users(), expenses(), classes()
 */
void user_menu(Empresa &E);

void search_user(Empresa& E);

void payments_menu(Empresa &E);

void print_user_report(Empresa &E);

void attend_class(Empresa &E);

void schedule_free_use(Empresa &E);

void print_bill(Empresa &E);

void pay_debt(Empresa& E);

//======================================================================================================================================================//

/**
 * @brief It shows a menu with options to manage the teachers
 */
void teacher_menu(Empresa &E);

void search_teacher(Empresa &E);

/**
 * @brief It shows a menu with options to manage the company
 */

 //======================================================================================================================================================//

void company_menu(Empresa &E);

void manage_users(Empresa &E);

void manage_teachers(Empresa &E);

void manage_courts(Empresa &E);

void manage_classes(Empresa &E);

void manage_uses(Empresa &E);

//======================================================================================================================================================//

void add_user(Empresa &E);

void remove_user(Empresa &E);

void update_gold_card(Empresa &E);

void search_user(Empresa &E);

//======================================================================================================================================================//

void add_teacher(Empresa &E);

void remove_teacher(Empresa &E);

void search_teacher(Empresa &E);

//======================================================================================================================================================//

void add_court(Empresa &E);

void remove_court(Empresa &E);

void change_court_capacity(Empresa &E);

//======================================================================================================================================================//

void search_class(Empresa &E);

void cancel_class(Empresa &E);

void change_teacher(Empresa &E);

void change_court(Empresa &E);

//======================================================================================================================================================//

void search_use(Empresa &E);

void cancel_use(Empresa &E);

//======================================================================================================================================================//

void schedules_menu(Empresa &E);

//======================================================================================================================================================//

/**
 * @brief It shows a menu with options to choose between
 * manage the users, the teachers, the courts, to save the company
 * and to exit the program
 */
void main_menu(Empresa &E);


// Main Menu

/**
 * @brief It shows a menu with options to create a new company,
 * to choose a company already created and to exit the program
 */
void start_menu();
#endif
