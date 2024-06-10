#include <stdio.h>
#include <stdlib.h>

#define SIZE 250

float myAtof(char *string, char *error);
int ctoi(char c);
int getLen(char *s);
float power(int number, int power);

int main()
{
    char string[SIZE]; // Array declaration.
    float fnum1;
    char errorState = 0;

    printf("Enter a number:\n");
    gets(string);

    fnum1 = myAtof(string, &errorState);

    if (errorState == 0)
    {
        printf("Your number is: %.2f \n", fnum1);
    }
    else if (errorState == 1)
    {
        printf("Error has been occurred due to inappropriate input!\n");
    }

    return 0;
}


float myAtof(char *string, char *error)
{
    float number = 0;
    int len = getLen(string);
    int decimalIdx = -1;
    int isNegative = 0;

    // removing the spaces from input
    for (int i = 0; i < len; i++)
    {
        if (string[i] == ' ')
        {
            for (int j = i; j < len; j++)
            {
                string[j] = string[j + 1];
            }
            len--;
            i--;
        }
    }

    if (string[0] == '-')
    {
        string[0] = '0';
        isNegative = 1;
    }

    for (int i = 0; i < len; i++)
    {
        int value = ctoi(string[i]);
        if (value == -1)
        {
            *error = 1;
            return -1;
        }

        if (value == 10)
        {
            decimalIdx = i;
        }
    }

    // printf("decimal index is %d \n", decimalIdx); // debug line

    if (decimalIdx == -1)
    {
        int pow = 0;
        for (int i = len - 1; i >= 0; i--)
        {
            number += ctoi(string[i]) * power(10, pow);
            pow++;
        }
    }
    else
    {
        int pow = 0;
        for (int i = decimalIdx - 1; i >= 0; i--)
        {
            number += ctoi(string[i]) * power(10, pow);
            pow++;
        }

        pow = -1;
        for (int i = decimalIdx + 1; i < len; i++)
        {
            number += ctoi(string[i]) * power(10, pow);
            pow--;
        }
    }

    if (isNegative)
    {
        return -1 * number;
    }
    else
    {
        return number;
    }
}

float power(int number, int power)
{
    float result = 1;
    int i;
    if (power >= 0)
    {
        for (i = 0; i < power; ++i)
        {
            result *= number;
        }
    }
    else
    {
        for (i = 0; i > power; --i)
        {
            result /= number;
        }
    }

    // printf("power calculation is %f\n", result); // debug line
    return result;
}

int getLen(char *s)
{
    int i = 0;
    while (s[i] != '\0')
    {
        i++;
    }
    return i;
}

int ctoi(char c)
{
    int value;
    switch (c)
    {
    case '.': // decimal point
        value = 10;
        break;
    default: 
        if (c >= '0' && c <= '9') {
            value = c - '0';
        } else {
            value = -1;
        }
    }

    return value;
}
