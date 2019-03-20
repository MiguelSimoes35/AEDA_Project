/*
 * (c) 2018 Griné, Matos, and Simões
 * This software is provided under the MIT License.
 * To obtain a copy of this license, please read the file LICENSE at the root of the repository, or visit
 * https://opensource.org/licenses/MIT
 */

#include <iostream>
#include "menu.h"
#include "menu_functions.h"
#define LOCALE_PT
using namespace std;

int main() {

	string title = "TENNIS COURT MANAGEMENT";

	system("title   TENNIS COURT MANAGEMENT");

	start_menu();

	menu_exit();

	return 0;
}
