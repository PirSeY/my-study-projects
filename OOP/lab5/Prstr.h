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

	virtual char* getpp();

	char* sum(const char* s);

	int search(const char* s);

	Prstr& operator=(const Prstr& other);

	Prstr& operator+(const Prstr& other);

	Prstr operator+(const char* other);

	friend bool operator == (const Prstr& pp, const Prstr& other);

	friend bool operator == (const Prstr& pp, const char* other);

	friend std::ostream& operator<< (std::ostream& out, const Prstr& pp);

	friend std::istream& operator>> (std::istream& is, Prstr& pp);

	bool read_binary(fstream& filename);

	bool write_binary(fstream& filename);

	void to_string();

	~Prstr();

protected:

	char* pp;
	int len_c = 0;
	int tabs = 0;
	const Prstr* field;
	Prstr* left;
	Prstr* right;
};