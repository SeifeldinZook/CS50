#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int startSize;
    int endSize;
    int n = 0;
    int bornEachYear;
    int passawayEachYear;
    int incEachYear;
    
    // TODO: Prompt for start size
    do
    {
        startSize = get_int("Start size: ");
    }
    while (startSize < 9);
    
    // TODO: Prompt for end size
    do
    {
        endSize = get_int("End size: ");
    }
    while (endSize < startSize);

    // TODO: Calculate number of years until we reach threshold
    bornEachYear = startSize / 3;
    passawayEachYear = startSize / 4;
    incEachYear = bornEachYear - passawayEachYear;

    while (startSize < endSize)
    {
        startSize = startSize + incEachYear;
        // printf("startSize: %i\n", startSize);
        bornEachYear = startSize / 3;
        passawayEachYear = startSize / 4;
        incEachYear = bornEachYear - passawayEachYear;
        n = n + 1;
    }
    
    // TODO: Print number of years
    printf("\nYears: %i\n", n);
}