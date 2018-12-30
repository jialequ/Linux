#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
int main()
{
1.
		5位运动员参加了10米台跳水比赛，有人让他们预测比赛结果
		A选手说：B第二，我第三；
		B选手说：我第二，E第四；
		C选手说：我第一，D第二；
		D选手说：C最后，我第三；
		E选手说：我第四，A第一；
		比赛结束后，每位选手都说对了一半，请编程确定比赛的名次。

	int a = 0, b = 0, c = 0, d = 0, e = 0;
	for (int a = 1; a <= 5; ++a)
	{
		for (int b = 1; b <= 5;++b)
		{
			for (int c = 1; c <= 5;++c)
			{
				for (int d = 1; d <= 5;++d)
				{
					for (int e = 1; e <= 5;++e)
					{
						if (((b == 2) + (a == 3) == 1)
							&& ((b == 2) + (e == 4) == 1)
							&& ((c == 1) + (d == 2) == 1)
							&& ((c == 5) + (d == 3) == 1)
							&& ((e == 4) + (a == 1) == 1)
							)
							if (a * b * c * d * e == 120)
							{
								printf("%d %d %d %d %d\n", a, b, c, d, e);
							}
					}
				}
			}
		}
	}
    system("pause");
    return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
int main()
{
	//2.
	//	日本某地发生了一件谋杀案，警察通过排查确定杀人凶手必为4个
	//	嫌疑犯的一个。以下为4个嫌疑犯的供词。
	//	A说：不是我。
	//	B说：是C。
	//	C说：是D。
	//	D说：C在胡说
	//	已知3个人说了真话，1个人说的是假话。
	//	现在请根据这些信息，写一个程序来确定到底谁是凶手。

		char killer;
	for (killer = 'A'; killer <= 'D'; ++killer)
	{
		if ((killer != 'A') + (killer == 'C') + (killer == 'D') + (killer != 'D') == 3)
		{
			printf("killer = %c\n", killer);
		}
	}


		char killer;
	for (killer = 'A'; killer <= 'D'; ++killer)
	{
		if ((killer != 'A') + (killer == 'C') + (killer == 'D') + (killer != 'D') == 3)
		{
			printf("killer = %c\n", killer);
		}
	}

    system("pause");
    return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
int main()
{
	//3.在屏幕上打印杨辉三角。
	//	1
	//	1 1
	//	1 2 1
	//	1 3 3 1
	
	int a[20][20] = { 0 };
	int n = 0;
	printf("输入要打印的行数:");
	scanf("%d", &n);

	for (int i = 0; i < n; ++i)
	{
		a[i][0] = 1;
	}
	for (int i = 1; i < n; ++i)
	{
		for (int j = 1; j <= i; ++j)
		{
			a[i][j] = a[i - 1][j - 1] + a[i - 1][j];
		}
	}
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j <= i; ++j)
		{
			printf("%d  ", a[i][j]);
		}
		printf("\n");
	}
  system("pause");
  return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
int  count_one_bits(unsigned int value)
{
	int count = 0;
	for (unsigned int i = 1; i != 0; i <<= 1)
	{
		if ((value & 1) == 1)
		{
			count++;
		}
		value >>= 1;
	}
	return count;
}

int main()
{
	//4.
	//	写一个函数返回参数二进制中 1 的个数
	//	比如： 15       0000 1111       4 个 1
	//	程序原型：
	//	int  count_one_bits(unsigned int value)
	//{
	//	// 返回 1的位数
	//}
	int n = 0;
	printf("输入一个人数计算二进制有几个一:");
	scanf("%u", &n);
	printf("%u\n", count_one_bits(n));
      system("pause");
    return 0;
}
