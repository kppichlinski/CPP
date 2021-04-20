#include "kruskal.h"
#include <fstream>
#include <string>
#include <cstdlib>
#include <time.h>

bool compare(Edge e1, Edge e2)
{
	return e1.weight < e2.weight;
}

pair<Graph, pair<double, int>> kruskal(vector<Edge> e, int option)
{
	double min_weight = 0;
	int find_number = 0;
	vector<Edge> edges;
	UnionFind un(e.size());

	clock_t begin = clock();
	sort(e.begin(), e.end(), compare);

	clock_t end = clock();
	double sort_time = (end - begin) / (double)CLOCKS_PER_SEC;
	double algorithm_time = 0;

	cout << "Czas sortowania: " << sort_time << endl;

	if (option == 1)
	{
		begin = clock();

		for (auto& it : e)
		{
			int x = it.index1;
			int y = it.index2;

			int set_x = un.find(x);
			int set_y = un.find(y);

			if (set_x != set_y)
			{
				min_weight += it.weight;
				edges.push_back(it);
				un.merge(set_x, set_y);
			}
		}

		end = clock();
		double algorithm_time = (end - begin) / (double)CLOCKS_PER_SEC;
	}

	if (option == 2)
	{
		begin = clock();

		for (auto& it : e)
		{
			int x = it.index1;
			int y = it.index2;

			int set_x = un.findCompressed(x);
			int set_y = un.findCompressed(y);

			if (set_x != set_y)
			{
				min_weight += it.weight;
				edges.push_back(it);
				un.merge(set_x, set_y);
			}
		}

		end = clock();
		double algorithm_time = (end - begin) / (double)CLOCKS_PER_SEC;
	}
	if (option == 3)
	{
		begin = clock();

		for (auto& it : e)
		{
			int x = it.index1;
			int y = it.index2;

			int set_x = un.find(x);
			int set_y = un.find(y);

			if (set_x != set_y)
			{
				min_weight += it.weight;
				edges.push_back(it);
				un.merge_by_rank(set_x, set_y);
			}
		}

		end = clock();
		double algorithm_time = (end - begin) / (double)CLOCKS_PER_SEC;
	}
	if (option == 4)
	{
		begin = clock();

		for (auto& it : e)
		{
			int x = it.index1;
			int y = it.index2;

			int set_x = un.findCompressed(x);
			int set_y = un.findCompressed(y);

			if (set_x != set_y)
			{
				min_weight += it.weight;
				edges.push_back(it);
				un.merge_by_rank(set_x, set_y);
			}
		}

		end = clock();
		double algorithm_time = (end - begin) / (double)CLOCKS_PER_SEC;
	}

	cout << "Czas algorytmu: " << algorithm_time << endl;

	Graph final_graph(edges);

	pair<double, int> data;
	data.first = min_weight;
	data.second = un.get_find_number();
	return make_pair(final_graph, data);
}

int main()
{
	for (int i = 1; i < 4; i++)
	{
		fstream file;
		vector<Edge> e;
		vector<Node> n;
		string text;
		int line = 1;
		int number = 0;

		file.open("g" + to_string(i) + ".txt", ios::in);
		cout << "Plik: g" + to_string(i) + ".txt" << endl;

		if (!file.is_open())
		{
			cout << "Plik nie istnieje" << endl;
			return 0;
		}

		getline(file, text);
		number = stoi(text);
		line++;

		string data1;
		string data2;
		string data3;

		for (int i = line; i < number + line; i++)
		{
			file >> data1 >> data2;
			getline(file, text);
			Node node(stod(data1), stod(data2));
			n.push_back(node);
		}

		line += number;

		getline(file, text);
		line++;

		while (!file.eof())
		{
			file >> data1 >> data2 >> data3;
			Edge edge(stod(data1), stod(data2), stod(data3));
			e.push_back(edge);
		}

		file.close();

		pair<Graph, pair <double, int>> result;

		for (int i = 1; i < 5; i++)
		{
			cout << "Sposob: " << i << endl;
			result = kruskal(e, i);
			cout << "Minimalna waga: " << result.second.first << endl;
			cout << "Ilosc krawedzi: " << result.first.get_size() << endl;
			cout << "Liczba operacji finds: " << result.second.second << endl;
		}

		cout << endl;
	}
	system("PAUSE");
	return 0;
}