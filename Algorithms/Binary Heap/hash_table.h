#ifndef DYNAMIC_TABLE_H
#define DYNAMIC_TABLE_H

#include <iostream>
#include <type_traits>

using namespace std;

template<class T>
class BinaryHeap;

template<class T>
class Tab
{
private:

	int size;
	int max_size;
	T* arr;

public:

	Tab()
	{
		size = 0;
		max_size = 1;
		arr = new T[max_size];
	}

	~Tab()
	{
		delete[] arr;
		max_size = 1;
	}

	const T& getTab(int a) const
	{
		return arr[a];
	}

	int getSize()
	{
		return size;
	}

	void check_size()
	{
		if (size == max_size)
		{
			max_size = max_size * 2;
			T* arr2 = new T[max_size];
			for (int i = 0; i < size; i++)
			{
				arr2[i] = move(arr[i]);
			}
			delete[] arr;
			arr = arr2;
		}
		return;
	}

	void push_back(const T& value)
	{
		check_size();
		arr[size] = value;
		size++;
	}

	T return_by_index(int index)
	{
		if (index<0 || index > size)
		{
			return NULL;
		}
		return arr[index];
	}

	bool replace(int index, const T& value)
	{
		if (index<0 || index > size)
		{
			return false;
		}
		arr[index] = value;
		return true;
	}

	void print(int number)
	{
		if (size == 0)
		{
			cout << "Lista pusta" << endl;
			return;
		}
		cout << "Rozmiar obecny: " << size << endl;
		cout << "Rozmiar maksymalny: " << max_size << endl;
		cout << "Adres tablicy: " << arr << endl;
		cout << "Kilka poczatkowych elementow tablicy " << "(" << number << ")" << endl;
		for (int i = 0; i < number; i++)
		{
			if (i == size)
			{
				cout << "Nie ma wiecej elementow" << endl;
				return;
			}
			cout << i << ": " << arr[i] << endl;
		}
	}

	void clear()
	{
		for (int i = 0; i < size; i++)
		{
			arr[i].~T();
		}
	}

	friend class BinaryHeap<T>;

};

#endif