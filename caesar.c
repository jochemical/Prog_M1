#include <cs50.h>
#include <stdio.h>
#include <string.h> // bibliotheek voor functie strlen()
#include <ctype.h> // bibliotheek voor functie toupper()
#include <stdlib.h> // bib voor de functie atio

int main(int argc, string argv[])
{
    if (argc != 2) // Checkt of het aanroepen van de functie 2 argumenten bevat.
    {
        printf("Usage: ./caesar k");
        return 1; // Geeft exit code = 1. (Normaal eindigt deze op 0)
    }
    else
    {
        string k1 = argv[1]; // Maak een sring van het tweede argument
        int k2 = atoi(k1); // Zet de string k1 om in een integer.
        int k = k2 % 26; // key

        string t = get_string("plaintekst:");
        printf("ciphertext: ");
        int l = strlen(t);
        for (int i = 0; i < l; i++) // Deze loop doorloopt alle letter van de ingevoerde string.
        {
            if isupper(t[i]) // Als t[i] is hoofdletter
            {
                int tu_asc = t[i]; //Gezien dit een letter is, is deze integer te Ascii eenheid van de letter.
                int tu_alp = tu_asc - 65; // Normaliseert de letter A op rangorde 1
                int cu_alp = (tu_alp + k) % 26;
                int cu_asc = cu_alp + 65;
                char cipher_u = cu_asc; // Leest de integer als een Ascii eenheid en zet hem om in de bijbehorende character
                printf("%c", cipher_u);
            }
            else if islower(t[i]) // Als t[i] is kleine letter
            {
                int tl_asc = t[i]; //Gezien dit een letter is, is deze integer te Ascii eenheid van de letter.
                int tl_alp = tl_asc - 97; // Normaliseert de letter a op rangorde 1
                int cl_alp = (tl_alp + k) % 26;
                int cl_asc = cl_alp + 97;
                char cipher_l = cl_asc; // Leest de integer als een Ascii eenheid en zet hem om in de bijbehorende character
                printf("%c", cipher_l);
            }
            else
            {
                printf("%c", t[i]); // niet alfabetische characters verandert hij niet
            }
        }
    }
    printf("\n");
}



