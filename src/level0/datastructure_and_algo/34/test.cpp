#include<stdio.h>
#define KON 50
int main(void)
{
    long bowle, i;
    int pan[KON] = {0};
    scanf("%ld", &bowle);
    for(i=0;bowle>10;i++){
        pan[i] = bowle%10;
        bowle /= 10;
    }
    pan[i] = bowle;
    for(;i>=0;i--)
        printf("%d\t", pan[i]);
    return 0;
}

