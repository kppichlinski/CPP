#include "red_black_tree.h"
#include <time.h>

struct object
{
	int field1;
	char field2;

	object()
	{
		field1 = rand() % 1000001;
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

int difference(object so1, object so2)
{
	int diff = so1.field1 - so2.field1;

	if (diff == 0)
	{
		return 0;
	}
	else if (diff < 0)
	{
		return -1;
	}
	else
	{
		return 1;
	}

}

ostream& operator<<(ostream& out, const object& o)
{
	return out << o.field1 << "," << o.field2;
}

int main()
{
	/*
	const int MAX_ORDER = 7; // maksymalny rzad wielkosci dodawanych danych
	Tree <object>* rbt = new Tree <object>(); // stworzenie drzewa
	for (int o = 1; o <= MAX_ORDER; o++)
	{
		const int n = pow(10, o); // rozmiar danych
		// dodawanie do drzewa
		clock_t t1 = clock();
		for (int i = 0; i < n; i++)
		{
			rbt->add(object(), place); // dodanie ( drugi argument to wskaznik na komparator )
		}
		clock_t t2 = clock();
		double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
		cout << "Czas dodawania " << n << " elemenow: " << time << endl;
		rbt->show(8); // wypis na ekran aktualnej postaci drzewa ( skrotowej ) wraz z wysokoscia oraz pomiarow czasowych
			// wyszukiwanieno tak

		const int m = pow(10, 4); // liczba prob wyszukiwania
		int hits = 0; // liczba trafien
		t1 = clock();
		for (int i = 0; i < m; i++)
		{
			Node <object>* result = rbt->find(object(), difference);
			if (result != NULL)
				hits++;
		}
		t2 = clock();
		time = (t2 - t1) / (double)CLOCKS_PER_SEC;
		cout << "Czas wyszukiwania " << m << " elemenow: " << time << endl; // wypis na ekran pomiarow czasowych i liczby trafien
		cout << "Liczba trafien: " << hits << endl;

	}
	delete rbt;*/


	
			Tree <object>* rbt = new Tree <object>(); // stworzenie drzewa
			object so;
			so.field1 = 55;
			so.field2 = 'Q';
			rbt->add(so, place);

			so.field1 = 69;
			so.field2 = 'U';
			rbt->add(so, place);

			so.field1 = 62;
			so.field2 = 'A';
			rbt->add(so, place);

			so.field1 = 57;
			so.field2 = 'N';
			rbt->add(so, place);

			so.field1 = 35;
			so.field2 = 'D';
			rbt->add(so, place);

			so.field1 = 83;
			so.field2 = 'I';
			rbt->add(so, place);

			so.field1 = 72;
			so.field2 = 'V';
			rbt->add(so, place);

			so.field1 = 74;
			so.field2 = 'X';
			rbt->add(so, place);

			so.field1 = 85;
			so.field2 = 'S';
			rbt->add(so, place);

			so.field1 = 96;
			so.field2 = 'O';
			rbt->add(so, place);

			so.field1 = 46;
			so.field2 = 'C';
			rbt->add(so, place);

			so.field1 = 49;
			so.field2 = 'P';
			rbt->add(so, place);
		
			so.field1 = 52;
			so.field2 = 'U';
			rbt->add(so, place);

			rbt->show(8);
			rbt->printHeight();

			rbt->preorder();

			delete rbt;
			
	system("PAUSE");
	return 0;
}
