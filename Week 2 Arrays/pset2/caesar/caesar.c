#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

string plaintext;
int cipharInt;
string ciphertext;
char currLetter;
string cryptosystem(int key);


int main(int argc, string argv[])
{
    if (argc == 2)
    {
        bool isInt = true;
        for (int i = 0, n = strlen(argv[1]); i < n && isInt; i++)
        {
            if ((int) argv[1][i] >= 48 && (int) argv[1][i] <= 57)
            {
                isInt = true;
            }
            else
            {
                isInt = false;
            }
        }

        if (isInt)
        {
            // Converting a numeric string
            int x = atoi(argv[1]);
            printf("Success \n%i\n", x);

            string Caesar = cryptosystem(x);
            printf("Ciphertext: %s\n", Caesar);

        }

    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
}

string cryptosystem(int key)
{
    key = key % 26;
    plaintext = get_string("Plaintext: ");
    ciphertext = plaintext;
    // printf("Before: %s\n", ciphertext);
    for (int letter = 0, n = strlen(plaintext); letter < n; letter++)
    {
        // printf("%i\n", letter);
        currLetter = plaintext[letter];
        if (((int) currLetter >= 65 && (int) currLetter <= 90) || ((int) currLetter >= 97 && (int) currLetter <= 122))
        {
            cipharInt = (int) currLetter + key;
            if (cipharInt > 90 && cipharInt <= 96)
            {
                cipharInt = cipharInt - 90 + 64;
            }
            else if (cipharInt > 122)
            {
                cipharInt = cipharInt - 122 + 96;
            }
            ciphertext[letter] = cipharInt;
            // printf("currLetter: %i\n", currLetter);
            // printf("cipharInt: %i\n", cipharInt);
        }
    }
    // printf("After: %s\n", ciphertext);
    return ciphertext;
}

