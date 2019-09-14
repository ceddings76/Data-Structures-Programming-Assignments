/*************************************************************************************************************************
Programming Assignment CS5343
Make a single linked list of integers.  There should be at least 15 nodes.  The list should not be sorted.
1.	Traverse the list
2.	Sort the list, list should be sorted by unlinking the nodes and relinking them. Use selection sort.
3.	Traverse the list again.
4.	Submit the complete code.
5.	A readme file with instructions to compile.
6.	Screenshot of the program execution.
*************************************************************************************************************************/

#include <iostream>
#include <cstdlib>							//pull the library to run the random integer generator

using namespace std;


struct node									//declaration for the list structure
{
	int value;								//Integer value held by the node
	struct node *next;						//pointer for the next node
};

struct node *head = nullptr; 				//pointer for the head, default value is NULL
	
void append(node *temp, int data)			//method to append a new node to the end of the list, with recursion
{
	if (temp == nullptr)
	{
		node *newNode;
		newNode = new node;
		newNode->value = data;
		newNode->next = nullptr;
		head = newNode;
		return;
	}
	else if (temp->next == nullptr)
	{
		node *newNode;
		newNode = new node;
		newNode->value = data;
		newNode->next = nullptr;
		temp->next = newNode;
		return;
	}
	else
		return append(temp->next, data);
};

void display(node *temp)					//method to traverse and print the list, with recursion
{
	if (temp == nullptr)
	{
		cout << "The list is empty." << endl;
		return;
	}
	else
	{
		cout << " " << temp->value;
		if (temp->next == nullptr)
			return;
		return display(temp->next);
	}
};

void createList(int counter)				//method to create a list based on the size of the argument.
{
	for (int i = 0; i < counter; i++)
	{
		int integer = rand();
		integer = integer % 100;
		append(head, integer);
	}
};

void sortList(node *temp)					//sort list from class.
{
	node *current;
	node *current2;
	node *min;
	int tmp;
	current = temp;
	while (current != nullptr)
	{
		min = current;
		current2 = current->next;
		while (current2 != nullptr)
		{
			if (min->value > current2->value)
				min = current2;
			current2 = current2->next;
		}
		tmp = current->value;
		current->value = min->value;
		min->value = tmp;
		current = current->next;
	}
};

void selectSort(node *temp)
{
	node *current = nullptr;			//node to start at the head of the list for traversing the list
	node *parent1 = nullptr;			//node to keep track of the current node's previous node
	node *index = nullptr;				//node to traverse the list and find the minimum value
	node *previous = nullptr;			//node to keep track of indexes previous node
	node *min = nullptr;				//node to keep track of the minimum value
	node *parent2 = nullptr;			//node to keep  track of node min's parent

	current = temp;						//set the current node to head to begin.
	while (current != nullptr)			//start traversing the list
	{
		min = current;					//start the min value at the current node value
		index = current->next;			//set the index to the next node in the sequence.
		previous = current;				//set the previous tracking node to the node before index.
		while (index != nullptr)		//start the index traversal of the list.
		{
			if (min->value > index->value)	//compare the min value to the index value to find the minimum value
			{
				min = index;
				parent2 = previous;
			}
			index = index->next;
			previous = previous->next;
		}
		if (current->value > min->value)	//if, else statement to determine if a swap on the nodes needs to be made.
		{
			if (current == head)			//if statement to do the work if the current node is the head node.
			{
				parent2->next = min->next;
				min->next = current;
				head = min;
			}
			else							//the current node is not the head do this work.
			{
				parent2->next = min->next;
				min->next = current;
				parent1->next = min;
			}
			current = min;
			parent1 = current;
			current = current->next;
		}
		else								//if no swap needs to be made go to the next node.
		{
			parent1 = current;
			current = current->next;
		}
		//display(head);
		//cout << endl << endl;
	}
};

void destroyList(node *temp)
{
	node *placeholder = temp;
	while (temp)
	{
		placeholder = temp;
		temp = temp->next;
		head = temp;
		delete placeholder;
	}
}

int main()
{
	cout << "This program creates a singly linked list of random integer values, displays";
	cout << endl << "the unsorted list, sorts the linked list by unlinking and relinking";
	cout << endl << "the nodes, and then displaying the sorted list." << endl << endl << endl;

	char choice = 'Y';

	do
	{

		createList(15);

		cout << "The head of the list is ";
		cout << head->value << endl << endl;

		cout << "The list contains: ";
		display(head);
		cout << endl << endl;

		//sortList(head);

		selectSort(head);

		cout << "The list sorted using selection sort is ordered: ";
		display(head);
		cout << endl;

		cout << endl << "The head of the sorted list is ";
		cout << head->value << endl << endl;

		destroyList(head);

		cout << endl << "Would you like to run the program again? Enter Y or N.\n";
		cin >> choice;
		cout << endl;

	} while (choice == 'Y' || choice == 'y');

	getchar();
	return 0;
}