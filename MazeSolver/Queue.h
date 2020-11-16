#pragma once
#include "Point.h"
#include <iostream>
using namespace std;


typedef Point Type;

class Queue
{
private:
	int head, tail;
	Type* data;
	int AddOne(int x);
	int phySize;
	int logSize;

public:
	Queue(int row, int col);
	~Queue();
	void MakeEmpty();
	int isEmpty();
	Type Front();
	void EnQueue(Type item);
	Type DeQueue();
	int getSize() const;

};