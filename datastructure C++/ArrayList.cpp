#include<iostream>
using namespace std;

const int MAX_SIZE = 100;

typedef struct ArrayList
{
	int List[MAX_SIZE];
	int length = 0;
}ArrayList;

// 맨 앞 데이터 추가 
void Add_First(ArrayList* arrayList, int value)
{
	if (arrayList->length >= 100)
		cout << "List is full" << endl;
	else
	{
		for (int i = arrayList->length; i > 0; i--) {
			arrayList->List[i] = arrayList->List[i - 1];
		}
		arrayList->List[0] = value;
		arrayList->length += 1;
	}
}

// 맨 뒤 데이터 추가
void Add_Last(ArrayList* arrayList, int value)
{
	if (arrayList->length >= 100)
	{
		cout << "List is full" << endl;
		return;
	}
	arrayList->List[arrayList->length] = value;
	arrayList->length += 1;
}
// 임의의 위치에 데이터 추가
void Add(ArrayList* arrayList, int value, int position)
{
	if (arrayList->length < position)
	{
		Add_Last(arrayList, value);
		return;
	}
	for (int i = arrayList->length; i > position; i--)
	{
		arrayList->List[i] = arrayList->List[i - 1];
	}
	arrayList->List[position] = value;
	arrayList->length += 1;

	if (arrayList->length >= 100)
	{
		cout << "List if full" << endl;
		return;
	}
}

// 임의의 위치에 데이터 삭제 
void Delete(ArrayList* arrayList, int position)
{
	if (arrayList->length == 0)
	{
		cout << "List is empty\n" << endl;
		return;
	}
	if (position > arrayList->length)
	{
		cout << "There is no data \n" << endl;
		return;
	}
	for (int i = position - 1; i < arrayList->length - 1; i++)
	{
		arrayList->List[i] = arrayList->List[i + 1];
	}
	arrayList->length -= 1;
}

// 맨 앞 데이터 삭제 
void Delete_First(ArrayList* arrayList) {
	if (arrayList->length == 0)
	{
		cout << "List is empty\n" << endl;
		return;
	}
	for (int i = 0; i < arrayList->length - 1; i++)
	{
		arrayList->List[i] = arrayList->List[i + 1];
	}
	arrayList->length -= 1;
}

// 맨 뒤 데이터 삭제 
void Delete_Last(ArrayList* arrayList) {
	if (arrayList->length == 0)
	{
		cout << "List is empty\n" << endl;
		return;
	}
	arrayList->List[arrayList->length] = NULL;
	arrayList->length -= 1;
}

// 결과 출력하기
void Print(ArrayList* arrayList)
{
	for (int i = 0; i < arrayList->length; i++)
		cout << arrayList->List[i] << " ";
	cout << endl;
}

void Access(ArrayList* arrayList, int position)
{
	cout << arrayList->List[position] << endl;
}
void main()
{
	ArrayList list;

	Add(&list, 1, 0);
	Add(&list, 2, 1);
	Add(&list, 3, 2);
	Add(&list, 4, 3);
	Add(&list, 5, 4);
	Print(&list);

	Add_First(&list, 10);

	Add_Last(&list, 20);

	Print(&list);

	Delete_First(&list);

	Delete_Last(&list);
	Print(&list);

	Delete(&list, 3);
	Print(&list);

	Access(&list, 2);
}