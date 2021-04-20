#ifndef TWO_WAY_LIST_H
#define TWO_WAY_LIST_H

#include <iostream>

using namespace std;

template<class T>
class Node
{
public:

	T data;

public:

	Node<T>* prev;
	Node<T>* next;

	Node(T value)
	{
		data = value;
	}

	~Node()
	{

	}

	const T getData() const
	{
		return data;
	}

};

template<class T>
class Lista
{
public:

	int size;
	Node<T>* head;
	Node<T>* tail;

public:

	Lista()
	{
		head = nullptr;
		tail = nullptr;
		size = 0;
	}

	~Lista()
	{
		Node<T>* temp = head;
		Node<T>* del;

		while (size != 0)
		{
			del = temp;
			temp = temp->next;
			del->prev = nullptr;
			del->next = nullptr;
			delete del->getData();
			delete del;
			size--;
		}
	}

	void push_back(const T& value)
	{
		if (size == 0)
		{
			push_front(value);
			return;
		}
		Node<T>* temp = new Node<T>{ value };
		tail->next = temp;
		temp->prev = tail;
		tail = temp;
		size++;
	}

	void push_front(const T& value)
	{

		Node<T>* temp = new Node<T>{ value };
		temp->next = head;

		if (head != nullptr)
		{
			head->prev = temp;
		}

		head = temp;

		if (size == 0)
		{
			tail = head;
		}

		size++;
	}

	void remove_back()
	{
		if (size == 0)
		{
			cout << "Nie mam czego usunac - lista pusta" << endl;
			return;
		}

		if (size == 1)
		{
			remove_front();
			return;
		}

		Node<T>* temp = tail;
		tail = tail->prev;
		tail->next = nullptr;
		delete temp->getData();
		delete temp;
		size--;
	}

	void remove_front()
	{
		if (size == 0)
		{
			cout << "Nie mam czego usunac - lista pusta ";
			return;
		}

		Node<T>* temp = head;
		head = head->next;

		if (head != nullptr)
		{
			head->prev = nullptr;
		}

		delete temp->getData();
		delete temp;
		size--;
	}

	void error() {
		cout << "Blad" << endl;
		exit(EXIT_FAILURE);
	}

	T return_by_index(const int index)
	{
		Node<T>* temp = head;

		if (index<0 || index>size)
		{
			error();
		}

		for (int i = 0; i < index; i++)
		{
			temp = temp->next;
		}

		return temp->getData();
	}

	void replace(int index, const T& value)
	{
		if (index<0 || index>size)
		{
			error();
		}

		Node<T>* temp = head;

		for (int i = 0; i < index; i++)
		{
			temp = temp->next;

		}

		temp->data = value;

	}

	Node<T>* search(const T& value, int (*data)(T, T))
	{
		if (size == 0)
		{
			return NULL;
		}

		Node<T>* temp = head;

		for (int i = 0; i < size; i++)
		{

			if (!data(temp->getData(), value))
			{
				return temp;
			}

			temp = temp->next;
		}

		return NULL;

	}

	bool remove_by_value(const T& value, int (*data)(T, T))
	{
		Node<T>* temp = head;
		Node<T>* temp_next;
		Node<T>* temp_prev;
		Node<T>* del;

		while (data(temp->getData(), value))
		{
			temp = temp->next;
			if (temp == NULL)
			{
				return false;
			}
		}
		if (temp == head)
		{
			remove_front();
			return true;
		}
		if (temp == tail)
		{
			remove_back();
			return true;
		}
		del = temp;
		temp_prev = del->prev;
		temp_next = del->next;
		temp_prev->next = temp_next;
		temp_next->prev = temp_prev;
		delete del->getData();
		delete del;
		size--;
		return true;

	}

	void insert(int index, const T& value)
	{
		if (size == 0)
		{
			push_front(value);
			return;
		}

		if (index == size)
		{
			push_back(value);
			return;
		}

		if (index<0 || index>size)
		{
			error();
		}

		Node<T>* temp = new Node<T>{ value };
		Node<T>* temp_next;
		Node<T>* temp_prev = head;

		for (int i = 0; i < index - 1; i++)
		{
			temp_prev = temp_prev->next;
		}

		temp_next = temp_prev->next;
		temp_prev->next = temp;
		temp_next->prev = temp;
		temp->next = temp_next;
		temp->prev = temp_prev;
		size++;
	}

	void find_place(const T& value, bool (*data)(T, T))
	{
		Node<T>* temp = head;
		Node<T>* help;
		Node<T>* that = new Node<T>{ value };

		if (size == 0)
		{
			push_front(value);
			return;
		}

		while (place(temp->getData(), value) && temp->next != NULL)
		{
			temp = temp->next;
		}

		if (temp == head)
		{
			if (place(temp->getData(), value))
			{
				if (temp->next == NULL)
				{
					push_back(value);
					return;
				}
				help = temp->next;
				temp->next = that;
				that->prev = temp;
				that->next = help;
				help->prev = that;
				size++;
				return;
			}
			else
			{
				push_front(value);
				return;
			}
		}
		else if (temp == tail)
		{
			if (place(temp->getData(), value))
			{
				push_back(value);
				return;
			}
		}

		help = temp->prev;
		that->next = temp;
		that->prev = help;
		help->next = that;
		temp->prev = that;
		size++;

	}

	void print(int a) const
	{
		Node<T>* temp = head;
		cout << "Rozmiar listy: " << size << endl;
		cout << "Adres listy: " << head << endl;
		cout << "Poczatkowe elementy" << "(" << a << ")" << endl;
		for (int i = 0; i < a; i++)
		{
			cout << *temp->getData() << endl;
			temp = temp->next;
		}
	}

};


#endif