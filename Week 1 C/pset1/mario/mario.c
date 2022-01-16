#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int h;
    int spaces;
    int row = 1;
    
    do
    {
        h = get_int("Height: ");
    }
    while (h < 1 || h > 8);
    
    for (int i = h; i > 0; i--) 
    {
        spaces = i - 1;
        while (spaces > 0)
        {
            printf(" ");
            spaces--;
        }
        for (int j = 0; j < row; j++) 
        {
            printf("#");
        }
        row++;
        printf("\n");
    }
}