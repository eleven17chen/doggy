#include <stdio.h>
#include <math.h>
#include <assert.h>

#define DEBUG_PRINT(format, ...) printf((format), ##__VA_ARGS__)

void test();
bool is_prime(int val);
bool is_truncatable_prime(int val);
bool is_double_truncatable_prime(int val);
void sum_truncatable_prime();
int reverse(int val);


int main()
{
    // test();
    sum_truncatable_prime();
    return 0;
}

void test()
{
    bool b= false;
    
    b = is_prime(0);
    assert(b == false);
    b = is_prime(1);
    assert(b == false);
    b = is_prime(2);
    assert(b == true);
    b = is_prime(3);
    assert(b == true);
    b = is_prime(4);
    assert(b == false);
    b = is_prime(3797);
    assert(b == true);
    b = is_prime(32);
    assert(b == false);

    b = is_truncatable_prime(3797);
    assert(b == true);
    b = is_truncatable_prime(7973);
    assert(b == false);
    b = is_truncatable_prime(11);
    assert(b == false);
    b = is_truncatable_prime(97);
    assert(b == false);
    b = is_truncatable_prime(79);
    assert(b == false);

/*
    b = is_double_truncatable_prime(32);
    assert(b == false);
    b = is_double_truncatable_prime(3797);
    assert(b == true);
    b = is_double_truncatable_prime(97);
    assert(b == false);

    int val = 0;
    val = reverse(1234);
    assert(val == 4321);
    val = reverse(0);
    assert(val == 0);
    val = reverse(4);
    assert(val == 4);
    val = reverse(1230);
    assert(val == 321);
*/

}

void sum_truncatable_prime()
{
    int cnt = 0;
    int val = 11;
    int sum = 0;
    for (int val = 11; ; val++)
    {
        if (is_truncatable_prime(val))
        {
            sum += val;
            cnt++;
        }

        if (cnt == 11)
            break;
    }
    printf("SUM = %d\n", sum);

    return;
}

/*
int reverse(int val)
{
    assert(val >= 0);
    int retval = 0;
    while (val > 0) 
    {
        retval *= 10;
        retval += val % 10;
        val /= 10;
    }
    return retval;
}

// 3797 -> 379 -> 37 -> 3
// 3797 -> 797 -> 97 -> 7
bool is_double_truncatable_prime(int val)
{
    bool ret = false;
    if (is_truncatable_prime(val) && is_truncatable_prime(reverse(val)))
    {
        printf("Found a truncatable prime: %d\n", val);
        ret = true;
    }
    return ret;
}
*/

// 3797 -> 379 -> 37 -> 3
bool is_truncatable_prime(int val)
{
    bool ret = false;

    if (val > 10 && is_prime(val))
    {
        ret = true;
        int tmpval = val;
        do
        {
            tmpval /= 10;
            if (tmpval > 0 && !is_prime(tmpval))
            {
                ret = false;
                break;
            }
        } while (tmpval > 0);       
    }

    if (true == ret)
    {
        int tens = 1;
        int tmpval2 = val;

        do
        {
            tens *= 10;
        } while ((tmpval2 / tens) > 0);
        
        do
        {
            tens /= 10;
            tmpval2 %= tens;
            if (tmpval2 > 0 && !is_prime(tmpval2))
            {
                ret = false;
                break;
            }    
        }
        while (tmpval2 > 10);
    }

    if (true == ret)
        printf("Found a truncatable prime: %d\n", val);

    return ret;
}

bool is_prime(int val)
{
    assert(val >= 0);
    bool ret = true;

    if (val < 2)
        ret = false;
    else
    {
        int tmp = (int)sqrt(val);
        for (int loop = 2; loop <= tmp; loop++)
        {
            if (val % loop == 0)
                ret = false;
        }
    }
    
    return ret;
}


