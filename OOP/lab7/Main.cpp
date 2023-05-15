#include <cstring>
#include <iostream>
#include "Prstr.h"
#include "Class_Tree.h"

#pragma warning(disable : 4996)

using namespace std;

void test_tree_int() {

	Tree<int> b;
	Tree<int>* a = NULL;

	int* A = new int[5];
	A[1] = 1;
	A[2] = -2;
	A[3] = 23;
	A[4] = 11;
	A[5] = 12;

	for (int i = 1; i <= 5; i++) {

		b.add(A[i], a);
	}
	b.print(a);
	b.delete_tree(a);
}


void test_tree_float() {

	Tree<float> b;
	Tree<float>* a = NULL;

	float* A = new float[5];
	A[1] = -1.1;
	A[2] = -2.2;
	A[3] = 1.23;
	A[4] = 11.0;
	A[5] = 0.12;

	for (int i = 1; i <= 5; i++) {

		b.add(A[i], a);
	}
	b.print(a);
	b.delete_tree(a);
}


void test_tree_Prstr() {

	Tree<int**> b;
	Tree<int**>* a = NULL;

	Prstr* strngs = new Prstr[5];
	Prstr* pt = strngs;
	pt[1].setpp("abc");
	pt[2].setpp("");
	pt[3].setpp("abc");
	pt[4].setpp(" ");
	pt[5].setpp("qwerty");



	for (int i = 1; i <= 5; i++) {

		int** pp = (int**)&pt[i];
		b.add(pp, a);
	}
	b.print(a);
	b.delete_tree(a);
}


int main() {

	test_tree_Prstr();
	cout << endl << endl;
	test_tree_float();
	cout << endl << endl;
	test_tree_int();
	cout << endl << endl;
}