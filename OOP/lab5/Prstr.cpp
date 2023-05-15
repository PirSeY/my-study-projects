#include "Prstr.h"
#include <cstring>
#include <iostream>
#include <fstream>
#include <clocale>
#include <cstdlib>
#include <string> 
#include <sstream>
#pragma warning(disable : 4996)

using namespace std;


Prstr::Prstr() {

	pp = new char[strlen(" ") + 1];
	len_c = NULL;
};


Prstr::Prstr(const Prstr& other) {

	try {


		if (other.pp == nullptr || !other.pp) throw "Field isn't solved ";

		len_c = strlen(other.pp);
		pp = new char[len_c + 1];
		strcpy(pp, other.pp);
	}

	catch (const char* exception) {

		std::cerr << "Error: " << exception << std::endl << "_______________" << std::endl;
	}
}


Prstr::Prstr(const char* other) {

	try {


		if (other == nullptr || !other) throw "Field isn't solved ";

		len_c = strlen(other);
		pp = new char[len_c + 1];
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

		len_c = strlen(other);
		pp = new char[64];
		strcpy(pp, other);

		return 1;
	}

	catch (const char* exception) {

		std::cerr << "Error: " << exception << std::endl << "_______________" << std::endl;
		return 0;
	}
}


char* Prstr::getpp() {

	try {

		if (pp == nullptr || !pp) throw "Empty string";
		char* pt = new char[strlen(pp)];
		strcpy(pt, pp);
		return pt;
	}
	catch (const char* exception) {

		char* s = nullptr;

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


bool Prstr::write_binary(fstream& filename) {

	try {

		if (pp == nullptr && !getpp()) { throw ErrorException("Write in binary hasn't been complited "); }

		if (!filename.is_open()) {

			cout << "error of open" << endl;
			return 0;
		}
		else {

			cout << "file is open" << endl;

			filename << pp;
			return 1;
		}
		filename.close();
	}

	catch (ErrorException& exception) {

		std::cerr << "Error: " << exception.getError() << std::endl << "_______________" << std::endl;
	}
}


void Prstr::to_string() {

	ostringstream oss;
	oss << len_c;
	cout << "string: " << pp << endl << "lenth of string: " << oss.str() << endl;
}


bool Prstr::read_binary(fstream& filename) {

	try {

		if (pp == nullptr && !getpp()) { throw ErrorException("Read from binary hasn't been complited "); }

		if (!filename.is_open()) {

			cout << "error of open" << endl;
			return 0;
		}
		else {

			cout << "file is open" << endl;

			int len = strlen(pp);

			filename.seekg(-len - 2, ios::end);
			filename >> pp;
			cout << pp;
			return 1;
		}
		filename.close();

	}

	catch (ErrorException& exception) {

		std::cerr << "Error: " << exception.getError() << std::endl << "_______________" << std::endl;
	}
}


Prstr::~Prstr() {

	/*std::cout << "Destructor was called" << std::endl << "_______________" << std::endl;*/
}


