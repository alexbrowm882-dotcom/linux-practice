#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    char *cwd = getcwd(NULL, 0);

    if (cwd == NULL)
    {
        perror("getcwd");
        return 1;
    }

    printf("cwd = %s\n", cwd);

    free(cwd);

    return 0;
}
