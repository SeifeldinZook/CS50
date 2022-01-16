from cs50 import get_string
import string

def main():
    text = get_string("Text: ")

    lettersF = count_letters(text)
    wordsF = count_words(text)
    sentencesF = count_sentences(text)
    # print(lettersF, wordsF, sentencesF)

    L = (lettersF / wordsF * 100)
    S = (sentencesF / wordsF * 100)
    index = round(0.0588 * L - 0.296 * S - 15.8)
    
    if (index < 1):
        print("Before Grade 1")
    elif (index >= 16):
        print("Grade 16+")
    else:
        print("Grade", index)


AlphaCharacters = string.ascii_lowercase

def count_letters(string):
    letters = 0
    for l in string:
        if l.lower() in AlphaCharacters:
            letters += 1
    return letters

def count_words(string):
    spaces = string.count(" ")
    return spaces + 1

def count_sentences(string):
    sentences = string.count(".") + string.count("!") + string.count("?")
    return sentences


if __name__ == "__main__":
    main()
