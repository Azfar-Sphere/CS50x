#include <stdio.h>

int get_int(char string[30]);

int main(void)
{
    int x = get_int("What is your number?");
    int y = (x + 20);
    printf("%i\n", y);
}


int get_int(char string[30])
{
    int num;
    printf("%s\n", string);
    scanf("%i", &num);
    return num;
}