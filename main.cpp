#include <iostream>
#include <string>

using namespace std;

const int MAX_ORDER_LIST_SIZE = 20;
const string RES_NAME = "Du skoniai";

struct MenuItemType {
	string menuItem;
	float menuPrice{};
};

const MenuItemType MENU_LIST[] = {
    {"Kiaušiniene", 1.45},
    {"Kiaulienos šoninė su keptu kiaušiniu", 2.45},
    {"Keksiukas su vyšnia", 0.99},
    {"Prancūziškas skrebutis", 1.99},
    {"Vaisių salotos", 2.49},
    {"Pusryčių dribsniai", 0.69},
    {"Kava", 0.50},
    {"Arbata", 0.75}};

const int MENU_SIZE = size(MENU_LIST);

struct OrderItemType {
	string menuItem;
	float menuPrice{};
	float amount{};
};

void showMenu() {
	cout << "\n----- Mūsų meniu -----\n";

	for (int i = 0; i < MENU_SIZE; i++) {
		// cout << setw(2) << i + 1 << setw(40) << MENU_LIST[i].menuItem <<
		// setw(5) << MENU_LIST[i].menuPrice << '\n';
		cout << i + 1 << ". " << MENU_LIST[i].menuItem << " - "
		     << MENU_LIST[i].menuPrice << " €\n";
	}
}

int choicePrompt() {
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

int main() {
	cout << "\nSveiki atvykę i restoraną \"" << RES_NAME << "\"\n";

	OrderItemType order_list[MAX_ORDER_LIST_SIZE];
	int choice = -1;

	while (choice != 0) {
		choice = choicePrompt();
		switch (choice) {
			case 1:
				showMenu();
				break;
			case 2:
				break;
			case 3:
				break;
			case 0:
				cout << "\nLauksime sugrįžtant..!\n\n";
				break;
			default:
				cout << "[info] Neteisingas pasirinkimas!\n";
				break;
		}
	}

	return 0;
}
