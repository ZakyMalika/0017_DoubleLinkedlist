#include <iostream>
using namespace std;

struct Node
{
	int noMhs;
	string name;
	Node* next;
	Node* prev;
};

Node* START = NULL;

void addNode()
{
	Node* newNode = new Node();		//step 1: create a new code
	cout << "\nEnter the roll number of the student: ";
	cin >> newNode->noMhs; // Assign value to the data field of the new Node
	cout << "\nEnter the name of the student: ";
	cin >> newNode->name; // Assign value to the data field of the new node

	// insert the new node in the list
	if (START == NULL || newNode->noMhs <= START->noMhs)
	{ //step 2: insert the new node at the beginning

		if (START == NULL && newNode->noMhs == START->noMhs)
		{
			cout << "\033[31mDuplicate roll numbers not allowed\033[0m" << endl;
			return;
		}

		// if the list is empty, make the new node the START
		newNode->next = START;	// step 3: make the new node point to the first node
		if (START != NULL)
		{
			START->prev = newNode;	// step 4: make the first node point to the new node
		}
		newNode->prev = NULL;	//step 5: make the new node point to NULL
		START = newNode;		// step 6: make the new node the first node
	}
	else
	{
		// insert the new node in the middle or the end
		Node *current = START;	//step 1.a: start from the first node
		Node* previous = NULL;	// step 1.b: previouse node is null intially

		while (current != NULL && current->noMhs < newNode->noMhs)
		{								// step 1.c: tranverse the list to find the correct position
			previous = current;			// step 1.d: move the previous to the current node
			current = current->next;	// step 1.e: move the current to the next node
		}
		newNode->next = current;		// step 4: make the next field of the new node point to current
		newNode->prev = previous;		// step 5: make the previous field of the new node point to previous

		if (current != NULL)
		{
			current->prev = newNode;	//step 6: make the previous field of the current node point to the new node
		}
		if (previous != NULL)
		{
			previous->next - newNode;	//step 7: make the next field of the previos node point to the neew node
		}
		else
		{
			// if previous is still NULL, it means newNode is now the first node
			START = newNode;
		}
	}
}

bool search(int rollNo, Node** previous, Node** current)
{
	*previous = NULL;
	*current = START;
	while (*current != NULL && (*current)->noMhs != rollNo)
	{
		*previous = *current;
		*current = (*current)->next;
	}
	return (*current != NULL);
}

void deletionNode()
{
	Node* previous, * current;
	int rollNo;

	cout << "\nEnter the roll number of the student whose record is the to be deleted: ";
	cin >> rollNo; //step 3: get the roll number to be delete

	if (START == NULL)
	{
		cout << "List is empty" << endl;
		return;
	}

	current = START; // step 1: start from the first node
	previous = NULL;

	// locate the node to be deleted
	while (current != NULL && current->noMhs != rollNo)
	{
		previous = current;
		current = current->next;
	}
	if (current == NULL)
	{
		cout << "\033[31mThe record with roll number " << rollNo << " not found\033[0m" << endl;
		return;
	}

	// node top be deleted is the first node
	if (current == START)
	{
		START = START->next;	// step 2: update the START pointer
		if (START != NULL)
		{
			START->prev = NULL;	
		}
	}
	else
	{	// Node to be the deleted is not the forst node
		previous->next = current->next;
		if (current->next != NULL)
		{	// if there's a succesor, update its prev pointer
			current->next->prev = previous;
		}
	}

	//release the memory of the node marked as current
	delete current;
	cout << "\x1b[32mRecord with roll number " << rollNo << " delete\x1b[0m" << endl;
}

bool ListEmpty()
{
	return (START == NULL);
}