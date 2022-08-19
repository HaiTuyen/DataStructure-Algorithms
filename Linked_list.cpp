#include <iostream>
using namespace std;

struct NODE {
	int key;
	NODE* p_next;
};

struct List {
	NODE* p_head;
	NODE* p_tail;
};

//4.1:
NODE* createNode(int data) {
	NODE* p = new NODE;
	if (p == NULL) {
		return NULL;
	}
	p->key = data;
	p->p_next = NULL;
	return p;
}

//4.2:
List* createList(NODE* p_node) {
	List* L = new List;
	if (L == NULL) {
		return NULL;
	}
	L->p_head = L->p_tail = p_node;
	return L;
}

// Ham viet them
void initList(List*& L) 
{
   L = new List;
   L->p_head = NULL;
   L->p_tail = NULL;
}

//4.3:
bool addHead(List*& L, int data) {
	NODE* p = createNode(data);
	if (p == NULL) {
		return false;
	}
	if (L->p_head == NULL) {
		L->p_head = L->p_tail = p;
	}
	else {
		p->p_next = L->p_head;
		L->p_head = p;
	}
	return true;
}

//4.4:
bool addTail(List*& L, int data) {
	NODE* p = createNode(data);
	if (p == NULL) {
		return false;
	}
	if (L->p_head == NULL){
		L->p_head = L->p_tail = p;
	}
	else {
		L->p_tail->p_next = p;
		L->p_tail = p;
	}
	return true;
}

//4.5:
void removeHead(List*& L) {
	if (L->p_head == NULL) {
		exit(0);
	}
	if (L->p_head == L->p_tail) {
		delete[] L->p_head;
		L->p_head = L->p_tail = NULL;
	}
	else {
		NODE* temp = L->p_head;
		L->p_head = L->p_head->p_next;
		delete[] temp;
	}
}

//4.6:
void removeTail(List*& L) {
	if (L->p_head == NULL) {
		exit(0);
	}
	if (L->p_head == L->p_tail) {
		delete L->p_head;
		L->p_head = L->p_tail = NULL;
	}
	else {
		NODE* temp = L->p_head;
		for (temp; temp->p_next != L->p_tail; temp = temp->p_next);
		delete L->p_tail;
		L->p_tail = temp;
		L->p_tail->p_next = NULL;
	}
}

//4.7:
void removeAll(List*& L) {
	if (L->p_head == NULL) {
		exit(0);
	}
	NODE* p;
	while (L->p_head) {
		p = L->p_head;
		L->p_head = L->p_head->p_next;
		delete[] p;
	}
}

//4.8: 
void removeBefore(List*& L, int val) {
	if (L->p_head == NULL) {
		return;
	}
	//if linked list has just 1 node or the head node key equal to val
	if (L->p_head == L->p_tail || L->p_head->key == val) {
		return;
	}
	if (L->p_head->p_next->key == val) {
		removeHead(L);
	}
	else {
		NODE* temp = L->p_head;
		for (temp; temp != NULL; temp = temp->p_next) {
			if (temp->p_next->p_next->key == val) {
				NODE* prev = temp->p_next;
				temp->p_next = temp->p_next->p_next;
				delete[] prev;
				break;
			}
		}
	}
}

//4.9: Remove an integer after a value of a given list:
void removeAfter(List*& L, int val) {
	if (L->p_head == NULL) {
		return;
	}
	if (L->p_head == L->p_tail || L->p_tail->key == val) {
		return;
	}
	NODE* temp = L->p_head;
	for (temp; temp->p_next != NULL; temp = temp->p_next) {
		if (temp->key == val) {
			if (temp->p_next == L->p_tail) {
				removeTail(L);
				break;
			}
			else {
				NODE* after = temp->p_next;
				temp->p_next = temp->p_next->p_next;
				delete[] after;
				break;
			}
		}
	}
}

//4.10: Insert an integer at a position of a given List:
bool addPos(List*& L, int data, int pos) {
	if (pos < 0) {
		cout << "Invalid position ";
		return false;
	}

	NODE* flag = L->p_head;
	while (--pos) {
		if (pos == -1) break;
		flag = flag->p_next;
		if (flag == NULL) {
			return false;
		}
	}
	if (pos == -1) {
		addHead(L, data);
	}
	else if (flag == L->p_tail) {
		addTail(L, data);
	}
	else {
		NODE* temp = createNode(data);
		temp->p_next = flag->p_next;
		flag->p_next = temp;
	}
	return true;
}

//4.11: Remove an integer at a position of a given List:
void removePos(List*& L, int pos) {
	if (pos < 0) {
		cout << "Invalid position ";
	}

	NODE* flag = L->p_head;
	while (--pos) {
		if (pos == -1) break;
		flag = flag->p_next;
		if (flag->p_next == NULL) {
			return;
		}
	}

	if (pos == -1 || L->p_head == L->p_tail) {
		removeHead(L);
	}
	else if (flag->p_next == L->p_tail) {
		removeTail(L);
	}
	else {
		NODE* temp = flag->p_next;
		flag->p_next = flag->p_next->p_next;
		delete[] temp;
	}
}

//4.12: Insert an integer before a value of a given List:
bool addBefore(List*& L, int data, int val) {
	if (L->p_head == NULL) {
		return false;
	}
	if (L->p_head->key == val) {
		addHead(L, data);
		return true;
	}
	else {
		NODE* flag = L->p_head;
		for (flag; flag->p_next != NULL; flag = flag->p_next) {
			if (flag->p_next->key == val) {
				NODE* temp = createNode(data);
				temp->p_next = flag->p_next;
				flag->p_next = temp;
				return true;
			}
		}
	}
	return false;
}

//4.13: Insert an integer after a value of a given List:
bool addAfter(List*& L, int data, int val) {
	if (L->p_head == NULL) {
		return false;
	}
	if (L->p_tail->key == val) {
		addTail(L, data);
		return true;
	}
	else {
		NODE* flag = L->p_head;
		for (flag; flag != NULL; flag = flag->p_next) {
			if (flag->key == val) {
				NODE* temp = createNode(data);
				temp->p_next = flag->p_next;
				flag->p_next = temp;
				return true;
			}
		}
	}
	return false;
}

//4.14: Print all elements of a given List:
void printList(List* mylist) {
	if (mylist->p_head == NULL) {
		cout << "Danh sach rong";
	}
	else {
		NODE* p = mylist->p_head;
		while (p != NULL) {
			cout << p->key << " ";
			p = p->p_next;
		}
	}
}

//4.15: Count the number of elements List:
int countElements(List* L) {
	if (L->p_head == NULL) {
		return 0;
	}
	NODE* temp = L->p_head;
	int count = 0;
	while (temp != NULL) {
		count++;
		temp = temp->p_next;
	}
	return count;
}

//4.16: Create a new List by reverse a given List:
List* reverseList(List* L) {
	NODE* temp = L->p_head;
	NODE* head = createNode(L->p_head->key);
	List* L_rev = createList(head);
	temp = temp->p_next;
	while (temp != NULL){
		addHead(L_rev, temp->key);
		temp = temp->p_next;
	}
	return L_rev;
}

//4.17: Remove all duplicates from a given List:
void removeNode(List* L, NODE* ptr) { 
	// Ptr truyen vao phai la mot p_next cua con tro truoc do) VD: removeNode( L, ptr->next). 
	// Neu khong se lam con tro hien tai mat phuong huong
	if (ptr == L->p_head && ptr == L->p_tail) {
		removeTail(L);
	}
	else if (ptr == L->p_head) {
		removeHead(L);
	}
	else if (ptr == L->p_tail) {
		removeTail(L);
	}
	else {
		NODE* temp = L->p_head;
		for (temp; temp->p_next != ptr; temp = temp->p_next);
		temp->p_next = temp->p_next->p_next;
		delete ptr;
	}
}

void removeDuplicate(List*& L) {
	NODE* ptr1, * ptr2, * dup;
	ptr1 = L->p_head;
	while (ptr1 != NULL) {
		ptr2 = ptr1;
		while (ptr2->p_next != NULL) {
			if (ptr1->key == ptr2->p_next->key) {
				removeNode(L, ptr2->p_next);
			}
			else {
				ptr2 = ptr2->p_next;
			}
		}
		ptr1 = ptr1->p_next;
	}
}

//4.18: Remove all key value from a given List:
bool removeElement(List*& L, int key) {
	if (L->p_head == NULL) {
		return false;
	}
	NODE* temp = L->p_head;
	while (temp->p_next != NULL) {
		if (temp->p_next->key == key) 
		{
			removeNode(L, temp->p_next);
		}
		else {
			temp = temp->p_next;
		}
	}
	if (L->p_head->key == key) {
		removeHead(L);
	}
	return true;
}

// Tim phan tu thu i cua linked list:
NODE* sreachNode(List* L, int i) 
{
    int size = countElements(L);
    if (i < 0 || i >= size) 
    {
        return NULL;
    }
    if (L->p_head == NULL)
    {
        return NULL;
    }
    NODE* temp = L->p_head;
    while (--i)
    {
        temp = temp->p_next;
    }
    return temp;
}

int main() {
	NODE* p = createNode(2);
	List* mylist = createList(p);
	addTail(mylist, 2);
	addTail(mylist, 10);
	addTail(mylist, 10);
	addTail(mylist, 10);

	/*removeHead(mylist);
	removeHead(mylist);
	removeHead(mylist);
	removeHead(mylist);*/

	/*removeTail(mylist);
	removeTail(mylist);
	removeTail(mylist);
	removeTail(mylist);
	removeTail(mylist);*/

	//removeAll(mylist);
	//removeBefore(mylist, 50);
	
	/*removeAfter(mylist, 50);
	removeAfter(mylist, 50);
	removeAfter(mylist, 50);
	removeAfter(mylist, 50);*/

	/*addPos(mylist, 10, 0);
	removePos(mylist, 0);
	removePos(mylist, 1);
	removePos(mylist, 2);
	removePos(mylist, 3);
	removePos(mylist, 4);
	removePos(mylist, 5);
	removePos(mylist, 0);
	removePos(mylist, 1);
	removePos(mylist, 1);*/

	//addBefore(mylist, 10, 20);
	//addAfter(mylist, 10, 20);
	
	/*int size = countElements(mylist);
	cout << size << endl;
	printList(mylist);*/
	
	/*printList(mylist);
	cout << endl;
	List* L_rev = reverseList(mylist);
	printList(L_rev);*/
	
	/*printList(mylist);
	cout << endl;
	removeDuplicate(mylist);
	printList(mylist);*/

	printList(mylist);
	cout << endl;
	removeElement(mylist, 10);
	printList(mylist);
	return 0;
}
