#include <iostream>
#include "menu.h"
#define LOCALE_PT
using namespace std;

int main() {

	string title = "TENNIS COURT MANAGEMENT";

	system("title   TENNIS COURT MANAGEMENT");

	main_header(title);

	start_menu();

	cout << endl;

	system("pause");

	return 0;
}
