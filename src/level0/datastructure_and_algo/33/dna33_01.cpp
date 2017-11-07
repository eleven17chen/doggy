#include <stdio.h>
#include <assert.h>

#define DEBUG_PRINT(format, ...) printf(format, ##__VA_ARGS__)
// #define DEBUG_PRINT(format, ...) 


void test();

bool is_palindrome_dec(int decval);
bool is_palindrome_bin(int decval);
void print_dec_to_bin(int decval);

int main()
{
    test();
    int sum = 0;
    for (int val = 0; val < 1000000; val++)
    {
        if (is_palindrome_bin(val) && is_palindrome_dec(val))
        {
            printf("Found on: %d\n", val);
            sum += val;
        }
    }
    printf("sum = %d\n", sum);
}

void test()
{
    bool d1 = is_palindrome_dec(585);
    assert(d1 == true);
    bool d2 = is_palindrome_dec(185);
    assert(d2 == false);
    bool d3 = is_palindrome_dec(4);
    assert(d3 == true);
    bool d4 = is_palindrome_dec(0);
    assert(d4 == true);

    bool b1 = is_palindrome_bin(585);
    assert(b1 == true);
    bool b2 = is_palindrome_bin(323);
    assert(b2 == false);
    bool b3 = is_palindrome_bin(1);
    assert(b3 == true);
    bool b4 = is_palindrome_bin(2);
    assert(b4 == false);
    bool b5 = is_palindrome_bin(5);
    assert(b5 == true);  
    bool b6 = is_palindrome_bin(0);
    assert(b6 == true);

    bool m1 = is_palindrome_dec(5) && is_palindrome_bin(5);
    assert(m1 == true);
    bool m2 = is_palindrome_dec(9) && is_palindrome_bin(9);
    assert(m2 == true);

    print_dec_to_bin(10);
    DEBUG_PRINT("\n");
    print_dec_to_bin(16);
    DEBUG_PRINT("\n");
    print_dec_to_bin(48);
    DEBUG_PRINT("\n");
}

bool is_palindrome_dec(int decval)
{
    assert(decval >= 0 && decval < 1000000);

    bool ret = false;
    int oldval = decval;
    int newval = 0;
    while (decval > 0)
    {
        newval *= 10;
        newval += decval % 10;
        decval /= 10;
    }

    if (oldval == newval)
        ret = true;
    else
        ret = false;

    DEBUG_PRINT("oldval = %d, newval = %d, is dec palindrome = %d\n", oldval, newval, ret);

    return ret;
}

bool is_palindrome_bin(int decval)
{
    assert(decval >= 0 && decval < 1000000);

    bool ret = false;
    int oldval = decval;
    int newval = 0;
    while (decval > 0)
    {
        newval <<= 1;
        newval += decval & 0x01;
        decval >>= 1;
    }

    if (oldval == newval)
        ret = true;
    else
        ret = false;

    DEBUG_PRINT("oldval = %d, newval = %d, is bin palindrome = %d\n", oldval, newval, ret);
    
    return ret;
}

void print_dec_to_bin(int decval)
{
    assert(decval >= 0 && decval < 1000000);
    int d2b[8] = {0};
    int oldval = decval;
    int idx = 0;
    while (decval > 0)
    {
        d2b[idx++] = decval & 1;
        decval >>= 1;
    }

    DEBUG_PRINT("%d to bin is ", oldval);
    for (idx = 7; idx > -1; --idx)
    {
        DEBUG_PRINT("%d", d2b[idx]);
    }

    return;
}

