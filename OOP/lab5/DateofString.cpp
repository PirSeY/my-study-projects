#pragma once
#pragma warning(disable : 4996)
#include "DateofString.h"
#include <cstring>
#include <iostream>
#include <fstream>


int DateofString::setpp(int day, int mounth, int year, const char* other) {

	try {

		if (day == NULL || mounth == NULL || year == NULL || ((mounth % 2 != 0) && (day > 30)) || mounth > 12 || day > 31) throw "Fields isn't set ";

		Prstr::setpp(other);
		this->day = day; this->mounth = mounth; this->year = year;

		return 1;
	}
	catch (const char* exception) {

		std::cerr << "Error: " << exception << std::endl << "_______________" << std::endl;
		return 0;
	}

}


DateofString& DateofString::getdate() {

	try {

		if (day == NULL || mounth == NULL || year == NULL || ((mounth % 2 != 0) && (day > 30)) || mounth > 12 || day > 31 || pp == nullptr || !pp) throw "Obj can't get";
		cout << this;
		return *this;
	}
	catch (const char* exception) {

		std::cerr << "Error: " << exception << std::endl << "_______________" << std::endl;
	}
}


DateofString& DateofString::operator=(const DateofString& other) {

	try {

		if (other.pp == NULL || !other.pp || other.day == NULL || other.mounth == NULL || other.year == NULL || ((other.mounth % 2 != 0) && (other.day > 30)) || other.mounth > 12 || other.day > 31) throw "Operator = didn't work ";

		day = mounth = year = 0;
		delete[]this->pp;

		strcpy(pp, other.pp);
		day = other.day; mounth = other.mounth; year = other.year;

		return *this;
	}

	catch (const char* exception) {

		std::cerr << "Error: " << exception << std::endl << "_______________" << std::endl;
	}
}


bool DateofString::rd_wt_binary() {

	try {

		if (pp == nullptr || !pp || day == NULL || mounth == NULL || year == NULL || ((mounth % 2 != 0) && (day > 30)) || mounth > 12 || day > 31) { throw "Binary hasn't been complited "; }
		else {

			std::fstream fs;

			fs.open("dat.dat", std::fstream::in | std::fstream::out | std::fstream::app | std::fstream::binary);

			if (!fs.is_open()) {

				std::cout << "error of open" << std::endl;
				return 0;
			}
			else {

				std::cout << "file is open" << std::endl;

				fs << pp << day << mounth << year;

				return 1;
			}
			fs.close();


			fs.open("dat.dat", std::fstream::in | std::fstream::out | std::fstream::app | std::fstream::binary);

			if (!fs.is_open()) {

				std::cout << "error of open" << std::endl;
				return 0;
			}
			else {

				std::cout << "file is open" << std::endl;

				int len = strlen(pp);

				fs.seekg(-len - 2, std::ios::end);

				fs >> pp >> day >> mounth >> year;
				std::cout << year << mounth << day << pp;

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


char* DateofString::getpp() {

	DateofString::getdate();
	char* pt = new char[strlen(pp)];
	strcpy(pt, pp);
	return pt;
}


bool operator==(const DateofString& my, const DateofString& other) {

	bool flag = false;

	try {

		if (other.pp == NULL || !other.pp || my.pp == NULL || !my.pp || other.day == NULL || other.mounth == NULL || other.year == NULL || ((other.mounth % 2 != 0) && (other.day > 30)) || my.day == NULL || my.mounth == NULL || my.year == NULL || ((my.mounth % 2 != 0) && (my.day > 30))) throw "Operator == didn't work ";

		if ((my.day == other.day && my.mounth == other.mounth && my.year == other.year) && (strstr(my.pp, other.pp) == &my.pp[0] && strlen(my.pp) == strlen(other.pp))) flag = true;
		return (flag) ? true : false;
	}

	catch (const char* exception) {

		std::cerr << "Error: " << exception << std::endl << "_______________" << std::endl;
	}
}


std::ostream& operator<<(std::ostream& out, const DateofString& pp) {

	try {

		if (pp.pp == nullptr || !pp.pp || pp.day == NULL || pp.mounth == NULL || pp.year == NULL || ((pp.mounth % 2 != 0) && (pp.day > 30))) throw "Empty string";

		out << pp.pp << std::endl << pp.day << std::endl << pp.mounth << std::endl << pp.year << std::endl;
		return out;
	}
	catch (const char* exception) {

		std::cerr << "Error: " << exception << std::endl << "_______________" << std::endl;
	}
}


std::istream& operator>>(std::istream& is, DateofString& pp) {

	try {

		if (pp.pp == nullptr || !pp.pp || pp.day == NULL || pp.mounth == NULL || pp.year == NULL || ((pp.mounth % 2 != 0) && (pp.day > 30))) throw "Empty string";

		is >> pp.pp >> pp.day >> pp.mounth >> pp.year;
		return is;
	}
	catch (const char* exception) {

		std::cerr << "Error: " << exception << std::endl << "_______________" << std::endl;
	}
}
