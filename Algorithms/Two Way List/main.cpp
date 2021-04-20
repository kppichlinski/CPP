#include "two_way_list.h"
#include <iostream>
#include <time.h>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>  

using namespace std;

struct object
{
	int field1;
	char field2;

	object()
	{
		field1 = rand() % 10001;
		field2 = rand() % 26 + 'A';
	}

};

ostream& operator<<(ostream& out, const object& o)
{
	return out << o.field1 << " " << o.field2;
}

int difference(object *so1, object *so2)
{
	int diff = so1->field1 - so2->field1;

	if (diff != 0)
	{
		return diff;
	}

	return so1->field2 - so2->field2;
}

bool place(object* so1, object* so2)
{
	if (so2->field1 > so1->field1)
	{
		return true;
	}
	else if (so2->field1 == so1->field1)
	{
		if (so2->field2 > so1->field2)
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


int main()
{
		srand(time(NULL));
		/*
		Lista < object > ll;

				object so;

				clock_t t1 = clock();

				for (int i = 0; i < 100000; i++)
				{
					so.field1 = rand() % 10001;
					so.field2 = rand() % 26 + 'A';
					ll.push_back(so);
				}

				clock_t t2 = clock();
				double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
				cout << "Czas dodawania 100000 elementow z przodu: " << time << endl;

				t1 = clock();

				for (int i = 0; i < 100000; i++)
				{
					so.field1 = rand() % 10001;
					so.field2 = rand() % 26 + 'A';
					ll.push_front(so);
				}

				t2 = clock();
				time = (t2 - t1) / (double)CLOCKS_PER_SEC;
				cout << "Czas dodawania 100000 elementow z tylu: " << time << endl;


				t1 = clock();

				for (int i = 0; i < 10000; i++)
				{
					ll.remove_back();
				}

				t2 = clock();
				time = (t2 - t1) / (double)CLOCKS_PER_SEC;
				cout << "Czas usuwania 10000 elementow z tylu: " << time << endl;

				t1 = clock();

				for (int i = 0; i < 10000; i++)
				{
					ll.remove_front();
				}

				t2 = clock();
				time = (t2 - t1) / (double)CLOCKS_PER_SEC;
				cout << "Czas usuwania 10000 elementow z przodu: " << time << endl;


				so.field1 = 23;
				so.field2 = 'B';

				object ao;
				ao.field1 = 25;
				ao.field2 = 'M';


				ll.print(5);

				ll.return_by_index(15);

				ll.replace(10000, so);

				t1 = clock();

				ll.search(so,*difference);

				t2 = clock();
				time = (t2 - t1) / (double)CLOCKS_PER_SEC;
				cout << "Czas wyszukiwania elementu po wartosci: " << time << endl;

				ll.print(8);

				t1 = clock();

				ll.remove_by_value(so,*difference);

				t2 = clock();
				time = (t2 - t1) / (double)CLOCKS_PER_SEC;
				cout << "Czas usuwania elementu po wartosci: " << time << endl;

				ll.remove_by_value(ao,*difference);

				ll.print(9);

				ll.insert(2, ao);

				ll.print(4);

				t1 = clock();

				ll.clear();

				t2 = clock();
				time = (t2 - t1) / (double)CLOCKS_PER_SEC;
				cout << "Czas usuwania calej listy: " << time << endl;
				*/

		const int MAX_ORDER = 4; // maksymalny rzad wielkosci rozmiaru dodawanych danych
		Lista<object*>* ll = new Lista < object* >();

		for (int o = 1; o <= MAX_ORDER; o++) // petla po kolejnych rzedach wielkosci
		{
			const int n = pow(10, o); // rozmiar danych
			// dodawanie do listy
			clock_t t1 = clock();
			for (int i = 0; i < n; i++) {
				object* so = new object(); // losowe dane
				ll->find_place(so, place);
			}
			clock_t t2 = clock();
			double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
			cout << "Czas dodawania " << n << " elemenow: " << time << endl;

			ll->print(8);// wypis na ekran aktualnej postaci listy ( skrotowej ) i pomiarow czasowych

			// wyszukiwanie i usuwanie z listy
			const int m = pow(10, 4); // liczba prob wyszukania
			t1 = clock();
			for (int i = 0; i < m; i++) {
				object* so = new object(); // losowe dane jako wzorzec do wyszukiwania ( obiekt chwilowy )
				ll->remove_by_value(so, difference);
				delete so;
			}
			t2 = clock();
			time = (t2 - t1) / (double)CLOCKS_PER_SEC;
			cout << "Czas wyszukania " << m << " i usuniecia tych, ktore zgadzaja sie z kluczem: " << time << endl;

		}

		object* so = new object();
		ll->replace(5,so);
		ll->print(8);
		ll->search(so, difference);
		ll->remove_by_value(so,difference);
		ll->print(8);
		so = new object();
		ll->insert(2,so);
		ll->print(8);

		delete ll;
	
	system("PAUSE");
	return 0;
	}



	// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
	// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

	// Porady dotyczące rozpoczynania pracy:
	//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
	//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
	//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
	//   4. Użyj okna Lista błędów, aby zobaczyć błędy
	//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
	//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
