// Helper functions

#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "helpers.h"

// Returns true if value is in array of n values, else false
bool search(int value, int values[], int n)
{

    if (n == 1) // check of de lijst uit 1 waarde bestaat (dan is een simpelere check mogelijk)
    {
        if (values[0] == value)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    int c = (n - 1) / 2; // Getal behordend bij de helft van de lijst (afgerond naar beneden, de 'check value')
    int hl = round( ( (float)(n-1) ) / 2); // halflenght: halve lengte van de overgebleven lijst

    int stop = 0; // variabele om de while loop te stoppen nadat hl op 1 is gesteld
    while (stop != 2)
    {

        if (hl == 1.0) // if statement om de while loop te stoppen de tweede keer nadat hl op 1 is gesteld
        {
            stop = stop + 1;
        }

        hl = round( ( (float) hl ) / 2); // De lengte van de nieuwe sublijst gehalveerd, afronden naar boven! (Zet dit overigens niet voor het if statement hierboven)

        if (value > values[c])
        {
            c = c + hl; // Verhoogd de checkvalue met een grootte van de helft van de overgebleven lijst
        }
        else if (value < values[c])
        {
            c = c - hl;
        }
        else if (value == values[c]) // Als de waarde in de lijst is gevonden returnt de functie true.
        {
            return true;
        }

    }
    return false; // Als de waarde binnen de while loop niet is gevonden
}

// Sorts array of n values (bubble technique)
void sort(int values[], int n)
{
    int temp; // tijdelijke opslag variabele om waarden te kunnen verwisselen.
    int s = 1; // teller die de hoeveelheid switches bij houd.
    while (s != 0)
    {
        s = 0;
        for (int q = 0; q < (n - 1); q++)
        {
            if (values[q] > values[q + 1])
            {
                temp = values[q];
                values[q] = values[q + 1];
                values[q + 1] = temp;
                s = s + 1;
            }
        }

    }

    return; // returnt de lijst 'values[]'' maar dan gerangschikt op grootte
}
