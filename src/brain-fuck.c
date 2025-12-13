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
void run(void *prBuffer, char *prCode)
{
    void *copy = prBuffer;
    int i = 0;
    int j = 0;
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
            // printf("%p : %d\n",(char *)prBuffer,*(char *)prBuffer);
            write(1,(char *)prBuffer,1);
        }
        // if(prCode[i] == '[')
        // {
        //     if(*(char *)prBuffer) i++;
        //     else {
        //         prBuffer = array[++j];
        //         j;
        //     }
        // }
        i++;
    }
    printf("\nprnt %s\n",(char *)(prBuffer - 2) );
}

// *get the number of square brackets
// char ***squareBrackets(char *prCode)
// {
//     int lenght = strlen(prCode);
//     int numberOfLeft = 0;
//     int numberOfRight = 0;
//     int i = 0;
//     // ? getting number of left and right square brackets
//     printf("lenght : %ld\n",strlen(prCode));
//     while(i < lenght)
//     {
//         if(prCode[i] == '['){
//             numberOfLeft++;
//         }
//         if(prCode[i] == ']'){
//             numberOfRight++;
//         }
//         i++;
//     }
//     printf("left br: %d\nright br: %d\n",numberOfLeft,numberOfRight);
//     // ? checking if they are aqual
//     if(numberOfLeft != numberOfRight || !numberOfLeft || !numberOfRight ){
//         printf("Syntax Error : FIN MA3ART\n");
//         return NULL;
//     }
    
//     // ? allocating for left brackets
//     char **bracketLeft = calloc(numberOfLeft, sizeof(char *));
//     if(!bracketLeft)
//     {
//         return NULL;
//     }

//     // ? allocating for right brackets
//     char **bracketRight = calloc(numberOfLeft, sizeof(char *));
//     if(!bracketRight)
//     {
//         free(bracketLeft);
//         return NULL;
//     }

//     int j = 0;
//     int h = 0;
//     i = 0;

//     while(i < lenght)
//     {
//         if(prCode[i] == '['){
//             bracketLeft[j] = &prCode[i];
//             printf("left bracket at position %d\nstrored at adrr: %p\n",i,bracketLeft[j]);
//             j++;
//         }
//         i++;
//     }

//     while(i >= 0)
//     {
//         if(prCode[i] == ']'){
//             bracketRight[h] = &prCode[i];
//             printf("right bracket at position %d\nstrored at adrr: %p\n",i,bracketRight[h]);
//             h++;
//         }
//         i--;
//     }

//     char ***bracketArray = calloc(2,sizeof(char ***));
//     bracketArray[0] = bracketLeft;
//     bracketArray[1] = bracketRight;
//     return bracketArray;
// }

char **getPsquarBracket(char *prcode)
{
    int lenght = strlen(prcode);
    int numberOfLeft = 0;
    int numberOfRight = 0;
    char **PsquarBracket = NULL;
    
    // ? getting number of left and right square brackets
    // printf("lenght : %ld\n",strlen(prcode));
    int i = 0;
    while(i < lenght)
    {
        if(prcode[i] == '['){
            numberOfLeft++;
        }
        if(prcode[i] == ']'){
            numberOfRight++;
        }
        i++;
    }

    // ? checking if they are aqual
    if(numberOfLeft != numberOfRight ){
        printf("Syntax Error : FIN MA3ART\n");
        return NULL;
    }

    // ? allocating for totalsq
    PsquarBracket = calloc(numberOfLeft + numberOfRight, sizeof(char *));
    if(!PsquarBracket)
    {
        return NULL;
    }
    
    i = 0;
    int j = 0;
    int g = 0;
    int k = 0;
    int tmp = 0;
    while(i < strlen(prcode))
    {
        if(prcode[i] == '['){
            PsquarBracket[j] = &prcode[i];
            // printf("%c at add : %p\n",*(char *)PsquarBracket[j],PsquarBracket[j]);
            j++;
            k = i;

            while(1){
                if(prcode[k] == '[') {
                    // printf("g+ : %d\n",g);
                    g++;
                };
                
                if(prcode[k] == ']') {
                    g--;
                    // printf("g- : %d\n",g);
                };

                if(g == 0){
                    PsquarBracket[j] = &prcode[k];
                    // printf("k : %d\n",k);
                    // printf("%c at add : %p\n",*(char *)PsquarBracket[j],PsquarBracket[j]);
                    j++;
                    break;
                }
                k++;
            }
            k = 0;  
            g = 0;
        }
        i++;
    }

    //print all brackets and ther addresse
    i = 0;
    printf("total square barckets: %d\n",numberOfLeft + numberOfRight);
    while(i < (numberOfLeft + numberOfRight))
    {
        printf("%c at add : %p\n",*(char *)PsquarBracket[i],PsquarBracket[i]);
        i++;
    }

    return PsquarBracket;
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

    printf("check1\n");
    // getting the addresses of the squar brackets
    char **PsquarBracket = getPsquarBracket(new);
    if(!PsquarBracket)
    {
        return 0;
    }
    
    
    // run the program 
    run(program,new);

    free(PsquarBracket);
    free(new);
    free(program);
    return (0);
}