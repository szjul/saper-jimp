#ifndef _OBSLUGA_H_IS_INCLUDED_
#define _OBSLUGA_H_IS_INCLUDED_

typedef struct 
{	
	char imie[50];
	int czas;
} Gracz;

void dodaj_gracza(Gracz gracze[], int *liczba_graczy, const char *imie, int czas);
void wyswietl_graczy(Gracz gracze[], int liczba_graczy);


#endif
