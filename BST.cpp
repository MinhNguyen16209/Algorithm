#include <iostream>
using namespace std;

struct node {
  int key;
  // Create 2 pointers that point to the left and the right child 
  struct node *left, *right;
};

// Create a new node
struct node *newNode(int value) {
  // Allocate the memory for the struct node temp to store value
  struct node *temp = (struct node *)malloc(sizeof(struct node));
  temp->key = value;
  // After being created, the node itself has a left and a right child
  temp->left = temp->right = NULL;
  return temp;
}

// Inorder Traversal
void inorder(struct node *root) {
  if (root != NULL) {
    // Traverse left
    inorder(root->left);

    // Traverse root
    cout << root->key << " -> ";

    // Traverse right
    inorder(root->right);
  }
}

// Insert a node
struct node *insert(struct node *node, int key) {
  // Return a new node if the tree is empty
  if (node == NULL) 
    return newNode(key);

  /* If the inserted key is less than the parent node, we traverse to
  the left branch to insert and vice-versa */
  if (key < node->key)
    node->left = insert(node->left, key);
  else
    node->right = insert(node->right, key);

  return node;
}

// Find the inorder successor
struct node *minValueNode(struct node *node) {
  struct node *current = node;

  // Find the leftmost leaf
  while (current && current->left != NULL)
    current = current->left;

  return current;
}

// Deleting a node
struct node *deleteNode(struct node *root, int key) {
  // Return the root if the tree is empty
  if (root == NULL) 
    return root;

  // Find the node to be deleted
  if (key < root->key)
    root->left = deleteNode(root->left, key);
  else if (key > root->key)
    root->right = deleteNode(root->right, key);
  else {
    // If the note has either one or no child
    if (root->left == NULL) {
      struct node *temp = root->right;
      free(root);
      return temp;
    } else if (root->right == NULL) {
      struct node *temp = root->left;
      free(root);
      return temp;
    }

    // If the node has two children
    struct node *temp = minValueNode(root->right);

    // Switch the place of inoder successor and the to be deleted node
    root->key = temp->key;

    // Delete the inorder successor
    root->right = deleteNode(root->right, temp->key);
  }
  return root;
}

// Find a node
void searchNode(struct node *root, int value) {
  if (root == NULL)
    cout << "Not found" << endl;
  // Compare the inserted value and the root
  /* If the value is below the root, we search in the left branch and vice-versa*/
  else if (value < root->key)
    searchNode(root->left, value);
  else if (value > root->key)
    searchNode(root->right, value);
  else cout << "Founded" << endl;
}

int main() {
  struct node *root = NULL;
  root = insert(root, 8);
  root = insert(root, 3);
  root = insert(root, 1);
  root = insert(root, 6);
  root = insert(root, 7);
  root = insert(root, 10);
  root = insert(root, 14);
  root = insert(root, 4);

  cout << "Inorder traversal: ";
  inorder(root);

  cout << "\nAfter deleting 10\n";
  root = deleteNode(root, 10);
  cout << "Inorder traversal: ";
  inorder(root);

  cout << "\nSearch for nodes: \n";
  searchNode(root, 8);
  searchNode(root, 17);
}