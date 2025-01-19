#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "plansza.h"

int main()
{
    plansza p;
    inicjalizuj_plansze(&p, 9, 9);
    start_plansza(&p, 4, 4, 9);
    wyswietl_plansze(&p);
    zwolnij_plansze(&p);
}
