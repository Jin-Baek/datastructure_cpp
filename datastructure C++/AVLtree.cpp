#include <iostream>
#include <stdio.h>
#include<stdlib.h>
using namespace std;

struct Node
{
	Node* left; // ���� �ڽ� ���
	Node* right;  // ������ �ڽ� ���
	int data;  // ��� ��
	int height;
};

// Ʈ���� �ִ� ��ȯ 
int getMaxValue(int a, int b) {
	if (a > b) {
		return a;
	}
	return b;
}

// Ʈ���� ���� ��ȯ 
int getHeight(Node* node) {
	if (node == NULL) {
		return 0;
	}
	return node->height;
}

// ���� ������ ���� �� ��ȯ ( BF ) 
int getDifference(Node* node) {
	Node* left = node->left;
	Node* right = node->right;
	return getHeight(left) - getHeight(right);
}

// Ʈ���� ���� �� ���
void setHeight(Node* node) {
	node->height = getMaxValue(getHeight(node->left), getHeight(node->right)) + 1;
}

// single - RR ȸ�� 
Node* RR_rotation(Node* node) {
	Node* right = node->right;
	node->right = right->left;
	right->left = node;
	setHeight(node);
	return right;
}

// single - LL ȸ�� 
Node* LL_rotation(Node* node) {
	Node* left = node->left;
	node->left = left->right;
	left->right = node;
	setHeight(node);
	return left;
}

// double - LR ȸ��
Node* LR_rotation(Node* node) {
	Node* left = node->left;
	node->left = RR_rotation(left);
	return LL_rotation(node);
}

// double - RL ȸ��
Node* RL_rotation(Node* node) {
	Node* right = node->right;
	node->right = LL_rotation(right);
	return RR_rotation(node);
}

// Ʈ�� �뷱�� ���߱� 
// BF = Left height - Right height
Node* setBalance(Node* node) {

	if (getDifference(node) >= 2) {
		if (getDifference(node->left) >= 1) {
			node = LL_rotation(node);
		}
		else {
			node = LR_rotation(node);
		}
	}
	else if (getDifference(node) <= -2) {
		if (getDifference(node->right) <= -1) {
			node = RR_rotation(node);
		}
		else {
			node = RL_rotation(node);
		}
	}
	setHeight(node);
	return node;
}

Node* Insert_Operation(Node* node, int data) {

	// ��� ���� 
	if (!node) {
		node = (Node*)malloc(sizeof(Node));
		node->height = 1;
		node->data = data;
		node->left = node->right = NULL;
	}
	else if (data < node->data) {  // �����Ϸ��� �� < �ش� ��� �� �̸� ���� �̵� 
		node->left = Insert_Operation(node->left, data);
		node = setBalance(node); // �뷱�� ���� 
	}
	else if (data > node->data) {  // �����Ϸ��� �� > �ش� ��� ���̸� ������ �̵� 
		node->right = Insert_Operation(node->right, data);
		node = setBalance(node);  // �뷱�� ���� 
	}
	else {
		printf("Cannot insert same data");
	}
	return node;
}

Node* Delete_Operation(Node* node, int data) {

	// �����Ϸ��� �����Ͱ� ������ �������� ã�ư�
	if (data < node->data) {
		node->left = Delete_Operation(node->left, data);
	} // �����Ϸ��� �����Ͱ� ũ�� ���������� ã�ư� 
	else if (data > node->data) {
		node->right = Delete_Operation(node->right, data);
	}
	else { // �����Ϸ��� ��� ã�� 

		// �ڽ� ���� ��� 
		if (node->left == nullptr && node->right == nullptr) {
			node = nullptr;
		}
		// �ڽ� 1�� - ���� �ڽ��� ���   
		else if (node->left != nullptr && node->right == nullptr) {
			Node* temp = node;
			node = node->left;
			temp = nullptr;
		} // �ڽ� 1�� - ������ �ڽ��� ���
		else if (node->left == nullptr && node->right != nullptr) {
			Node* temp = node;
			node = node->right;
			temp = nullptr;
		}
		else { // �ڽ� 2���� ��� 
			Node* temp = node->right;
			// ������ �ڽ� ��� �� while������ �������� ã�ư��鼭 ���� ���� ��� ã�� 
			while (temp->left != nullptr)
				temp = node->left;
			node->data = temp->data;
			node->right = Delete_Operation(node->right, temp->data);
		}
	}
	return setBalance(node);
}

void Search_Operation(Node* node, int data) {
	if (node == nullptr) {
		cout << "There is no data";
	}
	else if (node->data == data) {
		std::cout << "Data has been found";
	}
	else {
		if (data < node->data)
			Search_Operation(node->left, data);
		else if (data > node->data)
			Search_Operation(node->right, data);
	}
}

void display(Node* node, int depth) {
	Node* root = NULL;
	if (node != NULL) {
		// ������ ������ ��� 
		display(node->right, depth + 1);
		printf("\n");

		for (int i = 0; i < depth && node!=root; i++) {
			printf(" ");
		}
		printf("%d", node->data);
		display(node->left, depth + 1);
	}
}

int main() {
	Node* root = NULL;
	root = Insert_Operation(root, 3);
	root = Insert_Operation(root, 4);
	root = Insert_Operation(root, 5);
	root = Insert_Operation(root, 10);
	root = Insert_Operation(root, 2);
	root = Insert_Operation(root, 12);
	display(root, 1);
	return 0;
}
