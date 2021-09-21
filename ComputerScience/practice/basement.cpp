#include<iostream>
using namespace std;
#define maxSize 100

//顺序表
class Sqlist
{
	int data[maxSize];
	int length;
	Sqlist()
	{
		length = 0;
	}
public:
	int copyElem(int* arr, int len)
	{
		if (len > maxSize)
			return 0;
		for (int i = 0; i < len; i++)
			data[i] == arr[i];
	}
	int getElem(int& e, int p)
	{
		if (p<0 || p>length - 1)
			return 0;
		e = data[p];
		return 1;
	}
	int findElem(int e)//找到值为e元素在顺序表中的位置
	{
		for (int i = 0; i < length; i++)
		{
			if (data[i] == e)
				return i;
		}
		return -1;
	}
	int insertElem(int e,int p)//将元素e插入顺序表中p位置
	{
		if (length == maxSize || p<0 || p>length)
			return 0;
		for (int i = length - 1; i >= p; i--)
		{
			data[i + 1] = data[i];
		}
		data[p] = e;
		return 1;
	}
	int deleteElem(int& e, int p)//删除位置p上的元素,并用e接收
	{
		if (p<0 || p>length-1)
			return 0;
		e = data[p];
		for (int i = p + 1; i < length; i++)
		{
			data[i - 1] = data[i];
		}
		length--;
		return 1;
	}
};

//单链表
class LNode
{
	int data;
	struct LNode* next;
public:

};

//双链表
class DLNode
{
	int data;
	struct DLNode* prior;
	struct DLNode* next;
};