#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int count_letters(string str);
int count_words(string str);
int count_sentences(string str);
int main(void)
{
    // Get text from user
    string text = get_string("Text: ");

    int countLetters = count_letters(text);
    int countWords = count_words(text);
    int countSentences = count_sentences(text);

    // printf("%i letter(s)\n", countLetters);
    // printf("%i words(s)\n", countWords);
    // printf("%i sentence(s)\n", countSentences);

    float lettersF = countLetters;
    float wordsF = countWords;
    float sentencesF = countSentences;

    //Coleman-Liau index
    float L = (lettersF /  wordsF * 100);
    float S = (sentencesF /  wordsF * 100);
    int index = round(0.0588 * L - 0.296 * S - 15.8);
    // printf("L %f\n", L);
    // printf("S %f\n", S);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }

}

int count_letters(string str)
{
    int letters = 0;
    char currLetter;
    for (int letter = 0, n = strlen(str); letter < n; letter++)
    {
        currLetter = toupper(str[letter]);
        for (int decASCII = 65; decASCII <= 90; decASCII++)
        {
            if ((int) currLetter == decASCII)
            {
                letters++;
            }
        }
    }
    return letters;
}

int count_words(string str)
{
    bool afterSpace = false;
    int words = 0;
    char currLetter;
    for (int letter = 0, n = strlen(str); letter < n; letter++)
    {
        currLetter = str[letter];
        // printf("%c - ", currLetter);
        // printf("%i\n", (int) currLetter);

        if ((int) currLetter == 32)
        {
            words++;
        }
    }
    return words + 1;
}

int count_sentences(string str)
{
    int sentences = 0;
    char currLetter;
    for (int letter = 0, n = strlen(str); letter < n; letter++)
    {
        // printf("%c - ", currLetter);
        // printf("%i\n", (int) currLetter);
        currLetter = str[letter];
        if ((int) currLetter == 33 || (int) currLetter == 46 || (int) currLetter == 63)
        {
            sentences++;
        }
    }
    return sentences;
}