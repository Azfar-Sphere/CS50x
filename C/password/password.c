#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

bool valid(string password);

int main(void)
{
    //Asks for Password
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// Checks If Valid is True or Not
bool valid(string password)
{
    int n = strlen(password);
    int u = 0;
    int l = 0;
    int num = 0;
    int sym = 0;
    for (int i = 0; i < n; i++)
    {
        // Checks for Uppercase
        if (isupper(password[i]))
        {
            u++;
        }
        // Checks for Lower Case
        else if (islower(password[i]))
        {
            l++;
        }
        // Checks for Number
        else if (isdigit(password[i]))
        {
            num++;
        }
        // If a char is neither upper, lower or a number, it means it is a special char
        else
        {
            sym++;
        }
    }
    // Returns true if all criteria is met
    if (u >= 1 && l >= 1 && num >= 1 && sym >= 1)
    {
        return true;
    }
    return false;
}
