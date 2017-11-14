/*

*/

#include <stdio.h>

void sum(int outval, int *nums, int nums_len, int startidx, int k);


/*
int nums[] = {1, 2, 3, 4};
int k = 2;
int target = 5;

// found = 2
*/

int nums[] = {1, 2, 3, 4, 5};
int k = 3;
int target = 8;
// found = 3


int found = 0;

int main()
{
    int len = (int)(sizeof(nums) / sizeof(int));
    sum(0, nums, len, 0, k);

    printf("found : %d\n", found);

    return 0;
}

void sum(int outval, int *nums, int nums_len, int startidx, int k)
{
    for (int loop = startidx; loop < nums_len; ++loop)
    {
        int sumval = nums[loop] + outval;

        if (k > 1)
        {
            sum(sumval, nums, nums_len, loop + 1, k - 1);
        }
        else if (sumval == target)
        {
            found++;
        }
    }
}


