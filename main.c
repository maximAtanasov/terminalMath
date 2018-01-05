#include "defs.h"

void truncate(char* s);
int convertToRPN(char* infix, char* postfix, int buffer_size);
double evaluateRPN(char* postfix);

int main(void){
    printf("T3rmin4lMath by Max\n");
    printf("v1.0, Maxim Atanasoff\n");
    printf("Type help to see further options.\n\n");
    unsigned int buffer_size = 256;
    char input[buffer_size-50];
    while(strcmp(fgets(input, buffer_size-50, stdin), "exit\n") != 0){
        if(strcmp(input, "help\n") == 0)
            printf("Type \"clear\" to clear the screen or \"exit\" to exit the program\n");
        else if(strcmp(input, "\n") == 0)
            continue;
        else if(strcmp(input, "clear\n")== 0)
            printf("\e[1;1H\e[2J");
        else{
            char buff[buffer_size];
            memset(buff,1,sizeof(buff));
            buff[buffer_size-1] = 0;
            strtok(input, "\n");
            if(convertToRPN(input, buff, sizeof(buff)) == -1){
                printf("Invalid input!\n");
                continue;
            }
            double result = evaluateRPN(buff);
            snprintf(buff, sizeof(buff), "%lf", result);
            truncate(buff);
            printf("%s\n", buff);
        }
        memset(input,0,strlen(input));
    }
}


//removes any excess zeroes from a number
void truncate(char* s){
    int n;
    for(n = 0; s[n] != 0; ++n);
    for(int i = n-1; i >= 0; i--)
        if(s[i] == '0')
            s[i] = '\0';
        else if(s[i] == '.'){
            s[i] = '\0';
            break;
        }
        else
            break;
}
