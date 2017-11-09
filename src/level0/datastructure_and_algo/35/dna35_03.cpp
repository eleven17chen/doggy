#include <stdio.h>
#include <math.h>

// Max count = 16, hit perimeter = 840
// Total compute times 14013140, N = 1000

// Max count = 40, hit perimeter = 9240
// Total compute times 13901381390, N = 10000

long long compute_count = 0;

int find_solution(int perimeter);
bool is_perfect_square(int val);

int main()
{
    int max_count = 0;
    int hit_perimeter = 0;
    int N = 10000;
    for (int perimeter = 3; perimeter <= N; perimeter++)
    {
        int count = find_solution(perimeter);
        if (count > max_count)
        {
            max_count = count;
            hit_perimeter = perimeter;
        }
    }

    printf("Max count = %d, hit perimeter = %d\n", max_count, hit_perimeter);

    printf("Total compute times %lld, N = %d\n", compute_count, N);

    return 0;
}

// @return answer count
int find_solution(int perimeter)
{
    int count = 0;
    int half = (int)(perimeter / 2);
    for (int a = 1; a < half; a++)
    {
        // a + b > half，因此b从half - a开始
        for (int b = half - a; b < half && perimeter - a - b > (a > b ? a : b); b++)
        {
            compute_count++;
            int c = perimeter - a - b;
            if (a*a + b*b == c*c)
            {
                ++count;
                // printf("Found an answer: a = %d, b = %d, c = %d\n", a, b, c);
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

