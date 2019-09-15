#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

void execute(int a[10],int size)
{
	//思路:
	//如果第一个数为奇数,continue
	//如果第一个数为偶数,则与第一个奇数相交换
	//依次执行
	for (int i = 0; i < size;++i)
	{
		if (a[i] % 2 == 1)
		{
			continue;
		}
		if (a[i] % 2 == 0)
		{
			for (int j = i; j < size; ++j)
			{
				if (a[j] % 2 == 1)
				{
					swap(&a[i],&a[j]);
				}
			}
		}
	}
}

int main()
{
	//1.调整数组使奇数全部都位于偶数前面。
	//题目：
	//输入一个整数数组，实现一个函数，
	//来调整该数组中数字的顺序使得数组中所有的奇数位于数组的前半部分，
	//所有偶数位于数组的后半部分。
	int a[10];
	int size = sizeof(a) / sizeof(a[0]);
	printf("输入一个数组:");
	for (int i = 0; i < size; ++i)
	{
		scanf("%d", a + i);
	}
	execute(a, size);
	for (int i = 0; i < size; ++i)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
	system("pause");
    return 0;
}


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct position
{
	int x;
	int y;
}position;

position find(int a[3][3], int n)
{
	//返回两个值:采用封装成结构体的方式或者传入指针带入返回值;
	position p;
	p.x = -1;
	p.y = -1;
	int row = 0;
	int col = 2;
	while (row < 3 && col >= 0)
	{
		if (n > a[row][col])
		{
			row++;
		}
		else if (n < a[row][col])
		{
			col--;
		}
		else if (n == a[row][col])
		{
			p.x = row;
			p.y = col;
			return p;
		}
	}
	return p;
}

int main()
{
	//2.
	//	//杨氏矩阵 
	//	有一个二维数组.
	//	数组的每行从左到右是递增的，每列从上到下是递增的.
	//	在这样的数组中查找一个数字是否存在。
	//	时间复杂度小于O(N);
	//数组：
	//	1 2 3
	//	2 3 4
	//	3 4 5

	//	1 2 3
	//	4 5 6
	//	7 8 9
	int a[3][3] = { { 1, 3, 5 }, { 2, 4, 6 }, { 7, 8, 9 } };
	int num = 0;
	printf("输入一个数来寻找:");
	scanf("%d", &num);
	position p1 = find(a, num);
	if (p1.x == -1 && p1.y == -1)
	{
		printf("没找到\n");
	}
	else
	{
		printf("找到了\n");
	}
    system("pause");
    return 0;
}

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void levorotation(char a[], int size,int n)
{
	for (int i = 0; i < n; ++i)
	{
		char temp = a[0];
		for (int j = 0; j < size; ++j)
		{
			a[j] = a[j + 1];
		}
		a[size - 1] = temp;
	}
}

int main()
{
	//1.实现一个函数，可以左旋字符串中的k个字符。
	//  ABCD左旋一个字符得到BCDA
	//  ABCD左旋两个字符得到CDAB
	char arr[] = "ABCD";
	int size = strlen(arr);
	int n = 0;
	printf("输入要左旋的字符个数:");
	scanf("%d", &n);
	levorotation(arr,size,n);
	printf("%s\n", arr);
    system("pause");
    return 0;
}
