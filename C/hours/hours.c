#include <cs50.h>
#include <ctype.h>
#include <stdio.h>

float calc_hours(int hours[], int weeks, char output);

int main(void)
{
    int weeks = get_int("Number of weeks taking CS50: ");
    int hours[weeks];

    for (int i = 0; i < weeks; i++)
    {
        hours[i] = get_int("Week %i HW Hours: ", i);
    }

    char output;
    do
    {
        output = toupper(get_char("Enter T for total hours, A for average hours per week: "));
    }
    while (output != 'T' && output != 'A');

    printf("%.1f hours\n", calc_hours(hours, weeks, output));
}

// calc_hour; calcuates the hours
float calc_hours(int hours[], int weeks, char output)
{
    // Calculates Total Hours
    int total = 0;
    for (int i = 0; i < weeks; i++)
    {
        total += hours[i];
    }

    //Checks if Output is T
    if (output == 'T')
    {
        return total;
    }

    //Checks if Output is A
    else if (output == 'A')
    {
        return (float) total / weeks;
    }

    //Returns 0.0 if Neither
    return 0.0;
}