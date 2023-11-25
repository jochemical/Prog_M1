// Helper functions for music

#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    float num = fraction[0] - '0'; // Door - '0' verkrijg je geen asci eenheid, maar de waarde aangegeven in de string
    float den = fraction[2] - '0';
    float deelsom = num / den;
    int acht = round(deelsom / (1.0 / 8.0)); // Rekent uit hoeveel achtste noten er in de deelsom zitten
    return acht;
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    int l = strlen(note);

    int toon;
    char accent = 'X'; // variabele voor testing
    int oct;

    if (l == 3)
    {
        toon = note[0] - 'A'; // toon is een character
        accent = note[1]; // accent is een string
        oct = note[2] - '0'; // oct is een integer
    }
    if (l == 2)
    {
        toon = note[0] - 'A';
        oct = note[1] - '0';
    }

    // Eerst stellen we de frequentie op het juiste octaaf (toon A!)
    int delta_oct = oct - 4;
    float freq = 440.0 * pow(2.0, delta_oct);

    // Vervolgens stellen we de frequentie op de juiste toon
    int toon_norm = toon; // toon geeft rangorde nummer van de toon (A=0, B=1, C=2, enz...)
    if (toon_norm == 0)
    {
        freq = freq * pow(2.0, 0.0 / 12.0); // De A wordt omhoog verschoven omdat het nieuwe octaaf pas bij C begint!
    }
    if (toon_norm == 1)
    {
        freq = freq * pow(2.0, 2.0 / 12.0);
    }
    if (toon_norm == 2)
    {
        freq = freq * pow(2.0, -9.0 / 12.0);
    }
    if (toon_norm == 3)
    {
        freq = freq * pow(2.0, -7.0 / 12.0);
    }
    if (toon_norm == 4)
    {
        freq = freq * pow(2.0, -5.0 / 12.0);
    }
    if (toon_norm == 5)
    {
        freq = freq * pow(2.0, -4.0 / 12.0);
    }
    if (toon_norm == 6)
    {
        freq = freq * pow(2.0, -2.0 / 12.0);
    }

    // Tenslotte the # en b accenten toevoegen, indien aanwezig:
    if (l == 3)
    {
        if (accent == '#')
        {
            freq = freq * pow(2.0, 1.0 / 12.0);
        }
        else
        {
            freq = freq * pow(2.0, -1.0 / 12.0);
        }
    }
    int freq2 = round(freq);
    return freq2; // Uitvoer van het programma
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    int ls = strlen(s);
    if (ls == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
