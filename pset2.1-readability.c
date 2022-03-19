#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_words(string text);          // Counts the number of white spaces + 1 in the string
int count_letters(string text);        // Counts the number of alphabetical characters in the string
float count_avletters(string text);    // Number of letters / Number of words * 100
int count_sentences(string text);      // Count the number of sentences
float count_avsentences(string text);  // Number of sentences / Number of words * 100

int main(void)
{
    /* Retrive passage */
    string text = get_string("Enter your passage here: ");

    /* Compute averages */
    float avletters = count_avletters(text);
    float avsentences = count_avsentences(text);

    /* Obtain the Coleman-Liau Index and round it to nearest integer */
     int index = (int) round(0.0588 * avletters - 0.296 * avsentences - 15.8);

    /* Print the result */
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (1 <= index && index <= 15)
    {
        printf("Grade %i\n", index);
    }
    else
    {
        printf("Grade 16+\n");
    }
}

/* Counts the number of white spaces + 1 in the string */
int count_words(string text)
{
    int words = 0;
    for (int i = 0, length = strlen(text); i < length; i++)
    {
        if (isspace(text[i]))
        {
            words += 1;
        }
    }
    words += 1; // Final word does not have a corresponding white space. To count number of words, need to +1 to adjust correctly.
    return words;
}

/* Counts the number of alphabetical characters in the string */
int count_letters(string text)
{
    int letters = 0;
    for (int i = 0, length = strlen(text); i < length; i++)
    {
        if (isalpha(text[i]))
        {
            letters += 1;
        }
    }
    return letters;
}

/* Number of letters / Number of words * 100 */
float count_avletters(string text)
{
    float letters = (float) count_letters(text);
    float words = (float) count_words(text);
    return (letters / words) * 100;
}

/* Count the number of sentences */
int count_sentences(string text)
{
    int sentences = 0;
    for (int i = 0, length = strlen(text); i < length; i ++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences += 1;
        }
    }
    return sentences;
}

/* Number of sentences / Number of words  */
float count_avsentences(string text)
{
    float sentences = (float) count_sentences(text);
    float words = (float) count_words(text);
    return (sentences / words) * 100;
}