#include <stdio.h>

int add(int a, int b)
{
    int result = a + b;
    return result;
}

int main(void)
{
    int x = 10;
    int y = 20;

    int result = add(x, y);

    printf("result = %d\n", result);

    return 0;
}
