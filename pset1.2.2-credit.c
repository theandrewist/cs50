#include <cs50.h>
#include <stdio.h>
#include <math.h>

long question(void);
int getLastDigit(long number);
int getSumDigits(long number);
long removeLastDigit(long number);
int getChecksum(long number);
int getFirstDigits(long number);

int main(void)
{
    long number = question();
    int checksum = getChecksum(number);
    if (checksum == 0)
    {
        int firstDigits = getFirstDigits(number);
        int firstDigit = (firstDigits - (firstDigits % 10)) / 10;
        int noDigits = floor(log10(number)) + 1;
        if (firstDigits == 34 || firstDigits == 37)
            {
            if (noDigits == 15)
                {
                    printf("AMEX\n");
                }
            }
        else if (firstDigits == 51 || firstDigits == 52 || firstDigits == 53 || firstDigits == 54 || firstDigits == 55)
        {
            if (noDigits == 16)
            {
                printf("MASTERCARD\n");
            }
        }
        else if (firstDigit == 4)
        {
            if (noDigits == 13 || noDigits == 16)
            {
                printf("VISA\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}

long question(void)
{
    long number;
    do
    {
        number = get_long("What is your card number?: ");
    }
    while (number < 0);
    return number;
}

int getLastDigit(long number)
{
    int lastDigit = number % 10;
    return lastDigit;
}

int getSumDigits(long number)
{
    int zeroPlace, tensPlace, sumDigits;
    zeroPlace = number % 10;
    tensPlace = ((number - zeroPlace) / 10) % 10;
    sumDigits = zeroPlace + tensPlace;
    return sumDigits;
}

long removeLastDigit(long number)
{
    number = (number - getLastDigit(number)) / 10;
    return number;
}
int getChecksum(long number)
{
    int sum, checksum;
    sum = 0;
    do
    {
        sum += getLastDigit(number);
        number = removeLastDigit(number);
        sum += getSumDigits(getLastDigit(number) * 2);
        number = removeLastDigit(number);
    }
    while (number > 0);
    checksum = getLastDigit(sum);
    return checksum;
}
int getFirstDigits(long number)
{
    int noDigits, firstDigits;
    noDigits = floor(log10(number)) + 1;
    firstDigits = floor(number /  pow(10, (noDigits - 2)));
    return firstDigits;
}