#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int b;
    do
    {
        b = get_int("Height: ");
    }
    while (b > 23 || b < 0); // Herhaalt de vraag voor input indien aan deze voorwaarde wordt voldaan.
    int i;
    int s;
    for (i = 1; i <= b; i++) // Loop voor het aantal kolommen
    {
        s = b - i; // variabele s voor het aantal spaties
        for (int k = 1; k <= s; k++) // loop voor het aantal spaties per rij
        {
            printf(" ");
        }
        for (int j = 0; j <= i; j++) // loop voor het aantal hekjes per rij
        {
            printf("#");
        }
        printf("\n");
    }
}