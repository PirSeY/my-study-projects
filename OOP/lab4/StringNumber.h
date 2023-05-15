#include "Prstr.h"
#include <cstring>
#include <iostream>
#include <fstream>

#pragma once
#pragma warning(disable : 4996)

class StringNumber: public Prstr {
public:

	StringNumber() : Prstr() {}

	StringNumber(const StringNumber& other) : Prstr(other) {}

	StringNumber(const char* other) : Prstr(other) {}

	void toint();



private:

	char* buf = new char[64];
	int a;
};