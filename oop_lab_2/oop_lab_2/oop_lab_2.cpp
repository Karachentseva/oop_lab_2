// oop_lab_2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string.h>
#include <vector>
#include <string>
using namespace std;

class Container {
public:
	virtual int size() const = 0; // возвращает размер контейнера
	virtual bool isEmpty() const = 0; // проверяет пустой ли контейнер
	virtual string toString() const = 0; // строка со всеми элементами
	virtual ~Container() {};
};
class PushPopContainer :public virtual Container {
public:
	virtual bool push(int value) = 0; // добавить элемент
	virtual int pop() = 0; // забрать элемент
	virtual int peek() const = 0; // узнать элемент
	virtual ~PushPopContainer() {};
};
class Deque : public virtual Container {
public:
	virtual bool pushFront(int value) = 0; // добавить в начало
	virtual bool pushBack(int value) = 0; // добавить в конец
	virtual int popFront() = 0; // забрать из начала
	virtual int popBack() = 0; // забрать с конца
	virtual int peekFront() const = 0; // узнать элемент в начале
	virtual int peekBack() const = 0; // узнать элемент с конца
	virtual ~Deque() {};
};
class IndexedContainer :public virtual Container {
public:
	virtual int get(int index) const = 0; // узнать элемент по индексу index
	virtual int set(int index, int value) = 0; // задать значение элементу
	virtual ~IndexedContainer() {};
};
class InsertableContainer :public virtual IndexedContainer {
public:
	virtual bool insertAt(int index, int value) = 0; // вставить элемент со сдвигом
	virtual int removeAt(int index) = 0; // убрать элемент со сдвигом
	virtual ~InsertableContainer() {};
};
struct Node {
	int value;
	Node *next;
};
struct Node1
{
	int value;
	Node1 *next;
	Node1 *prev;
};
class Stack : public PushPopContainer
{
private:
	Node *first;
	int s;
public:
	Stack()
	{
		s = 0;
		first = nullptr;
	}
	virtual int size() const // возвращает размер контейнера
	{
		return s;
	}
	virtual bool isEmpty() const	// проверяет пустой ли контейнер
	{
		return first == nullptr;
	}
	virtual string toString() const // строка со всеми элементами
	{
		Node* tmp = first;
		string res = "";
		while (tmp != nullptr)
		{
			res.append(to_string(tmp->value));
			res.append(" ");
			tmp = tmp->next;
		}
		return res;
	}
	virtual bool push(int value)// добавить элемент
	{

		if (isEmpty())
		{
			first = new Node();
			first->value = value;
		}
		else
		{
			Node* tmp = new Node();
			tmp->value = value;
			tmp->next = first;
			first = tmp;
		}
		s++;
		return true;
	}

	virtual int pop()// забрать элемент
	{
		if (!isEmpty())
		{
			int res = first->value;
			Node* tmp = first->next;
			delete first;
			first = tmp;
			s--;
			return res;
		}
		return 0;
	}

	virtual int peek() const// узнать элемент
	{
		if (!isEmpty())
			return first->value;
		return 0;
	}
	~Stack()
	{
		Node* tmp = first;
		while (tmp != nullptr)
		{
			first = tmp->next;
			delete tmp;
			tmp = first;
		}
	};
};


class Queue : public PushPopContainer
{
private:
	Node *first, *last;
	int s;
public:
	Queue()
	{
		s = 0;
		first = last = nullptr;
	}
	int size() const  // возвращает размер контейнера
	{
		return s;
	}
	bool isEmpty() const  // проверяет пустой ли контейнер
	{
		return first == nullptr;
	}
	std::string toString() const// строка со всеми элементами
	{
		Node* tmp = first;
		string res = "";
		while (tmp != nullptr)
		{
			res.append(to_string(tmp->value));
			res.append(" ");
			tmp = tmp->next;
		}
		return res;
	}
	bool push(int value)// добавить элемент
	{
		try {
			if (isEmpty())
			{
				first = last = new Node();
				first->value = value;
			}
			else
			{
				last->next = new Node();
				last->next->value = value;
				last = last->next;
			}
			s++;
			return true;
		}
		catch (...)
		{
			return false;
		}
	}
	int pop() // забрать элемент
	{
		if (!isEmpty())
		{
			int res = first->value;
			Node* tmp = first->next;
			delete first;
			first = tmp;
			s--;
			return res;
		}
		return 0;
	}
	int peek() const// узнать элемент
	{
		if (!isEmpty())
			return first->value;
		return 0;
	}
	~Queue()
	{
		Node* tmp = first;
		while (tmp != nullptr)
		{
			first = tmp->next;
			delete tmp;
			tmp = first;
		}
	}
};


class LinkedList : public PushPopContainer, public InsertableContainer
{
private:
	Node *first, *last;
	int s;
public:

	LinkedList()
	{
		s = 0;
		first = last = nullptr;
	}

	int size() const// возвращает размер контейнера
	{
		return s;
	}

	bool isEmpty() const// проверяет пустой ли контейнер
	{
		return last == nullptr;
	}

	std::string toString() const// строка со всеми элементами
	{
		Node* tmp = last;
		string res = "";
		while (tmp != nullptr)
		{
			res.append(to_string(tmp->value));
			res.append(" ");
			tmp = tmp->next;
		}
		return res;
	}

	bool push(int value)// добавить элемент
	{
		try {
			if (isEmpty())
			{
				first = last = new Node();
				first->value = value;
			}
			else
			{
				Node* tmp = new Node();
				tmp->value = value;
				tmp->next = last;
				last = tmp;
			}
			s++;
			return true;
		}
		catch (...)
		{
			return false;
		}
	}
	int pop()// забрать элемент
	{
		if (!isEmpty())
		{
			int res =last->value;
			Node* tmp = last;
			last = last->next;
			delete tmp;
			s--;
			return res;
		}
		return 0;
	}

	int peek() const// узнать элемент
	{
		if (!isEmpty())
			return last->value;
		return 0;
	}
	int get(int index) const
	{
		if (index < s)
		{
			index = s - index;
			Node* tmp = last;
			for (int i = 0; i < index; i++)
			{
				tmp = tmp->next;
			}
			return tmp->value;
		}
		return 0;
	}

	int set(int index, int value)
	{
		if (index < s)
		{
			index = s - index - 1;
			Node* tmp = last;
			for (int i = 0; i < index; i++)
			{
				tmp = tmp->next;
			}
			tmp->value = value;
			return value;
		}
		return 0;
	}
	bool insertAt(int index, int value)// вставить элемент со сдвигом
	{
		if (index < s)
		{
			index = s - index;
			Node* tmp = last;
			for (int i = 0; i < index; i++)
			{
				tmp = tmp->next;
			}
			Node *n = new Node();
			n->value = value;
			n->next = tmp->next;
			tmp->next = n;
			s++;
			return true;
		}
		return false;
	}

	int removeAt(int index)// убрать элемент со сдвигом

	{
		if (index < s)
		{
			index = s - index;
			Node* tmp;
			if (index == 1)
			{
				tmp = last->next;
				delete last;
				last = tmp;
				s--;
				return true;
			}
			tmp = last;
			for (int i = 0; i < index - 1; i++)
			{
				tmp = tmp->next;
			}
			int res = tmp->value;
			Node* tmp2 = tmp->next;
			tmp->next = tmp2->next;
			delete tmp2;
			return res;
		}
		return 0;
	}
	~LinkedList()
	{
		Node* tmp = last;
		while (tmp != nullptr)
		{
			last = tmp->next;
			delete tmp;
			tmp = last;
		}
	}
};

class StaticArray :public IndexedContainer
{
private:
	int *arr;
	int si;
public:
	StaticArray(int s)
	{
		si = s;
		arr = new int[si];
	}
	int size() const// возвращает размер контейнера
	{
		return si;
	}
	bool isEmpty() const// проверяет пустой ли контейнер
	{
		return si == 0;
	}
	std::string toString() const// строка со всеми элементами
	{
		string res = "";
		for (int i = 0; i < si; i++)
		{
			res.append(to_string(arr[i]));
			res.append(" ");
		}
		return res;
	}
	int get(int index) const// узнать элемент по индексу index
	{
		if (index<si)
			return arr[index];
		return 0;
	}
	int set(int index, int value)// задать значение элементу
	{
		if (index < si)
			arr[index] = value;
		return value;
	}
	~StaticArray()
	{
		delete[] arr;
	}
};

class  LinkedDeque : public Deque
{
private:
	Node1 *first, *last;
	int s;
public:
	LinkedDeque() :s(0), first(nullptr), last(nullptr)
	{}
	int size() const// возвращает размер контейнера
	{
		return s;
	}
	bool isEmpty() const// проверяет пустой ли контейнер
	{
		return s == 0;
	}
	std::string toString() const// строка со всеми элементами
	{
		Node1* tmp = first;
		string res = "";
		while (tmp != nullptr)
		{
			res.append(to_string(tmp->value));
			res.append(" ");
			tmp = tmp->next;
		}
		return res;
	}

	bool pushFront(int value)// добавить в начало
	{
		if (isEmpty())
		{
			first = last = new Node1();
			first->value = value;
			last->value = value;
			s++;
			return true;
		}
		else
		{
			first->prev = new Node1();
			first->prev->value = value;
			Node1 *tmp = first;
			first = first->prev;
			first->next = tmp;
			s++;
			return true;
		}
		return false;
	}
	bool pushBack(int value)// добавить в конец
	{
		if (isEmpty())
		{
			first = last = new Node1();
			first->value = value;
			last->value = value;
			s++;
			return true;
		}
		else
		{
			last->next = new Node1();
			last->next->value = value;
			Node1 *tmp = last;
			last = last->next;
			last->prev = tmp;
			s++;
			return true;
		}
		return false;
	}
	int popFront()// забрать из начала
	{
		int res = first->value;
		Node1* tmp = first->next;
		delete first;
		first = tmp;
		s--;
		return res;
	}
	int popBack()// забрать с конца
	{
		int res = last->value;
		Node1* tmp = last->prev;
		delete last;
		last = tmp;
		s--;
		return res;
	}
	int peekFront() const // узнать элемент в начале
	{
		return first->value;
	}
	int peekBack() const // узнать элемент с конца
	{
		return last->value;
	}
	~LinkedDeque()
	{
		Node1* tmp = first;
		while (tmp != nullptr)
		{
			first = tmp->next;
			delete tmp;
			tmp = first;
		}
	}
};

void main()
{
	int n = 10;
	vector<Container*> arr({ new Stack(), new Queue(),  new LinkedList(), new StaticArray(n), new LinkedDeque() });
		for (int i = 0; i < arr.size(); i++)
		{
			PushPopContainer*mypushpopcontainer = dynamic_cast<PushPopContainer*>(arr[i]);
			if (mypushpopcontainer != nullptr)
			{
				mypushpopcontainer->push(1);
				mypushpopcontainer->push(2);
				mypushpopcontainer->push(3);
				mypushpopcontainer->push(4);
				mypushpopcontainer->push(5);
	
			}
			IndexedContainer*myindexedcontainer = dynamic_cast<IndexedContainer*>(arr[i]);
			if (myindexedcontainer != nullptr)
			{
				myindexedcontainer->set(0, 100);
				myindexedcontainer->set(1, 101);
				myindexedcontainer->set(2, 102);
				myindexedcontainer->set(3, 103);
				myindexedcontainer->set(4, 104);
			
			}
			Deque*mydequeue = dynamic_cast<Deque*>(arr[i]);
			if (mydequeue != nullptr)
			{
				mydequeue->pushBack(1);
				mydequeue->pushFront(-1);
				mydequeue->pushBack(2);
				mydequeue->pushFront(-2);
				mydequeue->pushBack(3);
				mydequeue->pushFront(-3);
			}
		}
		for (int j = 0; j < arr.size(); j++)
					cout << arr[j]->toString() << endl;
			cout <<"---------------------" <<endl ;
		
	for (Container *c : arr) 
	{
		PushPopContainer *mypoppushcontainer = dynamic_cast<PushPopContainer*>(c);
		if (mypoppushcontainer != nullptr)
		{
			while (!mypoppushcontainer->isEmpty() )
			{
				cout  << mypoppushcontainer->pop() << endl;
			}
		}
	
		cout << c->toString() << endl;

		Deque *mydeque = dynamic_cast<Deque*>(c);
		if (mydeque != nullptr)
		{

			while (!mydeque->isEmpty() )
			{
				cout << mydeque->popBack() << endl;
			}
		}
	}
	

	/*vector <PushPopContainer*> mystack({ new Stack() });
	//		vector <IndexedContainer*> mystaticarray({ new StaticArray(n) });
	//		vector <Deque*> mydequeue({ new LinkedDeque() });
	//		for (int i = 0; i < n; i++)
	//		{
	//
	//			for (int j = 0; j < mystack.size(); j++)
	//				mystack[j]->push(i);
	//			for (int i = 0; i < n; i++)
	//			{
	//				for (int j = 0; j < mystaticarray.size(); j++)
	//					mystaticarray[j]->set(i, i);
	//			}
	//			for (int i = 0; i < n; i++)
	//			{
	//				for (int j = 0; j < mydequeue.size(); j++)
	//				{
	//					mydequeue[j]->pushBack(i);
	//					mydequeue[j]->pushFront(i);
	//				}
	//			}
	//			for (int j = 0; j < mystack.size(); j++)
	//				cout << mystack[j]->toString() << endl;
	//			for (int j = 0; j < arr.size(); j++)
	//				cout << mystaticarray[j]->toString() << endl;
	//			for (int j = 0; j < mydequeue.size(); j++)
	//				cout << mydequeue[j]->toString() << endl;*/
	system("pause");

}

