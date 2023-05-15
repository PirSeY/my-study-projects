#pragma once
#pragma warning(disable : 4996)

#include "Prstr.h"
#include "StringNumber.h"
#include <cstring>
#include <iostream>
#include <fstream>
#include <bitset>
#include <cstdlib>

using namespace std;


void StringNumber::toint() {

	try {

		if (pp == nullptr || !pp) throw "Empty string";

		len_c = strlen(pp);

		for (int i = 0; i < len_c; i++) {

			a = (int)pp[i];
			itoa(a, buf, 8);

			cout << buf << endl;
		}

		free(buf);
	}
	catch (const char* exception) {

		std::cerr << "Error: " << exception << std::endl << "_______________" << std::endl;
	}
}


char* StringNumber::getpp() {

	len_c = strlen(pp);

	for (int i = 0; i < len_c; i++) {

		a = (int)pp[i];
		itoa(a, buf, 8);

		ostringstream os;
		os << buf;
		cout << "@ " << pp[i] << " @" << " - " << os.str() << endl;
	}

	free(buf);

	ostringstream oss;
	oss << len_c;
	cout << "string: " << pp << endl << "lenth of string: " << oss.str() << endl;

	char* pt = new char[strlen(pp)];
	strcpy(pt, pp);
	return pt;
}