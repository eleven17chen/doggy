#include <stdio.h>
#include <math.h>

#define max(a, b) (a) >= (b) ? (a) : (b)
#define min(a, b) (a) < (b) ? (a) : (b)

int main()
{
    int nums[] = {2, 3, -2, 4, 8};
    int arrlen = sizeof(nums) / sizeof(int);
    int posMax = nums[0];  
    int negMax = nums[0];  
    int ret = nums[0];  
    
    for(int i = 1; i < arrlen; i++)  
    {  
        int tempPosMax = posMax;  
        int tempNegMax = negMax;  
        posMax = max(nums[i],max(nums[i]*tempPosMax,nums[i]*tempNegMax));  
        negMax = min(nums[i],min(nums[i]*tempPosMax,nums[i]*tempNegMax));  
        ret = max(ret,posMax);  
    }  

    printf("ret = %d\n", ret);
}


