#include <iostream>
using namespace std;

struct d_NODE {
	int key;
	d_NODE* pNext;
	d_NODE* pPrev;
};

struct d_List {
	d_NODE* pHead;
	d_NODE* pTail;
};

//1. Initialize a NODE from a given integer:
d_NODE* createNode(int data) {
	d_NODE* p = new d_NODE;
	p->key = data;
	p->pNext = NULL;
	p->pPrev = NULL;
	return p;
}

//2. Initialize a List from a give NODE:
d_List* createList(d_NODE* p_node) {
	d_List* list = new d_List;
	list->pHead = p_node;
	list->pTail = p_node;
	return list;
}

void initList(d_List*& L) {
	L = new d_List;
	L->pHead = NULL;
	L->pTail = NULL;
}

//3.Insert an integer to the head of a given List
bool addHead(d_List*& L, int data) {
	d_NODE* temp = createNode(data);
	if (temp == NULL) {
		return false;
	}
	if (L->pHead == NULL) {
		L = createList(temp);
	}
	else {
		temp->pNext = L->pHead;
		L->pHead->pPrev = temp;
		L->pHead = temp;
	}
	return true;
}

//4. Insert an integer to the tail of a given List:
bool addTail(d_List*& L, int data) {
	d_NODE* temp = createNode(data);
	if (temp == NULL) {
		return false;
	}
	if (L->pHead == NULL) {
		L = createList(temp);
	}
	else {
		L->pTail->pNext = temp;
		temp->pPrev = L->pTail;
		L->pTail = temp;
	}
	return true;
}

//5. Remove the first NODE of a given List:
void removeHead(d_List*& L) {
	if (L->pHead == NULL) {
		return;
	}
	if (L->pHead == L->pTail) {
		delete L->pHead;
		L->pHead = NULL;
		L->pTail = NULL;
		return;
	}
	d_NODE* temp = L->pHead;
	L->pHead = L->pHead->pNext;
	L->pHead->pPrev = NULL;
	delete temp;
}

//6. Remove the last NODE of a given List:
void removeTail(d_List*& L) {
	if (L->pHead == NULL) {
		return;
	}
	if (L->pHead == L->pTail) {
		delete L->pHead;
		L->pHead = NULL;
		L->pTail = NULL;
		return;
	}
	d_NODE* temp = L->pTail;
	L->pTail = L->pTail->pPrev;
	L->pTail->pNext = NULL;
	delete temp;
}

//7. Remove all NODE from a given List:
void removeAll(d_List*& L) {
	if (L->pHead == NULL) {
		return;
	}
	d_NODE* temp = L->pHead;
	while (temp != NULL) {
		temp = temp->pNext;
		removeHead(L);
	}
}

//8. Remove an integer before a value of a given List:
void removeBefore(d_List*& L, int val) {
	if (L->pHead == NULL) {
		return;
	}
	if (L->pHead == L->pTail) {
		return;
	}
	d_NODE* temp = L->pHead->pNext;
	while (temp != NULL && temp->key != val) {
		temp = temp->pNext;
	}
	if (temp == NULL) {
		return;
	}
	d_NODE* temp_ = temp->pPrev;
	if (temp_ == L->pHead) {
		removeHead(L);
		return;
	}
	temp_->pPrev->pNext = temp;
	temp->pPrev = temp_->pPrev;
	delete temp_;
}

//9.Remove an integer after a value of a given List:
void removeAfter(d_List*& L, int val) {
	if (L->pHead == NULL) {
		return;
	}
	if (L->pHead == L->pTail) {
		return;
	}
	d_NODE* temp = L->pHead;
	while (temp->pNext != NULL && temp->key != val) {
		temp = temp->pNext;
	}
	if (temp->pNext == NULL) {
		return;
	}
	d_NODE* temp_ = temp->pNext;
	if (temp_ == L->pTail) {
		removeTail(L);
		return;
	}
	temp->pNext = temp_->pNext;
	temp_->pNext->pPrev = temp;
	delete temp_;
}

//10.Insert an integer at a position of a given List:
bool addPos(d_List*& L, int data, int pos) {
	if (pos < 0) {
		cout << "Invalid position ";
		return false;
	}

	d_NODE* flag = L->pHead;
	while (--pos) {
		if (pos == -1) break;
		flag = flag->pNext;
		if (flag == NULL) {
			return false;
		}
	}
	if (pos == -1) {
		addHead(L, data);
	}
	else if (flag == L->pTail) {
		addTail(L, data);
	}
	else {
		d_NODE* temp = createNode(data);
		temp->pNext = flag->pNext;
		flag->pNext->pPrev = temp;
		flag->pNext = temp;
		temp->pPrev = flag;
	}
	return true;
}

//11. Remove an integer at a position of a given:
void removePos(d_List*& L, int pos) {
	if (pos < 0) {
		cout << "Invalid position ";
	}

	d_NODE* flag = L->pHead;
	while (--pos) {
		if (pos == -1) break;
		flag = flag->pNext;
		if (flag->pNext == NULL) {
			return;
		}
	}

	if (pos == -1 || L->pHead == L->pTail) {
		removeHead(L);
	}
	else if (flag->pNext == L->pTail) {
		removeTail(L);
	}
	else {
		d_NODE* temp = flag->pNext;
		flag->pNext = temp->pNext;
		temp->pNext->pPrev = flag;
		delete temp;
	}
}

//12. Insert an integer before a value of a given List:
bool addBefore(d_List*& L, int data, int val) {
	if (L->pHead == NULL) {
		return false;
	}
	if (L->pHead->key == val) {
		addHead(L, data);
		return true;
	}
	else {
		d_NODE* flag = L->pHead;
		for (flag; flag->pNext != NULL; flag = flag->pNext) {
			if (flag->pNext->key == val) {
				d_NODE* temp = createNode(data);
				temp->pNext = flag->pNext;
				flag->pNext->pPrev = temp;
				flag->pNext = temp;
				temp->pPrev = flag;
				return true;
			}
		}
	}
	return false;
}

//13. Insert an integer after a value of a given List:
bool addAfter(d_List*& L, int data, int val) {
	if (L->pHead == NULL) {
		return false;
	}
	if (L->pTail->key == val) {
		addTail(L, data);
		return true;
	}
	else {
		d_NODE* flag = L->pHead;
		for (flag; flag != NULL; flag = flag->pNext) {
			if (flag->key == val) {
				d_NODE* temp = createNode(data);
				temp->pNext = flag->pNext;
				flag->pNext->pPrev = temp;
				flag->pNext = temp;
				temp->pPrev = flag;
				return true;
			}
		}
	}
	return false;
}

//14. Print all elements of a given List:
void printForward(d_List* L) {
	if (L->pHead == NULL) {
		cout << "Danh sach rong";
		return;
	}
	d_NODE* temp = L->pHead;
	while (temp != NULL) {
		cout << temp->key << " ";
		temp = temp->pNext;
	}
}

void printBackward(d_List* L) {
	if (L->pHead == NULL) {
		cout << "Danh sach rong";
		return;
	}
	d_NODE* temp = L->pTail;
	while (temp != NULL) {
		cout << temp->key << " ";
		temp = temp->pPrev;
	}
}

//15. Count the number of elements List:
int countElements(d_List* L) {
	if (L->pHead == NULL) {
		return 0;
	}
	d_NODE* temp = L->pHead;
	int count = 0;
	while (temp != NULL) {
		count++;
		temp = temp->pNext;
	}
	return count;
}

//16: Create a new List by reverse a given List:
d_List* reverseList(d_List* L) {
	d_NODE* temp = L->pHead;
	d_NODE* head = createNode(L->pHead->key);
	d_List* L_rev = createList(head);
	temp = temp->pNext;
	while (temp != NULL) {
		addHead(L_rev, temp->key);
		temp = temp->pNext;
	}
	return L_rev;
}

//17: Remove all duplicates from a given List:
void removeNode(d_List* L, d_NODE* ptr) { 
	if (ptr == L->pHead && ptr == L->pTail) {
		removeTail(L);
	}
	else if (ptr == L->pHead) {
		removeHead(L);
	}
	else if (ptr == L->pTail) {
		removeTail(L);
	}
	else {
		d_NODE* p_ = ptr->pPrev;
		p_->pNext = ptr->pNext;
		ptr->pNext->pPrev = p_;
		delete ptr;
	}
}

void removeDuplicate(d_List*& L) {
	d_NODE* ptr1, * ptr2, * dup;
	ptr1 = L->pHead;
	while (ptr1 != NULL) {
		ptr2 = ptr1;
		while (ptr2->pNext != NULL) {
			if (ptr1->key == ptr2->pNext->key) {
				removeNode(L, ptr2->pNext);
			}
			else {
				ptr2 = ptr2->pNext;
			}
		}
		ptr1 = ptr1->pNext;
	}
}

//18: Remove all key value from a given List:
bool removeElement(d_List*& L, int key) {
	if (L->pHead == NULL) {
		return false;
	}
	d_NODE* temp = L->pHead;
	while (temp->pNext != NULL) {
		if (temp->pNext->key == key) {
			removeNode(L, temp->pNext);
		}
		else {
			temp = temp->pNext;
		}
	}
	if (L->pHead->key == key) {
		removeHead(L);
	}
	return true;
}

int main() {
	d_List* L;
	initList(L);
	/*for (int i = 0; i < 10; i++) {
		addHead(L, i + 1);
	}*/
	/*for (int i = 0; i < 10; i++) {
		addTail(L, i + 1);
		addTail(L, i + 1);
		addTail(L, i + 1);
	}*/

	/*addTail(L, 2);
	addTail(L, 2);
	addTail(L, 2);
	addTail(L, 2);
	addTail(L, 3);
	addTail(L, 3);
	addTail(L, 2);
	addTail(L, 4);
	addTail(L, 5);
	addTail(L, 2);*/

	printForward(L);
	cout << endl;
	printBackward(L);
	cout << endl << endl;

	/*removeHead(L);
	removeHead(L);
	removeHead(L);
	removeHead(L);
	removeHead(L);
	removeHead(L);
	removeHead(L);
	removeHead(L);
	removeHead(L);
	removeHead(L);*/

	/*removeTail(L);
	removeTail(L);
	removeTail(L);
	removeTail(L);
	removeTail(L);
	removeTail(L);
	removeTail(L);
	removeTail(L);
	removeTail(L);
	removeTail(L);
	removeTail(L);
	removeTail(L);
	removeTail(L);*/

	//removeAll(L);

	/*removeBefore(L, 2);
	removeBefore(L, 3);
	removeBefore(L, 7);
	removeBefore(L, 7);
	removeBefore(L, 7);
	removeBefore(L, 7);
	removeBefore(L, 7);
	removeBefore(L, 7);
	removeBefore(L, 7);
	removeBefore(L, 7);*/

	/*removeAfter(L, 1);
	removeAfter(L, 1);
	removeAfter(L, 10);
	removeAfter(L, 5);
	removeAfter(L, 9);
	removeAfter(L, 8);
	removeAfter(L, 7);
	removeAfter(L, 10);
	removeAfter(L, 10);
	removeAfter(L, 1);
	removeAfter(L, 1);
	removeAfter(L, 1);
	removeAfter(L, 1);*/

	//addPos(L, 111, 11);

	/*removePos(L, 0);
	removePos(L, 0);
	removePos(L, 0);
	removePos(L, 0);
	removePos(L, 0);
	removePos(L, 0);
	removePos(L, 0);
	removePos(L, 0);
	removePos(L, 0);*/

	//addBefore(L, 111, 11);
	//addAfter(L, 111, 10);

	//cout << countElements(L) << endl;

	//d_List* L2 = reverseList(L);
	
	//removeDuplicate(L);
	
	//removeElement(L, 2);

	printForward(L);
	cout << endl;
	printBackward(L);
	return 0;
}