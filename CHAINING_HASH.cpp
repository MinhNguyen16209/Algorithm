#include <iostream>
#include <math.h>
#include <string>
using namespace std;
#define TABLE_SIZE 100

class Node
{
public:
	string key;
	int value;
	Node *prev;
	Node *next;
};

class List
{
public:
	Node* head;
};

// Converts from string to int using base 128
int convertToInt(string key) {
	int result = 0;
    for (int i = 0; i < key.size(); i++) {
    int j = key.size() - i - 1;
        result += key[i] * pow(128, j);
    }
    return result;
}

int hashFunction(string key) {
    int result = convertToInt(key);
    return result % TABLE_SIZE;
}

List *createList(string key, int value)
{
	List *list = new List;
	list->head = new Node;
	list->head->key = key;
	list->head->value = value;
	list->head->next = NULL;
	list->head->prev = NULL;
	return list;
}

List *push(List *list, string key, int value)
{
	Node *temp = new Node;
	temp->key = key;
	temp->value = value;
	temp->prev = nullptr;
	temp->next = list->head;
	list->head->prev = temp;
	list->head = temp;
	return list;
}

void insertNode(List** hashTable, string key, int value)
{
	int index = hashFunction(key);
	if (hashTable[index] == NULL) {
		hashTable[index] = createList(key, value);
	} else {
		hashTable[index] = push(hashTable[index], key, value);
	}
}

int findIndex(List *list, string key)
{
	Node *temp = list->head;
	int index = 0;
	while (temp != NULL) {
		if (temp->key == key) {
			return index;
		}
		index++;
		temp = temp->next;
	}
	return -1;
}

List *deleteHead(List *list)
{
	Node *temp = list->head->next;
	Node *p = list->head;
	temp->prev = NULL;
	list->head = temp;
	delete(p);
	return list;
}

List *deleteIndex(List *list, int index) {
	Node *temp = list->head;
	for (int i = 0; i < index - 1; i++) {
		temp = temp->next;
	}
	Node *p = temp->next;
	temp->next = temp->next->next;
	delete(p);	
	return list;
}

List *deleteNode(List *list, string key)
{
	Node *temp = list->head;
	while (temp != NULL) {
		int index = findIndex(list, key);
		if (index == -1) {
			return list;
		} else {
			Node *now = list->head->next;
			if (index == 0 && now->prev == NULL && now->next != NULL) {
				list = deleteHead(list);
			} else if (index == 0 && now->next == NULL && now->prev == NULL) {
				list->head = NULL;
				list = NULL;
			} else {
				list = deleteIndex(list, index);
			}
		}
		temp = temp->next;
	}
	return list;
}

int search(List *list, string key) {
	Node *temp = list->head;
	while (temp != NULL) {
		if (temp->key == key)
			return temp->value;
		temp = temp->next;
	}
	return -1;
}

int searchNode(List **hashTable, string key)
{
	int index = hashFunction(key);
	if (hashTable[index] == NULL) {
		return -1;
	} else {
		if (search(hashTable[index], key) != -1) {
			return search(hashTable[index], key);
		}
	}
	return -1;
}

void searchResult(List** hashTable, string key) {
    if (searchNode(hashTable, key) != -1) {
        cout << key <<  " founded with value of " << searchNode(hashTable, key) << endl;
    } else {
        cout << key << " not founded!" << endl;
    }
}

void deleteResult(List **hashTable, string key)
{
	if (searchNode(hashTable, key) == -1) {
		cout << key << " is invalid!" << endl;
	} else {
		int index = hashFunction(key);
		hashTable[index] = deleteNode(hashTable[index], key);
	}
}

void print(List *list)
{
	Node *temp = list->head;
	while (temp != NULL) {
		cout << "<" << temp->key << "," << temp->value << ">" << "<->";
		temp = temp->next;
	}
	cout << "X" << endl;
}

void printNode(List** hashTable)
{
	for (int i = 0; i < TABLE_SIZE; i++) {
		if (hashTable[i] == NULL) {
			continue;
		} else {
			cout << "Pos:" << i + 1 << "\t";
			print(hashTable[i]);
		}
	}
}

List* hashTable[TABLE_SIZE];

int main()
{
    cout << "Original:" << endl;
    insertNode(hashTable, "IRON", 1);
    insertNode(hashTable, "IRON", 2);
    insertNode(hashTable, "GOLD", 2);
    insertNode(hashTable, "WOOD", 3);
    insertNode(hashTable, "PLAS", 4);
    insertNode(hashTable, "PLAT", 5);
    insertNode(hashTable, "DIAM", 6);
    insertNode(hashTable, "SILV", 7);
    printNode(hashTable);
    cout << endl;

    cout << "Search a node:" << endl;
    searchResult(hashTable, "PLAT");
   	cout << endl;

   	cout << "Delete a node" << endl;
   	deleteResult(hashTable, "IRON");
   	printNode(hashTable);

}

