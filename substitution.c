// Encrypts user text by substituting alphabetical characters with the ones defined in key
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEYLEN 26

bool key_validation(string key);
char cipher_character(char letter, string key);

int main(int argc, string argv[])
{
    // Check if key is valid
    if (argc != 2)
    {
        printf("Usage: ./substitution KEY\n");
        return 1;
    }
    if (key_validation(argv[1]) == false)
    {
        return 1;
    }

    // Get text from the user
    string plaintext = get_string("plaintext:  ");

    // Cipher the text and print it out
    printf("ciphertext: ");
    for (int i = 0, length = strlen(plaintext); i < length; i++)
    {
        printf("%c", cipher_character(plaintext[i], argv[1]));
    }
    printf("\n");
    return 0;
}

// Check if key is valid
bool key_validation(string key)
{
    // Check key length is correct
    int length = strlen(key);
    if (length != KEYLEN)
    {
        printf("Key must contain %i characters.\n", KEYLEN);
        return false;
    }

    // Check if key contains non-alphabetical characters
    for (int i = 0; i < length; i++)
    {
        if (isalpha(key[i]) == 0)
        {
            printf("Key must only contain alphabetical characters.\n");
            return false;
        }
    }

    // Check if key contains repeated characters (case insensitive)
    char c;
    for (int i = 0; i < (length - 1); i++)
    {
        for (int j = i + 1; j < length; j++)
        {
            if (toupper(key[i]) == toupper(key[j]))
            {
                printf("Key must not contain repeated characters.\n");
                return false;
            }
        }
    }
    return true;
}

// Switch inputted characters according to key
char cipher_character(char letter, string key)
{
    // Check if the character is a letter
    if (isalpha(letter) == 0)
    {
        return letter;
    }

    // Check whether the character is lowercase or uppercase.
    // Then return switched character accordingly
    if (isupper(letter) != 0)
    {
        letter -= 'A';
        return toupper(key[(int) letter]);
    }
    else
    {
        letter -= 'a';
        return tolower(key[(int) letter]);
    }
}
