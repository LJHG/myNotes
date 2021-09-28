#include<iostream>

using namespace std;

void BubbleSort(int *A,int len)
{
	for (int i = len-1; i>0; --i)
	{
		for (int j = 0; j < i; ++j)
		{
			if (A[j] > A[j + 1])
			{
				int temp = A[j];
				A[j] = A[j + 1];
				A[j + 1] = temp;
			}
		}
	}
	return;
}

int main()
{
	int A[10];
	int len;
	cin >> len;
	for (int i = 0; i < len; i++)
	{
		cin >> A[i];
	}
	BubbleSort(A,len);
	return 0;
}