#include <iostream>
using namespace std;

struct Node {
	int data;
	Node* next;
};

Node* top = NULL;

void push(int data) {
	Node* node = new Node();
	node-> data = data;
	node->next = top;
	top = node;
}

void pop() {
	if (top == NULL) {
		cout << "Stack is Empty" << endl;
	}
	else {
		cout << "pop : "<<top->data << endl;
		top = top->next;
	}
}

bool isEmpty() {
	if (top == NULL) {
		return true;
	}
	return false;
}

void makeStackEmpty() {
	bool del = true;
	while (del) {
		if (top == NULL) 
			del = false;
		else 
			pop();
	}
}

void show() {
	Node* stack;
	if (top == NULL){
		cout<<"Stack is Empty";
	}
	else {
		stack = top;
		cout << "Stack : ";
		while (stack != NULL) {
			cout << stack->data << " ";
			stack = stack->next;
		}
	}
	cout << endl;
} 

int main() {

	push(1);
	push(2);
	push(3);
	show();

	pop();
	pop();
	if (isEmpty()) {
		push(4);
	}
	else {
		push(5);
	}
	show();

	push(6);
	push(7);
	show();

	makeStackEmpty();
	show();

	return 0;
}
