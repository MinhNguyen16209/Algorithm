#include <iostream>
using namespace std;


/* A linked list node */
class Node
{
    public:
    int key;

    // Pointer to the next node in DLL
    Node* next;

    // Pointer to the prev node in DLL
    Node* prev;
};
 
/* Given a reference (pointer to pointer) to the head of a list
   and an int, inserts a new node on the front of the list. */
void push(Node** head, int new_key)
{
    /* allocate node */
    Node* new_node = new Node();
 
    /* put in the key */
    new_node->key = new_key;
 
    /* since we are adding at the beginning,
    prev is always NULL */
    new_node->prev = NULL;
 

    /* link the old list off the new node */
    new_node->next = *head;
 
    /* change prev of head node to new node */
    if (*head != NULL)
        (*head)->prev = new_node;
 
    /* move the head to point to the new node */
    *head = new_node;
}

int search(Node** head, int key)
{
    // Stores head Node
    Node* temp = *head;
 
    // Stores position of the integer in DLL
    int pos = 0;
 
    // Traverse the DLL
    while (temp->key != key && temp->next != NULL) {
 
        // Update pos
        pos++;
 
        // Update temp
        temp = temp->next;
    }
 
    /* If the integer not present
        in the doubly linked list */
    if (temp->key != key)
        return -1;
 
    /* If the integer present in
        the doubly linked list */
    return (pos + 1);

}

/* Function to delete a node in a Doubly Linked List.
head --> pointer to head node pointer.
del --> pointer to node to be deleted. */
void deleteNode(Node** head, Node* del)
{
    /* base case */
    if (*head == NULL || del == NULL)
        return;
 
    /* If node to be deleted is head node */
    if ( *head == del)
        *head = del->next;
 
    /* Change next only if node to be
    deleted is NOT the last node */
    if (del->next != NULL)
        del->next->prev = del->prev;
 
    /* Change prev only if node to be
    deleted is NOT the first node */
    if (del->prev != NULL)
        del->prev->next = del->next;
 
    /* Finally, free the memory occupied by del*/
    free(del);
}

void deleteSearch(Node **head, int key)
{
    // Search for the postition
    if (search(head, key) != -1) {
        int pos = search(head, key);

        // If DLL is NULL or invalid index
        if (*head == NULL || pos <= 0) {
            return;
        }
     
        Node *temp = *head;

        // Traversing to the node at the index
        for (int i = 1; temp != NULL && i < pos; i++) {
            temp = temp->next;
        }
     
        // If index is greater than the number of nodes in DLL
        if (temp == NULL) {
            return;
        }

        deleteNode(head, temp);
    } else return;
}

// Prints nodes in a given DLL
void printList(Node* node)
{
    while (node != NULL)
    {
        cout << node->key << " ";
        node = node->next;
    }
}

int main()
{
    /* Start with the empty list */
    Node* head = NULL;
 
    // Creates the DLL 10<->8<->4<->2
    push(&head, 1);
    push(&head, 7);
    push(&head, 8);
    push(&head, 12);
    push(&head, 9);
 
    cout << "Original Linked list: ";
    printList(head);

    cout << "\nNode founded at: " << search(&head, 8);

    /* delete nodes from the doubly linked list */
    deleteSearch(&head, 12); /*delete first node*/
 
    /* Modified linked list will be NULL<-8->NULL */
    cout << "\nModified Linked list: ";
    printList(head);
 
    return 0;
}