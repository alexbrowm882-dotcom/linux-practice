#include <stdio.h>

int divide(int a, int b)
{
    int result = a / b;
    return result;
}

int calculate(int x)
{
    int y = 0;
    return divide(x, y);
}

int main(void)
{
    int number = 100;

    int result = calculate(number);

    printf("result = %d\n", result);

    return 0;
}
