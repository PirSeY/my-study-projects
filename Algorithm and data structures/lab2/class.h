#pragma once

#include <exception>
#include <vector>

template <class Td, class Tk> class Tree
{
private:
	extern class Node;
	int length; //����� ������
	Node *root;	//��������� �� ������

protected:
	class Node
	{
	public:
		Tk key;//���� �������
		Td data;//�������� ������� � ��������
		Node *left;// ��������� �� ������ ����
		Node *right;//��������� �� ������� ����
			Node(Td d, Tk k){//����������� � �����������
				key = k;
				data = d;
				left = right = NULL;
		}

	};

public:
	Tree();//����������� ��� ����������
	Tree(const Tree<Td, Tk>& anotherTree);//����������� �����������
	~Tree(void);//����������
	int sizeOfTree();//����� ������� ������
	void deleteTree();//������� ������
	bool EmptyTree();//�������� ������ �� �������
	Td& readObject(Tk key, int& looked);//������ � ������ � �������� ������
	bool addNewIndex(Tk key, Td obj, int& looked);//��������� ������ � �������� ������
	bool deleteIndex(Tk key, int& looked);//�������� ������ � �������� ������
	void show_tree();//����� ��������� ������ �� �����
    void go_LtR();//����� ����� ������ �� �����
	int lengthofThree();//����������� ����� �������� ���� ������  (����������)
	
private:
	void CopyTree(Node *r);//��������������� ������� ��� ����������� ������
	void ClearTree(Node *r);//��������������� ������� ��� ������� ������
	void Show(Node *r, int level);//��������������� ������� ��� ������ ���������
	void countlev(Node *r, int level, int &sum);//��������������� ������� ��� ����������� �������� ����
	Node* BSTPredecessor(Node *x);//����������� �������� ������ ����������� �� ����� ����
	Node* BSTSuccessor(Node *x);//����������� �������� ������ ���������� �� ����� ����
	Node* Max(Node *t);//����� ������������� �� ����� ���� � ��������� 
	Node* RParent(Node *t,Node *x);//����� ���������� ������� �������� ��� ��������� ���� ������
	Node* Min(Node *t);//����� ������������ �� ����� ���� � ��������� 
	Node* LParent(Node *t,Node *x);//����� ���������� ������ �������� ��� ��������� ���� ������

public:
	class Iterator
	{
	private:
		Tree *ptr;//��������� �� ������ ���������
		Node *cur;//��������� �� ������� ������� ���������
	public:
		Iterator(Tree<Td,Tk> &tree){//�����������
			ptr = &tree;
			cur = NULL;
		}
		
		void beg(){//��������� �� ������
			cur = ptr->root;
			if (cur != NULL)
				while(cur->left != NULL) 
					cur = cur->left;
		}
		
		void end(){//��������� �� ���������
			cur = ptr->root;
			if (cur != NULL)
				while(cur->right != NULL) 
					cur = cur->right;
		}
		
		void next(){//��������� �� ���������
			cur = ptr->BSTSuccessor(cur);
		}
		
		void prev(){//��������� �� ����������
			cur = ptr->BSTPredecessor(cur);
		}
		
		bool is_off() const{//�������� ��������� ���������
			return (cur == NULL);
		}
		
		Td& operator*(){//������ � ������ �������� ��������
			if (cur != NULL)
				return cur -> data;
			else
				throw exception("�������� �� ��������� ������");
		}
	};

	friend class Iterator;
};

	template<class Td, class Tk>
		Tree<Td,Tk>::Tree(void)//����������� ��� ����������
	{
		length = 0;
		root = NULL; //� ������ ������ �����
	}

	template<class Td, class Tk>
		Tree<Td, Tk>::Tree(const Tree<Td, Tk>& anotherTree)//����������� �����������
	{
		root = NULL;
		length = 0;
		CopyTree(anotherTree.root);
	}

	template<class Td, class Tk>
		void Tree<Td, Tk>::CopyTree(Node *r)//����������� ������
	{
		if (r == NULL)
			return;
		int tmp;
		addNewIndex(r -> key, r -> data, tmp);
		CopyTree(r->left);
		CopyTree(r->right);
	}

	template<class Td, class Tk>
		Tree<Td, Tk>::~Tree(void)//����������
	{
		deleteTree();
	}

	template<class Td, class Tk>
		int Tree<Td, Tk>::sizeOfTree()//����� ������� ������
	{
		return length;
	}

	template<class Td, class Tk>
		void Tree<Td, Tk>::deleteTree()//������� ������
	{
		ClearTree(root);
		///looked = length;
		root = NULL;
		length = 0;
	}

	template<class Td, class Tk>
		void Tree<Td, Tk>::ClearTree(Node *r)//������� �� ������ LtR ������
	{
		if (r == NULL)
			return;
		ClearTree(r->left); 
		Node *rtree = r->right;
		delete r;
		ClearTree(rtree);
	}

	template<class Td, class Tk>
		bool Tree<Td, Tk>::EmptyTree()//�������� ������ �� �������
	{
		return (length == 0 && root == NULL);
	}

	template<class Td, class Tk>
		Td& Tree<Td, Tk>::readObject(Tk key, int& looked)//������ � ������ � �������� ������
	{
		looked = 0;
		Node* t = root;
		while(t != NULL && key != (t->key))//������ �� ������ �� ��������� �����
		{
			if(key < (t->key))//���� ���� ������
				t = t->left;//���� �����
			else
				t = t->right;//���� �����
			looked++;
		}
		if(t == NULL)//���� ����� �� ����������
			throw exception("������� ����� �� ����������");
		return t->data;
	}

	template<class Td, class Tk>
		bool Tree<Td, Tk>::addNewIndex(Tk key, Td obj, int& looked)//��������� ������ � �������� ������
	{
		looked = 0;
		if(root == NULL){//���������� � ������
			root = new Node(obj, key);
			length++;
			return true;
		}

		Node *t = root, *pred = NULL;
		while(t != NULL){
			pred = t;
			looked++;
			if(key == (t->key))//���� ����� ���������
				return false;
			if(key < (t->key))//���� ���� ������ 
				t = t->left;//��������� �����
			else 
				t = t->right;//����� ��������� ������
		}

		if(key < (pred->key)) 
			pred->left = new Node(obj, key);
		else
			pred->right = new Node(obj, key);
		length++;
		return true;
	}

	template<class Td, class Tk>
		bool Tree<Td, Tk>::deleteIndex(Tk key, int& looked)//�������� ������ � �������� ������
	{
		Node *t = root, *pred = NULL, *next = NULL, *t0 = NULL;
		looked = 1;

		while(t != NULL && t->key != key){
			pred = t; //���������� �������� ����������
			if(key < t->key) //���� ���� ������ 
				t = t->left;//���� �����
			else 
				t = t->right;//���� ������
			looked++;
		}

		if(t == NULL) //��������� �� ������
			return false;

		if(t->left != NULL && t->right != NULL){ //��� ������� � ���������� ����
			t0 = t;	//���������� ����������
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
		else //����� ���� �������� � ����������
			if(t->left == NULL && t->right == NULL) //��� �������� � ����������
				next = NULL;
			else 
				if(t->left == NULL) //��� ������ ������� � ����������
					next = t->right;
				else 
					if(t->right == NULL) //��� ������� ������� � ����������
						next = t->left;

		if(pred == NULL) //��� �������� � ����������
			root = next;
		else
			if(t->key < pred->key)	//��������� ����� �������� pred
				pred->left = next;
			else					//��������� ������ �������� pred
				pred->right = next;

		delete t;
		length--;
		return true;
	}

	template <class Td,class Tk>
		void Tree<Td,Tk>::go_LtR()//����� ��������� �� LtR
	{   
		if (root == NULL)
			throw exception("��� ������");

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
		void Tree<Td,Tk>::Show(typename Tree<Td,Tk>::Node *r, int level)//��������������� ������� ��� ������ ���������
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
		void Tree<Td, Tk>::show_tree()//����� ��������� ������ �� �����
	{
		if(root == NULL){
			return;
		}
		Show(root,0);
	}


	template<class Td, class Tk>
		int Tree<Td, Tk>::lengthofThree()//����������� ����� �������� ���� ������ 
	{
		if(root == NULL) 
			return -1;
		int sum = 0;
		countlev(root,1,sum);
		return sum;
	}

	template <class Td, class Tk>
		void Tree<Td,Tk>::countlev(Node *r, int level, int &sum)//��������������� ������� ��� ����������� �������� ����
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
