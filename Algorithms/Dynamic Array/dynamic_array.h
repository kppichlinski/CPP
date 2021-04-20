#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <iostream>


using namespace std;

template<class T>
class Tab
{
public:

	int size = 0;
	int max_size = 1;
	T* arr;

public:

	Tab()
	{
		arr = new T[max_size];
	}

	~Tab()
	{
		delete[] arr;
	}

	void check_size()
	{
		if (size == max_size)
		{
			max_size = max_size * 2;
			T* arr2 = new T[max_size];
			for (int i = 0; i < size; i++)
			{
				arr2[i] = arr[i];
			}
			delete[] arr;
			arr = arr2;
		}
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
		cout << "Rozmiar obecny: " << size << endl;
		cout << "Rozmiar maksymalny: " << max_size << endl;
		cout << "Adres tablicy: " << arr << endl;
		cout << "Kilka poczatkowych elementow tablicy " << "(" << number << ")" << endl;
		for (int i = 0; i < number ; i++)
		{
			cout << *arr[i] << endl;
		}
	}

	void clear()
	{
		for (int i=0; i <size; i++)
		{
			delete arr[i];
		}
	}

};










#endif 

