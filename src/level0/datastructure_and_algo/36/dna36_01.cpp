// dna 36, Champernowne constant
// 钱珀瑙恩数

// 0.123456789101112131415

// ? d1 * d10 * d100 * d1000 * d10000 * d100000 * d1000000

/*
num is 1 at position[1]
num is 1 at position[10]
num is 5 at position[100]
num is 3 at position[1000]
num is 7 at position[10000]
num is 2 at position[100000]
num is 1 at position[1000000]
MUL = 210, SUM = 20
Total compute times: 185185
*/


#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#define MAX 10000000

long long compute_times = 0;

int main()
{
    // position必须是单调递增数组
    int position[] = {1, 10, 100, 1000, 10000, 100000, 1000000};
    // int position[] = {10, 10, 11, 200, 2000};

    int pos = 0;
    char *arr = new char[MAX * 100];
    char *parr = arr;
    int d = 1;
    for (; d <= MAX; ++d)
    {
        char a[32] = {'\0'};
        sprintf(a, "%d", d);
        strcpy(parr, a);
        assert(parr + strlen(a) - arr >= 0);
        parr += strlen(a);
        compute_times++;
        if (parr - arr > position[(sizeof(position)/sizeof(int) - 1)])
            break;
    }

    int mul = 1;
    int sum = 0;
    for (int loop = 0; loop < sizeof(position)/sizeof(int); ++loop)
    {
        arr[position[loop]] = '\0';
        int num = atoi((const char*)(arr + (position[loop] - 1)));
        mul *= num;
        sum += num;
        printf("num is %d at position[%d]\n", num, position[loop]);
    }

    printf("MUL = %d, SUM = %d\n", mul, sum);
    printf("Total compute times: %lld\n", compute_times);
}


