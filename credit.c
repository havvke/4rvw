#include <cs50.h>
#include <stdio.h>

int checksum(long numb);
int check_length(long numb);
int check_start1(long numb);
int check_start2(long numb);

int main(void)
{
    // Prompt the user for credit card number
    long cnumber;
    do
    {
        cnumber = get_long("Number: ");
    }
    while (cnumber < 1);

    // Check the sum, if true, do other checks
    if (checksum(cnumber) == 0)
    {
        switch (check_length(cnumber))
        {
            case 13:
                // Check if starting number is 4 (Visa)
                if (check_start1(cnumber) == 4)
                {
                    printf("VISA\n");
                }
                else
                {
                    printf("INVALID\n");
                }
                break;
            case 15:
                // Check if starting numbers are 34 or 37 (Amex)
                if (check_start2(cnumber) == 34 || check_start2(cnumber) == 37)
                {
                    printf("AMEX\n");
                }
                else
                {
                    printf("INVALID\n");
                }
                break;
            case 16:
                // Check if starting numbers are 51 52 53 54 55 (MasterCard) or 4 (Visa)
                if (check_start1(cnumber) == 4)
                {
                    printf("VISA\n");
                }
                else if (check_start2(cnumber) >= 51 && check_start2(cnumber) <= 55)
                {
                    printf("MASTERCARD\n");
                }
                else
                {
                    printf("INVALID\n");
                }
                break;
            default:
                printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}

// Calculate the sum of the credit card numbers
int checksum(long numb)
{
    int sum = 0;
    while (numb > 0)
    {
        sum = sum + (numb % 10);
        numb = numb / 10;
        if ((numb % 10) * 2 >= 10)
        {
            sum = sum + (((numb % 10) * 2) % 10);
            sum = sum + (((numb % 10) * 2) / 10);
        }
        else
        {
            sum = sum + ((numb % 10) * 2);
        }
        numb = numb / 10;
    }
    return sum % 10;
}

// Return number length
int check_length(long numb)
{
    int length = 0;
    while (numb > 0)
    {
        length++;
        numb = numb / 10;
    }
    return length;
}

// Return the first number
int check_start1(long numb)
{
    while (numb > 10)
    {
        numb = numb / 10;
    }
    return numb;
}

// Return the first two numbers
int check_start2(long numb)
{
    while (numb > 100)
    {
        numb = numb / 10;
    }
    return numb;
}
