#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    // prompt user to include key in command line
    if (argc <= 1 || argc >= 3)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    // prompt user to include key with 26 characters
    int length = strlen(argv[1]);
    if (length != 26)
    {
        printf("Key must contain 26 characters\n");
        return 1;
    }
    // prompt user to include key with only alphabets
    for (int i = 0; i < 26; i++)
    {
        int a = isalpha(argv[1][i]);
        if (a == 0)
        {
            printf("Key must contain only alphabets\n");
            return 1;
        }
    }
    // prompt user to only use each alphabet exactly once
    for (int i = 0; i < 26; i++)
    {
        for (int j = i + 1; j < 26; j++)
        {
            if (argv[1][i] == argv[1][j])
            {
                printf("Key cannot contain repeated alphabets\n");
                return 1;
            }
        }
    }
    // converting key into all upppercase
    for (int i = 0; i < length; i++)
    {
        argv[1][i] = toupper(argv[1][i]);
    }

    // prompt user to input plain text
    string plaintext = get_string("plaintext: ");

    // encrypting each character of plaintext
    int n = strlen(plaintext);
    char c;
    int ascii;

    printf("ciphertext: ");
    for (int i = 0; i < n; i++)
    {
        ascii = toupper(plaintext[i]);
        if (plaintext[i] >= 'a' && plaintext[i] <= 'z')
        {
            c = tolower(argv[1][ascii - 65]); // since char and int are interchangable
        }
        else if (plaintext[i] >= 'A' && plaintext[i] <= 'Z')
        {
            c = argv[1][ascii - 65];
        }
        else
        {
            c = plaintext[i];
        }
        // printing each character to form the enciphertext
        printf("%c", c);
    }
    printf("\n");
    return 0;
}
