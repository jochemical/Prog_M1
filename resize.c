// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: resize-factor infile outfile\n");
        return 1;
    }

    // remember filenames and arguments
    char *t = argv[1]; //char t wordt hier gedefenieerd als pointer
    int n = *t - '0'; // Dit is de juiste manier om van een character een integer te maken
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // Size vastleggen voor de infile en outfile:
    int Width1 = bi.biWidth; // 1 staat voor de oude BMP-file
    int Width2 = bi.biWidth * n; // 2 staat voor de nieuwe BMP-file

    int Height1 = bi.biHeight;
    int Height2 = bi.biHeight * n;

    // De nieuwe en de oude padding berekenen:
    int padding1 = (4 - (Width1 * sizeof(RGBTRIPLE)) % 4) % 4; // De oude padding
    int padding2 = (4 - (Width2 * sizeof(RGBTRIPLE)) % 4) % 4; // De nieuwe padding

    // Updaten van de Headers
    bi.biWidth = bi.biWidth * n;
    bi.biHeight = bi.biHeight * n;
    bi.biSizeImage = abs(bi.biHeight) * (bi.biWidth * sizeof(RGBTRIPLE) + padding2); // Hiervoor moet je de hoeveelheid padding weten, dus voor bf.bfSize ook.
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER); // bf.bfSize is in bytes

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr); // Dit mag niet omhoog verplaatst, want padding verandert biSize en bfSize.

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // Hieronder worden de infile uitgelezen en resized, en de outfile geschreven
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(Height1); i < biHeight; i++) // Loop voor de hoeveelheid scanlines. LEt op dat dit de oude biheight is!
    {
        for (int u = 0; u < (n - 1); u++) // De code moet 'n' keer dezelfde regel schijven in de outputfile! De laatste keer wordt apart uitgevoerd.
        {
            // iterate over pixels in scanline
            for (int j = 0; j < Width1; j++) // Let op dat dit de oude biwidth is!
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile
                for (int x = 0; x < n; x++) // Deze loop schrijft iedere triple 'n' keer.
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }

            }

            // En nu de nieuwe padding toevoegen!
            for (int k = 0; k < padding2; k++)
            {
                fputc(0x00, outptr);
            }

            fseek(inptr, -((Width1 * sizeof(RGBTRIPLE)) ), SEEK_CUR); // Dit brengt de cursor terug naar het begin van de scanline
        }

        // Hieronder wordt de gescande regel nog een laatse keer geschreven:
        for (int p = 0; p < Width1; p++) // Dit moet de oude biwidth zijn!
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            for (int y = 0; y < n; y++)
            {
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr); // write RGB triple to outfile n times
            }
        }

        // En nu de nieuwe padding toevoegen!
        for (int g = 0; g < padding2; g++)
        {
            fputc(0x00, outptr);
        }

        // skip over padding, if any:
        fseek(inptr, padding1, SEEK_CUR); // Dit moet de oude padding zijn!
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
