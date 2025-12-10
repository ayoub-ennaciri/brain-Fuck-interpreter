#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<math.h>

// *filtering brain code 
char *filtreString(char *inputString)
{
    int stringLenght = strlen(inputString);
    char *newString = calloc(stringLenght,1);
    int i = 0;
    int j = 0;
    

    while(i < stringLenght)
    {
        if(inputString[i] == '+' || inputString[i] == '-' || inputString[i] == '>' 
            || inputString[i] == '<' || inputString[i] == '[' || inputString[i] == ']' 
            ||inputString[i] == '.')
        {
            newString[j] = inputString[i];
            j++;
        }
        i++;
    }
    return newString;
}

// *program run
void run(void *prBuffer,char *prCode)
{
    void *copy = prBuffer;
    int i = 0;
    while(prCode[i])
    {
        if(prCode[i] == '+')
        {
            *(char *)prBuffer += 1 ;
        }
        if(prCode[i] == '-')
        {
            *(char *)prBuffer -= 1;
        }
        if(prCode[i] == '<')
        {
            prBuffer--;
        }
        if(prCode[i] == '>')
        {
            prBuffer++;
        }
        if(prCode[i] == '.')
        {
            write(1,(char *)prBuffer,1);
        }
        i++;
    }
    printf("\nprnt %s\n",(char *)(prBuffer - 2) );
}

int main(int argc,char **argv)
{
    //check the nember of arguments
    if(argc != 2 )
    {
        printf("invalid number of arguments\n");
        return 0;
    }


    printf("aus dial 4 : %d\n",pow(4,2));

    void *program;
    program = calloc(30000,1);
    char *new = filtreString(argv[1]);
    run(program,new);
    free(new);
    free(program);
    return (0);
}