#include "Queue.h"

Queue::Queue(int row, int col)
{
	phySize = row * col;
	data = new Type[phySize];
	head = 1;
	tail = 0;
	logSize = 0;
}

Queue::~Queue()
{
	delete[] data;
}

void Queue::MakeEmpty()
{
	head = 1;
	tail = 0;
	logSize = 0;
}

int Queue::isEmpty()
{
	return (AddOne(tail) == head);
}

int Queue::AddOne(int x)
{
	return((1 + x) % phySize);
}

Type Queue::Front()
{
	if (isEmpty())
	{
		cout << "Error: Queue Empty\n";
		exit(1);
	}
	return(data[head]);
}

void Queue::EnQueue(Type item)
{
	if (AddOne(AddOne(tail)) == head)
	{
		cout << "Error: Queue Full\n";
		exit(1);
	}
	tail = AddOne(tail);
	data[tail] = item;
	logSize++;
}

Type Queue::DeQueue()
{
	if (isEmpty())
	{
		cout << "Error: Queue Empty\n";
		exit(1);
	}
	Type item = data[head];
	head = AddOne(head);
	logSize--;
	return(item);
}

int Queue::getSize() const
{
	return logSize;
}