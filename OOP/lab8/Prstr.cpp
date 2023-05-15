#include "Prstr.h"
#include <cstring>
#include <iostream>
#pragma warning(disable : 4996)

Prstr::Prstr() {

	pp = new char[strlen(" ") + 1];
	len_c = NULL;
	count++;
};

Prstr::Prstr(const Prstr& str) {

	pp = new char[strlen(str.pp) + 1];
	strcpy(pp, str.pp);
	count++;
}

Prstr::Prstr(const char* s) {

	len_c = strlen(s);
	pp = new char[strlen(s) + 1];
	strcpy(pp, s);
	count++;
}

int Prstr::setpp(const char* s) {

	try {

		if (s == NULL || !s) throw "Field was not introduced ";


		pp = new char[64];

		strcpy(pp, s);

		return 1;
	}

	catch (const char* exception) {

		std::cerr << "Error: " << exception << std::endl << "_______________" << std::endl;
	}

}

int Prstr::getpp() {

	try {

		if (&pp == NULL || !&pp) throw "Empty string";

		return len_c;
		
	}
	catch (const char* exception) {

		std::cerr << "Error: " << exception << std::endl << "_______________" << std::endl;
	}
}

char* Prstr::sum(const char* s) {

	try {

		if (s == NULL && !s) throw "Sum isn't solved ";


		strcat(pp, s);
		std::cout << "Resulting string: " << pp << std::endl << "_______________" << std::endl;
		return pp;
	}

	catch (const char* exception) {

		std::cerr << "Error: " << exception << std::endl << "_______________" << std::endl;
	}



}

int Prstr::search(const char* s) {

	try {

		if (s == NULL && !s) throw "No search ";

		if (strstr(pp, s)) {

			std::cout << "Substring isn't search " << std::endl << "_______________" << std::endl;
			return 1;
		}
	}

	catch (const char* exception) {

		std::cerr << "Error: " << exception << std::endl << "_______________" << std::endl;
		return 0;
	}
}

int Prstr::numberobject() {
	std::cout << "Number obj of class: " << count << std::endl << "_______________" << std::endl;
	return 1;
}

Prstr::~Prstr() {
	count--;
	/*std::cout << "Destructor was called" << std::endl << "_______________" << std::endl;*/
}

int Prstr::count = 0;