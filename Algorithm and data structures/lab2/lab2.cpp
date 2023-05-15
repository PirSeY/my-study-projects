// lab2.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <conio.h>
#include <ctime>

#include "class.h"

using namespace std;

typedef long long MyTypeD;
typedef long long MyTypeK;

MyTypeD lrand()
{
	return rand()<<16 | rand();
}

void test_rand(int n){
	Tree <MyTypeD, MyTypeK> tree;
	
	srand((unsigned)time(NULL));	//Инициализация генератора ПСЧ
	MyTypeK* m = new MyTypeK[n];
	MyTypeD data = 1;
	int nn = 0;
	for(int i = 0; i < n; i++)
	{
		m[i] = lrand();
		tree.addNewIndex(m[i], data, nn);
	}
	
	nn = 0;
	double I = 0;
	double D = 0;
	double S = 0;

	for(int i = 0; i < n/2; i++)
		if(i%10 == 0)
		{
			tree.deleteIndex(lrand(), nn);
			D += nn;
			tree.addNewIndex(m[rand()%n], data, nn);
			I += nn;
			try
			{
				tree.readObject(lrand(), nn);
			}
			catch(exception&) { }
			S += nn;
		}
		else
		{
			int ind = rand() % n;
			tree.deleteIndex(m[ind], nn);
			D += nn;
			MyTypeD data = lrand();
			tree.addNewIndex(data, data, nn);
			I += nn;
			m[ind] = data;
			try
			{
				tree.readObject(m[rand()%n], nn);
			}
			catch(exception&) { }
			S += nn;
		}

	cout<<"Размер дерева после удаления: " << tree.sizeOfTree() << endl;
	cout<<"1.39*log2(n) = " << 1.39*(log((double)n)/log(2.)) << endl;
	cout<<"Вставка: " << I/(n/2) << endl;
	cout<<"Удаление: " << D/(n/2) << endl;
	cout<<"Поиск: " << S/(n/2) << endl;
	delete[] m;
}

void test_sort(int n)
{
	Tree <MyTypeD, MyTypeK> tree;
	
	MyTypeK* m = new MyTypeK[n];
	MyTypeD v = 1;
	int nn = 0;
	for(int i = 0; i < n; i++)
	{
		m[i] = i*1000;
		tree.addNewIndex(m[i], v, nn);
	}
	
	nn = 0;
	double I = 0;
	double D = 0;
	double S = 0;

	for(int i = 0; i < n/2; i++)
		if(i%10 == 0)
		{
			tree.deleteIndex(lrand(), nn);
			D += nn;
			tree.addNewIndex(m[rand()%n], v, nn);
			I += nn;
			try
			{
				tree.readObject(lrand(), nn);
			}
			catch(exception&) { }
			S += nn;
		}
		else
		{
			int ind=rand()%n;
			tree.deleteIndex(m[ind], nn);
			D += nn;
			MyTypeK key = lrand()%1000*n;
			key = key + key%2;
			tree.addNewIndex(key, v, nn);
			I += nn;
			m[ind]=key;
			try
			{
				tree.readObject(m[rand()%n], nn);
			}
			catch(exception&) { }
			S += nn;
		}

	cout << "Размер дерева после удаления: " << tree.sizeOfTree()<< endl;
	cout << "n/2 = " << n / 2. << endl;
	cout << "Вставка: " << I/(n/2) << endl;
	cout << "Удаление: " << D/(n/2) << endl;
	cout << "Поиск: " << S/(n/2) << endl;
	delete[] m;
}


bool CheckLimits(const Tree <MyTypeD, MyTypeK>::Iterator& it)
{
	if (it.is_off())
		return true;
	else
		return false;
}

int _tmain(int argc, char*  argv[])
{
	Tree <MyTypeD, MyTypeK> t;
	Tree <MyTypeD, MyTypeK>::Iterator it(t);
	int key, tmp, looked = 0;
	int nnn = 0;
	bool isExit = false;	//Флаг выхода
	setlocale(LC_ALL, "Russian");
	cout << "Меню:" << endl;
	cout << "0) опрос размера дерева" << endl;
	cout << "1) очистка дерева" << endl;
	cout << "2) проверка дерева на пустоту" << endl;
	cout << "3) доступ к данным с заданным ключом" << endl;
	cout << "4) включение данных с заданным ключом" << endl;
	cout << "5) удаление данных с заданным ключом" << endl;
	cout << "6) определение длины внешнего пути дерева" << endl;
	cout << "7) вывод структуры дерева на экран" << endl;
	cout << "8) опрос числа просмотренных операцией узлов дерева" << endl;
	cout << "9) обход узлов дерева по схеме LtR" << endl;
	cout << "10) вызвать конструктор копирования" << endl;
	cout << "11) " << endl;
	cout << "Итератор:" << endl;
	cout << "\t12) установка на первый узел в дереве с  минимальным  ключом" << endl;
	cout << "\t13) установка на последний узел  в дереве  с максимальным ключом" << endl;
	cout << "\t14) установка на следующий" << endl;
	cout << "\t15) установка на предыдущий" << endl;
	cout << "\t16) проверка состояния итератора" << endl;
	cout << "\t17) доступ по чтению к данным текущего узла в дереве" << endl;
	cout << "\t18) доступ записи к данным текущего узла в дереве" << endl;
	cout << "19) тест" << endl;
	cout << "27) Выход" << endl;
	cout << "\t28) тест 1" << endl;
	cout << "\t29) тест 2" << endl;
	
	while(!isExit)
	{
		int ans;	//Код нажатой клавиши
		cin >> ans;
		
		try
		{
			switch(ans)
			{
			case 0:	
				cout << t.sizeOfTree() << endl;
				break;
			
			case 1:	
				t.deleteTree();
				cout<< "Дерево очищено"<<endl;
				break;

			case 2:
				cout << t.EmptyTree() << endl;
				break;

			case 3:			
				cout << "Введите ключ: ";
				cin >> key;
				cout << t.readObject(key, looked) << endl;
				break;
			
			case 4:
				cout << "Введите ключ: ";
				cin >> key;
				cout << "Значение: ";
				cin >> tmp;
				cout << t.addNewIndex(key,tmp,looked) << endl;
				break;

			case 5:
				cout << "Введите ключ: ";
				cin >> key;
				cout << t.deleteIndex(key,looked) << endl;
				break;

			case 6:
				cout << t.lengthofThree() << endl;
				break;
			
			case 7:
				t.show_tree();
				break;
			
			case 8:
				cout << looked << endl;
				break;

            case 9:
				t.go_LtR();
				break;

			case 10:
				{
					Tree<MyTypeD, MyTypeK> tmp(t);
					cout << "Исходное дерево:" << endl;
					t.show_tree();
					cout << "Скопированное дерево:" << endl;
					tmp.show_tree();
				}
				break;

			case 11:
				break;

			case 12:
				it.beg();
				cout << endl;
				break;

			case 13:
				it.end();
				cout << endl;
				break;

			case 14:
				it.next();
				cout << CheckLimits(it)<<endl;
				break;
			
			case 15:
				it.prev();
				cout << CheckLimits(it)<<endl;
				break;
			
			case 16:
				cout << CheckLimits(it)<<endl;
				break;
				
			case 17:
				cout << *it;
				break;

			case 18:
				cout << "Новое значение: ";
				cin >> *it;
				break;

			case 27:	//Выход
				isExit = true;
				break;

			case 28:
				cout << "Введите размерность" << endl;
				cin >> nnn;
				test_rand(nnn);
				break;

			case 29:
				cout << "Введите размерность" << endl;
				cin >> nnn;
				test_sort(nnn);
				break;

			default:	//Нажата клавиша, не соответствующая ни одной команде
				cout << "Неизвестная команда" << endl;
				break;
			}
		}
		catch(exception& exc)
		{
			cout << exc.what() << endl;
		}
	}
	return 0;
}
