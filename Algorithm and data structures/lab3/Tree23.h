#include <iostream>
#include <string>
using namespace std;

class TreeException
{
	string code;
public:
	TreeException()
	{
		code = "����������";
	}
	string What()
	{
		return code;
	}
};

template<class K, class T>
class T23
{
	class Node	//����������� ����� "����"
	{
	public:
		virtual bool type() = 0;	//��� ����
		virtual void Show(int level) = 0;	//����������
	};
	class Leaf : public Node  //����
	{
	public:
		K key; // �������� �����
		T data; // ������
		bool type() { return 0; }
		void Show(int level)
		{
			for (int i = 0; i < 6 * level; i++) cout << " ";
			cout << key << endl;
		}
		Leaf(K _key, T _data) { key = _key; data = _data; }
	};
	class Internal : public Node	//���������� ���� 
	{
	public:
		Node *son1, *son2, *son3; // ��������� �� ������� 
		K low2, low3; // ��������� ���������� ������ �� 2 � 3 ����������� 
		bool type() { return 1; }
		Internal()  //����������� "�����������" ������
		{
			son1 = son2 = son3 = NULL;
			low2 = low3 = INT_MAX;
		}
		void Show(int level)
		{
			if (son3 != NULL)
				son3->Show(level + 1);
			if (son2 != NULL)
				son2->Show(level + 1);
			for (int i = 0; i < 6 * level; i++) cout << " ";
			if (son2 == NULL)
				cout << "-";
			else
				cout << low2;
			if (son3 == NULL)
				cout << "," << "-";
			else
				cout << "," << low3;
			cout << endl;
			son1->Show(level + 1);
		}
	};
	Internal* root; //��������� �� ������
	int size; //������� ������ ������
	void _Clear(Internal*); //����������� ������� ������
	bool _Insert(Node*, Node*, Node*&, K&); //����������� ������� �������
	bool _Delete(Internal*, K, Leaf*&, bool &one_sone); //����������� ������� ��������
	T _GetData(Internal*, K); //����������� ������� ������
	void _Copy(Internal*);
	//Leaf* _FindMin(Internal* t);  //����� ���. �����
	//Leaf* _FindMax(Internal *t);   //����� ����. �����
	int cnt; //������� ���������� ������������� ��������� ����� ������
public:
	T23();  //�����������
	T23(T23<K, T>& t); //����������� �����������
	~T23(); //����������
	int GetSize();       //����� ������� ������
	void Clear();     //������� ������
	bool IsEmpty();     //�������� ������ �� �������
	bool Insert(K, T); //��������� ������ �������� � �������� ������
	bool Delete(K);   //�������� �������� � �������� ������
	T GetData(K);    //����� �������� � �������� ������
	void Show();
	int getCountNodesView()
	{
		int temp = cnt;
		cnt = 0;
		return temp;
	}
	class Iterator
	{
	public:
		Iterator(T23<K, T>* owner);
		void beg();
		void end();
		void next();
		void prev();
		bool IsOff();
		bool operator++(int); // �������� �������� � ���������� �� ����� ���� � ������
		bool operator--(int); // �������� �������� � ����������� �� ����� ���� � ������
		bool operator==(Leaf* node); // �������� ��������� ���������� ����������
		bool operator!=(Leaf* node); // �������� ����������� ���������� ����������
		T& operator*();
	private:
		T23<K, T>* tree;
		Leaf* cur;
		Leaf* _FindMin(Internal* t);  //����� ���. �����
		Leaf* _FindMax(Internal *t);   //����� ����. �����
		void _Next(Internal *t); //����������� ������� �������� � ���������� �����
		void _Prev(Internal *t);	//� �����������
	};

	class rIterator
	{
	public:
		rIterator(T23<K, T>* owner);
		void beg();
		void end();
		void next();
		void prev();
		bool IsOff();
		bool operator++(int); // �������� �������� � ���������� �� ����� ���� � ������
		bool operator--(int); // �������� �������� � ����������� �� ����� ���� � ������
		bool operator==(Leaf* node); // �������� ��������� ���������� ����������
		bool operator!=(Leaf* node); // �������� ����������� ���������� ����������
		T& operator*();
	private:
		T23<K, T>* tree;
		Leaf* cur;
		Leaf* _FindMin(Internal* t);  //����� ���. �����
		Leaf* _FindMax(Internal *t);   //����� ����. �����
		void _Next(Internal *t); //����������� ������� �������� � ���������� �����
		void _Prev(Internal *t);	//� �����������
	};
};

template<class K, class T>
T23<K, T>::T23()
{
	root = NULL; //��������� �� ������ ������
	cnt = size = 0; //����� �������� � ������� ������ � 0
}

template<class K, class T>
T23<K, T>::T23(T23<K, T>& t)
{
	root = NULL; //��������� �� ������ ������
	cnt = size = 0; //����� �������� � ������� ������ � 0
	_Copy(t.root);
}

template<class K, class T> T23<K, T>::~T23() { Clear(); }
template<class K, class T> int T23<K, T>::GetSize() { return size; } //����� ������� ������

template<class K, class T>
void T23<K, T>::Clear() //������� ������� ������
{
	_Clear(root);  //����� ������� ����������� ������� ������
	delete root;    //������� ������
	root = NULL;    //�������� ��������� �� ������ � NULL
	size = 0;     //������ ������ 0
}

template<class K, class T>
void T23<K, T>::_Clear(Internal *t)  //������� ����������� ������� ������
{
	if (t == NULL) return; //���� ������ � ��� ������
	if (t->son1->type() == 0)
	{
		if (t->son1) delete t->son1; //�������� 1-�� �����
		if (t->son2) delete t->son2; //�������� 2-�� �����
		if (t->son3) delete t->son3; //�������� 3-��� �����
		return;
	}
	_Clear(((Internal*)t->son1)); //����  ������� �� 1-�� ��������� 
	delete t->son1; //�������� 1-�� ���������
	_Clear(((Internal*)t->son2)); //���� ������� �� 2-�� ���������
	delete t->son2; //�������� 2-�� ��������� 
	if (t->son3) //���� ������� �� 3-�� ���������
	{
		_Clear(((Internal*)t->son3));
		delete t->son3; //�������� 3-�� ���������
	}
}

template<class K, class T>
void T23<K, T>::_Copy(Internal *t)
{
	if (t == NULL) return;
	if (t->son1->type() == 0)
	{
		if (t->son1) Insert(t->son1->key, t->son1->data);
		if (t->son2) Insert(t->son2->key, t->son2->data);
		if (t->son3) Insert(t->son3->key, t->son3->data);
		return;
	}
	_Copy(((Internal*)t->son1, t));
	Insert(t->son1->key, t->son1->data);
	_Copy(((Internal*)t->son2, t));
	Insert(t->son2->key, t->son2->data);
	if (t->son3)
	{
		_Copy(((Internal*)t->son3, t));
		Insert(t->son3->key, t->son3->data);
	}
}

template<class K, class T>
bool T23<K, T>::IsEmpty() //������� �������� ������ �� �������
{
	return (size == 0);
}

template<class K, class T>
void T23<K, T>::Show() //������� ���������� ������
{
	if (IsEmpty())
		return;
	root->Show(0);
}

template<class K, class T>
bool T23<K, T>::Insert(K k, T data) //������� ������� � ������
{
	Node *lt = new Leaf(k, data);  //������� ������
	if (root == NULL)      //���� ������ ������
	{
		root = new Internal;   //������� ������
		root->son1 = lt;  //������� ������
		root->son2 = root->son3 = NULL;
		size++; //��������� ������� ������� ������

		return true;
	}
	if (root->son2 == NULL)
	{
		if (((Leaf*)root->son1)->key < k)
		{
			root->son2 = lt;
			root->low2 = k;
			size++; //��������� ������� ������� ������
			return true;
		}
		else
		{
			if (((Leaf*)root->son1)->key > k)
			{
				root->son2 = root->son1;
				root->low2 = ((Leaf*)root->son1)->key;
				root->son1 = lt;
				size++; //��������� ������� ������� ������

				return true;
			}
			else
			{
				delete lt;
				return false;
			}
		}

	}
	Node *tbk = new Internal;
	K lbk;
	bool inserted = _Insert(root, lt, tbk, lbk); //����� ������� ����������� ������� � ������
	if (inserted == false)
	{
		delete lt;
		return false;
	}
	if (tbk != NULL) //���� ��������� ����� ��������� (��������� �����������)
	{
		Node *temp;
		temp = root; //�� ��������� �������� ������,
		root = new Internal;   //������� ������
		root->son1 = temp;	//1-�� ����� �������� ����� ������ "�������" ������,
		root->son2 = tbk;    //� 2-�� ����� ����� "�����" ���������
		root->low2 = lbk;
		root->son3 = NULL;

	}
	return true;
}

template<class K, class T>
bool T23<K, T>::_Insert(Node *t, Node *lt, Node *&tup, K &lup) //������� ����������� ������� � ������
{
	cnt++;
	int child = 0;
	tup = NULL;
	if (t->type() == 0)
	{
		if (((Leaf*)t)->key == ((Leaf*)lt)->key)
			return false;
		else
		{
			tup = lt;
			if ((((Leaf*)t)->key) < (((Leaf*)lt)->key)) lup = ((Leaf*)lt)->key;
			else
			{
				lup = ((Leaf*)t)->key;
				K temp1;
				T temp2;
				temp1 = ((Leaf*)t)->key;
				((Leaf*)t)->key = ((Leaf*)lt)->key;
				((Leaf*)lt)->key = temp1;
				temp2 = ((Leaf*)t)->data;
				((Leaf*)t)->data = ((Leaf*)lt)->data;
				((Leaf*)lt)->data = temp2;
			}
		}
		size++;
		return true;
	}
	Node *w;
	if ((((Leaf*)lt)->key) < (((Internal*)t)->low2))
	{
		child = 1;
		w = ((Internal*)t)->son1;
	}
	else
	{
		if ((((Internal*)t)->son3 == NULL) || (((((Internal*)t)->son3) != NULL) & (((Leaf*)lt)->key < ((Internal*)t)->low3)))
		{
			child = 2;
			w = ((Internal*)t)->son2;
		}
		else
		{
			child = 3;
			w = ((Internal*)t)->son3;
		}
	}
	K lbk;
	Node *tbk = new Internal;
	bool inserted = _Insert(w, lt, tbk, lbk);

	if (inserted == true)
	{
		if (tbk != NULL)
		{
			if (((Internal*)t)->son3 == NULL)
			{
				if (child == 2)
				{
					((Internal*)t)->son3 = tbk;
					((Internal*)t)->low3 = lbk;
				}
				else
				{
					((Internal*)t)->son3 = ((Internal*)t)->son2;
					((Internal*)t)->low3 = ((Internal*)t)->low2;
					((Internal*)t)->son2 = tbk;
					((Internal*)t)->low2 = lbk;
				}
			}
			else
			{
				cnt++;
				tup = new Internal;
				if (child == 3)
				{
					((Internal*)tup)->son1 = ((Internal*)t)->son3;
					((Internal*)tup)->son2 = tbk;
					((Internal*)tup)->son3 = NULL;
					((Internal*)tup)->low2 = lbk;
					((Internal*)t)->son3 = NULL;
					lup = ((Internal*)t)->low3;
				}
				else
				{
					((Internal*)tup)->son2 = ((Internal*)t)->son3;
					((Internal*)tup)->low2 = ((Internal*)t)->low3;
					((Internal*)tup)->son3 = NULL;
					if (child == 2)
					{
						((Internal*)tup)->son1 = tbk;
						lup = lbk;
					}
					if (child == 1)
					{
						((Internal*)tup)->son1 = ((Internal*)t)->son2;
						((Internal*)t)->son2 = tbk;
						lup = ((Internal*)t)->low2;
						((Internal*)t)->low2 = lbk;
					}
				}
				((Internal*)t)->son3 = NULL;
			}
		}

	}
	return inserted;
}

template<class K, class T>
bool T23<K, T>::Delete(K k) // ������� �������� 
{
	Internal *t;
	Leaf *tmin;
	bool one;
	int fl = size;
	if (root == NULL)
		return false;
	if (root->son2 == NULL)
	{
		if (((Leaf*)root->son1)->key == k)
		{
			delete root->son1;
			root->son1 = NULL;
			delete root;
			root = NULL;
			size = 0;
			return true;
		}

		else
		{
			return false;
		}
	}
	bool deleted;
	deleted = _Delete(root, k, tmin, one);
	if (deleted == true)
	{
		if (one == true)
		{
			if (root->son1->type() == 1)
			{
				t = ((Internal*)root->son1);
				delete root;
				root = t;
			}
		}
	}
	return deleted;
}

template<class K, class T>
bool T23<K, T>::_Delete(Internal *t, K k, Leaf *&tlow1, bool &one_son) //������� ������������ �������� �� ������
{
	Internal *w, *y, *z;
	int child;
	cnt++;
	tlow1 = NULL;
	one_son = false;
	if (t->son1->type() == 0)
	{
		if (((Leaf*)t->son1)->key == k)
		{
			delete t->son1;
			t->son1 = t->son2;
			t->son2 = t->son3;
			t->son3 = NULL;
			t->low2 = t->low3;
			t->low3 = INT_MAX;
			size--;
		}

		else
		{
			if (((Leaf*)t->son2)->key == k)
			{
				delete t->son2;
				t->son2 = t->son3;
				t->son3 = NULL;
				t->low2 = t->low3;
				t->low3 = INT_MAX;
				size--;
			}
			else
			{
				if ((t->son3 != NULL) && (((Leaf*)t->son3)->key == k))
				{
					delete t->son3; ;
					t->son3 = NULL;
					size--;
				}
				else
				{
					return false;
				}
			}
		}
		tlow1 = ((Leaf*)t->son1);
		if (t->son2 == NULL)
		{
			one_son = true;
		}
		return true;
	}
	if (k < t->low2)
	{
		child = 1;
		w = ((Internal*)t->son1);
	}
	else
	{
		if ((t->son3 == NULL) || (k < t->low3))
		{
			child = 2;
			w = ((Internal*)t->son2);
		}
		else
		{
			child = 3;
			w = ((Internal*)t->son3);
		}
	}
	bool one_son_bk;
	Leaf *tlow1_bk;
	if ((_Delete(w, k, tlow1_bk, one_son_bk)) == false)
	{
		return false;
	}

	tlow1 = tlow1_bk;
	//one_son=false;
	if (tlow1_bk != NULL)
	{
		if (child == 2)
		{
			t->low2 = ((Leaf*)tlow1_bk)->key;
			tlow1 = NULL;
		}
		if (child == 3)
		{
			t->low3 = ((Leaf*)tlow1_bk)->key;
			tlow1 = NULL;
		}
	}
	if (one_son_bk == false)
		return true;
	if (child == 1)
	{
		y = ((Internal*)t->son2);
		if (y->son3 != NULL)
		{
			w->son2 = y->son1;
			w->low2 = t->low2;
			t->low2 = y->low2;
			y->son1 = y->son2;
			y->son2 = y->son3;
			y->low2 = y->low3;
			y->son3 = NULL;
			y->low3 = INT_MAX;
		}
		else
		{
			y->son3 = y->son2;
			y->low3 = y->low2;
			y->son2 = y->son1;
			y->low2 = t->low2;
			y->son1 = w->son1;
			delete w;
			t->son1 = t->son2;
			t->son2 = t->son3;
			t->low2 = t->low3;
			t->son3 = NULL;
			t->low3 = INT_MAX;
			//one_son=true; 
			if (t->son2 == NULL)
			{
				one_son = true;
			}
		}
		return true;
	}
	if (child == 2)
	{
		y = ((Internal*)t->son1);
		if (y->son3 != NULL)
		{
			w->son2 = w->son1;
			w->low2 = t->low2;
			w->son1 = y->son3;
			y->son3 = NULL;
			t->low2 = y->low3;
			y->low3 = INT_MAX;
			//one_son=false;
			return true;
		}
		else
		{
			z = ((Internal*)t->son3);
			if ((z != NULL) && (z->son3 != NULL))
			{
				w->son2 = z->son1;
				w->low2 = t->low3;
				t->low3 = z->low2;
				z->son1 = z->son2;
				z->son2 = z->son3;
				z->low2 = z->low3;
				z->son3 = NULL;
				z->low3 = INT_MAX;
				//one_son=false;
				return true;
			}
		}
		y->son3 = w->son1;
		y->low3 = t->low2;
		delete w;
		t->son2 = t->son3;
		t->low2 = t->low3;
		t->son3 = NULL;
		t->low3 = INT_MAX;
		if (t->son2 == NULL)
		{
			one_son = true;
		}
		return true;
	}
	y = ((Internal*)t->son2);
	if (y->son3 != NULL)
	{
		w->son2 = w->son1;
		w->low2 = t->low3;
		w->son1 = y->son3;
		t->low3 = y->low3;
		y->son3 = NULL;
		y->low3 = INT_MAX;
	}
	else
	{
		y->son3 = w->son1;
		y->low3 = t->low3;
		t->son3 = NULL;
		t->low3 = INT_MAX;
		delete w;
	}
	return true;
}

template<class K, class T>
T T23<K, T>::GetData(K k) //����� ����� � �������� ������
{
	return _GetData(root, k);
}

template<class K, class T>
T T23<K, T>::_GetData(Internal *t, K k) //����������� ������� ������ ����� � �������� ������
{
	cnt++;
	if (t == NULL)
		throw TreeException(); //���� ������ ������
	if (t->son1->type() == 0)
	{
		if (((Leaf *)t->son1)->key == k)
			return ((Leaf *)t->son1)->data;
		if (t->son2)
			if (((Leaf *)t->son2)->key == k)
				return ((Leaf *)t->son2)->data;
		if (t->son3)
			if (((Leaf *)t->son3)->key == k)
				return ((Leaf *)t->son3)->data;
		throw TreeException();
	}
	if (t->low2 > k)
		return _GetData(((Internal *)t->son1), k); //����� � 1-�� ���������
	if (t->low3 > k)
		return _GetData(((Internal *)t->son2), k); //����� �� 2-�� ���������
	return _GetData(((Internal *)t->son3), k); //����� � 3-�� ���������
}

template <class K, class T>
T23<K, T>::Iterator::Iterator(T23<K, T>* t)  //����������� 
{
	tree = t;
	if (tree)
	{
		if (tree->root)
		{
			cur = _FindMin(tree->root);
		}
		else { cur = NULL; }
	}
	else { cur = NULL; }
}
template <class K, class T>
void T23<K, T>::Iterator::beg() //��������� �� ������ ���� � ������ (� ���. ������)
{
	if (tree->root != 0)
	{
		cur = _FindMin(tree->root);
	}
}
template <class K, class T>
void T23<K, T>::Iterator::end() //��������� �� ��������� ���� � ������ (� ����. ������)
{
	if (tree->root != 0)
	{
		cur = _FindMax(tree->root);
	}
}

template <class K, class T>
void T23<K, T>::Iterator::next()   //������� � ���������� ����� 
{
	if (tree->root)
	{
		_Next(tree->root);
	}
}

template <class K, class T>
void T23<K, T>::Iterator::prev()  //������� � ����������� �����
{
	if (tree->root)
	{
		_Prev(tree->root);
	}
}

template <class K, class T>
bool T23<K, T>::Iterator::IsOff()  //�������� ��������� ���������
{
	return (cur == 0);
}

template <class K, class T>
bool T23<K, T>::Iterator::operator++(int)
{
	if (tree->root)
	{
		_Next(tree->root);
		return true;
	}
	return false;
}

template <class K, class T>
bool T23<K, T>::Iterator::operator--(int)
{
	if (tree->root)
	{
		_Prev(tree->root);
		return true;
	}
	return false;
}

template <class K, class T>
bool T23<K, T>::Iterator::operator==(Leaf* node)
{
	return cur == node;
}

template <class K, class T>
bool T23<K, T>::Iterator::operator!=(Leaf* node)
{
	return cur != node;
}

template <class K, class T>
T& T23<K, T>::Iterator::operator*()  //������ �� ������ � ������ � �������� ����
{
	if (!cur) throw TreeException();
	return cur->data;
}

template <class K, class T>
typename T23<K, T>::Leaf* T23<K, T>::Iterator::_FindMin(Internal* t)  //����� ���. �����
{
	if (t == NULL) return NULL;
	if ((t->son1->type() == 0))
	{
		return ((Leaf*)t->son1);
	}
	return _FindMin(((Internal*)t->son1));
}
template <class K, class T>
typename T23<K, T>::Leaf* T23<K, T>::Iterator::_FindMax(Internal* t)   //����� ����. �����
{
	if (t == NULL)return 0;
	if ((t->son1->type() == 0))
	{
		if (t->son3)return ((Leaf*)t->son3);
		if (t->son2)return ((Leaf*)t->son2);
		return ((Leaf*)t->son1);
	}
	if (t->son3)return _FindMax(((Internal*)t->son3));
	if (t->son2)return _FindMax(((Internal*)t->son2));
	return _FindMax(((Internal*)t->son1));
}

template <class K, class T>
void T23<K, T>::Iterator::_Next(Internal* t) //����������� ������� �������� � ���������� �����
{
	if (t == NULL) return;
	if ((t->son1->type() == 0))
	{
		if (t->son1 == cur)
		{
			if (t->son2) cur = ((Leaf*)t->son2);
			return;
		}

		if (t->son2)
		{
			if (t->son2 == cur)
			{
				if (t->son3)cur = ((Leaf*)t->son3);
				else cur = NULL;
				return;
			}
		}

		if (t->son3)
		{
			if (t->son3 == cur)
			{
				cur = NULL;
				return;
			}
		}
		return;
	}

	if (cur == NULL)
		return;
	if (t->low2 > cur->key)
	{
		_Next(((Internal*)t->son1));
		if (cur == NULL)
		{
			cur = _FindMin(((Internal*)t->son2));
		}
		return;
	}

	if (t->low3 > cur->key)
	{
		_Next(((Internal*)t->son2));
		if (cur == NULL)
		{
			if (t->son3)cur = _FindMin(((Internal*)t->son3));
		}
		return;
	}

	_Next(((Internal*)t->son3));
	if (cur == NULL)
	{
		cur = _FindMax(((Internal*)t->son3));
	}
	return;
}

template <class K, class T>
void T23<K, T>::Iterator::_Prev(Internal* t)
{
	if (t == NULL)return;
	if ((t->son1->type() == 0))
	{
		if (t->son1 == cur)
		{
			cur = NULL;
			return;
		}

		if (t->son2)
		{
			if (t->son2 == cur)
			{
				cur = ((Leaf*)t->son1);
				return;
			}
		}

		if (t->son3)
		{
			if (t->son3 == cur)
			{
				cur = ((Leaf*)t->son2);
				return;
			}
		}
		return;
	}

	if (cur == NULL)
		return;            //�������� ��� ������
	if (t->low2 > cur->key)
	{
		_Prev(((Internal*)t->son1));
		if (cur == NULL) { ; }
		return;
	}

	if (t->low3 > cur->key)
	{
		_Prev(((Internal*)t->son2));
		if (cur == NULL)
		{
			cur = _FindMax(((Internal*)t->son1));
		}
		return;
	}

	_Prev(((Internal*)t->son3));
	if (cur == NULL)
	{
		cur = _FindMax(((Internal*)t->son2));
	}
	return;
}

template <class K, class T>
T23<K, T>::rIterator::rIterator(T23<K, T>* t)
{
	tree = t;
	if (tree)
	{
		if (tree->root)
		{
			cur = _FindMin(tree->root);
		}
		else { cur = NULL; }
	}
	else { cur = NULL; }
}

template <class K, class T>
void T23<K, T>::rIterator::beg()
{
	if (tree->root != 0)
	{
		cur = _FindMax(tree->root);
	}
}

template <class K, class T>
void T23<K, T>::rIterator::end()
{
	if (tree->root != 0)
	{
		cur = _FindMin(tree->root);
	}
}

template <class K, class T>
void T23<K, T>::rIterator::next()
{
	if (tree->root)
	{
		_Prev(tree->root);
	}
}

template <class K, class T>
void T23<K, T>::rIterator::prev()
{
	if (tree->root)
	{
		_Next(tree->root);
	}
}

template <class K, class T>
bool T23<K, T>::rIterator::IsOff()
{
	return (cur == 0);
}

template <class K, class T>
bool T23<K, T>::rIterator::operator++(int)
{
	if (tree->root)
	{
		_Prev(tree->root);
		return true;
	}
	return false;
}

template <class K, class T>
bool T23<K, T>::rIterator::operator--(int)
{
	if (tree->root)
	{
		_Next(tree->root);
		return true;
	}
	return false;
}

template <class K, class T>
bool T23<K, T>::rIterator::operator==(Leaf* node)
{
	return cur == node;
}

template <class K, class T>
bool T23<K, T>::rIterator::operator!=(Leaf* node)
{
	return cur != node;
}

template <class K, class T>
T& T23<K, T>::rIterator::operator*()
{
	if (!cur) throw TreeException();
	return cur->data;
}

template <class K, class T>
typename T23<K, T>::Leaf* T23<K, T>::rIterator::_FindMin(Internal* t)  //����� ���. �����
{
	if (t == NULL) return NULL;
	if ((t->son1->type() == 0))
	{
		return ((Leaf*)t->son1);
	}
	return _FindMin(((Internal*)t->son1));
}
template <class K, class T>
typename T23<K, T>::Leaf* T23<K, T>::rIterator::_FindMax(Internal* t)   //����� ����. �����
{
	if (t == NULL)return 0;
	if ((t->son1->type() == 0))
	{
		if (t->son3)return ((Leaf*)t->son3);
		if (t->son2)return ((Leaf*)t->son2);
		return ((Leaf*)t->son1);
	}
	if (t->son3)return _FindMax(((Internal*)t->son3));
	if (t->son2)return _FindMax(((Internal*)t->son2));
	return _FindMax(((Internal*)t->son1));
}

template <class K, class T>
void T23<K, T>::rIterator::_Next(Internal* t)
{

	if (t == NULL) return;
	if ((t->son1->type() == 0))
	{
		if (t->son1 == cur)
		{
			if (t->son2) cur = ((Leaf*)t->son2);
			return;
		}

		if (t->son2)
		{
			if (t->son2 == cur)
			{
				if (t->son3)cur = ((Leaf*)t->son3);
				else cur = NULL;
				return;
			}
		}

		if (t->son3)
		{
			if (t->son3 == cur)
			{
				cur = NULL;
				return;
			}
		}
		return;
	}

	if (cur == NULL)
		return;
	if (t->low2 > cur->key)
	{
		_Next(((Internal*)t->son1));
		if (cur == NULL)
		{
			cur = _FindMin(((Internal*)t->son2));
		}
		return;
	}

	if (t->low3 > cur->key)
	{
		_Next(((Internal*)t->son2));
		if (cur == NULL)
		{
			if (t->son3)cur = _FindMin(((Internal*)t->son3));
		}
		return;
	}

	_Next(((Internal*)t->son3));
	if (cur == NULL)
	{
		cur = _FindMax(((Internal*)t->son3));
	}
	return;
}

template <class K, class T>
void T23<K, T>::rIterator::_Prev(Internal* t)
{
	if (t == NULL)return;
	if ((t->son1->type() == 0))
	{
		if (t->son1 == cur)
		{
			cur = NULL;
			return;
		}

		if (t->son2)
		{
			if (t->son2 == cur)
			{
				cur = ((Leaf*)t->son1);
				return;
			}
		}

		if (t->son3)
		{
			if (t->son3 == cur)
			{
				cur = ((Leaf*)t->son2);
				return;
			}
		}
		return;
	}

	if (cur == NULL)
		return;            //�������� ��� ������
	if (t->low2 > cur->key)
	{
		_Prev(((Internal*)t->son1));
		if (cur == NULL) { ; }
		return;
	}

	if (t->low3 > cur->key)
	{
		_Prev(((Internal*)t->son2));
		if (cur == NULL)
		{
			cur = _FindMax(((Internal*)t->son1));
		}
		return;
	}

	_Prev(((Internal*)t->son3));
	if (cur == NULL)
	{
		cur = _FindMax(((Internal*)t->son2));
	}
	return;
}
#pragma once
