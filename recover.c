// Recovers a memory card

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: infile\n");
        return 1;
    }

    unsigned char buffer[512]; // Dit is de struct, een lijst genaamd 'buffer' bestaande uit 512 unsigned characters
    char *infile = argv[1]; // Hier krijgt de invoerargument een naam(string) en die wordt gedefenieerd als char (dit wordt de geheugenkaart card.raw).

    // open input file
    FILE *inptr = fopen(infile, "r"); // open file om te lezen
    if (inptr == NULL) // inptr geeft NULL als de file niet geopend kan worden
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    FILE *img; //img is een file pointer
    char filename[7]; // 7 want 000.jpg bestaat uit 7 characters
    int g = - 1; // getal om nieuwe filename aan te maken
    int jpg = 0; // Number of JPG's
    int quit = 0; // End of Card boolean
    //int nf = 0; // Newfile Boolean
    while (quit == 0)
    {
        if(fread(buffer, 512, 1, inptr) == 0) // lengte van het te lezen element < 512 wanneer het einde van de memorycard is bereikt
        {
            quit = quit + 1; // Stop boolean om while loop te stoppen
        }

        else if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0)== 0xe0) // Voorwaarde om het begin van een nieuw JPG-bestand op te merken.
        {
            if (jpg == 0) // Als er nog geen nieuwe files zijn aangemaakt
            {
                g = g + 1; // Variabel om de nieuwe jpg bestanden een naam te geven: 000.jpg, 001.jpg, enz.
                sprintf(filename, "%03i.jpg", g); // Als hij een nieuw jpg-bestand tegenkomt maakt hij een nieuw jpg-bestand aan
                img = fopen(filename, "w");
                jpg = jpg + 1; // telt het aantal nieuw gemaakte jpg bestanden
            }
            else if (jpg > 0)
            {
                // Sluit het oude jpg bestand en maak een nieuwe aan:
                fclose(img); // close outfile
                g = g + 1;
                sprintf(filename, "%03i.jpg", g); // Als hij een nieuw jpg-bestand leest wordt er een nieuw file aangemaakt
                img = fopen(filename, "w");
                jpg = jpg + 1;
            }
        }
        if (jpg >= 1 && quit != 1)
        {
            fwrite(buffer, 512, 1, img); // Zolang er een nieuw jpg bestand is geopend en er op de memory card geen nieuw
            //begin wordt gevonden van een nieuw jpg bestand, blijf schrijven!
        }
    }
    fclose(inptr);
    fclose(img); // Het laatst aangemaakte jpg-bestand wordt gesloten
    return 0;
}
