#pragma once
#pragma warning(disable : 4996)

#include <cstring>
#include <iostream>
#include <fstream>

using namespace std;

class ErrorException {

public:

	ErrorException(string error) : m_error(error) {}

	const char* getError() { return m_error.c_str(); }

private:

	string m_error;
};


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

	friend std::ostream& operator<< (std::ostream &out, const Prstr &pp);

	friend std::istream& operator>> (std::istream& is, Prstr& pp);

	bool write_binary(std::fstream& filename);

	bool read_binary(std::fstream& filename);

	~Prstr();

private:

	char* pp;
	int len_c = 0;
};