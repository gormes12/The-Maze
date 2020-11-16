#include "Stack.h"

Stack::Stack()
{
	top = nullptr;
}

Stack::~Stack()
{
	MakeEmpty();
}

void Stack::MakeEmpty()
{
	Node* temp;
	while (top!=nullptr)
	{
		temp = top;
		top = top->next;
		delete temp;
	}
}

int Stack::isEmpty()
{
	return(top == nullptr);
}


void Stack::Push(Type item)
{
	top = new Node(item, top);
}

Type Stack::Pop()
{
	if (isEmpty())
	{
		cout << "Error:STACK UNDERFLOW\n";
		exit(1);
	}
	Node* temp = top;
	Type item = top->data;
	top = top->next;
	delete temp;
	return item;
}

Type Stack::Top()
{
	return top->data;
}