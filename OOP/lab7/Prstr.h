#pragma once

class Prstr {
public:

	Prstr();

	Prstr(const char* s);

	Prstr(const Prstr& str);

	char* sum(const char* s);

	int search(const char* s);

	static int numberobject();

	int setpp(const char* s);

	char* getpp();

	~Prstr();

private:

	static int count;
	char* pp;
	int len_c;
};
