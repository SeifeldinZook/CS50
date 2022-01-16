// Greedy Algorithms

#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    float change;
    int coins = 0;
    int quarters = 25;
    int dimes = 10;
    int nickels = 5;
    int pennies = 1;
    
    
    do
    {
        change = get_float("Change owed: ");
    }
    while (change < 0);
    
    int cents = round(change * 100);
    // printf("%i\n", cents);
    
    for (int i = cents; i >= 0 && cents != 0; i--)
    {
        if (cents >= quarters)
        {
            cents = cents - quarters;
            // printf("%i\n",i);
            // printf("Cents: %i\n", cents);
        }
        else if (cents >= dimes)
        {
            cents = cents - dimes;
            // printf("%i\n",i);
            // printf("Cents: %i\n", cents);
        }
        else if (cents >= nickels)
        {
            cents = cents - nickels;
            // printf("%i\n",i);
            // printf("Cents: %i\n", cents);
        }
        else
        {
            cents = cents - pennies;
            // printf("%i\n",i);
            // printf("Cents: %i\n", cents);
        }
        coins++;
    }
    printf("Coins: %i\n", coins);
}