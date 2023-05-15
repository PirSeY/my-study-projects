#include "Prstr.h"
#include "StringNumber.h"
#include <cstring>
#include <iostream>
#include <fstream>
#include <bitset>
#include <cstdlib>

using namespace std;

#pragma once
#pragma warning(disable : 4996)

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
