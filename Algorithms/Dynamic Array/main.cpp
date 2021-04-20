
#include "dynamic_array.h"
#include <time.h>
#include <iostream>

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


int main()
{

	while (1)
	{
		Tab < object* >* da = new Tab < object* >(); // stworzenie tablicy
		const int order = 7; // rzad wielkosci rozmiaru dodawanych danych
		const int n = pow(10, order); // rozmiar danych
		// dodawanie do tablicy
		clock_t t1 = clock();
		double max_time_per_element = 0.0; // najgorszy zaobserwowany czas operacji dodawania
		for (int i = 0; i < n; i++) {
			object* so = new object(); // losowe dane
			clock_t t1_element = clock();
			da->push_back(so);
			clock_t t2_element = clock();
			double time_per_element = (t2_element - t1_element) / (double)CLOCKS_PER_SEC; // obliczenie czasu pojedynczej operacji dodawania
			if (time_per_element > max_time_per_element)
			{
				cout << "Nowy najgorszy czas odnotowany zostal prz elemencie " << i << endl; // odnotowanie nowego najgorszego czasu i komunikat informacyjny na ekran ( przy ktorym
																							//indeksie mialo to miejsce )
			}
		}
		clock_t t2 = clock();
		da->print(8); // wypis na ekran aktualnej postaci tablicy ( skrotowej ) i pomiarow czasowych ( czas calkowity i
					//zamortyzowany )
		da->clear(); // czyszczenie tablicy wraz z uwalnianiem pamieci danych
		delete da;
	}
	system("PAUSE");
	return 0;
}