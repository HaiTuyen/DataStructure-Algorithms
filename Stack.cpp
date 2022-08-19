#include <iostream>
using namespace std;

struct NODE {
	int key;
	NODE* pNext;
};

struct Stack {
	NODE* pHead;
};

void init(Stack*& stack) {
	stack = new Stack;
	stack->pHead = NULL;
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

void push(Stack* stack, int data) {
	NODE* temp = createNode(data);
	if (temp == NULL) {
		cout << "Stack overflow error";
		return;
	}
	temp->pNext = stack->pHead;
	stack->pHead = temp;
}

int isEmpty(Stack* stack) {
	return stack->pHead == NULL;
}

int pop(Stack* stack) {
	if (isEmpty(stack) != 0) {
		cout << "Stack is empty!";
		return INT_MIN;
	}
	int pop_data = stack->pHead->key;
	NODE* temp = stack->pHead;
	stack->pHead = stack->pHead->pNext;
	delete temp;
	return pop_data;
}

void printStack(Stack* stack) {
	if (stack->pHead == NULL) {
		cout << "Stack rong";
	}
	else {
		NODE* p = stack->pHead;
		while (p != NULL) {
			cout << p->key << " ";
			p = p->pNext;
		}
	}
}

int size(Stack* stack) {
	int size = 0;
	NODE* temp = stack->pHead;
	while (temp) {
		size++;
		temp = temp->pNext;
	}
	return size;
}

int main() {
	Stack* stack;
	init(stack);
	push(stack, 1);
	push(stack, 2);
	push(stack, 3);
	push(stack, 3);
	push(stack, 3);
	printStack(stack);
	cout << endl;
	
	/*int pop_data = pop(stack);
	cout << pop_data;
	pop_data = pop(stack);
	cout << pop_data;
	pop_data = pop(stack);
	cout << pop_data;
	pop_data = pop(stack);
	cout << pop_data;*/

	int count = size(stack);
	cout << count;

	return 0;
}