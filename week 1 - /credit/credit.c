#include <cs50.h>
#include <stdio.h>

int number_of_digits(long ccnumber);
int checksum(long ccnumber);
int starting(long ccnumber);

int main(void)
{
    int d;
    long ccnumber;
    int t;
    int f2d;
    // prompt user to input credit card number
    do
    {
        ccnumber = get_long("Credit Card number? ");
    }
    while (ccnumber < 0);

    // determining if number of digits is valid
    d = number_of_digits(ccnumber);
    if (d != 13 && d != 15 && d != 16)
    {
        printf("INVALID\n");
        return 0;
    }

    // determing if checksum test is valid
    t = checksum(ccnumber);
    if (t < 10)
    {
        printf("INVALID\n");
        return 0;
    }
    t = t % 10;
    if (t != 0)
    {
        printf("INVALID\n");
        return 0;
    }

    // determing which company
    f2d = starting(ccnumber);
    // checking Mastercard
    if (f2d == 51 || f2d == 52 || f2d == 53 || f2d == 54 || f2d == 55)
    {
        d = number_of_digits(ccnumber);
        if (d == 16)
        {
            printf("MASTERCARD\n");
        }
        else
            printf("INVALID\n");
    }
    // checking AMEX
    else if (f2d == 34 || f2d == 37)
    {
        d = number_of_digits(ccnumber);
        if (d == 15)
        {
            printf("AMEX\n");
        }
        else
            printf("INVALID\n");
    }
    // checking VISA
    else if ((f2d / 10) == 4)
    {
        d = number_of_digits(ccnumber);
        if (d == 13 || d == 16)
        {
            printf("VISA\n");
        }
        else
            printf("INVALID\n");
    }

    else
    {
        printf("INVALID\n");
        return 0;
    }
}

// calculating number of digits in cc number
int number_of_digits(long ccnumber)
{
    int digits = 0;
    while (ccnumber > 0)
    {
        ccnumber = ccnumber / 10;
        digits++;
    }
    return digits;
}

// checksum (luhn's algorithm)
int checksum(long ccnumber)
{
    int sumx1 = 0;
    int sumx2 = 0;
    int i = 0;
    int j = 0;
    int rightd = 0;
    int leftd = 0;
    int totalsum = 0;

    while (ccnumber > 0)
    {
        // adding last digit
        i = ccnumber % 10;
        sumx1 = sumx1 + i;

        // removing last digit + finding 2nd last digit
        ccnumber = ccnumber / 10;
        j = ccnumber % 10;

        // doubling 2nd last digit + finding sum
        rightd = (j * 2) % 10;
        leftd = (j * 2) / 10;
        sumx2 = sumx2 + rightd + leftd;

        // removing 2nd last digit
        ccnumber = ccnumber / 10;
    }
    // total sum
    totalsum = sumx2 + sumx1;
    return totalsum;
}

// Determing starting digits
int starting(long ccnumber)
{
    int f2digit = 0;
    while (ccnumber > 100)
    {
        f2digit = ccnumber / 10;
    }
    return f2digit;
}
