#pragma once
#include "Point.h"
#include "Node.h"
#include <iostream>
using namespace std;


typedef Point Type;

class Stack
{
private:
	Node* top; // pointer to top of stack
public:
	Stack();
	~Stack();
	void MakeEmpty();
	int isEmpty();
	
	void Push(Type item);
	Type Pop();
	Type Top();
};