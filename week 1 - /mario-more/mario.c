#include <cs50.h>
#include <stdio.h>

void print_row(int spaces, int length);

int main(void)
{
    // prompt user to input a suitable value
    int height;
    do
    {
        height = get_int("height of pyramid? ");
    }
    while (height < 1 || height > 8);

    // build pyramid of input height
    for (int i = 0; i < height; i++)
    {
        print_row(height - i, i + 1);
    }
}

// Defining print_row
void print_row(int spaces, int length)
{
    // producing correct number of " "
    for (int i = 0; i < spaces - 1; i++)
    {
        printf(" ");
    }
    // producing correct number of "#" left of gap
    for (int j = 0; j < length; j++)
    {
        printf("#");
    }
    // producing the 2 spacing gap
    printf("  ");
    
    // producing correct number of "#" right of gap
    for (int j = 0; j < length; j++)
    {
        printf("#");
    }
    printf("\n");
}
