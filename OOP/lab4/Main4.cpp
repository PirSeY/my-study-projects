#include <cstring>
#include <iostream>
#include <fstream>
#include <clocale>
#include <bitset>
#include "Header4.h"
#include "Header4.1.h"
#include "Header4.2.h"


#pragma warning(disable : 4996)

using namespace std;


bool test_original_file(Prstr& a) {

	const char* s = "}{uLiGaHcheG2007";
	bool rez = NULL;

	try {

		if (a.getpp() == nullptr && !a.getpp()) { throw "Test hasn't been complited "; }
		else {

			fstream fs;

			fs.open("txt.txt", fstream::in | fstream::out | fstream::app);

			if (!fs.is_open()) {

				cout << "error of open" << endl;
			}
			else {

				cout << "file is open" << endl;

				fs << a;
			}
			fs.close();


			fs.open("txt.txt", fstream::in | fstream::out | fstream::app);

			if (!fs.is_open()) {

				cout << "error of open" << endl;
			}
			else {

				cout << "file is open" << endl;

				int len = strlen(a.getpp());

				fs.seekg(-len - 2, ios::end);
				fs >> a;
				cout << a;
			}
			fs.close();

			if (a == s) {

				rez = true;
				cout << "Result test: " << "test original is OK" << endl << endl << endl << endl << "***************" << endl;
			}
			else {

				rez = false;
				cout << "Result test: " << "test original is BAD" << endl << endl << endl << endl << "***************" << endl;
			}
		}

		return (rez) ? true : false;
	}
	catch (const char* exception) {

		std::cerr << "Error: " << exception << std::endl << "_______________" << std::endl;
		return 0;
	}
}


bool test_binary_file(Prstr& a) {

	const char* s = "}{uLiGaHcheG2007";
	bool rez;

	try {

		if (a.getpp() == nullptr && !a.getpp()) { throw "Test hasn't been complited "; }
		else {

			if (a == s && a.read_wrire_binary()) {

				rez = true;
				cout << "Result test: " << "test binary is OK" << endl << endl << endl << endl << "***************" << endl;
			}
			else {

				rez = false;
				cout << "Result test: " << "test binary is BAD" << endl << endl << endl << endl << "***************" << endl;
			}
		}

		return (rez) ? true : false;
	}
	catch (const char* exception) {

		std::cerr << "Error: " << exception << std::endl << "_______________" << std::endl;
		return 0;
	}
}


bool test_sum(Prstr& a, const char* b) {

	const char* s = "abcdef";
	bool rez;

	try {

		if (b == nullptr && !b) throw "Test hasn't been complited ";


		cout << "First string: " << a.getpp() << endl << "Second string: " << b << endl << "The line that should turn out: " << s << endl;

		if (strcmp(a.sum(b), s) == 0) {
			rez = true;
			cout << "Result test: " << "test sum is OK" << endl << endl << endl << endl << "***************" << endl;
		}
		else {
			rez = false;
			cout << "Result test: " << "test sum is BAD" << endl << endl << endl << endl << "***************" << endl;
		}

		return (rez) ? true : false;
	}
	catch (const char* exception) {

		std::cerr << "Error: " << exception << std::endl << "_______________" << std::endl;
		return 0;
	}
}


bool test_search(Prstr& a, const char* b) {

	bool rez;

	try {

		if (b == NULL && !b) throw "Test hasn't been complited ";


		cout << "First string: " << a.getpp() << endl << "Second string: " << b << endl;

		if (a.search(b)) {
			rez = true;
			cout << "Result test: " << "test search is OK" << endl << endl << endl << endl << "***************" << endl;
		}
		else {
			rez = false;
			cout << "Result test: " << "test search is BAD" << endl << endl << endl << endl << "***************" << endl;
		}

		return (rez) ? true : false;
	}

	catch (const char* exception) {

		std::cerr << "Error: " << exception << std::endl << "_______________" << std::endl;
		return 0;
	}
}


bool test_operator_pls1_comp(Prstr& myfield, Prstr& other) {

	const char* s = "asdfas";
	bool rez;

	try {

		if (myfield.getpp() == nullptr && !myfield.getpp() && other.getpp() == nullptr && !other.getpp()) throw "Test hasn't been complited ";

		cout << "First string: " << myfield.getpp() << endl << "Second string: " << other.getpp() << endl << "The line that should turn out: " << s << endl;


		if ((myfield.operator+(other)) == s) {
			rez = true;
			cout << "Result test: " << "test 1 is OK" << endl << endl << endl << endl << "***************" << endl;
		}
		else {
			rez = false;
			cout << "Result test: " << "test 1 is BAD" << endl << endl << endl << endl << "***************" << endl;
		}

		return (rez) ? true : false;
	}
	catch (const char* exception) {

		std::cerr << "Error: " << exception << endl << "_______________" << endl;
		return 0;
	}
}


bool test_operator_pls2_comp(Prstr& myfield, const char* other) {

	const char* s = "asdf";
	bool rez;

	try {

		if (myfield.getpp() == nullptr && !myfield.getpp() && other == nullptr && !other) throw "Test hasn't been complited ";

		cout << "First string: " << myfield.getpp() << endl << "Second string: " << other << endl << "The line that should turn out: " << s << endl;


		if (myfield.operator+(other) == s) {
			rez = true;
			cout << "Result test: " << "test 2 is OK" << endl << endl << endl << endl << "***************" << endl;
		}
		else {
			rez = false;
			cout << "Result test: " << "test 2 is BAD" << endl << endl << endl << endl << "***************" << endl;
		}

		return (rez) ? true : false;
	}
	catch (const char* exception) {

		std::cerr << "Error: " << exception << std::endl << "_______________" << endl;
		return 0;
	}
}


int main() {	
	
	StringNumber a;
	StringNumber b("qwerty");
	
	
}
