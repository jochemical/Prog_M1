#include <cs50.h>
#include <stdio.h>
#include <string.h> // bibliotheek voor functie strlen()
#include <ctype.h> // bibliotheek voor functie toupper()
#include <stdlib.h> // bib voor de functie atio

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./vigenere k\n");
        return 1; // Geeft exit code = 1. (Normaal eindigt deze op 0)
    }
    else
    {
        string key = argv[1]; // defenieer keyword

        // Keyword omschrijven naar kleine letters:
        int l_key = strlen(key); // lengte van de te coderen tekst te gebruiken voor de loop
        for (int k = 0; k < l_key; k++)
        {
            if isupper(key[k])
            {
                int hl_asci = key[k];
                int kl_asci = hl_asci + 32;
                char kl = kl_asci;
                key[k] = kl;
            }
            else if islower(key[k])
            {

            }
            else
            {
                printf("Usage: Alphabetical keyword\n");
                return 1; // Programma exit code bij verkeerd gebruik
            }
        }



        string t = get_string("plaintekst:"); // aanvraag van de te coderen tekst
        int l = strlen(t); // lengte van de te coderen tekst te gebruiken voor de loop

        // Hieronder volgt de transitie naar code tekst:
        printf("ciphertext: ");
        int j = 0; // teller voor het keyword
        for (int i = 0; i < l; i++)
        {
            int key_asc = key[j];
            int key_alp = key_asc - 97;
            if isupper(t[i]) // Voor hoofdletters
            {
                int tu_asc = t[i];

                int tu_alp = tu_asc - 65;
                int cu_alp = (tu_alp + key_alp) % 26;
                int cu_asc = cu_alp + 65;

                char cipher_u = cu_asc;
                printf("%c", cipher_u);

                j = (j + 1) % l_key; // cyclische verschuiving van de letter uit het keyword
            }
            else if islower(t[i]) // Voor kleine letters
            {
                int tl_asc = t[i];

                int tl_alp = tl_asc - 97;
                int cl_alp = (tl_alp + key_alp) % 26;
                int cl_asc = cl_alp + 97;

                char cipher_l = cl_asc;
                printf("%c", cipher_l);

                j = (j + 1) % l_key; // cyclische verschuiving van de letter uit het keyword
            }
            else
            {
                printf("%c", t[i]); // niet alfabetische characters verandert hij niet
            }
        }
    }
    printf("\n");
}



