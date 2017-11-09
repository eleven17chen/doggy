#include <stdio.h>
#include <math.h>

// Max count = 16, hit perimeter = 840

int find_solution(int perimeter);
bool is_perfect_square(int val);

int main()
{
    int max_count = 0;
    int hit_perimeter = 0;
    for (int perimeter = 3; perimeter <= 1000; perimeter++)
    {
        int count = find_solution(perimeter);
        if (count > max_count)
        {
            max_count = count;
            hit_perimeter = perimeter;
        }
    }

    printf("Max count = %d, hit perimeter = %d\n", max_count, hit_perimeter);

    return 0;
}

// @return answer count
int find_solution(int perimeter)
{
    int count = 0;
    int half = (int)(perimeter / 2);
    for (int a = 1; a < half; a++)
    {
        for (int b = 1; b < half; b++)
        {
            int c = perimeter - a - b;
            if (a*a + b*b == c*c)
            {
                ++count;
                printf("Found an answer: a = %d, b = %d, c = %d\n", a, b, c);
            }
        }
    }
    return count;
}

bool is_perfect_square(int val)
{
    int square_root = (int)sqrt(val);
    return square_root*square_root == val;
}

