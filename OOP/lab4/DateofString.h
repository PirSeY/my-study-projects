#include "Prstr.h"
#include <cstring>
#include <iostream>
#include <fstream>

#pragma once
#pragma warning(disable : 4996)

class DateofString : public Prstr {
public:

	DateofString() : Prstr() { day = mounth = year = 0; }

	DateofString(const DateofString& other) : Prstr(other) {

		try {

			if (other.day == NULL || other.mounth == NULL || other.year == NULL || ((other.mounth % 2 == 0) && (other.day > 30)) || other.mounth > 12 || other.day > 31) throw "Fields isn't solved ";

			day = other.day; mounth = other.mounth; year = other.year;
		}
		catch (const char* exception) {

			std::cerr << "Error: " << exception << std::endl << "_______________" << std::endl;
		}
	}

	DateofString(int day, int mounth, int year, const char* other) : Prstr(other) {

		try {

			if (day == NULL || mounth == NULL || year == NULL || ((mounth % 2 != 0) && (day > 30)) || mounth > 12 || day > 31) throw "Fields isn't solved ";

			this->day = day; this->mounth = mounth; this->year = year;
		}
		catch (const char* exception) {

			std::cerr << "Error: " << exception << std::endl << "_______________" << std::endl;
		}
	}

	int setpp(int day, int mounth, int year, const char* other);

	DateofString& getpp();

	DateofString& operator=(const DateofString& other);

	friend bool operator==(const DateofString& pp, const DateofString& other);

	friend std::ostream& operator<< (std::ostream& out, const DateofString& pp);

	friend std::istream& operator>> (std::istream& is, DateofString& pp);

	bool rd_wt_binary();

private:

	int day, mounth, year;
};
