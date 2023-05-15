#include "Head.h"
#include <cstring>
#include <iostream>
#pragma warning(disable : 4996)

Prstr::Prstr() {

	pp = new char[strlen(" ") + 1];
	len_c = NULL;
	count++;
};

Prstr::Prstr(const Prstr &str) {

	pp = new char[strlen(str.pp) + 1];
	strcpy(pp, str.pp);
	count++;
}

Prstr::Prstr(const char* s) {

	pp = new char[strlen(s) + 1];
	strcpy(pp, s);
	count++;
}

int Prstr::setpp(const char* s)  {
	
	try {

		if (s == NULL || !s) throw "Ввод поля не выполнен";

		
		pp = new char[64];

		strcpy(pp, s);
		
		return 1;
	}

	catch (const char* exception) {

		std::cerr << "Ошибка: " << exception << std::endl << "_______________" << std::endl;
	}

}

char* Prstr::getpp() {

	try {

		if (&pp == NULL || !&pp) throw "Пустая строка";


		std::cout << pp << std::endl;
		return pp;
	}
	catch(const char* exception) {

		std::cerr << "Ошибка: " << exception << std::endl << "_______________" << std::endl;
	}
}

char* Prstr::sum(const char* s) {

	try {

		if (s == NULL && !s) throw "Сумма не выполнено";
		
		
		strcat(pp, s);
		std::cout << "Получившаяся строка: " << pp << std::endl << "_______________" << std::endl;
		return pp;
	}

	catch (const char* exception) {

		std::cerr << "Ошибка: " << exception << std::endl << "_______________" << std::endl;
	}

	
	
}

int Prstr::search(const char* s) {

	try {

		if (s == NULL && !s) throw "Поиск не выполнен";

		if (strstr(pp, s)) {

			std::cout << "Подстрока найдена" << std::endl << "_______________" << std::endl;
			return 1;
		}
	}

	catch (const char* exception) {

		std::cerr << "Ошибка: " << exception << std::endl << "_______________" << std::endl;
		return 0;
	}
}

void Prstr::numberobject() {
	std::cout<<"Количество обьектов класса: " << count <<  std::endl << "_______________" << std::endl;
}

Prstr::~Prstr() {
	count--;
	std::cout << "Вызвался деструктор" << std::endl << "_______________" << std::endl;
}

int Prstr::count = 0;