#include "Node.h"

Node::Node()
{
	next = nullptr;
}

Node::~Node()
{

}

Node::Node(Type item, Node* ptr)
{
	data = item;
	next = ptr;
}

void Node::InsertAfter(Node* newnode)
{
	newnode->next = next;
	next = newnode;
}

Node* Node::DeleteAfter()
{
	Node* temp = next;
	if (next == nullptr)
		return nullptr;
	next = temp->next;
	return(temp);
}