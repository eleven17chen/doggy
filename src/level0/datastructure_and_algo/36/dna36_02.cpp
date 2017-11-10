// dna 36, Champernowne constant
// 钱珀瑙恩数

// 0.123456789101112131415

// ? d1 * d10 * d100 * d1000 * d10000 * d100000 * d1000000

// 1位数有9个，2位数有90个，3位数有900个，以此类推
// 1 * 9 + 2 * 90 + 3 * 900 + 4 * 9000

// 如果n表示n位数，Y表示一共有多少位
// Y = segma(n * (9*10^(n-1))) : n = 1 ~ 无穷

/*

num is 1 at position[1]
num is 1 at position[10]
num is 5 at position[100]
num is 3 at position[1000]
num is 7 at position[10000]
num is 2 at position[100000]
num is 1 at position[1000000]
MUL = 210, SUM = 20
Total compute times: 6


num is 1 at position[1]
num is 1 at position[10]
num is 5 at position[100]
num is 3 at position[1000]
num is 7 at position[10000]
num is 2 at position[100000]
num is 1 at position[1000000]
num is 1 at position[10000000000]
MUL = 210, SUM = 21
Total compute times: 10
*/

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

// #define DEBUG_PRINT(format, ...) sprintf(format, ##__VA_ARGS__)
#define DEBUG_PRINT(format, ...)

long long compute_times = 0;

int main()
{
    // position必须是单调递增数组
    long long position[] = {1, 10, 100, 1000, 10000, 100000, 1000000 };
    // long long position[] = {10, 10, 11, 200, 2000};

    long long mul = 1;
    long long sum = 0;
    
    long long n = 0;
    
    long long last_n_len = 0;
    long long super_n_len = 0;
        
    for (long long loop = 0; loop < sizeof(position)/sizeof(long long); ++loop)
    {
        long long pos = position[loop];

        // 一个n可能覆盖多个pos
        if (super_n_len < pos)
        {
			last_n_len = super_n_len;
            // n表示几位数
            for (n = n + 1; ; n++)
            {
                compute_times++;
                super_n_len = last_n_len + n * (9 * (long long)pow(10, n-1));
                if (super_n_len >= pos)
                    break;
				else
					last_n_len = super_n_len;
            }
        }
        
        long long offset = pos - last_n_len;
        DEBUG_PRINT("n = %d, n_len = %d, pos = %d\n", n, n_len, pos);
        
        long long offset_mod = offset % n;
        long long offset_div = offset / n;

        long long n_start_val = (long long)pow(10, n-1);

        // hit_pos start from 1, not 0
        long long hit_pos = offset_mod;

        long long hit_num = 0;
        if (offset_mod == 0)
        {
            hit_num = n_start_val + offset_div - 1;
            hit_pos = n;
        }
        else
        {
            hit_num = n_start_val + offset_div;
        } 

        char arr[32] = {'\0'};
        sprintf(arr, "%d", hit_num);
		
        arr[hit_pos] = '\0';
        long long find_num = atoi((const char*)(arr + (hit_pos-1)));
        printf("num is %lld at position[%lld]\n", find_num, pos);
        mul *= find_num;
        sum += find_num;
    }
    printf("MUL = %lld, SUM = %lld\n", mul, sum);
    printf("Total compute times: %lld\n", compute_times);

    return 0;
}


