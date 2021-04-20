#include "hash_table.h"
#include <ctime>

string random_key(int a)
{
	string key;
	key.resize(6);
	for (int i = 0; i < a; i++)
	{
		key[i] = rand() % 26 + 'A';
	}
	return key;
}

int main()
{
	const int MAX_ORDER = 7; // maksymalny rzad wielkosci dodawanych danych
	HashTable<int>* ht = new HashTable<int>(); // w tym przykladzie tablica mieszajaca par < string ,
													  //int > jako < klucz, wartosc >
	for (int o = 1; o <= MAX_ORDER; o++)
	{
		const int n = pow(10, o); // rozmiar danych
		// dodawanie do tablicy mieszajacej
		clock_t t1 = clock();

		for (int i = 0; i < n; i++)
			ht->add(random_key(6), i); // klucze losowe 6 - znakowe , a jako wartosci indeks petli
		clock_t t2 = clock();
		double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
		cout << "Czas dodawania " << n << " elementow: " << time << endl;
		ht->print(10);// wypis na ekran aktualnej postaci tablicy mieszajacej ( skrotowej ) oraz pomiarow czasowych
					 // wyszukiwanie w tablicy mieszajacej
		const int m = pow(10, 4);
		int hits = 0;
		t1 = clock();
		for (int i = 0; i < m; i++)
		{
			pair<string,int>* entry = ht->find(random_key(6)); // wyszukiwanie wg losowego klucza
			if (entry != NULL)
				hits++;
		}
		t2 = clock();
		time = (t2 - t1) / (double)CLOCKS_PER_SEC;
		cout << "Czas wyszukiwania elementow po kluczu: " << time << endl; // wypis na ekran pomiarow czasowych i liczby trafien
		cout << "Liczba trafien: " << hits << endl;
		// wypis statystyk ( dlugosci list kryjacych sie w tablicy mieszajacej )
		ht->print_stats();
		ht->clear(); // czyszczenie tablicy mieszajacej*/
	}
	delete ht;
	system("PAUSE");
	return 0;
}