#include "binary_heap.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>

using namespace std;

struct object
{
	float field1;
	char field2;

	object()
	{
		field1 = rand() % 10001;
		field2 = rand() % 26 + 'A';
	}

};

double key(object* so)
{
	return so->field1;
}

bool place(object so2, object so1)
{
	if (so2.field1 > so1.field1)
	{
		return true;
	}
	else if (so2.field1 == so1.field1)
	{
		if (so2.field2 > so1.field2)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

bool placeWsk(object* so1, object* so2)
{
	if (so1->field1 > so2->field1)
	{
		return true;
	}
	else if (so1->field1 == so2->field1)
	{
		if (so1->field2 > so2->field2)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

bool place_int(int int1, int int2)
{
	if (int1 > int2)
	{
		return true;
	}
	return false;
}

template<class T>
void bucketSort(T* tab, int size, int m, double (*key)(T), bool (*comp)(T, T))
{
	vector <T>* arr = new vector<T>[size];

	for (int i = 0; i < size; i++)
	{
		arr[(int)(key(tab[i])*double(size)/m)].push_back(tab[i]);
	}
	for (int i = 0; i < size; i++)
	{
		object* k;
		int w = 0;
		for (int j = 1; j < arr[i].size(); j++)
		{
			k = arr[i][j];
			w = j - 1;
			while (w > 0 && comp(arr[i][w], k))
			{
				arr[i][w + 1] = arr[i][w];
				w--;
			}
			arr[i][w] = k;
		}
	}
	int index = 0;
	for (int i = 0; i < size; i++)
	{
		while (!arr[i].empty())
		{
			tab[index++] = *(arr[i].begin());
			arr[i].erase(arr[i].begin());
		}
	}

	delete[] arr;
}

void bucketSort(int* tab, int size, int m)
{
	vector<int>* arr = new vector<int>[size];

	for (int i = 0; i < size; i++)
	{
		arr[(int)tab[i]*(size/m)].push_back(tab[i]);
	}
	for (int i = 0; i < size; i++)
	{
		sort(arr[i].begin(), arr[i].end());
	}
	int index = 0;
	for (int i = 0; i < size; i++)
	{
		while (!arr[i].empty())
		{
			tab[index++] = *(arr[i].begin());
			arr[i].erase(arr[i].begin());
		}
	}

	delete[] arr;
}

void countingSort(int* tab, int size, int m)
{
	int* arr = new int[m];
	int* fin = new int[size];
	for (int i = 0; i < m; i++)
	{
		arr[i] = 0;
	}
	for (int i = 0; i < size; i++)
	{
		arr[tab[i]]++;
	}
	for (int i = 1; i < m; i++)
	{
		arr[i] = arr[i] + arr[i - 1];
	}
	for (int i = size - 1; i >= 0; i--)
	{
		fin[arr[tab[i]] - 1] = tab[i];
		arr[tab[i]]--;
	}
	for (int i = 0; i < size; i++)
	{
		tab[i] = move(fin[i]);
	}

	delete arr;
	delete fin;
}

bool check(int* tab1, int* tab2, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (tab1[i] != tab2[i])
		{
			return false;
		}
	}
	return true;
}

template <class T>
bool check(T* tab1, T* tab2, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (tab1[i] != tab2[i])
		{
			return false;
		}
	}
	return true;
}

ostream& operator<<(ostream& out, const object& o)
{
	return out << o.field1 << ", " << o.field2;
}

/*
int main()
{
	srand(0);
	const int MAX_ORDER = 7; // maksymalny rzad wielkosci sortowanych danych
	const int m = (int)pow(10, 7); // sortowane liczby ze zbioru {0 , ... , m - 1}
	for (int o = 1; o <= MAX_ORDER; o++)
	{
		const int n = (int)pow(10, o); // rozmiar tablicy z danymi
		int* array1 = new int[n];
		for (int i = 0; i < n; i++)
		{
			int rand_val = rand() % 10001; // tu losowanie liczby calkowitej
			array1[i] = rand_val;
		}
		for (int i = 0; i < 10; i++) // skrotowy wypis tablicy do posortowania ( np . pewna liczba poczatkowych elementow )
		{
			cout << array1[i] << " ";
		}
		cout << endl;
		int* array2 = new int[n];
		int* array3 = new int[n];
		memcpy(array2, array1, n * sizeof(int)); // pierwsza kopia
		memcpy(array3, array1, n * sizeof(int)); // druga kopia
		// sortowanie przez zliczanie ( do wykonania w miejscu )
		clock_t t1 = clock();
		countingSort(array1, n, m);
		clock_t t2 = clock();
		double time = (t2 - t1) / (double)CLOCKS_PER_SEC;  // wypis pomiaru czasu i skrotowej postaci wynikowej tablicy
		cout << "Czas dodawania " << n << " elementow z tylu: " << time << endl;
		for (int i = 0; i < 10; i++)
		{
			cout << array1[i] << " ";
		}
		cout << endl;
		// sortowanie przez kopcowanie ( do wykonania w miejscu )
		t1 = clock();
		BinaryHeap<int>* bh = new BinaryHeap<int>(array2, n, place_int, true); // konstruktor kopca z
		//mozliwoscia przekazania zewnetrznej tablicy(ostatni argument wskazuje kierunek naprawy :
		//top - down lub bottom - up)
		bh->show();
		bh->sort(place_int);
		t2 = clock();
		time = (t2 - t1) / (double)CLOCKS_PER_SEC; // wypis pomiaru czasu i skrotowej postaci wynikowej tablicy
		cout << "Czas dodawania " << n << " elementow z tylu: " << time << endl;
		for (int i = 0; i < 10; i++)
		{
			cout << array2[i] << " ";
		}
		cout << endl;
		// sortowanie kubelkowe ( do wykonania w miejscu )
		t1 = clock();
		bucketSort(array3, n, m); // szczegolna wersja bucket sort tylko dla liczb calkowitych
		t2 = clock();
		time = (t2 - t1) / (double)CLOCKS_PER_SEC; // wypis pomiaru czasu i skrotowej postaci wynikowej tablicy
		cout << "Czas dodawania " << n << " elementow z tylu: " << time << endl;
		for (int i = 0; i < 10; i++)
		{
			cout << array3[i] << " ";
		}
		cout << endl;
		bool a = check(array1, array2, n);  // sprawdzenie zgodnosci tablic array1 , array2 , array3 i wypis informacji o zgodnosci na ekran
		bool b = check(array1, array3, n);
		bool c = check(array2, array3, n);
		cout << a << " " << b << " " << c << endl;
		delete[] array1, array2, array3;
	}

	system("PAUSE");
	return 0;
}
*/
int main()
{
	srand(time(NULL));
	const int MAX_ORDER = 7; // maksymalny rzad wielkosci sortowanych danych
	const double m_double = (double)pow(2, 30); // mianownik przy ustalaniu losowej liczby
												//z m i e n n o p r z e c i n k o w e j
	for (int o = 1; o <= MAX_ORDER; o++)
	{
		const int n = (int)pow(10, o); // rozmiar tablicy z danymi
		object** array1 = new object * [n];
		for (int i = 0; i < n; i++)
		{
			object* so = new object();
			so->field1 = ((rand() << 15) + rand()) / m_double; // przykladowy sposob wylosowania pola
															  //typu double(ktore bedzie stanowilo klucz sortowania)
			so->field2 = 'a' + rand() % 26; // przykladowy sposob wylosowania pola typu char
			array1[i] = so;
		}
		for (int i = 0; i < 10; i++) // skrotowy wypis tablicy do posortowania ( np . pewna liczba poczatkowych elementow )
		{
			cout << *array1[i] << " ";
		}
		cout << endl;
		object** array2 = new object * [n];
		memcpy(array2, array1, n * sizeof(object*)); // kopia
		// sortowanie przez kopcowanie
		clock_t t1 = clock();
		BinaryHeap<object*>* bh = new BinaryHeap<object*>(array1, n, placeWsk, true);
		// konstruktor kopca z mozliwoscia przekazania zewnetrznej tablicy ( ostatni
		//argument wskazuje kierunek naprawy : top - down lub bottom - up )
		bh->sort(placeWsk);
		clock_t t2 = clock();
		double time = (t2 - t1) / (double)CLOCKS_PER_SEC; // wypis pomiaru czasu i skrotowej postaci wynikowej tablicy
		cout << "Czas dodawania " << n << " elementow z tylu: " << time << endl;
		for (int i = 0; i < 10; i++)
		{
			cout << *array1[i] << " ";
		}
		cout << endl;
		// sortowanie kubelkowe
		t1 = clock();
		bucketSort<object*>(array2, n , 1.0, key, placeWsk); // trzeci
		//argument wskazuje, ze liczby sa z przedzialu[0, 1]
		t2 = clock();
		time = (t2 - t1) / (double)CLOCKS_PER_SEC; // wypis pomiaru czasu i skrotowej postaci wynikowej tablicy
		cout << "Czas dodawania " << n << " elementow z tylu: " << time << endl;
		for (int i = 0; i < 10; i++)
		{
			cout << *array2[i] << " ";
		}
		cout << endl;
		bool a = check(array1, array2, n);  // sprawdzenie zgodnosci tablic array1 , array2 i wypis informacji o zgodnosci na ekran
		cout << a << endl;
		delete[] array1, array2;
	}
	system("PAUSE");
	return 0;
}

