#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <iomanip>
#include "empresa.h"
#include "menu_functions.h"

//======================================================================================================================================================//
/**
 * @defgroup menu
 * Implementation of the user interface
 * @{
 */


/**
 * @brief It shows a menu with options to manage the users:
 * edit_users(), expenses(), classes()
 */
void user_menu(Empresa &E);

/**
 * Operation: search for a user in the company
 * @param E Company to manage
 */
void search_user(Empresa& E);

/**
 * Shows a menu with payment options
 * @param E Company to manage
 */
void payments_menu(Empresa &E);

/**
 * Lists the users in the company
 * @param E Company to manage
 */
void list_users(Empresa &E);

/**
 * Prints a user's report
 * @param E Company to manage
 */
void print_user_report(Empresa &E);

/**
 * Schedules a class attendance
 * @param E Company to manage
 */
void attend_class(Empresa &E);

/**
 * Schedules a free use attendance
 * @param E Company to manage
 */
void schedule_free_use(Empresa &E);

/**
 * Prints a user's bill for the current month
 * @param E Company to manage
 */
void print_bill(Empresa &E);

/**
 * Liquidates all current debts of a user
 * @param E Company to manage
 */
void pay_debt(Empresa& E);

//======================================================================================================================================================//

/**
 * @brief It shows a menu with options to manage the teachers
 * @param E Company to manage
 */
void teacher_menu(Empresa &E);

/**
 * Lists the company's current and past teachers
 * @param E Company to manage
 */
void list_teachers(Empresa &E);

 //======================================================================================================================================================//

/**
 * @brief It shows a menu with options to manage the company
 * @param E Company to manage
 */
void company_menu(Empresa &E);

/**
 * Options for user management
 * @param E Company to manage
 */
void manage_users(Empresa &E);

/**
 * Options for teacher management
 * @param E Company to manage
 */
void manage_teachers(Empresa &E);

/**
 * Options for technician management
 * @param E Company to manage
 */
void manage_technicians(Empresa &E);

/**
 * Options for court management
 * @param E Company to manage
 */
void manage_courts(Empresa &E);

/**
 * Options for class management
 * @param E Company to manage
 */
void manage_classes(Empresa &E);

/**
 * Options for use management
 * @param E Company to manage
 */
void manage_uses(Empresa &E);

/**
 * Closes the day, incrementing the date and updating repairs
 * @param E Company to manage
 */
void end_day(Empresa &E);

//======================================================================================================================================================//

/**
 * Adds a new user to the company
 * @param E Company to manage
 */
void add_user(Empresa &E);

/**
 * Removes an user from the company
 * @param E Company to manage
 */
void remove_user(Empresa &E);

/**
 * Changes the gold card status of a user
 * @param E Company to manage
 */
void update_gold_card(Empresa &E);

//======================================================================================================================================================//

/**
 * Adds a teacher to the company
 * @param E Company to manage
 */
void add_teacher(Empresa &E);

/**
 * Marks a teacher as not employed
 * @param E Company to manage
 */
void remove_teacher(Empresa &E);

/**
 * Seachers for a teacher and displays their information
 * @param E Company to manage
 */
void search_teacher(Empresa &E);

//======================================================================================================================================================//

/**
 * Adds a court to the compnay
 * @param E Company to manage
 */
void add_court(Empresa &E);

/**
 * Removes a court from the company
 * @param E Company to manage
 */
void remove_court(Empresa &E);

/**
 * Changes the capacity of a court
 * @param E Company to manage
 */
void change_court_capacity(Empresa &E);

/**
 * Lists information on all courts managed by the company
 * @param E Company to manage
 */
void list_courts(Empresa &E);

//=======

/**
 * Adds a technician to the company
 * @param E Company to manage
 */
void add_technician(Empresa &E);

/**
 * Removes technician from the company
 * @param E Company to manage
 */
void remove_technician(Empresa &E);

/**
 * Assigns a repair job to the best fit technician
 * @param E Company to manage
 */
void assign_technician(Empresa &E);

/**
 * Lists the technicians in the company
 * @param E Company to manage
 */
void list_technicians(Empresa &E);



//======================================================================================================================================================//

/**
 * Schedules a new class
 * @param E Company to manage
 */
void schedule_class(Empresa &E);

/**
 * Searches for a class and information on it
 * @param E Company to manage
 */
void search_class(Empresa &E);

/**
 * Cancels a class
 * @param E Company to manage
 */
void cancel_class(Empresa &E);

/**
 * Changes the teacher giving the class
 * @param E Company to manage
 */
void change_teacher(Empresa &E);

/**
 * Changes the court where the class will be given
 * @param E Company to manage
 */
void change_court(Empresa &E);

/**
 * Lists classes to be given
 * @param E Company to manage
 */
void list_classes(Empresa &E);

//======================================================================================================================================================//

/**
 * Searches for a use and information on it
 */
void search_use(Empresa &E);

/**
 * Lists uses and info on them
 * @param E Company to manage
 */
void list_uses(Empresa &E);

/**
 * Cancels an use
 * @param E Company to manage
 */
void cancel_use(Empresa &E);

//======================================================================================================================================================//

/**
 * Options for displaying schedules
 * @param E Company to manage
 */
void schedules_menu(Empresa &E);

/**
 * Prints the schedule of a user
 * @param E Company to manage
 */
void print_user_schedule(Empresa &E);

/**
 * Prints the schedule of a teacher
 * @param E Company to manage
 */
void print_teacher_schedule(Empresa &E);

/**
 * Prints the schedule of a court
 * @param E Company to manage
 */
void print_court_schedule(Empresa &E);

/**
 * Prints a schedule of all courts for a certain day
 * @param E Company to manage
 */
void print_day_schedule(Empresa &E);

//======================================================================================================================================================//

/**
 * @brief It shows a menu with options to choose between
 * manage the users, the teachers, the courts, to save the company
 * and to exit the program
 * @param E Company to manage
 */
void main_menu(Empresa &E);


// Main Menu

/**
 * @brief It shows a menu with options to create a new company,
 * to choose a company already created and to exit the program
 */
void start_menu();

/** @} */
#endif/*MENU_H*/
