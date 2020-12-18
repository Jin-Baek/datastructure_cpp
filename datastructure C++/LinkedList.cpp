#include <iostream>
using namespace std;

typedef struct Node
{
	int data;
	Node* next;
} Node;

// 임의의 위치에 데이터 추가 
void Add(Node** head, int data, int position)
{
	Node* newNode = new Node;
	newNode->data = data;

	// 맨 앞 쪽 데이터 추가 
	if (position == 1)
	{
		newNode->next = *head;
		*head = newNode;
	}
	else
	{
		Node* newNode_pre = *head;

		for (int i = 1; (newNode_pre->next != NULL) && (i < position - 1); i++)
		{
			newNode_pre = newNode_pre->next;
		}

		Node* newNode_next = newNode_pre->next;

		newNode_pre->next = newNode;
		newNode->next = newNode_next;
	}
}

// 임의의 위치 데이터 삭제 
void Delete(Node** head, int position)
{
	if (*head == NULL)
	{
		cout << "List is empty" << "\n";
		return;
	}
	Node* deleteNode_pre;
	Node* deleteNode;

	// 맨 앞 쪽 데이터 삭제
	if (position == 1)
	{
		deleteNode = *head;
		*head = (*head)->next;
		delete(deleteNode);
	}
	else
	{
		Node* deleteNode_pre = *head;
		deleteNode = deleteNode_pre->next;

		for (int i = 1; (deleteNode->next != NULL) && (i < position - 1); i++)
		{
			deleteNode_pre = deleteNode_pre->next;
			deleteNode = deleteNode_pre->next;
		}
		deleteNode_pre->next = deleteNode->next;

		delete(deleteNode);
	}
}

void Access(Node* head, int position)
{
	Node* current = head;

	int length = 0;

	while (length != position)
	{
		length++;
		current = current->next;
	}
	cout << current->data << "\n";
}

void Print(Node* head)
{
	Node* current = head;

	while (current != NULL)
	{
		cout << current->data << " , ";
		current = current->next;
	}
	cout << "NULL\n";
}

int main()
{
	Node* head = NULL;
	Add(&head, 2, 1);
	Add(&head, 4, 2);
	Add(&head, 6, 3);
	Add(&head, 8, 4);
	Print(head);

	Add(&head, 10, 1);
	Add(&head, 12, 3);
	Print(head);

	Delete(&head, 1);
	Print(head);

	Delete(&head, 3);
	Print(head);

	Access(head, 1);
	Access(head, 2);

}