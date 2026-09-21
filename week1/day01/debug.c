#include <stdio.h>
int main()
{
    int a,b;
    a=10;
    b=20;
    int sum=a+b;
#ifdef DEBUG
    printf("DEBUG a=%d\n",a);
    printf("DEBUG b=%d\n",b);
#endif
    printf("sun=%d\n",sum);
    return 0;
}

