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
            printf("%p : %d\n",(char *)prBuffer,*(char *)prBuffer);
            write(1,(char *)prBuffer,1);
        }
        i++;
    }
    printf("\nprnt %s\n",(char *)(prBuffer - 2) );
}

// *get the number of square brackets
char ***squareBrackets(char *prCode)
{
    int lenght = strlen(prCode);
    int numberOfLeft = 0;
    int numberOfRight = 0;
    int i = 0;
    // ? getting number of left and right square brackets
    printf("lenght : %ld\n",strlen(prCode));
    while(i < lenght)
    {
        if(prCode[i] == '['){
            numberOfLeft++;
        }
        if(prCode[i] == ']'){
            numberOfRight++;
        }
        i++;
    }
    printf("left br: %d\nright br: %d\n",numberOfLeft,numberOfRight);
    // ? checking if they are aqual
    if(numberOfLeft != numberOfRight || !numberOfLeft || !numberOfRight ){
        printf("Syntax Error : FIN MA3ART\n");
        return NULL;
    }
    
    // ? allocating for left brackets
    char **bracketLeft = calloc(numberOfLeft, sizeof(char *));
    if(!bracketLeft)
    {
        return NULL;
    }

    // ? allocating for right brackets
    char **bracketRight = calloc(numberOfLeft, sizeof(char *));
    if(!bracketRight)
    {
        free(bracketLeft);
        return NULL;
    }

    int j = 0;
    int h = 0;
    i = 0;

    while(i < lenght)
    {
        if(prCode[i] == '['){
            bracketLeft[j] = &prCode[i];
            printf("left bracket at position %d\nstrored at adrr: %p\n",i,bracketLeft[j]);
            j++;
        }
        i++;
    }

    while(i >= 0)
    {
        if(prCode[i] == ']'){
            bracketRight[h] = &prCode[i];
            printf("right bracket at position %d\nstrored at adrr: %p\n",i,bracketRight[h]);
            h++;
        }
        i--;
    }

    char ***bracketArray = calloc(2,sizeof(char ***));
    bracketArray[0] = bracketLeft;
    bracketArray[1] = bracketRight;
    return bracketArray;
}

int main(int argc,char **argv)
{
    //check the nember of arguments
    if(argc != 2 )
    {
        printf("invalid number of arguments\n");
        return 0;
    }

    // alloc program buffer
    void *program;
    program = calloc(30000,1);
    if(!program)
    {
        return 0;
    }

    // filtering the input string from unwanted chars
    char *new = filtreString(argv[1]);

    // getting the addresses of the squar brackets
    char ***array = squareBrackets(new);
    if(!array)
    {
        return 0;
    }

    run(program,new);
    free(array);
    free(new);
    free(program);
    return (0);
}