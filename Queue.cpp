#include <iostream>
using namespace std;

struct NODE {
	int key;
	NODE* pNext;
};

struct Queue {
	NODE* pHead;
	NODE* pTail;
};

void init(Queue*& queue) {
	queue = new Queue;
	queue->pHead = NULL;
	queue->pTail = NULL;
}

NODE* createNode(int data) {
	NODE* p = new NODE;
	if (p == NULL) {
		return NULL;
	}
	p->key = data;
	p->pNext = NULL;
	return p;
}

bool enqueue(Queue* queue, int data) {
	NODE* temp = createNode(data);
	if (temp == NULL) {
		return false;
	}
	if (queue->pHead == NULL) {
		queue->pHead = queue->pTail = temp;
	}
	else {
		queue->pTail->pNext = temp;
		queue->pTail = temp;
	}
	return true;
}

int  isEmpty(Queue* queue) {
	return queue->pHead == NULL;
}

int dequeue(Queue* queue) {
	if (isEmpty(queue) != 0) {
		cout << "Queue is empty";
		return INT_MIN;
	}
	int dequeue_data = queue->pHead->key;
	NODE* temp = queue->pHead;
	queue->pHead = queue->pHead->pNext;
	delete temp;
	return dequeue_data;
}

int size(Queue* queue) {
	int size = 0;
	NODE* temp = queue->pHead;
	while (temp) {
		size++;
		temp = temp->pNext;
	}
	return size;
}

void printQueue(Queue* queue) {
	if (queue->pHead == NULL) {
		cout << "Queue rong";
	}
	else {
		NODE* p = queue->pHead;
		while (p != NULL) {
			cout << p->key << " ";
			p = p->pNext;
		}
	}
}

int main() {
	Queue* queue;
	init(queue);
	enqueue(queue, 1);
	enqueue(queue, 2);
	enqueue(queue, 3);
	enqueue(queue, 4);
	enqueue(queue, 5);
	enqueue(queue, 6);
	enqueue(queue, 7);
	enqueue(queue, 7);
	printQueue(queue);
	cout << endl;

	/*int dequeue_data = dequeue(queue);
	cout << dequeue_data << endl;
	printQueue(queue);
	cout << endl;
	dequeue_data = dequeue(queue);
	cout << dequeue_data << endl;
	printQueue(queue);
	cout << endl;
	dequeue_data = dequeue(queue);
	cout << dequeue_data << endl;
	printQueue(queue);
	cout << endl;
	dequeue_data = dequeue(queue);
	cout << dequeue_data << endl;
	printQueue(queue);
	cout << endl;
	dequeue_data = dequeue(queue);
	cout << dequeue_data << endl;
	printQueue(queue);
	cout << endl;
	dequeue_data = dequeue(queue);
	cout << dequeue_data << endl;
	printQueue(queue);
	cout << endl;
	dequeue_data = dequeue(queue);
	cout << dequeue_data << endl;
	printQueue(queue);
	cout << endl;*/

	int count = size(queue);
	cout << count;
	return 0;
}