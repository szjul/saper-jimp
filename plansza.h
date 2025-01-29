#ifndef _PLANSZA_H_IS_INCLUDED_
#define _PLANSZA_H_IS_INCLUDED_

#include "saper.h"

typedef struct _plansza{
    int w; //wiersze
    int k;  //kolumny
    int ile_min;
    char **board;
    int **stan; //zakryte (0), odkryte (1), flaga(2)
}plansza;

typedef enum StepResult
{
	STEP_OK,
	STEP_INVALID_CMD,
	STEP_BOMB_HIT,
	STEP_ALREADY_USED,
	STEP_FLAG_1,
	STEP_FLAG_2

} StepResult;

void inicjalizuj_plansze(plansza *p, int wymiar_x, int wymiar_y, int ile_min);
void zwolnij_plansze(plansza *p);
void start_plansza(plansza *p, int podane_start_x, int podane_start_y);
void wyswietl_plansze(plansza *p);
int sprawdzenie_czy_wygrana(plansza *p);
void zamiana_kolo_pktu(plansza *p, int w, int k, char znak);
StepResult ruch(plansza *p, char co, int x, int y);
StepResult gra_z_pliku(plansza *p, const char *sciezka);

#endif
