#include<set>
#include<queue>
#include<iostream>
#include<time.h>
#include<iterator>
#include"Prstr.h"

using namespace std;

void test_queue_add() {

	Prstr* a = new Prstr[1000];
	Prstr* pp = a;
	for (int i = 0; i < 1000; i++) {

		pp[i] = "qwerty";
	}

	queue<Prstr> q;

	clock_t time_funk = clock();

	for (int i = 0; i < 1000; i++) {

		q.push(pp[i]);
	}

	time_funk = clock() - time_funk;
	cout << "time of add Prstr's objects in queue: " << (double)time_funk / CLOCKS_PER_SEC << endl;
}


void test_queue_out() {

	Prstr* a = new Prstr[1000];
	Prstr* pp = a;
	for (int i = 0; i < 1000; i++) {

		pp[i] = "qwerty";
	}

	queue<Prstr> q;

	clock_t time_funk = clock();

	while(!q.empty()) {

		q.front();
		q.pop();
	}

	cout << endl;
	time_funk = clock() - time_funk;
	cout << "time of delete Prstr's objects from queue: " << (double)time_funk / CLOCKS_PER_SEC << endl;
}


void test_set_add() {

	Prstr* a = new Prstr[1000];
	Prstr* pp = a;
	for (int i = 0; i < 1000; i++) {

		pp[i] = "qwerty" + i;
	}

	multiset<int> q;
	

	clock_t time_funk = clock();

	for (int i = 0; i < 1000; i++) {

		q.insert(pp[i].getpp());
	}

	cout << endl;
	time_funk = clock() - time_funk;
	cout << "time of add Prstr's objects in set: " << (double)time_funk / CLOCKS_PER_SEC << endl;
}


void test_set_search() {

	Prstr* a = new Prstr[1000];
	Prstr* pp = a;
	for (int i = 0; i < 1000; i++) {

		pp[i] = "qwerty" + i;
	}

	multiset<int> q;

	clock_t time_funk = clock();

	auto result = q.find(26);

	cout << endl;
	time_funk = clock() - time_funk;
	cout << "time of search Prstr's objects in set: " << (double)time_funk / CLOCKS_PER_SEC << endl;
}


void test_set_delete() {

	Prstr* a = new Prstr[1000];
	Prstr* pp = a;
	for (int i = 0; i < 1000; i++) {

		pp[i] = "qwerty" + i;
	}

	multiset<int> q;


	clock_t time_funk = clock();

	for (int i = 0; i < 1000; i++) {

		q.clear();
	}

	cout << endl;
	time_funk = clock() - time_funk;
	cout << "time of delete Prstr's objects from set: " << (double)time_funk / CLOCKS_PER_SEC << endl;
}



int main() {

	test_queue_add();
	test_queue_out();
	test_set_add();
	test_set_search();
	test_set_delete();
}