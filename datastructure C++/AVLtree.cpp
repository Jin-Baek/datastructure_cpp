#include <iostream>
#include <stdio.h>
#include<stdlib.h>
using namespace std;

struct Node
{
	Node* left; // 왼쪽 자식 노드
	Node* right;  // 오른쪽 자식 노드
	int data;  // 노드 값
	int height;
};

// 트리의 최댓값 반환 
int getMaxValue(int a, int b) {
	if (a > b) {
		return a;
	}
	return b;
}

// 트리의 높이 반환 
int getHeight(Node* node) {
	if (node == NULL) {
		return 0;
	}
	return node->height;
}

// 왼쪽 오른쪽 높이 차 반환 ( BF ) 
int getDifference(Node* node) {
	Node* left = node->left;
	Node* right = node->right;
	return getHeight(left) - getHeight(right);
}

// 트리의 높이 재 계산
void setHeight(Node* node) {
	node->height = getMaxValue(getHeight(node->left), getHeight(node->right)) + 1;
}

// single - RR 회전 
Node* RR_rotation(Node* node) {
	Node* right = node->right;
	node->right = right->left;
	right->left = node;
	setHeight(node);
	return right;
}

// single - LL 회전 
Node* LL_rotation(Node* node) {
	Node* left = node->left;
	node->left = left->right;
	left->right = node;
	setHeight(node);
	return left;
}

// double - LR 회전
Node* LR_rotation(Node* node) {
	Node* left = node->left;
	node->left = RR_rotation(left);
	return LL_rotation(node);
}

// double - RL 회전
Node* RL_rotation(Node* node) {
	Node* right = node->right;
	node->right = LL_rotation(right);
	return RR_rotation(node);
}

// 트리 밸런스 맞추기 
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

	// 노드 생성 
	if (!node) {
		node = (Node*)malloc(sizeof(Node));
		node->height = 1;
		node->data = data;
		node->left = node->right = NULL;
	}
	else if (data < node->data) {  // 삽입하려는 값 < 해당 노드 값 이면 왼쪽 이동 
		node->left = Insert_Operation(node->left, data);
		node = setBalance(node); // 밸런스 유지 
	}
	else if (data > node->data) {  // 삽입하려는 값 > 해당 노드 값이면 오른쪽 이동 
		node->right = Insert_Operation(node->right, data);
		node = setBalance(node);  // 밸런스 유지 
	}
	else {
		printf("Cannot insert same data");
	}
	return node;
}

Node* Delete_Operation(Node* node, int data) {

	// 삭제하려는 데이터가 작으면 왼쪽으로 찾아감
	if (data < node->data) {
		node->left = Delete_Operation(node->left, data);
	} // 삭제하려는 데이터가 크면 오른쪽으로 찾아감 
	else if (data > node->data) {
		node->right = Delete_Operation(node->right, data);
	}
	else { // 삭제하려는 노드 찾음 

		// 자식 없을 경우 
		if (node->left == nullptr && node->right == nullptr) {
			node = nullptr;
		}
		// 자식 1개 - 왼쪽 자식일 경우   
		else if (node->left != nullptr && node->right == nullptr) {
			Node* temp = node;
			node = node->left;
			temp = nullptr;
		} // 자식 1개 - 오른쪽 자식일 경우
		else if (node->left == nullptr && node->right != nullptr) {
			Node* temp = node;
			node = node->right;
			temp = nullptr;
		}
		else { // 자식 2개일 경우 
			Node* temp = node->right;
			// 오른쪽 자식 노드 중 while문으로 왼쪽으로 찾아가면서 가장 작은 노드 찾기 
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
		// 오른쪽 노드부터 출력 
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
