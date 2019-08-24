#include <stdio.h>
#include <stdlib.h>

int main()
{
	//思路:
	//从第一个数开始,如果在数组中可以找到一个下标不相等值相等的,就结束本次循环.
	//如果在数组中找不到一个一样的,就把这个数输出.
	int a[10] = { 1, 3, 4, 5, 1, 6, 5, 4, 7, 6 };
	int size = sizeof(a) / sizeof(a[0]);
	for (int i = 0; i < size; ++i)
	{
		int temp = a[i];
		for (int j = 0; j < size; ++j)
		{
			if (i != j && a[j] == temp)
			{
				break;
			}
			if (j == size - 1)
			{
				printf("%d\n", a[i]);
			}		
		}
	}
    system("pause");
    return 0;
}

#include <stdio.h>
#include  <stdlib.h>

int main()
{
	int count = 0;
	int i = 20;
	while (i > 0)
	{
		--i;
		count++;
		if (count % 2 == 0)
		{
			count++;
		}
	}
	printf("%dƿ\n", count);
	system("pause");
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
char* copy(char* a2, char* a1)
{
	assert(a1);
	assert(a2);
	char* temp = a2;
	while (*a1 != '\0')
	{
		*a2++ = *a1++;
	}
	return temp;
}

int main()
{
	char a1[8] = "success";
	char a2[10] = { 0 };
	printf("%s\n", a1);
	copy(a2, a1);
	for (int i = 0; i < 8; ++i)
	{
		printf("%c", a2[i]);
	}
	printf("\n");
	system("pause");
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
char* visualcat(char* arr1, char* arr2)
{
	assert(arr1);
	assert(arr2);
	char* temp = arr1;
	while (*arr1 != '\0')
	{
		arr1++;
	}
	while (*arr2 != '\0')
	{
		*arr1 = *arr2;
		arr1++;
		arr2++;
	}
	return temp;
}
int main()
{
	//思路:
	//先让第一个到'\0',然后开始赋值,当第二个为'\0'时停止
	char arr1[10] = "good";
	char arr2[] = " boy";
	visualcat(arr1, arr2);
	printf("%s\n", arr1);
	system("pause");
    return 0;
}
