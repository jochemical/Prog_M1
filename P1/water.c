#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int i = get_int("Minutes: ");
    int b = 12*i;
    printf("Bottle: %i\n", b);
}