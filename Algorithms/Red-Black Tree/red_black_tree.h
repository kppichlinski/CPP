#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <iostream>
#include <math.h>

using namespace std;

template<class T>
class Tree;

template<class T>
class Node
{
protected:

	T data;
	Node<T>* parent;
	Node<T>* right;
	Node<T>* left;
	bool flag;
	static int number;
	int index;
	//czarny=true;

public:


	Node(T value)
	{
		data = value;
		parent = nullptr;
		right = nullptr;
		left = nullptr;
		index = number;
		number++;
	}

	~Node()
	{
		parent = nullptr;
		right = nullptr;
		left = nullptr;
	}

	const T& getData() const
	{
		return data;
	}

	Node<T>* getLeft()
	{
		return left;
	}

	Node<T>* getRight()
	{
		return right;
	}


	friend class Tree<T>;

};

template<class T>
class Tree
{
private:

	int size;
	Node<T>* root;

	void rotate_left(Node<T>* x, Node<T>* y)
	{
		if (y == nullptr)
		{
			return;
		}
		else
		{
			if (y->left != nullptr)
			{
				x->right = y->left;
				y->left->parent = x;
			}
			else
			{
				x->right = nullptr;
			}
			if (x->parent != nullptr)
			{
				y->parent = x->parent;
			}
			if (x->parent == nullptr)
			{
				root = y;
				y->parent = nullptr;
			}
			else if (x == x->parent->left)
			{
				x->parent->left = y;
			}
			else
			{
				x->parent->right = y;
			}
			y->left = x;
			x->parent = y;
		}
	}

	void rotate_right(Node<T>* x, Node<T>* y)
	{
		if (y == nullptr)
		{
			return;
		}
		else
		{
			if (y->right != nullptr)
			{
				x->left = y->right;
				y->right->parent = x;
			}
			else
			{
				x->left = nullptr;
			}
			if (x->parent != nullptr)
			{
				y->parent = x->parent;
			}
			if (x->parent == nullptr)
			{
				root = y;
				y->parent = nullptr;
			}
			else if (x == x->parent->left)
			{
				x->parent->left = y;
			}
			else
			{
				x->parent->right = y;
			}
			y->right = x;
			x->parent = y;
		}
	}

public:

	Tree()
	{
		root = nullptr;
		size = 0;
	}

	~Tree()
	{
		Node<T>* temp = root;
		temp->number = 0;
		del(temp);
		root = nullptr;
		size = 0;
	}

	Node<T>* getRoot()
	{
		return root;
	}

	void add(const T& value, bool (*comp)(T, T))
	{
		Node<T>* adder = new Node<T>{ value };
		if (size == 0)
		{
			adder->flag = true;
			adder->parent = nullptr;
			adder->data = value;
			root = adder;
			size++;
			return;
		}

		Node<T>* temp = root;
		Node<T>* prev = nullptr;
		while (temp != nullptr)
		{
			prev = temp;
			if (place(value, temp->data))
			{
				temp = temp->right;
			}
			else
			{
				temp = temp->left;
			}
		}
		temp = adder;
		adder->parent = prev;
		if (place(value, prev->data))
		{
			prev->right = adder;
		}
		else
		{
			prev->left = adder;
		}
		change_color(adder);
		size++;
	}

	void change_color(Node<T>* node)
	{
		Node<T>* temp = node;
		if (root == temp)
		{
			temp->flag = true;
			return;
		}
		while (temp->parent != nullptr && temp->parent->flag == false)
		{
			if (temp->parent->parent->left == temp->parent)
			{
				if (temp->parent->parent->right != nullptr && temp->parent->parent->right->flag == false)
				{
					temp->parent->flag = true;
					temp->parent->parent->right->flag = true;
					temp->parent->parent->flag = false;
					temp = temp->parent->parent;
				}
				else
				{
					if (temp->parent->right == temp)
					{
						temp = temp->parent;
						rotate_left(temp, temp->right);
					}
					temp->parent->parent->flag = false;
					temp->parent->flag = true;
					rotate_right(temp->parent->parent, temp->parent->parent->left);
				}
			}
			else
			{
				if (temp->parent->parent->left != nullptr && temp->parent->parent->left->flag == false)
				{
					temp->parent->flag = true;
					temp->parent->parent->left->flag = true;
					temp->parent->parent->flag = false;
					temp = temp->parent->parent;
				}
				else
				{
					if (temp->parent->left == temp)
					{
						temp = temp->parent;
						rotate_right(temp, temp->left);
					}
					temp->parent->parent->flag = false;
					temp->parent->flag = true;
					rotate_left(temp->parent->parent, temp->parent->parent->right);
				}
			}
			root->flag = true;
		}
	}

	Node<T>* find(const T& value, int (*comp)(T, T))
	{
		Node<T>* temp = root;
		while (temp != nullptr)
		{
			if (difference(value, temp->data) == 0)
			{
				return temp;
			}
			else if (difference(value, temp->data) == -1)
			{
				temp = temp->left;
			}
			else
			{
				temp = temp->right;
			}
		}
		return NULL;
	}

	void inorderHelp(Node<T>* node)
	{
		if (node != nullptr)
		{
			inorderHelp(node->left);
			cout << node->data << " ";
			inorderHelp(node->right);
		}
	}

	void preorderHelp(Node<T>* node)
	{
		if (node != nullptr)
		{
			cout << node->data << " ";
			preorderHelp(node->left);
			preorderHelp(node->right);
		}
	}

	void inorder()
	{
		Node<T>* temp = root;
		inorderHelp(temp);
	}

	void preorder()
	{
		Node<T>* temp = root;
		preorderHelp(temp);
	}

	int max(int a, int b)
	{
		int bigger;
		if (a > b)
		{
			bigger = a;
		}
		else
		{
			bigger = b;
		}
		return bigger;
	}

	int height(Node<T>* node)
	{
		if (node == nullptr)
		{
			return 0;
		}
		return (1 + max(height(node->left), height(node->right)));

	}

	void printHeight()
	{
		if (size == 0)
		{
			cout << "Drzewo jest puste" << endl;
		}
		Node<T>* temp = root;
		cout << height(temp) - 1 << endl;;
	}

	void del(Node<T>* node)
	{
		if (node == nullptr)
		{
			return;
		}
		del(node->left);
		del(node->right);
		delete node;
	}



	void disp(Node<T>* temp,int elements,int& counter)
	{
		if (counter == elements)
		{
			return;
		}
		if (temp != nullptr)
		{

			cout << "(";
			cout << temp->index << ": [";
			if (temp->flag)
			{
				cout << "black";
			}
			else
			{
				cout << "red";
			}
			cout << ", p: ";
			if (temp->parent == nullptr)
			{
				cout << "NULL";
			}
			else
			{
				cout << temp->parent->index;
			}
			cout << ", l: ";
			if (temp->left == nullptr)
			{
				cout << "NULL";
			}
			else
			{
				cout << temp->left->index;
			}
			cout << ", r: ";
			if (temp->right == nullptr)
			{
				cout << "NULL";
			}
			else
			{
				cout << temp->right->index;
			}

			cout << "]" << "(" << temp->data << "))" << endl;

			counter++;

			if (temp->left != nullptr)
			{
				disp(temp->left,elements,counter);
			}
			if (temp->right != nullptr)
			{
				disp(temp->right,elements,counter);
			}

		}
	}

	void show(int elements)
	{
		if (size == 0)
		{
			cout << "Drzewo jest puste" << endl;
			return;
		}
		static int counter = 0;
		Node<T>* temp = root;
		cout << "Rozmiar: " << size << endl;
		cout << "{" << endl;
		disp(temp,elements,counter);
		cout << "}" << endl;
		counter = 0;
	}

};

template<class T>
int Node<T>::number = 0;

#endif