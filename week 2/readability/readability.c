#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    // prompt user for text
    string text = get_string("Input text: ");

    // count number of letters, words and sentences
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    // calculate coleman-liau index
    float letters_per_100 = letters / (float) words * 100.0;
    float sentences_per_100 = sentences / (float) words * 100.0;

    double coleman_liau = (0.0588 * letters_per_100) - (0.296 * sentences_per_100) - 15.8;
    int grade = round(coleman_liau);

    // print out appropriate grade for text
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}

int count_letters(string text)
{
    int sum = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        int a = toupper(text[i]);
        if (a >= 65 && a <= 90)
        {
            sum++;
        }
    }
    return sum;
}

int count_words(string text)
{
    int sumspaces = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        int a = text[i];
        if (a == 32)
        {
            sumspaces++;
        }
    }
    return (sumspaces + 1);
}

int count_sentences(string text)
{
    int sumsentences = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        int a = text[i];
        if (a == 33 || a == 46 || a == 63)
        {
            sumsentences++;
        }
    }
    return (sumsentences);
}
