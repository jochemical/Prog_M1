#include <cs50.h>
#include <stdio.h>
#include <string.h> // bibliotheek voor functie strlen()
#include <ctype.h> // bibliotheek voor functie toupper()

int main(void)
{
    string b = get_string();
    int l = strlen(b); // functie geeft lengte van b
    printf("%c", toupper(b[0]) ); // print eerste letter
    for(int i=0; i<l; i++) // loop om de voorletters van de overige namen te printen
        if(b[i]==' ') // if loop zoekt naar spaties
            printf("%c", toupper(b[i+1]) ); // %c staat voor character nodig voor letters
    printf("\n");
}