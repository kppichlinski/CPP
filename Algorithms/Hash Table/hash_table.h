#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <iostream>
#include <vector>
#include <list>
#include <cmath>

using namespace std;

template<class T>
class HashTable
{
private:

	list<pair<string, T>>* arr;
	int size;
	int max_size;

	int shuffle(string key)
	{
		unsigned int sum = 0;
		for (int i = 0; i < key.length(); i++)
		{
			sum += (int)(key[i] * pow(31, key.length() - 1 - i));
		}
		sum %= max_size;
		return sum;
	}

	void rehash()
	{
		max_size = max_size * 2;
		list<pair<string, T>>* tab = new list<pair<string, T>>[max_size];
		for (int i = 0; i < size; i++)
		{
			if (!arr[i].empty())
			{
				string k = arr[i].front().first;
				int sum = shuffle(k);
				tab[sum] = move(arr[i]);
			}
		}
		arr = tab;
	}

public:

	HashTable()
	{
		max_size = 10;
		size = 0;
		arr = new list<pair<string, T>>[max_size];
	}

	~HashTable()
	{
		delete[] arr;
	}

	void add(string key, T value)
	{
		int sum = shuffle(key);
		if (size > ((3.0 / 4.0) * max_size))
		{
			rehash();
		}
		if (arr[sum].empty())
		{
			list<pair<string, T>> l;
			arr[sum] = l;
			size++;
		}
		pair<string, T> p;
		p.first = key;
		p.second = value;
		arr[sum].push_back(p);
	}

	pair<string, T>* find(string key)
	{
		int sum = shuffle(key);
		for (auto& x : arr[sum])
		{
			if (x.first == key)
			{
				return &x;
			}
		}
		return NULL;
	}

	bool del(string key)
	{
		int sum = shuffle(key);
		for (auto it = arr[sum].begin(); it != arr[sum].end(); it++)
		{
			if ((*it).first == key)
			{
				arr[sum].erase(it);
				return true;
			}
		}
		return false;
	}

	void clear()
	{
		for (int i = 0; i < max_size; i++)
		{
			arr[i].clear();
		}
		max_size = 10;
		size = 0;
	}

	void print(int number)
	{
		cout << "hash table :" << endl;
		cout << "\tcurrent_size: " << size << endl;
		cout << "\tmax_size : " << max_size << endl;
		cout << "\ttable :" << endl;
		cout << "\t{" << endl;
		for (int i = 0; i < number; i++)
		{
			for (auto& x : arr[i])
			{
				cout << "\t\t" << i << ": " << x.first << " ---> " << x.second << endl;
			}
		}
		cout << "\t}" << endl;
	}

	void print_stats()
	{
		int max = 0;
		int min = 1000000;
		int counter = 0;
		int non_null = 0;
		float av = 1;
		for (int i = 0; i < max_size; i++)
		{
			counter = 0;
			for (auto& x : arr[i])
			{
				counter++;
			}
			if (counter > max)
			{
				max = counter;
			}
			if (counter < min && counter > 0)
			{
				min = counter;
			}
			if (!arr[i].empty())
			{
				non_null++;
				av = (av + counter) / 2;
			}
		}

		cout << "\tstats:" << endl;
		cout << "\t\tlist min size : " << min << endl;
		cout << "\t\tlist max size : " << max << endl;
		cout << "\t\tnon - null lists : " << non_null << endl;
		cout << "\t\tlist avg size : " << av << endl;
	}

};

#endif

