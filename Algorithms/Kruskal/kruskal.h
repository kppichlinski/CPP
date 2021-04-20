#ifndef KRUSKAL_H
#define KRUSKAL_H

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct Node
{
	double x;
	double y;

	Node(double x, double y)
	{
		this->x = x;
		this->y = y;
	}
};

struct Edge
{
	int index1, index2;
	double weight;

	Edge(int index1, int index2, double weight)
	{
		this->index1 = index1;
		this->index2 = index2;
		this->weight = weight;
	}
};

class Graph
{
private:

	vector<Edge> edges;

public:

	Graph(vector<Edge> e)
	{
		edges = e;
	}

	Graph()
	{

	}

	size_t get_size()
	{
		return edges.size();
	}

	void set_edges(vector<Edge> e)
	{
		edges = e;
	}

};

class UnionFind
{
private:

	int* parents;
	int* rank;

	int find_number;

public:

	UnionFind(int n)
	{
		parents = new int[n];
		rank = new int[n];
		for (int i = 0; i < n; i++)
		{
			rank[i] = 0;
			parents[i] = i;
		}
	}

	~UnionFind()
	{
		delete[] parents;
		delete[] rank;
	}

	int get_find_number()
	{
		return find_number;
	}

	void merge(int ind1, int ind2)
	{
		parents[ind1] = ind2;
	}

	void merge_by_rank(int ind1, int ind2)
	{
		if (rank[ind1] > rank[ind2])
		{
			parents[ind2] = ind1;
		}
		else if (rank[ind1] < rank[ind2])
		{
			parents[ind1] = ind2;
		}
		else
		{
			parents[ind1] = ind2;
			rank[ind2]++;
		}
	}

	int findCompressed(int ind)
	{
		find_number++;
		if (parents[ind] == ind)
		{
			return ind;
		}
		parents[ind] = findCompressed(parents[ind]);
		return findCompressed(parents[ind]);
	}

	int find(int ind)
	{
		find_number++;
		if (parents[ind] == ind)
		{
			return ind;
		}
		return findCompressed(parents[ind]);
	}

};


#endif

