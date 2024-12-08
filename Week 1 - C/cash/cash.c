#include <cs50.h>
#include <stdio.h>

int calculate_quarters(int cents);
int calculate_tencents(int cents);
int calculate_fivecents(int cents);
int calculate_onecents(int cents);

int main(void)
{
    // prompt user to input change owed
    int cents;
    do
    {
        cents = get_int("amount of change owed, in cents? ");
    }
    while (cents < 0);

    // calculte number of quarters
    int quarters = calculate_quarters(cents);
    cents = cents - (quarters * 25);

    // calculte number of tens
    int tens = calculate_tencents(cents);
    cents = cents - (tens * 10);

    // calculte number of fives
    int fives = calculate_fivecents(cents);
    cents = cents - (fives * 5);

    // calculte number of ones
    int ones = calculate_onecents(cents);

    int total = quarters + tens + fives + ones;
    printf("%i\n", total);
}

int calculate_quarters(int cents)
{
    // calculate number of quarters to give
    int quarters = 0;
    while (cents >= 25)
    {
        quarters++;
        cents = cents - 25;
    }
    return quarters;
}

int calculate_tencents(int cents)
{
    // calculate number of tencents to give
    int tencents = 0;
    while (cents >= 10)
    {
        tencents++;
        cents = cents - 10;
    }
    return tencents;
}

int calculate_fivecents(int cents)
{
    // calculate number of fivecents to give
    int fivecents = 0;
    while (cents >= 5)
    {
        fivecents++;
        cents = cents - 5;
    }
    return fivecents;
}

int calculate_onecents(int cents)
{
    // calculate number of onecents to give
    int onecents = 0;
    while (cents >= 1)
    {
        onecents++;
        cents = cents - 1;
    }
    return onecents;
}
