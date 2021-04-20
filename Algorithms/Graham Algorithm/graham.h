#ifndef GRAHAM_H
#define GRAHAM_H

#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <cstdlib>

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

	bool operator==(Node& n)
	{
		return (x == n.x) && (y == n.y);
	}

};

int direction(Node a, Node b, Node c)
{
	double value = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);
	if (value > 0)
	{
		return -1;
	}
	else if (value < 0)
	{
		return 1;
	}
	return 0;
}

bool compare(int a, int b, vector<Node> nodes, double min)
{
	int dir = direction(nodes[a], nodes[min], nodes[b]);
	if (nodes[a] == nodes[min] || nodes[b] == nodes[min])
	{
		return nodes[a].x > nodes[b].x;
	}
	return dir > 0;
}

int direction(Node a, Node b)
{
	double value = a.y * b.x - b.y * a.x;
	if (value < 0)
	{
		return 1;
	}
	return 0;
}

vector<Node> graham(vector<Node> nodes)
{
	double ymin = nodes[0].y;
	int min = 0;
	int size = nodes.size();

	for (int i = 1; i < size; i++)
	{
		double y = nodes[i].y;

		if ((y < ymin) || (ymin == y && nodes[i].x < nodes[min].x))
		{
			ymin = nodes[i].y;
			min = i;
		}
	}

	vector<int> index(size, 0);

	sort(index.begin(), index.end(), compare);

	for (int i = 0; i < size; i++)
	{
		cout << nodes[i].x << " " << nodes[i].y << endl;
	}

	vector<Node> final_nodes;

	final_nodes.push_back(nodes[0]);
	final_nodes.push_back(nodes[1]);

	for (int i = 2; i < size; i++)
	{
		final_nodes.push_back(nodes[i]);

		while (i < size - 1 && direction(final_nodes[final_nodes.size() - 2], final_nodes[final_nodes.size() - 1]))
		{
			cout << "siema" << endl;
			final_nodes.erase(final_nodes.end() - 1);
		}

	}

	return final_nodes;
}

#endif
