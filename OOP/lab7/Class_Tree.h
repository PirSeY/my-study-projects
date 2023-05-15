#pragma once
#pragma warning(disable : 4996)
#include <cstring>
#include <iostream>
#include <fstream>

using namespace std;

template<typename T>
class Tree {
public:

	Tree() {}

	Tree(T a) { field = 0; left = 0; right = 0; }

	void add(T other, Tree*& pp);

	void print(Tree*& pp);

	void delete_tree(Tree*& pp);

protected:

	T field;
	Tree* left;
	Tree* right;
	int tabs = 0;
};


template<typename T>
inline void Tree<T>::add(T other, Tree*& pp) {

	if (!pp) {

		pp = new Tree<T>;
		pp->field = other;
		pp->left = 0;
		pp->right = 0;
		return;
	}
	else

		if (pp->field > other) {

			add(other, pp->left);
		}
		else {

			add(other, pp->right);
		}
}


template<typename T>
inline void Tree<T>::print(Tree*& pp) {

	if (!pp) return;
	tabs++;


	print(pp->left);

	for (int i = 0; i < tabs; i++) cout << " ";
	cout << pp->field << endl;

	print(pp->right);

	tabs--;
}


template<typename T>
inline void Tree<T>::delete_tree(Tree*& pp) {

	if (!pp) return;
	Tree::delete_tree(pp->left);
	Tree::delete_tree(pp->right);
	delete pp;
	return;
}