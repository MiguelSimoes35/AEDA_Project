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
