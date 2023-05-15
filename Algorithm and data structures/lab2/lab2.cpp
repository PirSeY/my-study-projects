// lab2.cpp: ���������� ����� ����� ��� ����������� ����������.
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
	
	srand((unsigned)time(NULL));	//������������� ���������� ���
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

	cout<<"������ ������ ����� ��������: " << tree.sizeOfTree() << endl;
	cout<<"1.39*log2(n) = " << 1.39*(log((double)n)/log(2.)) << endl;
	cout<<"�������: " << I/(n/2) << endl;
	cout<<"��������: " << D/(n/2) << endl;
	cout<<"�����: " << S/(n/2) << endl;
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

	cout << "������ ������ ����� ��������: " << tree.sizeOfTree()<< endl;
	cout << "n/2 = " << n / 2. << endl;
	cout << "�������: " << I/(n/2) << endl;
	cout << "��������: " << D/(n/2) << endl;
	cout << "�����: " << S/(n/2) << endl;
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
	bool isExit = false;	//���� ������
	setlocale(LC_ALL, "Russian");
	cout << "����:" << endl;
	cout << "0) ����� ������� ������" << endl;
	cout << "1) ������� ������" << endl;
	cout << "2) �������� ������ �� �������" << endl;
	cout << "3) ������ � ������ � �������� ������" << endl;
	cout << "4) ��������� ������ � �������� ������" << endl;
	cout << "5) �������� ������ � �������� ������" << endl;
	cout << "6) ����������� ����� �������� ���� ������" << endl;
	cout << "7) ����� ��������� ������ �� �����" << endl;
	cout << "8) ����� ����� ������������� ��������� ����� ������" << endl;
	cout << "9) ����� ����� ������ �� ����� LtR" << endl;
	cout << "10) ������� ����������� �����������" << endl;
	cout << "11) " << endl;
	cout << "��������:" << endl;
	cout << "\t12) ��������� �� ������ ���� � ������ �  �����������  ������" << endl;
	cout << "\t13) ��������� �� ��������� ����  � ������  � ������������ ������" << endl;
	cout << "\t14) ��������� �� ���������" << endl;
	cout << "\t15) ��������� �� ����������" << endl;
	cout << "\t16) �������� ��������� ���������" << endl;
	cout << "\t17) ������ �� ������ � ������ �������� ���� � ������" << endl;
	cout << "\t18) ������ ������ � ������ �������� ���� � ������" << endl;
	cout << "19) ����" << endl;
	cout << "27) �����" << endl;
	cout << "\t28) ���� 1" << endl;
	cout << "\t29) ���� 2" << endl;
	
	while(!isExit)
	{
		int ans;	//��� ������� �������
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
				cout<< "������ �������"<<endl;
				break;

			case 2:
				cout << t.EmptyTree() << endl;
				break;

			case 3:			
				cout << "������� ����: ";
				cin >> key;
				cout << t.readObject(key, looked) << endl;
				break;
			
			case 4:
				cout << "������� ����: ";
				cin >> key;
				cout << "��������: ";
				cin >> tmp;
				cout << t.addNewIndex(key,tmp,looked) << endl;
				break;

			case 5:
				cout << "������� ����: ";
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
					cout << "�������� ������:" << endl;
					t.show_tree();
					cout << "������������� ������:" << endl;
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
				cout << "����� ��������: ";
				cin >> *it;
				break;

			case 27:	//�����
				isExit = true;
				break;

			case 28:
				cout << "������� �����������" << endl;
				cin >> nnn;
				test_rand(nnn);
				break;

			case 29:
				cout << "������� �����������" << endl;
				cin >> nnn;
				test_sort(nnn);
				break;

			default:	//������ �������, �� ��������������� �� ����� �������
				cout << "����������� �������" << endl;
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
