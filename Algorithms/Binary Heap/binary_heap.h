#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#include "hash_table.h"
#include <iostream>

using namespace std;

template<class T>
class BinaryHeap
{
private:

	Tab<T>* tab;

	//numer lewego syna = 2k + 1

	//numer prawego syna = 2k + 2

	//numer ojca = [(k - 1) / 2], dla k > 0

	//lewy syn istnieje, jeœli 2k + 1 < n

	//prawy syn istnieje, jeœli 2k + 2 < n

	//wêze³ k jest liœciem, jeœli 2k + 2 > n

	void HeapUp(int index, bool(*comp)(T, T))
	{
		if (index == 0)
		{
			return;
		}
		if (comp(tab->arr[index], tab->arr[(index - 1) / 2]))
		{
			T a = tab->arr[(index - 1) / 2];
			tab->arr[(index - 1) / 2] = tab->arr[index];
			tab->arr[index] = a;
		}
		HeapUp((index - 1) / 2, comp);
	}

	void HeapDown(int index, bool(*comp)(T, T))
	{
		if (2 * index + 1 > tab->size && 2 * index + 2 > tab->size)
		{
			return;
		}
		bool left_bigger = comp(tab->arr[2 * index + 1], tab->arr[2 * index + 2]);
		if (comp(tab->arr[2 * index + 1], tab->arr[index]) && left_bigger)
		{
			T a = tab->arr[2 * index + 1];
			tab->arr[2 * index + 1] = tab->arr[index];
			tab->arr[index] = a;
			HeapDown(2 * index + 1, comp);
		}
		else if (comp(tab->arr[2 * index + 2], tab->arr[index]))
		{
			T a = tab->arr[2 * index + 2];
			tab->arr[2 * index + 2] = tab->arr[index];
			tab->arr[index] = a;
			HeapDown(2 * index + 2, comp);

		}

	}

public:

	BinaryHeap()
	{
		tab = new Tab<T>();
	}

	~BinaryHeap()
	{
		delete tab;
	}

	int getSize()
	{
		return tab->size;
	}

	void add(const T & value, bool (*comp)(T, T))
	{
		tab->push_back(value);
		HeapUp(tab->size, comp);
	}

	T delMax(bool (*comp)(T, T))
	{
		if (tab->size == 0)
		{
			cout << "Kopiec pusty" << endl;
			return T();
		}
		tab->arr[0] = tab->arr[tab->size - 1];
		tab->arr[tab->size - 1].~T();
		tab->size--;
		/*T* arr2 = new T[tab->max_size];
		for (int i = 0; i < tab->size; i++)
		{
			arr2[i] = move(tab->arr[i]);
		}
		delete[] tab->arr;
		tab->arr = arr2;*/
		HeapDown(0, comp);
		return tab->arr[0];
	}

	void showMax()
	{
		if (tab->size == 0)
		{
			cout << "Brak najwiekszego elementu. Lista pusta" << endl;
			return;
		}
		cout << tab->arr[0] << endl;
	}

	void show()
	{
		tab->print(10);
	}

	void clear()
	{
		delete[] tab->arr;
		tab->max_size = 1;
		tab->arr = new T[tab->max_size];
	}

};

#endif