#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int points[26] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int calculate_score(string player_word);

int main(void)
{
    // player 1 and 2 words
    string w1 = get_string("Player 1: ");
    string w2 = get_string("Player 2: ");

    // calculate score of each word
    int score1 = calculate_score(w1);
    int score2 = calculate_score(w2);

    // print winner
    if (score1 == score2)
    {
        printf("Tie!\n");
    }
    else if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else
        printf("Player 2 wins!\n");
}

int calculate_score(string player_word)
{
    // converts into uppercase
    int value = 0;
    int sum = 0;
    for (int i = 0, n = strlen(player_word); i < n; i++)
    {
        // calculate score if alphabet
        int a = toupper(player_word[i]);
        if (a >= 65 && toupper(a) <= 90)
        {
            value = points[(a - 65)];
        }
        else
        {
            // calculate score if not a alphabet
            value = 0;
        }
        sum = sum + value;
    }
    return sum;
}
