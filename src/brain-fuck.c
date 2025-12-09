#include<stdlib.h>
#include<stdio.h>




int main()
{

    void *programe;
    programe = calloc(30000,1);

    printf("hello in c");

    free(programe);
    return (0);
}