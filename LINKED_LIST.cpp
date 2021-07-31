#include <iostream>
using namespace std;


/* A linked list node */
class Node
{
    public:
    int data;

    // Pointer to the next node in DLL
    Node* next;

    // Pointer to the prev node in DLL
    Node* prev;
};
 
/* Given a reference (pointer to pointer) to the head of a list
   and an int, inserts a new node on the front of the list. */
void push(Node** head, int new_data)
{
    /* allocate node */
    Node* new_node = new Node();
 
    /* put in the data */
    new_node->data = new_data;
 
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

int search(Node** head, int k)
{
    // Stores head Node
    Node* temp = *head;
 
    // Stores position of the integer in DLL
    int pos = 0;
 
    // Traverse the DLL
    while (temp->data != k && temp->next != NULL) {
 
        // Update pos
        pos++;
 
        // Update temp
        temp = temp->next;
    }
 
    /* If the integer not present
        in the doubly linked list */
    if (temp->data != k)
        return -1;
 
    /* If the integer present in
        the doubly linked list */
    return (pos + 1);

}

/* Function to delete a node in a Doubly Linked List.
head_ref --> pointer to head node pointer.
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
    return;
}
 
// Prints nodes in a given DLL
void printList(Node* node)
{
    while (node != NULL)
    {
        cout << node->data << " ";
        node = node->next;
    }
}

int main()
{
    /* Start with the empty list */
    Node* head = NULL;
    int X = 8;
 
    // Creates the DLL 10<->8<->4<->2
    push(&head, 2);
    push(&head, 4);
    push(&head, 8);
    push(&head, 10);
 
    cout << "Original Linked list: ";
    printList(head);

    cout << "\nNode founded at: " << search(&head, X);

    /* delete nodes from the doubly linked list */
    deleteNode(&head, head); /*delete first node*/
    deleteNode(&head, head->next); /*delete middle node*/
 
    /* Modified linked list will be NULL<-8->NULL */
    cout << "\nModified Linked list: ";
    printList(head);
 
    return 0;
}