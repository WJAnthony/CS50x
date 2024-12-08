#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    // prompt user to input credit card number
    long number;
    do
    {
        number = get_long("credit card number? ");
    }
    while (number < 1);

    int i = number / 10;
    printf("%i\n", i);
}
