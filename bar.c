#include <stdio.h>

int main()
{
	char per[10] = {0};
	int i = 0;
	while(i < 10)
	{
		per[i] = '-';
		printf("%s\r",per);
		fflush(stdout);
		usleep(100000);
		i++;
	}
	return 0;
}
