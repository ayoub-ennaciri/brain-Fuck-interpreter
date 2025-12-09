#include<stdlib.h>
#include<stdio.h>
#include<string.h>

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


int main(int argc,char **argv)
{
    //check the nember of arguments
    if(argc != 2 )
    {
        printf("invalid number of arguments\n");
        return 0;
    }

    void *programe;
    programe = calloc(30000,1);
    char *new = filtreString(argv[1]);
    free(new);
    free(programe);
    return (0);
}