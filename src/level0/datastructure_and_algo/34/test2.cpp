#include <math.h>
#include<stdio.h>

int main()
{
    int Num;

	scanf("%d",&Num);
	int Num_get = 1,i = 1;
	while(Num_get != 0)
	{
		Num_get=Num % (int)(pow(10,i));	
		printf("%d\n",Num_get);
		i++;
	}
	return 0;
}
