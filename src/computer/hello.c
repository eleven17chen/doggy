#include <stdio.h>

int main()
{
    const char *abc = "abc";
    char arr[10] = {'\0'};
    char arr2[10] = {'\0'};
    const char *p0arr = arr;
    // error : assignment of read-only location '*p0arr'
    // p0arr[0] = 'a';
    // ok
    p0arr = arr2;

    char * const p1arr = arr;
    // ok
    p1arr[0] = 'a';
    // error : assignment of read-only variable 'p1arr'
    // p1arr = arr2;
    
    // pointer and element all are read-only
    const char * const p2arr = arr;
    // p2arr[0] = 'a';
    // p2arr = arr2;

    printf("Hello C\n");
    return 0;
}

