#include <cs50.h>
#include <stdio.h>

#define AMEX_LENGTH 15
#define VISA_LENGTH_13 13
#define VISA_LENGTH_16 16
#define MASTERCARD_LENGTH 16
#define AMEX_START1 34
#define AMEX_START2 37
#define VISA_START 4
#define MASTERCARD_START_MIN 51
#define MASTERCARD_START_MAX 55

int calculate_checksum(long number);
int get_card_length(long number);
int get_starting_digits(long number, int digit_count);
void determine_card_type(long number);

int main(void)
{
    long card_number;
    do {
        card_number = get_long("Number: ");
    } while (card_number < 1);

    if (calculate_checksum(card_number) != 0) {
        printf("INVALID\n");
        return 0;
    }
    determine_card_type(card_number);
    return 0;
}

void determine_card_type(long number)
{
    int length = get_card_length(number);
    int start1 = get_starting_digits(number, 1);
    int start2 = get_starting_digits(number, 2);

    if (length == AMEX_LENGTH && (start2 == AMEX_START1 || start2 == AMEX_START2)) {
        printf("AMEX\n");
    } else if (length == VISA_LENGTH_13 && start1 == VISA_START) {
        printf("VISA\n");
    } else if (length == VISA_LENGTH_16 && start1 == VISA_START) {
        printf("VISA\n");
    } else if (length == MASTERCARD_LENGTH && (start2 >= MASTERCARD_START_MIN && start2 <= MASTERCARD_START_MAX)) {
        printf("MASTERCARD\n");
    } else {
        printf("INVALID\n");
    }
}

int calculate_checksum(long number)
{
    int sum = 0, factor = 1;
    while (number > 0) {
        int digit = (number % 10) * factor;
        sum += (digit > 9) ? (digit % 10 + digit / 10) : digit;
        number /= 10;
        factor = (factor == 1) ? 2 : 1;
    }
    return sum % 10;
}

int get_card_length(long number)
{
    int length = 0;
    while (number > 0) {
        length++;
        number /= 10;
    }
    return length;
}

int get_starting_digits(long number, int digit_count)
{
    while (number > 1) {
        if (get_card_length(number) == digit_count) {
            // Break the while loop
            break;
        }
        // Nicer way of doing number = number / 10 (reasigns to the same variable)
        number /= 10;
    }
    return (int) number;
}
