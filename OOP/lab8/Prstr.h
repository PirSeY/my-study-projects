#pragma once
#pragma warning(disable : 4996)
#include <cstring>
#include <iostream>

class Prstr {
public:

	Prstr();

	Prstr(const char* s);

	Prstr(const Prstr& str);

	char* sum(const char* s);

	int search(const char* s);

	static int numberobject();

	int setpp(const char* s);

	int getpp();

	~Prstr();

private:

	static int count;
	char* pp;
	int len_c;
};


