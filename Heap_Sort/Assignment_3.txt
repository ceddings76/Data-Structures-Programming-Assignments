/*********************************************************************************************************
CS5343 - Algorithm Analysis and Data Structures
Cliff Eddings
Assignment 3

This program implements the heap sort algorithm.  The program outputs an array of a random list of integers,
makes the heap, and sorts the array in ascending order. Ascending order requires a max heap.
1.	Initialize an array of random numbers, in this program we will use integers, at least 20 integers
2.	Print the random numbers in the array.
3.	Build the heap.
4.	Print the heap in the array.
5.	Sort the heap using heap sort.
6.	Print the sorted array.

Submit code and screenshots of code running showing each printout.

*********************************************************************************************************/
#include <iostream>
#include <cstdlib>					//pull the library to use the random integer generator.

using namespace std;

const int SIZE = 21;

void fill_array(int arr[])		//initialize an array or integers
{
	int integer = 0;					//variable used to insert a random integer into the array
	arr[0] = SIZE-1;					//number of nodes of the heap goes into the index = 0

	for (int i = 1; i < (SIZE); i++)
	{
		integer = rand();				//generate random number
		integer = integer % 100;		//get an integer using the modulus operator
		arr[i] = integer;				//add the integer to the arrary.

	}
}

void print_array(int arr[])
{
	for (int i = 1; i < (SIZE); i++)										//print the contents of the array.
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}

void max_heapify(int arr[], int index, int size)					//max heapify function to percolate the values down.
{
	if (index <= size/2)											//check the node in question is not a leaf node.
	{
		int left_child = index * 2;									//set the left and right children indexes.
		int right_child = left_child + 1;
		int max = index;											//variable to hold the largest value location in the array.
		if (left_child <= size && arr[left_child] > arr[index])		//compare the left and right nodes to the index selecting the largest value's index
			max = left_child;
		if (right_child <= size && arr[right_child] > arr[max])
			max = right_child;
		if (max != index)											//if the max index is not the parent index do this work and swap values.
		{															//then recursively call the method on the swapped index
			int temp = arr[index];
			arr[index] = arr[max];
			arr[max] = temp;
			max_heapify(arr, max, size);
		}
	}
	else
	{
		return;
	}
}

void build_heap(int arr[])
{
	int last_parent = ((SIZE - 1) / 2);				//set the last parent node.
	for (int i = last_parent; i > 0; i--)			//go from the last parent node to the root node.
	{
		max_heapify(arr, i, SIZE);					//call heapify on the index to percolate up.
	}
}

void heap_sort(int arr[])
{
	int heap_size = SIZE-1;							//set the heap size
	while(heap_size != 1)							//traverse the heap.
	{
		int temp = arr[1];							//switch index 1 with the last index.
		arr[1] = arr[heap_size];
		arr[heap_size] = temp;
		max_heapify(arr, 1, (heap_size-1));			//run heapify on index 1 down to the end of the heap.
		heap_size--;
	}
}

int main()
{
	cout << endl << "This program builds an array with 20 random integers, builds a heap, and sorts the heap\n";
	cout << "in ascending order using heap sort.\n\n";

	char choice = 'Y';

	do
	{
		int ranArray[SIZE];
		fill_array(ranArray);
		cout << "The number of nodes in the heap is indicated by index 0 will be: " << ranArray[0] << endl;   //number of nodes is indicated by index = 0
		cout << endl << "The numbers generated randomly are: \n";
		print_array(ranArray);

		cout << endl << "The array after the build heap method is ran: \n";
		build_heap(ranArray);																				//build the heap
		print_array(ranArray);

		cout << endl << "The array in ascending order after the heap sort method is ran: \n";
		heap_sort(ranArray);																				//sort the heap in ascending order
		print_array(ranArray);

		cout << endl << endl << "Would you like to run the program again? Enter Y for yes or N for No.\n";
		cin >> choice;

	} while (choice == 'Y' || choice == 'y');


	getchar();
	return 0;
}
