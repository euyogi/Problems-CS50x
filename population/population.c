#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int min;
    do
    {
        min = get_int("Start size: ");
    }
    while (min < 9);

    // TODO: Prompt for end size
    int end;
    do
    {
        end = get_int("End size: ");
    }
    while (end < min);

    // TODO: Calculate number of years until we reach threshold
    int pop = min, years = 0;
    if (min != end)
    {
        do
        {
            pop = pop + pop / 3 - pop / 4;
            years++;
        }
        while (pop < end);
    }
    
    // TODO: Print number of years
    printf("Years: %i\n", years);
}
