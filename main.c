#include <stdio.h>
#include <string.h>

void swap(int *x,int *y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

void bubblesort(int a[],int size)
{
	int i = 0;
	int bound = 0;
	for(bound = 0;bound < size;bound++)
	{
		for(i = size - 1;i > bound;i--)
		{
			if(a[i - 1] > a[i])
			{
				swap(&a[i - 1],&a[i]);
			}
		}
	}
}

int main()
{
	int a[10] = {1,2,5,8,3,9,4,6,7,0};
	int size = sizeof(a)/sizeof(a[0]);
	bubblesort(a,size);
	int i = 0;
	for(i = 0;i < size;i++)
	{
		printf("%d ",a[i]);
	}
	return 0;
}
