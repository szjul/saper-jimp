#ifndef _PLANSZA_H_IS_INCLUDED_
#define _PLANSZA_H_IS_INCLUDED_

typedef struct _plansza{
    int w; //wiersze
    int k;  //kolumny
    char **board;
}plansza;

void inicjalizuj_plansze(plansza *p, int wymiar_x, int wymiar_y);
void zwolnij_plansze(plansza *p);
void start_plansza(plansza *p, int podane_start_x, int podane_start_y, int ile_min);
void wyswietl_plansze(plansza *p);
void zamiana_kolo_pktu(plansza *p, int w, int k, char znak);

#endif
