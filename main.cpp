#include <ios>
#include <iostream>
#include <iterator>
#include <string>

using namespace std;

const int MAX_ORDER_COUNT = 20;
const string RES_NAME = "Du skoniai";
const string EURO_SIGN = "€";
const string DELIM = " | ";

struct MenuItem_T {
	string menuItem;
	float itemPrice = 0;
	int amount = 1; // porciju skaicius
};

const MenuItem_T MENU_LIST[] = {{"Kiaušiniene", 1.45},
                                {"Kiaulienos šoninė su keptu kiaušiniu", 2.45},
                                {"Keksiukas su vyšnia", 0.99},
                                {"Prancūziškas skrebutis", 1.99},
                                {"Vaisių salotos", 2.49},
                                {"Pusryčių dribsniai", 0.69},
                                {"Kava", 0.50},
                                {"Arbata", 0.75}};

const int MENU_SIZE = size(MENU_LIST);

void showMenu() {
	cout << "\n----- Mūsų meniu -----\n";
	for (int i = 0; i < MENU_SIZE; i++) {
		cout << i + 1 << ". " << MENU_LIST[i].menuItem << DELIM << MENU_LIST[i].itemPrice << ' ' << EURO_SIGN << '\n';
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
// returns --> success
bool getData(MenuItem_T orderList[], int &lastOrderIndex) {
	int order = 0;
	int count = 1;
	static int num = 1;

	// cout << "\nPasirinkite patiekalą ir įveskite porcijų skaičių.\n";
	cout << "Jūsų pasirinkimas nr. " << num << " (patiekalas, porcijos): ";
	cin >> order >> count;

	if (order >= 1 && order <= MENU_SIZE) {
		order--;

		// strukturos inicializavimas
		orderList[lastOrderIndex] = MenuItem_T{MENU_LIST[order].menuItem, MENU_LIST[order].itemPrice, count};

		// orderList[lastOrderIndex].menuItem = MENU_LIST[order].menuItem;
		// orderList[lastOrderIndex].itemPrice = MENU_LIST[order].itemPrice;
		// orderList[lastOrderIndex].amount = count;

		lastOrderIndex++;
		num++;

		return true;
	}

	return false;
}

int main() {
	cout << "\nSveiki atvykę i restoraną \"" << RES_NAME << "\"\n";

	MenuItem_T order_list[MAX_ORDER_COUNT];
	int lastOrderListItem = 0;

	// uzsakymu saraso inicializacija
	// for (int i = 0; i < MAX_ORDER_COUNT; i++) {
	// 	order_list[i] = MenuItem_T{};
	// }

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
				showMenu();
				while (orderSuccess) {
					orderSuccess = getData(order_list, lastOrderListItem);
				}
				break;
			case 3:
				cout << "empty? " << boolalpha << empty(order_list) << '\n';
				cout << "\nJūsų užsakymas:\n";
				for (int i = 0; i < MAX_ORDER_COUNT; i++) {
					MenuItem_T item = order_list[i];
					if (item.menuItem.empty()) {
						break;
					}
					cout << item.menuItem << DELIM << item.itemPrice << ' ' << EURO_SIGN << DELIM << 'x' << item.amount
					     << '\n';
				}
				break;
			case 0:
				cout << "\nLauksime sugrįžtant..!\n\n";
				break;
			default:
				cout << "Neteisingas pasirinkimas.\n";
				break;
		}
	}

	return 0;
}
