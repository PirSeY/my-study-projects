#pragma once
#pragma warning(disable : 4996)

#include <cstring>
#include <iostream>


class Prstr {
public:

	Prstr();

	Prstr(const char* other);

	Prstr(const Prstr& other);

	int setpp(const char* other);

	const char* getpp();

	char* sum(const char* s);

	int search(const char* s);

	Prstr& operator=(const Prstr& other);

	Prstr& operator+(const Prstr& other);

	Prstr operator+(const char* other);

	friend bool operator == (const Prstr& pp, const Prstr& other);
	
	friend bool operator == (const Prstr& pp, const char* other);
	
	~Prstr();

private:

	char* pp;
	int len_c = 0;
};