#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Asks for Name
    string name = get_string("What is your name?\n");

    // Prints Name
    printf("hello, %s\n", name);
}