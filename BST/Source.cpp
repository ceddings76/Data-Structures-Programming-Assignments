/**********************************************************************************************
CS5343 Programming assignment #2
First make a BST, Binary Search Tree, algorithm given in class.
DO NOT USE THE ARRAY REPRESENTATION FOR BST.
The NODE structure must NOT have parent pointer.
Binary Search Tree has the following properties:
	-left subtree of a node contains only nodes with keys lesser than the node's key
	-right subtree of a node contains only nodes with keys greater than the node's key
	-left and right subtree must each also be a binary search tree
	-no duplicate nodes.
	-Tree must have at least 15 nodes.
1. Make tht BST and do an inorder traversal.
2.	Delete the nodes as follows:
	a.	a leaf node, then do an inorder traversal.
	b.	a node that has a subtree and do an inorder traversal again.
Submit code
Submit screenshots
**********************************************************************************************/
#include <iostream>
#include <cstdlib>			//library to use random integer generator.

using namespace std;

class BST
{
private:
	struct bstnode
	{
		int value;			//value held in the node
		bstnode *left;		//pointer to the left child
		bstnode *right;		//pointer to the right child
		
	};

public:

	bstnode *root;			//pointer for the root of the tree

	BST()					//constructor for the BST class tree
	{
		root = nullptr;
	}

	void insert(bstnode *temp, int data)		//method to insert a new node using recursion
	{
		if (temp == nullptr)					//base case is the tree is empty
		{
			if (root == nullptr)
			{
				bstnode *newNode;
				newNode = new bstnode;
				newNode->value = data;
				newNode->left = nullptr;
				newNode->right = nullptr;
				root = newNode;
			}
		}
		else if (temp->value < data)			//if data greater than the node value go right
		{
			if (temp->right == nullptr)			//if the child is empty add the value here
			{
				bstnode *newNode;
				newNode = new bstnode;
				newNode->value = data;
				newNode->left = nullptr;
				newNode->right = nullptr;
				temp->right = newNode;
			}
			else
				return insert(temp->right, data);		//otherwise recursive call and go right.
		}
		else											//else go to the left
		{
			if (temp->left == nullptr)					//if the left child is empty add here
			{
				bstnode *newNode;
				newNode = new bstnode;
				newNode->value = data;
				newNode->left = nullptr;
				newNode->right = nullptr;
				temp->left = newNode;
			}
			else
				return insert(temp->left, data);		//otherwise recursive call and go left.
		}
	}

	void inorderTrav(bstnode *temp)		//recursive function to display in order traversal: left child, then parent, then right child
	{
		if (temp != nullptr)
		{
			inorderTrav(temp->left);
			cout << temp->value << " ";
			inorderTrav(temp->right);
		}
	}

	void createTree(int counter)
	{
		for (int i = 0; i < counter; i++)
		{
			int integer = 0;
			cout << "Insert an integer value: ";
			cin >> integer;
			insert(root, integer);
		}
	}

	void deleteNode(bstnode *temp1, bstnode *temp2, int data)
	{
		if (temp2 == nullptr)
		{
			cout << "cannot delete, node not in the tree." << endl;		//base case, tree is empty
			return;
		}
		if (temp2->value == data)										//case does the work
		{
			bstnode *lft = nullptr;
			bstnode *rgt = nullptr;
			bstnode *work = nullptr;

			if (temp2 == root)
			{
				lft = temp2->left;
				rgt = temp2->right;
				work = temp2->right;
				while (work->left != nullptr)
				{
					rgt = work;
					work = work->left;
				}
				work->left = lft;
				if (work != temp2->right)
				{
					work->right = temp2->right;
					rgt->left = nullptr;
				}
				else
					work->right = temp2->right;
				root = work;
				work = temp2;
				delete work;
				return;
			}
			else if (temp2->left != nullptr && temp2->right != nullptr)
			{
				lft = temp2->left;
				rgt = temp2->right;
				work = temp2->right;
				while (work->left != nullptr)
				{
					rgt = work;
					work = work->left;

				}
				if (work != temp2->right)
				{
					work->right = temp2->right;
					rgt->left = nullptr;
				}
				else
					work->right = nullptr;
				work->left = lft;				
				if (temp1->left == temp2)
					temp1->left = work;
				else
					temp1->right = work;
				work = temp2;
				delete work;
				return;
			}
			else if (temp2->left == nullptr && temp2->right != nullptr)
			{
				rgt = temp2->right;
				work = temp2->right;
				while (work->left != nullptr)
				{
					rgt = work;
					work = work->left;
				}
				work->left = nullptr;
				if (work != temp2->right)
				{
					work->right = temp2->right;
					rgt->left = nullptr;
				}
				else
					work->right = nullptr;
				if (temp1->left == temp2)
					temp1->left = work;
				else
					temp1->right = work;
				work = temp2;
				delete work;
				return;

			}
			else if (temp2->left != nullptr && temp2->right == nullptr)
			{
				lft = temp2->left;
				work = temp2;
				if (temp1->left == temp2)
					temp1->left = lft;
				else
					temp1->right = lft;
				delete work;
				return;				
			}
			else
			{
				work = temp2;
				if (temp1->left == temp2)
				{
					temp1->left = nullptr;
					delete work;
				}
				else
				{
					temp1->right = nullptr;
					delete work;
				}
				return;
			}
		}
		else if (temp2->value > data)									//recursion call to the left.
		{
			if (temp2->left != nullptr)
			{
				temp1 = temp2;
				temp2 = temp2->left;
				return deleteNode(temp1, temp2, data);
			}
		}
		else															//recursion call to the right.
		{
			if (temp2->right != nullptr)
			{
				temp1 = temp2;
				temp2 = temp2->right;
				return deleteNode(temp1, temp2, data);
			}
		}

	}
};

int main()
{
	cout << "\nThis program creates a binary search tree using a class implementation.\n";
	cout << "The tree is created with 15 nodes, an in-order traversal is performed displaying the\n";
	cout << "nodes, a leaf node is deleted and the tree is displayed again, a subtree node\n";
	cout << "is deleted, and the tree displayed again.\n\n";
	
	char choice = 'Y';

	do
	{
		BST tree;

		tree.createTree(15);
		
		cout << "\nThe root of the tree is: " << tree.root->value << endl;
		cout << "The tree traversed in order is as follows: ";
		tree.inorderTrav(tree.root);
		cout << endl << endl;

		int val = 0;
		cout << "Enter the leaf value you would like to delete." << endl;
		cin >> val;
		
		tree.deleteNode(tree.root, tree.root, val);

		cout << "\nThe root of the tree is: " << tree.root->value << endl;
		cout << "The tree traversed in order after deletion of leaf node " << val << " is as follows: ";
		tree.inorderTrav(tree.root);
		cout << endl << endl;

		val = 0;
		cout << "Enter the internal node value you would like to delete." << endl;
		cin >> val;
		
		tree.deleteNode(tree.root, tree.root, val);

		cout << "\nThe root of the tree is: " << tree.root->value << endl;
		cout << "The tree traversed in order after deletion of node " << val << " is as follows: ";
		tree.inorderTrav(tree.root);
		cout << endl << endl;

		cout << "Would you like to run the program again?" << endl;
		cin >> choice;
		
		cout << endl << endl;

	} while (choice == 'Y' || choice == 'y');

	getchar();		//call for the program to wait for input before exiting.
	return 0;
}