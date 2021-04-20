#include "binary_heap.h"
#include <time.h>

struct object
{
	int field1;
	char field2;

	object()
	{

	}

	object(int i)
	{
		field1 = rand() % 10000001;
		field2 = rand() % 26 + 'A';
	}

};



bool place(object so1, object so2)
{
	if (so1.field1 > so2.field1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

ostream& operator<<(ostream& out, const object& o)
{
	return out << o.field1 << "," << o.field2;
}

int main()
{
	srand(time(NULL));

	const int MAX_ORDER = 7; // maksymalny rzad wielkosci dodawanych danych
	BinaryHeap < object >* bh = new BinaryHeap < object >();
	for (int o = 1; o <= MAX_ORDER; o++)
	{
		const int n = pow(10, o); // rozmiar danych
		// dodawanie do kopca
		clock_t t1 = clock();
		for (int i = 0; i < n; i++) {
			object so = object(1); // losowe dane
				bh->add(so, place);
		}
		clock_t t2 = clock();
		double time = (t2 - t1) / (double)CLOCKS_PER_SEC; // wypis na ekran aktualnej postaci kopca ( skrotowej ) oraz pomiarow czasowych
		cout << "Czas dodawania " << n << " elemenow: " << time << endl;
		bh->show();
		// pobieranie ( i usuwanie ) elementu maksymalnego z kopca
		t1 = clock();
		for (int i = 0; i < n; i++) {
			object polled = bh->delMax(place);// argument : wskaznik na komparator
			if (n < 20) // ewentualny wypis na ekran danych elementu pobranego ( przy malym eksperymencie )
			{
				cout << "Nowy najwiekszy element: ";
				if (bh->getSize() == 0)
				{
					cout << "Brak najwiekszego elementu. Lista pusta" << endl;
				}
				else
				{
					cout << polled << endl;
				}
			}
		}
		t2 = clock();
		time = (t2 - t1) / (double)CLOCKS_PER_SEC; // wypis na ekran aktualnej postaci kopca ( kopiec pusty ) oraz pomiarow czasowych
		cout << "Czas usuwania " << n << " elemenow: " << time << endl;
		bh->show(); 
		
		bh->clear(); // czyszczenie kopca ( tak naprawde ,, zresetowanie ’’ tablicy dynamicznej opakowanej przez kopiec )
	}
	delete bh;

	/*BinaryHeap <object>* bh = new BinaryHeap<object>();
	bh->show();
	for (int i = 0; i < 10; i++)
	{
		object so = object(1);
		bh->add(so, place);
	}
	bh->show();
	bh->delMax(place);
	bh->show();

	delete bh;*/

	system("PAUSE");
	return 0;
}