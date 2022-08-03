#include<iostream>
#include<fstream>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include<limits>
#include<ctype.h>



#define KEY_SPACE 32
#define KEY_x 120
#define KEY_X 88
#define KEY_0 48
#define KEY_1 49
#define KEY_2 50
#define KEY_3 51
#define KEY_4 52
#define KEY_5 53
#define KEY_6 54
#define KEY_7 55
#define KEY_8 56
#define KEY_9 57

using namespace std;

//Creating a class called Store

class Store {
private:
	int product_no;								//Product No	
	char product_name[20];			//Product Name
	double product_price;						//Price of the Product 
	double discount;							//Discount for the Product 
	int quantity;								//Quantity of the Product 

	//Dates
	int dd;
	int mm;
	int yy;

public:
	//Using default Constructor to initialize datamembers to default values
	Store() {
		product_no = 0;
		product_price = 0;
		discount = 0;
		quantity = 0;
	}
	//destructor
	~Store() {
		//delete discount;
	}

	//member function returns product name	
	char* getProduct_name() {
		return product_name;
	}
	//member function returns product id
	int getProduct_no() {
		return product_no;
	}

	//member function returns product price
	double getProduct_price() {
		return product_price;
	}

	//member function returns product quantity
	int getProduct_quantity() {
		return quantity;
	}

	//member function returns product discount
	double getProduct_discount() {
		return discount;
	}

	//member function to display product details
	void display_product() {
		
		cout << endl << "======================================================================" << endl;
		cout << endl << "Product Number   : " << product_no << endl;
		cout << endl << "Product Name     : " << product_name << endl;
		cout << endl << "Product Price    : " << product_price << endl;
		cout << endl << "Product Quantity : " << quantity << endl;
		cout << endl << "Date			  :" << dd << "/" << mm << "/" << yy << "/" << endl;
		cout << endl << "======================================================================" << endl;
	}

	//member function to add product details
	void add_products() {
		cout << endl << endl << "Enter Product id : ";
		cin >> product_no;
		while (cin.fail() || cin.peek() != '\n') {
			cin.clear();
			cin.ignore();
			cout << "You have entered wrong input!. Re-Enter : ";
			cin >> product_no;
		}
		cin.ignore();
		cout << "Name of the Product : ";cin >> product_name;
		cout << "Enter Price of the Product : ";
		cin >> product_price;
		while (cin.fail() || cin.peek() != '\n') {
			cin.clear();
			cin.ignore();
			cout << "You have entered wrong input!. Re-Enter : ";
			cin >> product_price;
		}
		cin.ignore();
		cout << "Enter the quantity of the product : ";
		cin >> quantity;
		while (cin.fail() || cin.peek() != '\n') {
			cin.clear();
			cin.ignore();
			cout << "You have entered wrong input!. Re-Enter : ";
			cin >> quantity;
		}
		cin.ignore();
		cout << "Enter the discount for the product : ";
		cin >> discount;
		cout << "Enter Date (DD/MM/YYYY) : ";
		while (inDates(dd, mm, yy));
	}

	int key() {
		char key = _getch();
		int value = key;
		while (value != KEY_0 && value != KEY_1 && value != KEY_2 && value != KEY_3 && value != KEY_4 && value != KEY_5 && value != KEY_6 && value != KEY_7 && value != KEY_8 && value != 9 && value != KEY_SPACE && value != KEY_X && value != KEY_x) {
			key = _getch();
			value = key;
		}
		if (value == KEY_0)
			return 0;
		if (value == KEY_1)
			return 1;
		if (value == KEY_2)
			return 2;
		if (value == KEY_3)
			return 3;
		if (value == KEY_4)
			return 4;
		if (value == KEY_5)
			return 5;
		if (value == KEY_6)
			return 6;
		if (value == KEY_7)
			return 7;
		if (value == KEY_8)
			return 8;
		if (value == KEY_9)
			return 9;
		if (value == KEY_SPACE)
			return 11;
		if (value == KEY_X || value == KEY_x)
			return 22;
	}

	int inDates(int& d, int& m, int& y) {
		cin >> d;
		if (cin.get() != '/') {
			cout << "Expected '/'. Re_Enter Date : ";
			return 1;
		}
		cin >> m;
		if (cin.get() != '/') {
			cout << "Expected '/'. Re-Enter Date : ";
			return 1;
		}
		cin >> y;
		return 0;
	}
};

inline int search(char a[], char b[]) {
	int flag = 0;
	if (strlen(a) == strlen(b)) {
		for (int i = 0;i < strlen(a);i++) {
			if (a[i] != b[i]) {
				flag = 1;
				break;
			}
		}
	}
	else
		return 0;
	if (flag)
		return 0;
	else
		return 1;
}

inline int delete_product(int n) {
	int notfound = 1;
	char confirm;
	Store s;
	fstream f1("Store.dat", ios::in | ios::binary);
	fstream f2("Temp.dat", ios::out | ios::binary);
	f1.seekg(0);
	if (!f1) {
		cout << "FAILED TO OPEN FILE!" << endl;
		_getche();
	}
	while (f1.read((char*)&s, sizeof s)) {
		if (n == s.getProduct_no()) {
			notfound = 0;								  //product found
			cout << "\n\nProduct Found :\n\n";
			s.display_product();
			cout << "\n\nDelete this Product (y/n) : ";   //confirmation
			do {
				cin >> confirm;
				if (confirm == 'n')
					f2.write((char*)&s, sizeof s);
				if (confirm == 'y') {
					cout << "\nProduct Deleted.\n";
					break;
				}
			} while (confirm != 'y' && confirm != 'n');  //user input validation
		}
		else
			f2.write((char*)&s, sizeof s);
	}
	f2.close();
	f1.close();
	remove("Store.dat");
	rename("Temp.dat", "Store.dat");

	if (notfound) {
		cout << "Product Not Found.\n";
	}
	_getch();
	return 0;
}

inline void delete_All() {
	Store s;
	int confirm = 0;
	cout << "ARE YOU SURE YOU WANT TO DELETE ALL RECORDS?\n\n\n[SPACE : NO | X :YES]\n\n";
	while (confirm != 22 && confirm != 11) {
		confirm = s.key();
	}
	if (confirm == 22) {
		remove("Store.dat");
		fstream f("Store.dat", ios::out | ios::binary);
		f.close();
		cout << "\nAll Products Deleted.\n";
	}

}

inline int input() {
	Store s;
	fstream f("Store.dat", ios::app | ios::binary);
	int x = 11;
	while (x != 22) {
		s.add_products();
		f.write((char*)&s, sizeof s);
		cout << "\n[SPACE : Enter Next Entry | X: Return to Menu]\n\n";
		x = s.key();
	}
	f.close();
	return 0;
}

struct cred {
	char username[20];
	char pass[20];
};

inline int login() {
	cred x;
	int tries = 3, correct = 0;
	char uname[20], pas[20];
	fstream f("Cred.dat", ios::in | ios::binary);
	if (!f) {
		cout << "\n\n****************************************************" << endl;
		cout << "\t\t\t\tWelcome to Grocery Store" << endl;
		cout << "\n\nPress any key to continue" << endl;
		_getch();
		f.open("Cred.dat", ios::out | ios::binary);
		strcpy_s(x.username, "manju");
		strcpy_s(x.pass, "1234");
		f.write((char*)&x, sizeof x);
		f.close();
	}
	system("cls");
	f.close();
	cout << "\n\n\t\t\t\tGrocery Store Login\n\n" << endl;
	cout << "LOGIN : " << endl;

	while (tries) {
		f.open("Cred.dat", ios::in | ios::binary);
		f.seekg(0);
		_getch();
		cout << "\n\n\nUSERNAME : "; cin >> uname;
		cout << "PASSWORD : ";cin >> pas;
		while (f.read((char*)&x, sizeof x)) {
			if (search(uname, x.username) == 1 && search(pas, x.pass) == 1) {
				correct = 1;
				f.close();
				cout << "\n\nWelcome.\n\nPress any key to continue.";
				_getch();
				return 1;
			}
		}
		f.close();
		if (!correct) {
			cout << "\nIncorrect username or password. ";
			if (--tries > 0)
				cout << tries << " attempts left. \n";
			else
				cout << "No attempts left. Terminating.";
		}
	}
	_getch();
	return 0;
}

inline int newAcc() {
	cred x;
	char uname[20], pas[20];
	int flag = 1;
	while (flag) {
		cout << "ENTER NEW USERNAME AND PASSWORD : \n\n";
		cout << "USERNAME : "; cin >> x.username;
		cout << "PASSWORD : "; cin >> x.pass;
		if (search(uname, x.username) == 1 && search(pas, x.pass) == 1) {
			flag = 0;
			fstream f("Cred.dat", ios::out | ios::binary | ios::trunc);
			f.write((char*)&x, sizeof x);
			cout << "\n\nDetails updated.\n\n";
			_getch();
			return 1;
		}
		else {
			cout << "MISMATCHED.\n\n Please Re-Enter\n\n";
		}
	}
}

inline void disp() {
	system("cls");
	Store s1;
	fstream fi("Store.dat", ios::in | ios::binary);
	while (fi.read((char*)&s1, sizeof(s1))) {
		cout << endl << "\t\t==================================================" << endl;
		s1.display_product();
		cout << endl << "\t\t==================================================" << endl;
	}
	fi.close();
}

inline int search(int n) {
	int notfound = 1;
	Store s;
	fstream f("Store.dat", ios::in | ios::binary);
	f.seekp(0);
	if (!f) {
		cout << "FAILED TO OPEN FILE!";
		_getche();
	}
	while (!f.eof()) {
		f.read((char*)&s, sizeof s);
		if (n == s.getProduct_no()) {
			notfound = 0;
			cout << "Product Found : \n\n";
			s.display_product();
			break;
		}
	}
	f.close();
	if (notfound)
		cout << "PRODUCT NOT FOUND!\n";
	return 0;
}

int sort() {
	int n, f;
	char confirm;
	Store s;
	cout << "Enter Product Number : ";
	cin >> n;
	fstream f1("Store1.dat", ios::in | ios::binary);
	fstream f2("Temp.dat", ios::out | ios::binary);
	f1.seekp(0);
	if (!f1) {
		cout << "FAILED TO OPEN FILE!";
		_getche();
	}
	while (!f1.eof()) {
		system("cls");
		f1.read((char*)&s, sizeof s);
		if (n == s.getProduct_quantity()) {
			s.display_product();
			cout << "\n\nDelete this item? (y/n)";
			f = 0;
			do {
				cin >> confirm;
				if (confirm == 'n')
					f2.write((char*)&s, sizeof s);
				if (f)
					cout << "\nPlease give a valid input.\n";
				f++;
			} while (confirm != 'y' || confirm != 'n');
		}
		else
			f2.write((char*)&s, sizeof s);
	}
	f2.close();
	f1.close();
	remove("Store1.dat");
	rename("Temp.dat", "Store.dat");
	return 0;
}


inline void update(int n) {
	int notfound = 1;
	char confirm;
	Store s;
	fstream f("Store.dat", ios::in | ios::out | ios::ate | ios::binary);
	f.seekg(0);
	if (!f) {
		cout << "FAILED TO OPEN FILE!";
		_getche();
	}
	while (!f.eof()) {
		f.read((char*)&s, sizeof s);
		if (n == s.getProduct_no()) {
			notfound = 0;
			cout << "RECORD FOUND : \n\n";
			s.display_product();
			cout << "\n\nUpdate this item? (y/n) : ";
		}do {
			cin >> confirm;
			if (confirm == 'n')
				break;
			if (confirm == 'y') {
				cout << "\n\nENTER NEW DETAILS : \n\n";
				s.add_products();
				long x = f.tellp(), y = sizeof(s);
				f.seekp(x - y);
				f.write((char*)&s, sizeof s);
				cout << "\n\nRecord Updated.\n\n";
				break;
			}
		} while (confirm != 'y' || confirm != 'n');
		break;
	}
	f.close();
	if (notfound)
		cout << "Record not found.\n";
}

void m() {
	system("cls");
	char b;
	cout << "Enter the character";
	cin >> b;
	int c = b - '0';
	cout << "the int is : " << c;
	cout << "\nthe Integer twice : " << c + c;
	_getche();
}
fstream file;
Store product;

void menu() {
	system("cls");
	file.open("Store.dat", ios::in);
	if (!file) {
		cout << endl << "\t\t\t\tFailed to open to file" << endl;
		cout << endl << "\t\t\t\tClosing Program" << endl;
		cin.get();
		exit(0);
	}
	cout << endl << "\t\t\t\t\t\tItem Menu ";
	cout << endl << "\t\t======================================================================" << endl;
	cout << "\t\tProduct Name\tProduct id\tProduct Price" << endl;
	cout << endl << "\t\t======================================================================" << endl;
	while (file.read((char*)&product, sizeof(product))) {
		cout << "\t\t" << product.getProduct_name() << "\t\t\t\t" << product.getProduct_no() << "\t\t\t\t" << product.getProduct_price() << endl;
		cout << "\t\t======================================================================" << endl;
		cout << endl;
	}
	file.close();
	_getch();
}

//Menu
void owner_menu() {
	system("cls");

	if (!login()) {
		exit(0);
	}
	int product_no;
	Store s;
	int repeat = 1, confirm;
	while (repeat) {
		system("cls");
		cout << "\n1.Create New Product\n\n2.Display all Products\n\n3.Delete Specific Record\n\n4.Search Products by Number\n\n";
		cout << "5.Update Existing Product details\n\n6.Delete all Products\n\n7.Chage login details\n\n0.Exit";
		int x = s.key();
		switch (x) {
		case 1:
			system("cls");
			cout << "Create New Product\n\n\n";
			input();
			break;
		case 2:
			system("cls");
			cout << "Display all Products\n\n\n";
			cout << "All Products\n\n\n";
			disp();
			cout << "\n\n[SPACE : Return to Menu]\n\n";
			confirm = 0;
			while (confirm != 11) {
				confirm = s.key();
			}
			break;
		case 3:
			system("cls");
			cout << "Delete Record\n\n\n";
			cout << "Enter Serial Number : ";cin >> product_no;
			delete_product(product_no);
			cout << "\n\n[SPACE : Return to Menu]\n\n";
			confirm = 0;
			while (confirm != 11) {
				confirm = s.key();
			}
			break;
		case 4:
			system("cls");
			cout << "Search Record\n\n\n";
			cout << "Enter Serial Number : ";cin >> product_no;
			while (cin.fail() || cin.peek() != '\n') {
				cin.clear();
				cin.ignore();
				cout << "You have entered wrong input. Re-Enter : ";
				cin >> product_no;
			}
			search(product_no);
			cout << "\n\n[SPACE : Return to Menu]\n\n";
			confirm = 0;
			while (confirm != 11) {
				confirm = s.key();
			}
			break;
		case 5:
			system("cls");
			cout << "Upadte Record\n\n\n";
			cout << "Enter Serial Number : ";cin >> product_no;
			while (cin.fail() || cin.peek() != '\n') {
				cin.clear();
				cin.ignore();
				cout << "You have entered wrong input. Re-Enter : ";
				cin >> product_no;
			}
			update(product_no);
			cout << "\n\n[SPACE : Return to Menu]\n\n";
			confirm = 0;
			while (confirm != 11) {
				confirm = s.key();
			}
			break;
		case 6:
			system("cls");
			cout << "Delete all Products\n\n\n";
			delete_All();
			cout << "\n\n[SPACE : Return to Menu]\n\n";
			confirm = 0;
			while (confirm != 11) {
				confirm = s.key();
			}
			break;
		case 7:
			system("cls");
			cout << "Change Login Details\n\n\n";
			newAcc();
			cout << "\n\n[SPACE : Return to Menu]\n\n";
			confirm = 0;
			while (confirm != 11) {
				confirm = s.key();
			}
			break;
		case 0:
			system("cls");
			cout << "ARE YOU SURE YOU WANT TO EXIT?\n\n\n[SPACE : NO | X : YES\n\n ";
			confirm = 0;
			while (confirm != 22 && confirm != 11) {
				confirm = s.key();
			}
			if (confirm == 22) {
				repeat = 0;
			}
			break;
		}
	}
	_getch();
}


//Customer login page
void customerlogin() {
	int count = 0;
	string username, password, u, p;
	system("cls");
	cout << endl << endl << endl;
	cout << "\t\t\t\tPlease enter the following details" << endl;
	//_getch();
	cout << "\t\t\t\tUsername : ";
	cin >> username;
	//_getch();
	cout << endl << "\t\t\t\tPassword : ";
	cin >> password;
	ifstream input("customerlogin.txt");
	while (input >> u >> p) {
		if (u == username && p == password) {
			count = 1;
			system("cls");
		}
	}
	input.close();
	if (count == 1) {
		cout << "\t\t\t\tLogin successfull " << endl;
		system("cls");
		int order_arr[50], quant[50], c = 0;
		double amount, damount, total = 0;
		char choice = 'y';
		menu();
		cout << endl << "\t\t======================================================================" << endl;
		cout << endl << "\t\t\t\tPlace your order !" << endl;
		cout << endl << "\t\t======================================================================" << endl;
		do {
			cout << endl << "Enter the product id : " << endl;
			cin >> order_arr[c];
			cout << endl << "Quantity in Number : " << endl;
			cin >> quant[c];
			c++;
			if (quant[c] > product.getProduct_quantity()) {
				try {
					throw runtime_error("Product quantity is Less!");
				}
				catch (runtime_error& er) {
					cout << er.what() << endl;
				}
			}
			cout << endl << "Do you Want to order another item ? (y/n) \t";
			cin >> choice;
		} while (choice == 'y' || choice == 'Y');

		//_getch();
		system("cls");
		cout << endl << endl << endl;
		cout << "\t\t====================invoice====================" << endl;
		cout << endl << "\t\tProduct Name\tProduct id\tProduct Price\tQuantity" << endl;

		for (int i = 0;i <= c;i++) {
			file.open("Store.dat", ios::in | ios::binary);
			file.read((char*)&product, sizeof(product));
			while (!file.eof()) {
				if (product.getProduct_no() == order_arr[i]) {
					amount = product.getProduct_price() * quant[i];
					damount = amount - (amount * product.getProduct_discount() / 100);
					cout << endl << "\t\t" << product.getProduct_name() << "\t\t" << order_arr[i] << "\t\t" << amount << "\t\t" << product.getProduct_quantity() << endl;
					total += damount;
				}
				file.read((char*)&product, sizeof(product));
			}
			file.close();
		}
		cout << endl << "\t\t===============================================" << endl;
		cout << endl << endl << "\t\tTotal Price = " << total << endl;
		cout << endl << "\t\tThank you for Purchasing" << endl;
		_getch();
	}
	else {
		try {
			throw runtime_error("Invalid username or password!.please enter correct details ");
			cout << endl;
		}
		catch (runtime_error& ex) {
			cout << ex.what() << endl;
		}
	}
}

//Registeration for new customers
void customerRegister() {
	string reguser, regpass, ru, rpas;
	system("cls");
	cin.get();
	cout << endl << "\t\t\t\tEnter username : ";
	cin >> reguser;
	//cin.get();
	if (sizeof(reguser) == sizeof(int)) {
		cout << endl << "Please enter valid username " << endl;
	}
	cout << endl << "\t\t\t\tEnter Password : ";
	cin >> regpass;
	ofstream regist("customerlogin.txt", ios::app | ios::binary);
	regist << reguser << ' ' << regpass << endl;
	system("cls");
	cout << "Registeration Successfull!" << endl;
}

int main() {

	int repeat = 1;
	char confirm;
	Store s;
	fstream f("Store.dat", ios::in | ios::out);
	f.close();
	while(repeat){
		system("cls");
		cout << endl << endl;
		cout << endl << "\t\t======================================================================" << endl;
		cout << endl << "\t\t\t\t\t\tMain Menu" << endl;
		cout << endl << "\t\t======================================================================" << endl;
		cout << endl << "\t\t\t\t\t\t1.Owner Login" << endl;
		cout << endl << "\t\t\t\t\t\t2.Customer Login" << endl;
		cout << endl << "\t\t\t\t\t\t3.Customer Register" << endl;
		cout << endl << "\t\t\t\t\t\t4.Exit" << endl;
		cout << endl << "\t\t======================================================================" << endl;
		cout << "\t\t\t\t\tPlease enter the choice  :  ";
		int x = s.key();
		switch (x) {

		case 1:
			system("cls");
			owner_menu();
			confirm = 0;
			while (confirm != 22 && confirm != 11) {
				confirm = s.key();
			}
			break;

		case 2:system("cls");
			customerlogin();
			confirm = 0;
			while (confirm != 22 && confirm != 11) {
				confirm = s.key();
			}
			break;

		case 3:system("cls");
			customerRegister();
			break;

		case 4:system("cls");
			cout << "ARE YOU SURE YOU WANT TO EXIT?\n\n\n[SPACE : NO | X : YES]\n\n";
			confirm = 0;
			while (confirm != 22 && confirm != 11) {
				confirm = s.key();
			}
			if (confirm == 22) {
				repeat = 0;
			}
		}
		return 0;
	}
}
