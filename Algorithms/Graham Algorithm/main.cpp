#include "graham.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <cstdlib>
#include <time.h>


int main()
{
	for (int i = 1; i <= 5; i++)
	{
		fstream file;
		string text;
		int number;
		vector<Node> points;

		file.open("points" + to_string(i) + ".txt", ios::in);
		cout << "Plik: points" + to_string(i) + ".txt" << endl;

		if (!file.is_open())
		{
			cout << "Plik nie istnieje" << endl;
			return 0;
		}

		getline(file, text);
		number = stoi(text);

		string data1;
		string data2;

		for (int i = 0; i < number; i++)
		{
			file >> data1 >> data2;
			getline(file, text);
			Node node(stod(data1), stod(data2));
			points.push_back(node);
		}

		vector<Node> Graham;

		Graham = graham(points);
		cout << "Rozmiar: " << Graham.size() << endl;

	}

	system("PAUSE");
	return 0;
}