#pragma once
#include "Point.h"

typedef Point Type;

class Node
{
public:
	Type data;
	Node* next;
	Node();
	Node(Type item, Node* ptr = nullptr);
	~Node();
	void InsertAfter(Node* newnode);
	Node* DeleteAfter();
};