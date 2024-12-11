#include <fstream>
#include <iomanip>
#include <ios>
#include <iostream>
#include <iterator>
#include <string>
#include "utf8.hpp"

using namespace std;

const int MAX_ORDER_COUNT = 20;
const string RES_NAME = "Du skoniai";
const string EURO_SIGN = " €";
const double PVM = 0.21;

struct MenuItem_T {
	string menuItem;
	double itemPrice = 0;
	int amount = 1; // porciju skaicius
};

const MenuItem_T MENU[] = {{"Kiaušiniene", 1.45},
                           {"Kiaulienos šoninė su keptu kiaušiniu", 2.45},
                           {"Keksiukas su vyšnia", 0.99},
                           {"Prancūziškas skrebutis", 1.99},
                           {"Vaisių salotos", 2.49},
                           {"Pusryčių dribsniai", 0.69},
                           {"Kava", 0.50},
                           {"Arbata", 0.75}};

const int MENU_SIZE = size(MENU);

string doubleToStr(double value) {
	ostringstream stream;
	stream << fixed << setprecision(2) << value;
	return stream.str();
}

string repeatChar(char symbol, int count) {
	string result;
	for (int i = 0; i < count; i++) {
		result += symbol;
	}
	return result;
}

void showMenu() {
	cout << "\n------------------ Mūsų meniu ------------------\n\n";

	cout << pad_utf8("Patiekalas", 43) << pad_utf8("Kaina", 5) << '\n';
	cout << pad_utf8(repeatChar('-', 10), 43) << repeatChar('-', 5) << '\n';

	for (int i = 0; i < MENU_SIZE; i++) {
		MenuItem_T item = MENU[i];
		string price = doubleToStr(item.itemPrice);
		cout << i + 1 << ". " << pad_utf8(MENU[i].menuItem, 40) << pad_utf8(price, 4) << EURO_SIGN << '\n';
	}
}

int getChoice() {
	int choice = 0;

	cout << "\n----- " << RES_NAME << " -----\n";
	cout << "1. Pamatyti meniu\n";
	cout << "2. Užsakyti patiekalus\n";
	cout << "3. Spausdinti sąskaitą\n";
	cout << "0. Išeiti\n";

	cout << "\nPasirinkite, ką norite daryti: ";
	cin >> choice;

	return choice;
}

// patiekalu uzsakymas
bool getData(MenuItem_T menuList[], int &lastOrderIndex) {
	int order = 0;
	int count = 1;

	cout << "Jūsų pasirinkimas (patiekalas, porcijos): ";

	cin >> order;
	if (order == 0) {
		return false;
	}

	cin >> count;
	if (count < 1) {
		cout << "Įvestas klaidingas porcijų skaičius.\n";
		return false;
	}

	if (order >= 1 && order <= MENU_SIZE) {
		order--;

		// strukturos inicializavimas
		menuList[lastOrderIndex] = MenuItem_T{MENU[order].menuItem, MENU[order].itemPrice, count};

		lastOrderIndex++;
		return true;
	}

	return false;
}

void printCheck(MenuItem_T menuList[]) {
	string bill;

	double sum = 0;
	double pvm = 0;
	double finalSum = 0;

	bill += "\n-------------------------------- Jūsų užsakymas --------------------------------\n\n";
	bill += pad_utf8("Patiekalas", 40) + pad_utf8("Vienos porcijos kaina", 25) + "Užsakyta porcijų\n";
	bill += pad_utf8(repeatChar('-', 10), 40) + pad_utf8(repeatChar('-', 21), 25) + repeatChar('-', 16) + '\n';

	for (int i = 0; i < MAX_ORDER_COUNT; i++) {
		MenuItem_T item = menuList[i];

		if (item.menuItem.empty()) {
			break;
		}

		string price = doubleToStr(item.itemPrice) + EURO_SIGN;
		string amount = to_string(item.amount) + " porcija(-os)";

		bill += pad_utf8(item.menuItem, 40) + pad_utf8(price, 25) + amount + '\n';

		sum += (item.itemPrice * item.amount);
	}

	pvm = sum * PVM;
	finalSum = sum + pvm;

	string sum_str = doubleToStr(sum) + EURO_SIGN;
	string pvm_str = doubleToStr(pvm) + EURO_SIGN;
	string finalSum_str = doubleToStr(finalSum) + EURO_SIGN;

	bill += "\n------------ Sąskaita ------------\n";
	bill += pad_utf8("Kaina be PVM", 27) + sum_str + '\n';
	bill += pad_utf8("PVM suma", 27) + pvm_str + '\n';
	bill += pad_utf8("Galutinė kaina (su PVM)", 27) + finalSum_str + '\n';

	// saskaitos irasymas i faila
	ofstream billFile("saskaita.txt");
	if (billFile.is_open()) {
		billFile << bill;
		billFile.close();
	} else {
		cerr << "Error: Could not open file for writing.\n";
	}

	// saskaitos isvedimas i konsole
	cout << bill;
}

int main() {
	cout << "\nSveiki atvykę i restoraną \"" << RES_NAME << "\"\n";

	MenuItem_T menuList[MAX_ORDER_COUNT];
	int lastOrderListItem = 0;

	int actionChoice = -1;
	bool orderSuccess = true;

	while (actionChoice != 0) {
		orderSuccess = true; // reset
		actionChoice = getChoice();
		switch (actionChoice) {
			case 1:
				showMenu();
				break;
			case 2:
				cout << '\n';
				while (orderSuccess) {
					orderSuccess = getData(menuList, lastOrderListItem);
				}
				break;
			case 3:
				printCheck(menuList);
				break;
			case 0:
				cout << "\nLauksime sugrįžtant!\n\n";
				break;
			default:
				cout << "Neteisingas pasirinkimas.\n";
				break;
		}
	}

	return 0;
}
