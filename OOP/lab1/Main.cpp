#include<iostream>
#include<string>
#include<clocale>
#include "Head.h"
#pragma warning(disable : 4996)

using namespace std;

bool test_sum(Prstr& a, const char* b) {
	
	const char* s = "abcdef";
	bool rez;

	try {

		if (b == NULL && !b) throw "Тест не выполнен";


		cout << "Основная строка: " << a.getpp() << endl << "Строка, с которой складываем: " << b << endl << "Строка, которая должна получится: " << s << endl;

		if (strcmp(a.sum(b), s) == 0) {
			rez = true;
			cout << "Результаты теста суммы: " << "true" << endl << endl << endl << endl << "***************" << endl;
		}
		else {
			rez = false;
			cout << "Результаты теста суммы: " << "false" << endl << endl << endl << endl << "***************" << endl;
		}

		return (rez) ? true : false;
	}
	catch (const char* exception) {

		std::cerr << "Ошибка: " << exception << std::endl << "_______________" << std::endl;
		return 0;
	}
}

bool test_search(Prstr& a, const char* b) {

	bool rez;

	try {

		if (b == NULL && !b) throw "Тест не выполнен";
		

		cout << "Основная строка: " << a.getpp() << endl << "Искомая подстрока: " << b << endl;

		if (a.search(b)) {
			rez = true;
			cout << "Результаты теста поиска: " << "true" << endl << endl << endl << endl << "***************" << endl;
		}
		else {
			rez = false;
			cout << "Результаты теста поиска: " << "false" << endl << endl << endl << endl << "***************" << endl;
		}

		return (rez) ? true : false;
	}

	catch (const char* exception) {

		std::cerr << "Ошибка: " << exception << std::endl << "_______________" << std::endl;
		return 0;
	}
}


int main() {
	setlocale(LC_ALL, "russian");
	int c = 0;

	
	Prstr* strngs = new Prstr[5];
	Prstr* pt = strngs;
	pt[1].setpp("abc");
	pt[2].setpp("");
	pt[3].setpp("abc");
	pt[4].setpp(" ");
	pt[5].setpp("qwerty");

	for (int i = 0; i < 5; i++) {

		if (test_sum(pt[i + 1], "def")) {
			c++;
		}
	}
	cout << "Успешно выполненые тесты сложения: " << c << "/5 выполненны успешно" << endl << endl;
	c = 0;

	for (int i = 0; i < 5; i++) {

		if (test_search(pt[i + 1], "a")) {
			c++;
		}
	}
	cout << "Успешно выполненые тесты поиска: " << c << "/5 выполненны успешно" << endl << endl;



}