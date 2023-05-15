#pragma once
#include "Prstr.h"
#include<iostream>
#include <string> 
#include <sstream>

using namespace std;

class Tree : public Prstr{
public:

	bool add_tree_class(Prstr& other, Tree*& aBranch) {

		try {

			if (&other == NULL) { throw ErrorException("func(add_tree_class) hasn't been complited "); }

			if (!aBranch) {

				aBranch = new Tree;
				aBranch->field = &other;
				aBranch->left = 0;
				aBranch->right = 0;
				return true;
			}
			else {

				if (aBranch->field > & other) {

					Tree::add_tree_class(other, aBranch->left);
				}
				else {

					Tree::add_tree_class(other, aBranch->right);
				}
			}
			return true;
		}
		catch (ErrorException& exception) { 
			
			std::cerr << "Error: " << exception.getError() << std::endl << "_______________" << std::endl; 
			return false;
		}
	}


	void print_tree_class(Tree*& aBranch) {

		if (!aBranch) return;
		tabs++;

		Tree::print_tree_class(aBranch->left);

		for (int i = 0; i < tabs; i++) cout << " ";

		cout<<aBranch->field->getpp();

		Tree::print_tree_class(aBranch->right);

		tabs--;
	}


	void delete_tree_class(Tree*& aBranch) {

		if (!aBranch) return;
		Tree::delete_tree_class(aBranch->left);
		Tree::delete_tree_class(aBranch->right);
		delete aBranch;
		return;
	}


	char* getpp() override;

protected:

	Prstr* field;
	Tree* left;
	Tree* right;
	int tabs = 0;
};

char* Tree::getpp() {

	char* pt = new char[strlen(pp)];
	strcpy(pt, pp);
	return pt;
}