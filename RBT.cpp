#include <iostream>
using namespace std;

struct Node
{
	int key;
	// Set pointers that point to parent, left child and right child
	Node *parent, *left, *right;
	// 1 for RED and 0 for BLACK
	int color; 
};

typedef Node *NodePtr;

class RBT {
private:
	NodePtr root;
	NodePtr NIL;
public:
	RBT()
	{
		NIL = new Node;
		NIL->color = 0;
		NIL->left = nullptr;
		NIL->right = nullptr;
		root = NIL;
	}

	NodePtr searchTree(NodePtr node, int k)
	{
		if (node == NIL || k == node->key)
			return node;
		else if (k < node->key)
			return searchTree(node->left, k);
		else if(k > node->key)
			return searchTree(node->right, k);
		else return nullptr;
	}

	void leftRotate(NodePtr x) {
		// Create y as the right child of x
		NodePtr y = x->right;
		// Set the right child of x to the left child of y
		x->right = y->left;
		/* If the left child of y is not NIL, change the parent of 
		the left child of y to x */
		if (y->left != NIL)
			y->left->parent = x;
		// Set the parent of y to the parent of x
		y->parent = x->parent;
		// If the parent of x is NIL, set root to y
		if (x->parent == nullptr)
			this->root = y;
		// Else if x is a left child, set the parent of x to y.
		else if (x == x->parent->left)
			x->parent->left = y;
		// Else change the parent of x to y
		else x->parent->right = y;
		// Set x as the left child of y
		y->left = x;
		// Set y as the parent of x
		x->parent = y;
	}

	void rightRotate(NodePtr y) {
		// Create x as the left child of y
		NodePtr x = y->left;
		// Set the left child of y to the right child of x
		y->left = x->right;
		/* If the right child of y is not NIL, change the parent of 
		the right child of x to y */
		if (x->right != NIL)
			x->right->parent = y;
		// Set the parent of x to the parent of y
		x->parent = y->parent;
		// If the parent of y is NIL, set root to y
		if (y->parent == nullptr)
			this->root = x;
		// Else if y is a right child, set the parent of y to x.
		else if (y == y->parent->right)
			y->parent->right = x;
		// Else change the parent of y to x
		else y->parent->left = x;
		// Set y as the right child of x
		x->right = y;
		// Set x as the parent of y
		y->parent = x;
	}	

	void fixInsert(NodePtr node) {
		NodePtr uncle;
		// While the color of the parent node is RED
		while (node->parent->color == 1) {
			/* If the parent node is on the left ,
			set uncle node to the right */
			if (node->parent == node->parent->parent->left) {
				uncle = node->parent->parent->right;
				// Case 1: if the uncle node is RED (LL Rotation)
				if (uncle->color == 1) {
					// Set the color of the parent node to BLACK 
					node->parent->color = 0;
					// Set the color of the uncle node to BLACK
					uncle->color = 0;
					/* Set the color of the grandparent node to RED as 
					both uncle and parent node are BLACK*/
					node->parent->parent->color = 1;
					// Set the new node to the grandparent node
					node = node->parent->parent;
				/* Case 2: if the uncle node is BLACK and 
				the new node is on the right */
				} else {
					if (node == node->parent->right) {
						// Set the new node to the parent node
						node = node->parent;
						/* Do a left rotation around the parent of the new node,
						which is a left child, and both it and its parent are RED */
						leftRotate(node);
					}

					// Case 3: uncle node is BLACK and the new node is a left child
					// Set the parent node color to BLACK
					node->parent->color = 0;
					// Set the grandparent node color to RED
					node->parent->parent->color = 1;
					// Do a left rotation around the grandparent node
					rightRotate(node->parent->parent);
				}
			/* If the parent node is on the right, 
			set the uncle node to the left */
			} else {
				uncle = node->parent->parent->left;
				// Case 4: if the uncle node is RED
				if (uncle->color == 1) {
					// Set the color of the parent node to BLACK 
					node->parent->color = 0;
					// Set the color of the uncle node to BLACK
					uncle->color = 0;
					/* Set the color of the grandparent node to RED as 
					both uncle and parent node are BLACK*/
					node->parent->parent->color = 1;
					// Set the new node to the grandparent node
					node = node->parent->parent;
				/* Case 5: if the uncle node is BLACK and 
				the new node is on the left */
				} else {
					if (node == node->parent->left) {
						// Set the new node to the parent node
						node = node->parent;
						/* Do a right rotation around the parent of the new node,
						which is a right child, and both it and its parent are RED */
						rightRotate(node);
					}

					// Case 6: uncle node is BLACK and the new node is a right child
					// Set the parent node color to BLACK
					node->parent->color = 0;
					// Set the grandparent node color to RED
					node->parent->parent->color = 1;
					// Do a left rotation around the grandparent node
					leftRotate(node->parent->parent);
				}
			}
			if (node == root)
				break;
		}
		// Set the color of the root to BLACK
		root->color = 0;
	}

	void printTree(NodePtr root, string prefix, bool branch)
	{
		if (root != NIL) {
			cout << prefix;
			if (branch) {
				// Right child
				cout << "R----";
				prefix += "     ";
			} else {
				// Left child
				cout << "L----";
				prefix += "|    ";
			}
            string sColor;
            if (root->color)
                sColor = "RED";
            else
                sColor = "BLACK";
			cout << root->key << "(" << sColor << ")" << endl;
			// Print the left subtree
			printTree(root->left, prefix, false);
			// Print the right subtree
			printTree(root->right, prefix, true);
		}
	}

	NodePtr searchRBT(int k)
	{
		return searchTree(this->root, k);
	}

	void insertNode(int key)
	{
		NodePtr node = new Node;
		node->parent = nullptr;
		node->key = key;
		node->left = NIL;
		node->right = NIL;

		// Color of a new node is always RED
		node->color = 1;

		// Program of insertion
		NodePtr y = nullptr;
		NodePtr x = this->root;


		while (x != NIL)
		{
			y = x;
			if (node->key < x->key)
				x = x->left;
			else
				x = x->right;
		}

		node->parent = y;
		if (y == nullptr)
			root = node;
		else if (node->key < y->key)
			y->left = node;
		else 
			y->right = node;
		/* If the parent node is the root, change the node color 
		and return */
		if (node->parent == nullptr) {
			// Change the node color to BLACK
			node->color = 0;
			return;
		}
		// If the grandparent node is the root, return
		if (node->parent->parent == nullptr)
			return;
		// Fix the tree
		fixInsert(node);
	}

	void printRBT()
	{
		if (root)
			printTree(this->root, "", true);
	}
};

int main()
{
    RBT tree;
    tree.insertNode(11);
    tree.insertNode(2);
    tree.insertNode(14);
    tree.insertNode(1);
    tree.insertNode(7);
    tree.insertNode(5);
    tree.insertNode(8);

    tree.insertNode(12);
    tree.insertNode(10);

    tree.searchRBT(10);

    tree.printRBT();
}
