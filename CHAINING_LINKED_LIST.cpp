#include <iostream>
#include <math.h>
#include <string>
using namespace std;
#define TABLE_SIZE 100

int convertStrToInt(string key)
{
	int result = 0;
	for (int i = 0; i < key.size(); ++i) {
		int j = key.size() - i - 1;
		result += key[i] * pow(128, j);
	}
	return result;
}

int hashFunction(string key)
{
	int result = convertStrToInt(key);
	return (result % TABLE_SIZE);
}

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
	Node *head;
	Node *tail;
};

List *createList(string key, int value)
{
	List *ls = new List;
	ls->head = new Node;
	ls->head->key = key;
	ls->head->value = value;
	ls->head->next = NULL;
	ls->head->prev = NULL;
	ls->tail = ls->head;
	return ls;
}

List *push(List *ls, string key, int value)
{
	Node *temp = new Node;
	temp->key = key;
	temp->value = value;
	temp->prev = NULL;
	temp->next = ls->head;
	ls->head->prev = temp;
	ls->head = temp;
	return ls;
}

List *deleteHead(List *ls)
{
	Node *nd = ls->head->next;
	Node *temp = ls->head;
	nd->prev = NULL;
	ls->head = nd;
	free(temp);
	return ls;
}

List *deleteTail(List *ls)
{
	Node *nd = ls->tail->prev;
	Node *temp = ls->tail;
	nd->next = NULL;
	ls->tail = nd;
	free(temp);
	return ls;
}

int searchIndex(List *ls, string key)
{
	Node *nd = ls->head;
	int index = 0;
	while (nd != NULL) {
		if (nd->key == key) {
			return index;
		}
		nd = nd->next;
		index++;
	}
	return -1;
}

List *deleteIndex(List *ls, int index)
{
	Node *nd = ls->head;
	for (int i = 0; i < index - 1; i++) {
		nd = nd->next;
	}
	Node *temp = nd->next;
	nd->next = nd->next->next;
	free(temp);
	return ls;
}

List *deleteNode(List *ls, string key)
{
	Node *nd = ls->head;
	while (nd != NULL) {
		int index = searchIndex(ls, key);
		if (index == -1) {
			return ls;
		} else {
			Node *new_nd = ls->head;
			if (index == 0 && new_nd->prev == NULL && new_nd->next != NULL) {
				ls = deleteHead(ls);
				cout << "Deleted the head, " << key << endl;
			} else if (index != 0 && new_nd->prev != NULL && new_nd->next == NULL) {
				ls = deleteTail(ls);
				cout << "Deleted the tail, " << key << endl;
			} else if (index == 0 && new_nd->prev == NULL && new_nd->next == NULL) {
				ls->head = NULL;
				ls = NULL;
				cout << "Deleted the node, " << key << endl;
			} else {
				ls = deleteIndex(ls, index);
				cout << "Deleted the node at index, " << key << endl;
			}
		}
		nd = nd->next;
	}
	return ls;
}

int searchNode(List *ls, string key) 
{
	Node *nd = ls->head;
	while (nd != NULL) {
		if (nd->key == key) {
			return nd->value;
		}
		nd = nd->next;
	}
	return -1;
}

void displayNode(List *ls)
{
	Node *nd = ls->head;
	while (nd != NULL) {
		cout << "<" << nd->key << ", " << nd->value << ">" << " <-> ";
		nd = nd->next;
	}
	cout << "X" << endl;
}

int searchTable (List **hash_table, string key)
{
	int index = hashFunction(key);
	if (hash_table[index] == NULL) {
		return -1;
	} else {
		if (searchNode(hash_table[index], key) != -1) {
			return searchNode(hash_table[index], key);
		}
	}
	return -1;
}

void insertTable(List **hash_table, string key, int value)
{
	// indicates the index using hash function
	int index = hashFunction(key);
	if (hash_table[index] == NULL) {
		hash_table[index] = createList(key, value);
	} else {
		hash_table[index] == push(hash_table[index], key, value);
	}
}

void deleteTable(List **hash_table, string key)
{
	if (searchTable(hash_table, key) == -1) {
		cout << "Invalid key!" << endl;
	} else {
		// indicates the index using hash function
		int index = hashFunction(key);
		hash_table[index] = deleteNode(hash_table[index], key);
	}
}

void displayTable(List **hash_table)
{
	for (int i = 0; i < TABLE_SIZE; i++) {
		if (hash_table[i] == NULL) {
			continue;
		} else {
			cout << "Position: " << i + 1 << " ";
			displayNode(hash_table[i]);
		}
	}	
}

List *hash_table[TABLE_SIZE];
int main()
{
	cout << "Insert nodes:" << endl;
	insertTable(hash_table, "GOLD", 1);
	insertTable(hash_table, "ALUP", 2);
	insertTable(hash_table, "SILV", 3);
	insertTable(hash_table, "ALUM", 4);
	insertTable(hash_table, "TITA", 5);
	insertTable(hash_table, "PLAS", 6);
	insertTable(hash_table, "PLAS", 1);
	insertTable(hash_table, "PLAT", 7);
	insertTable(hash_table, "TITH", 8);
	displayTable(hash_table);

	cout << endl;
	cout << "Search a node: " << endl;
	string search_node = "TITA";
	if (searchTable(hash_table, search_node) != -1) {
		cout << "The value of " << search_node << " is " << searchTable(hash_table, search_node) << endl;
	} else {
		cout << search_node << " is invalid!" << endl;
	}

	cout << endl;
	cout << "Delete a node:" << endl;
	string delete_node = "TITH";
	deleteTable(hash_table, delete_node);

	cout << endl;
	displayTable(hash_table);
}