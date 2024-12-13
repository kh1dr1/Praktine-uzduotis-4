#include <fstream>
#include <iomanip>
#include <ios>
#include <iostream>
#include <iterator>
#include <string>

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

// Function to calculate the visual width of a UTF-8 string
size_t utf8_visual_width(const string &str) {
	size_t width = 0;
	for (size_t i = 0; i < str.size();) {
		unsigned char symbol = str[i];
		if ((symbol & 0x80) == 0) { // 1-byte character (ASCII)
			width += 1;
			i += 1;
		} else if ((symbol & 0xE0) == 0xC0) { // 2-byte character
			width += 1;
			i += 2;
		} else if ((symbol & 0xF0) == 0xE0) { // 3-byte character
			width += 1;
			i += 3;
		} else if ((symbol & 0xF8) == 0xF0) { // 4-byte character
			width += 2; // Wide character
			i += 4;
		} else {
			throw runtime_error("Invalid UTF-8 sequence");
		}
	}
	return width;
}

// Function to pad a UTF-8 string to a specific width
string pad_utf8(const string &str, size_t width) {
	size_t visual_width = utf8_visual_width(str);
	if (visual_width >= width) {
		return str;
	}

	// Add spaces to reach the desired width
	return str + string(width - visual_width, ' ');
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

	bill += "\n----------------------------- Jūsų užsakymas -----------------------------\n\n";
	bill += pad_utf8("Patiekalas", 40) + pad_utf8("Porcijos kaina", 18) + "Užsakyta porcijų\n";
	bill += pad_utf8(repeatChar('-', 10), 40) + pad_utf8(repeatChar('-', 14), 18) + repeatChar('-', 16) + '\n';

	for (int i = 0; i < MAX_ORDER_COUNT; i++) {
		MenuItem_T item = menuList[i];

		if (item.menuItem.empty()) {
			break;
		}

		string price = doubleToStr(item.itemPrice) + EURO_SIGN;
		string amount = to_string(item.amount) + " porcija(-os)";

		bill += pad_utf8(item.menuItem, 40) + pad_utf8(price, 18) + amount + '\n';

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
				cout << "\n(Įveskite 0 kad išeitumėte iš užsakymo režimo)\n\n";
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
