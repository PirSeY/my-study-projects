#include "Prstr.h"
#include <cstring>
#include <iostream>
#include <fstream>
#include <clocale>
#include <cstdlib>
#pragma warning(disable : 4996)

using namespace std;


Prstr::Prstr() {
	
	pp = new char[strlen(" ") + 1];
	len_c = NULL;
};


Prstr::Prstr(const Prstr& other) {

	try {


		if (other == nullptr || !other.pp) throw "Field isn't solved ";

		pp = new char[strlen(other.pp) + 1];
		strcpy(pp, other.pp);
	}

	catch (const char* exception) {

		std::cerr << "Error: " << exception << std::endl << "_______________" << std::endl;
	}
}


Prstr::Prstr(const char* other) {

	try {


		if (other == nullptr || !other) throw "Field isn't solved ";

		pp = new char[strlen(other) + 1];
		strcpy(pp, other);
	}

	catch (const char* exception) {

		std::cerr << "Error: " << exception << std::endl << "_______________" << std::endl;
	}
}


char* Prstr::sum(const char* s) {

	try {

		if (s == NULL || !s) throw "Sum isn't complited";


		strcat(pp, s);
		std::cout << "Result string: " << pp << std::endl << "_______________" << std::endl;
		return pp;
	}

	catch (const char* exception) {

		std::cerr << "Error: " << exception << std::endl << "_______________" << std::endl;
	}
}


int Prstr::search(const char* s) {

	try {

		if (s == NULL || !s) throw "Search isnt'complited";

		if (strstr(pp, s)) {

			std::cout << "Substring" << std::endl << "_______________" << std::endl;
			return 1;
		}
	}

	catch (const char* exception) {

		std::cerr << "Error: " << exception << std::endl << "_______________" << std::endl;
		return 0;
	}
}


int Prstr::setpp(const char* other) {

	try {

		if (other == nullptr || !other) throw "Field was not introduced ";


		pp = new char[64];
		strcpy(pp, other);

		return 1;
	}

	catch (const char* exception) {

		std::cerr << "Error: " << exception << std::endl << "_______________" << std::endl;
		return 0;
	}
}


const char* Prstr::getpp() {

	try {

		if (pp == nullptr || !pp) throw "Empty string";

		return pp;
	}
	catch (const char* exception) {

		const char* s = " ";

		std::cerr << "Error: " << exception << std::endl << "_______________" << std::endl;
		return s;
	}
}


Prstr& Prstr::operator=(const Prstr& other) {

	try {

		if (other.pp == NULL && !other.pp) throw "Operator = didn't work ";

		delete[] this->pp;
		strcpy(pp, other.pp);
		return *this;
	}

	catch (const char* exception) {

		std::cerr << "Error: " << exception << std::endl << "_______________" << std::endl;
	}
}


Prstr& Prstr::operator+(const Prstr& other) {

	try {

		if (other.pp == NULL || !other.pp) throw "Operator + didn't work ";

		strcat(pp, other.pp);
		return *this;
	}

	catch (const char* exception) {

		std::cerr << "Error: " << exception << std::endl << "_______________" << std::endl;
	}
}


Prstr Prstr::operator+(const char* other) {

	try {

		if (other == NULL || !other || pp == NULL || !pp) throw "Operator + didn't work ";

		delete[] pp;
		return Prstr(strcpy(pp, other));
	}

	catch (const char* exception) {

		std::cerr << "Error: " << exception << std::endl << "_______________" << std::endl;
	}
}


bool operator==(const Prstr& pp, const char* other) {

	try {

		if (other == NULL || !other || pp.pp == NULL || !pp.pp) throw "Operator == didn't work ";

		return (strstr(pp.pp, other) == &pp.pp[0] && strlen(pp.pp) == strlen(other)) ? true : false;
	}

	catch (const char* exception) {

		std::cerr << "Error: " << exception << std::endl << "_______________" << std::endl;
	}
}


bool operator==(const Prstr& pp, const Prstr& other) {

	try {

		if (other.pp == NULL || !other.pp || pp.pp == NULL || !pp.pp) throw "Operator == didn't work ";

		return (strstr(pp.pp, other.pp) == &pp.pp[0] && strlen(pp.pp) == strlen(other.pp)) ? true : false;
	}

	catch (const char* exception) {

		std::cerr << "Error: " << exception << std::endl << "_______________" << std::endl;
	}
}


std::ostream& operator<< (std::ostream& out, const Prstr& pp) {

	try {

		if (pp.pp == nullptr || !pp.pp) throw "Empty string";

		out << pp.pp << endl;
		return out;
	}
	catch (const char* exception) {

		std::cerr << "Error: " << exception << std::endl << "_______________" << std::endl;
	}
}


std::istream& operator>> (std::istream& is, Prstr& pp) {

	try {

		if (pp.pp == nullptr || !pp.pp) throw "Empty string";

		is >> pp.pp;
		return is;
	}
	catch (const char* exception) {

		std::cerr << "Error: " << exception << std::endl << "_______________" << std::endl;
	}
}


bool Prstr::read_wrire_binary() {

	try {

		if (pp == nullptr && !getpp()) { throw "Binary hasn't been complited "; }
		else {

			fstream fs;

			fs.open("dat.dat", fstream::in | fstream::out | fstream::app | fstream::binary);

			if (!fs.is_open()) {

				cout << "error of open" << endl;
				return 0;
			}
			else {

				cout << "file is open" << endl;

				fs << pp;
				return 1;
			}
			fs.close();


			fs.open("dat.dat", fstream::in | fstream::out | fstream::app | fstream::binary);

			if (!fs.is_open()) {

				cout << "error of open" << endl;
				return 0;
			}
			else {

				cout << "file is open" << endl;

				int len = strlen(pp);

				fs.seekg(-len - 2, ios::end);
				fs >> pp;
				cout << pp;
				return 1;
			}
			fs.close();

		}
	}
	catch (const char* exception) {

		std::cerr << "Error: " << exception << std::endl << "_______________" << std::endl;
		return 0;
	}
}


Prstr::~Prstr() {

	/*std::cout << "Destructor was called" << std::endl << "_______________" << std::endl;*/
}