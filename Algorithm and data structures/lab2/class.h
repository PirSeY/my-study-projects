#pragma once

#include <exception>
#include <vector>

template <class Td, class Tk> class Tree
{
private:
	extern class Node;
	int length; //длина дерева
	Node *root;	//указатель на корень

protected:
	class Node
	{
	public:
		Tk key;//ключ объекта
		Td data;//значение объекта в элементе
		Node *left;// указатель на левого сына
		Node *right;//указатель на правого сына
			Node(Td d, Tk k){//конструктор с параметрами
				key = k;
				data = d;
				left = right = NULL;
		}

	};

public:
	Tree();//конструктор без параметров
	Tree(const Tree<Td, Tk>& anotherTree);//конструктор копирования
	~Tree(void);//деструктор
	int sizeOfTree();//опрос размера дерева
	void deleteTree();//очистка дерева
	bool EmptyTree();//проверка дерева на пустоту
	Td& readObject(Tk key, int& looked);//доступ к данным с заданным ключом
	bool addNewIndex(Tk key, Td obj, int& looked);//включение данных с заданным ключом
	bool deleteIndex(Tk key, int& looked);//удаление данных с заданным ключом
	void show_tree();//вывод структуры дерева на экран
    void go_LtR();//обход узлов дерева по схеме
	int lengthofThree();//определение длины внешнего пути дерева  (рекурсивно)
	
private:
	void CopyTree(Node *r);//вспомогательная функция для копирования дерева
	void ClearTree(Node *r);//вспомогательная функция для очистки дерева
	void Show(Node *r, int level);//вспомогательная функция для вывода структуры
	void countlev(Node *r, int level, int &sum);//вспомогательная функция для определения внешнего пути
	Node* BSTPredecessor(Node *x);//рекурсивный алгоритм поиска предыдущего по ключу узла
	Node* BSTSuccessor(Node *x);//рекурсивный алгоритм поиска следующего по ключу узла
	Node* Max(Node *t);//поиск максимального по ключу узла в поддереве 
	Node* RParent(Node *t,Node *x);//поиск ближайшего правого родителя для заданного узла дерева
	Node* Min(Node *t);//поиск минимального по ключу узла в поддереве 
	Node* LParent(Node *t,Node *x);//поиск ближайшего левого родителя для заданного узла дерева

public:
	class Iterator
	{
	private:
		Tree *ptr;//указатель на объект коллекции
		Node *cur;//указатель на текущий элемент коллекции
	public:
		Iterator(Tree<Td,Tk> &tree){//конструктор
			ptr = &tree;
			cur = NULL;
		}
		
		void beg(){//установка на первый
			cur = ptr->root;
			if (cur != NULL)
				while(cur->left != NULL) 
					cur = cur->left;
		}
		
		void end(){//установка на последний
			cur = ptr->root;
			if (cur != NULL)
				while(cur->right != NULL) 
					cur = cur->right;
		}
		
		void next(){//установка на следующий
			cur = ptr->BSTSuccessor(cur);
		}
		
		void prev(){//установка на предыдущий
			cur = ptr->BSTPredecessor(cur);
		}
		
		bool is_off() const{//проверка состояния итератора
			return (cur == NULL);
		}
		
		Td& operator*(){//доспуп к данным текущего элемента
			if (cur != NULL)
				return cur -> data;
			else
				throw exception("Итератор за пределами дерева");
		}
	};

	friend class Iterator;
};

	template<class Td, class Tk>
		Tree<Td,Tk>::Tree(void)//конструктор без параметров
	{
		length = 0;
		root = NULL; //в начале дерево пусто
	}

	template<class Td, class Tk>
		Tree<Td, Tk>::Tree(const Tree<Td, Tk>& anotherTree)//конструктор копирования
	{
		root = NULL;
		length = 0;
		CopyTree(anotherTree.root);
	}

	template<class Td, class Tk>
		void Tree<Td, Tk>::CopyTree(Node *r)//копирование дерева
	{
		if (r == NULL)
			return;
		int tmp;
		addNewIndex(r -> key, r -> data, tmp);
		CopyTree(r->left);
		CopyTree(r->right);
	}

	template<class Td, class Tk>
		Tree<Td, Tk>::~Tree(void)//деструктор
	{
		deleteTree();
	}

	template<class Td, class Tk>
		int Tree<Td, Tk>::sizeOfTree()//опрос размера дерева
	{
		return length;
	}

	template<class Td, class Tk>
		void Tree<Td, Tk>::deleteTree()//очистка дерева
	{
		ClearTree(root);
		///looked = length;
		root = NULL;
		length = 0;
	}

	template<class Td, class Tk>
		void Tree<Td, Tk>::ClearTree(Node *r)//очистка по обходу LtR дерева
	{
		if (r == NULL)
			return;
		ClearTree(r->left); 
		Node *rtree = r->right;
		delete r;
		ClearTree(rtree);
	}

	template<class Td, class Tk>
		bool Tree<Td, Tk>::EmptyTree()//проверка дерева на пустоту
	{
		return (length == 0 && root == NULL);
	}

	template<class Td, class Tk>
		Td& Tree<Td, Tk>::readObject(Tk key, int& looked)//доступ к данным с заданным ключом
	{
		looked = 0;
		Node* t = root;
		while(t != NULL && key != (t->key))//проход по дереву до задонного ключа
		{
			if(key < (t->key))//если ключ меньше
				t = t->left;//идем влево
			else
				t = t->right;//идем влево
			looked++;
		}
		if(t == NULL)//если ключа не существует
			throw exception("Данного ключа не существует");
		return t->data;
	}

	template<class Td, class Tk>
		bool Tree<Td, Tk>::addNewIndex(Tk key, Td obj, int& looked)//включение данных с заданным ключом
	{
		looked = 0;
		if(root == NULL){//добавление в начало
			root = new Node(obj, key);
			length++;
			return true;
		}

		Node *t = root, *pred = NULL;
		while(t != NULL){
			pred = t;
			looked++;
			if(key == (t->key))//если ключи совпадают
				return false;
			if(key < (t->key))//если ключ меньше 
				t = t->left;//добавляем влево
			else 
				t = t->right;//иначе добавляем вправо
		}

		if(key < (pred->key)) 
			pred->left = new Node(obj, key);
		else
			pred->right = new Node(obj, key);
		length++;
		return true;
	}

	template<class Td, class Tk>
		bool Tree<Td, Tk>::deleteIndex(Tk key, int& looked)//удаление данных с заданным ключом
	{
		Node *t = root, *pred = NULL, *next = NULL, *t0 = NULL;
		looked = 1;

		while(t != NULL && t->key != key){
			pred = t; //Запоминаем родителя удаляемого
			if(key < t->key) //если ключ меньше 
				t = t->left;//идем влево
			else 
				t = t->right;//идем вправо
			looked++;
		}

		if(t == NULL) //Удаляемый не найден
			return false;

		if(t->left != NULL && t->right != NULL){ //Оба потомка у удаляемого есть
			t0 = t;	//Запоминаем удаляемого
			pred = t;
			t = t->right;
			while(t->left != NULL){
				pred = t;
				t = t->left;
				looked++;
			}
			t0->key = t->key;
			t0->data = t->data;
			next = t->right;
		}
		else //Менее двух потомков у удаляемого
			if(t->left == NULL && t->right == NULL) //Нет потомков у удаляемого
				next = NULL;
			else 
				if(t->left == NULL) //Нет левого потомка у удаляемого
					next = t->right;
				else 
					if(t->right == NULL) //Нет правого потомка у удаляемого
						next = t->left;

		if(pred == NULL) //Нет родителя у удаляемого
			root = next;
		else
			if(t->key < pred->key)	//Удаляемый левым потомком pred
				pred->left = next;
			else					//Удаляемый правым потомком pred
				pred->right = next;

		delete t;
		length--;
		return true;
	}

	template <class Td,class Tk>
		void Tree<Td,Tk>::go_LtR()//обход структуры по LtR
	{   
		if (root == NULL)
			throw exception("Нет данных");

		Node *it = root;
		vector<Node*> up(length);
		int top = 0;
 
		while (it != NULL) {
				while (it != NULL) {
						if (it->right != NULL)
								up [top++] = it->right;

						up [top++] = it;
						it = it->left;
				}

				it = up [--top];

				while (top != 0 && it->right == NULL) {                      
				cout << it->key << "->";
						it = up [--top];
				}

				cout << it->key << "->";

				if (top == 0)
						break;

				it = up [--top];
		}
		cout << endl;
	}

	template <class Td,class Tk>
		void Tree<Td,Tk>::Show(typename Tree<Td,Tk>::Node *r, int level)//вспомогательная функция для вывода структуры
	{
		if(r == NULL) 
			return;
		Show(r->right, level+1);
		for(int i = 0; i <= 2*level; i++) 
			cout << " ";
		cout << r->key << endl;
		Show(r->left, level+1);
	}

	template<class Td, class Tk>
		void Tree<Td, Tk>::show_tree()//вывод структуры дерева на экран
	{
		if(root == NULL){
			return;
		}
		Show(root,0);
	}


	template<class Td, class Tk>
		int Tree<Td, Tk>::lengthofThree()//определение длины внешнего пути дерева 
	{
		if(root == NULL) 
			return -1;
		int sum = 0;
		countlev(root,1,sum);
		return sum;
	}

	template <class Td, class Tk>
		void Tree<Td,Tk>::countlev(Node *r, int level, int &sum)//вспомогательная функция для определения внешнего пути
	{
		if(r==NULL) 
			return;
		countlev(r->left, level+1, sum);
		countlev(r->right, level+1, sum);
		if(r->right == NULL || r->left == NULL)
			sum += level;
	}

	template <class Td,class Tk> typename Tree<Td,Tk>::Node* Tree<Td,Tk>::BSTSuccessor(typename Tree<Td,Tk>::Node *x)
	{
		if(x == NULL) 
			return NULL;
		if(x->right != NULL)
		{
			Node* t = x->right;
			while(t->left != NULL) 
				t = t->left;
			return t;
		}
		else 
			return LParent(root,x);
	}

template <class Td,class Tk> typename Tree<Td,Tk>::Node* Tree<Td,Tk>::LParent(typename Tree<Td,Tk>::Node *t,typename Tree<Td,Tk>::Node *x){
	if(t == x)
		return NULL;
	if(x->key < t->key){
		Node *rp = LParent(t->left, x);
		if(rp != NULL)
			return rp;
		else 
			return t;
	}
	else 
		return LParent(t->right, x);
}

template <class Td,class Tk> typename Tree<Td,Tk>::Node* Tree<Td,Tk>::BSTPredecessor(typename Tree<Td,Tk>::Node *x){
	if(x == NULL) 
		return NULL;
	if(x->left != NULL)
	{
		Node* t = x->left;
		while(t->right != NULL) 
			t = t->right;
		return t;
	}
	else 
		return RParent(root,x);
}

template <class Td,class Tk> typename Tree<Td,Tk>::Node* Tree<Td,Tk>::RParent(typename Tree<Td,Tk>::Node *t,typename Tree<Td,Tk>::Node *x){
	if(t == x) 
		return NULL;
	if(x->key > t->key){
		Node *rp = RParent(t->right, x);
		if(rp != NULL) 
			return rp;
		else 
			return t;
	}
	else 
		return RParent(t->left, x);
}
