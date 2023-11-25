#include <cs50.h>
#include <stdio.h>
#include <math.h>


int main(void)
{
    float c = get_float("Change owed: "); // Vraagt om het invoeren van het bedrag (float)
    int d = round(c * 100); // vermenigdvuldigt met 100 om ermee te kunnen rekenen als integer.
    int quarters = 0; // hier de aantal munten (integer)
    int dimes = 0;
    int nickels = 0;
    int pennies = 0;
    int coins;
    quarters = (int)(d / 25); // checkt hoevaak de 25 in het bedrag past , decimalen worden geschrapt!
    d = d % 25; // Dit zorgt ervoor dat er wordt doorgerekend met het overgebleven bedrag
    dimes = (int)(d / 10);
    d = d % 10;
    nickels = (int)(d / 5);
    d = d % 5;
    pennies = (int)(d / 1);
    d = d % 1;
    coins = (quarters + dimes + nickels + pennies); // Optellen van het totaal aantal munten.
    printf("%i\n", coins);
}
