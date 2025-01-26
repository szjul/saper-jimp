#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "obsluga.h"


void wybor_poziomu()
{

}


void dodaj_gracza(Gracz gracze[], int *liczba_graczy, const char *imie, int czas) {
	if (*liczba_graczy < 5)
	{
	strncpy(gracze[*liczba_graczy].imie, imie, sizeof(gracze[*liczba_graczy].imie) - 1);
	gracze[*liczba_graczy].czas = czas;
	(*liczba_graczy)++;
	}	
	else 
	{
		printf("Brak miejsca na nowych graczy!\n");
	}
}

void wyswietl_graczy(Gracz gracze[], int liczba_graczy) {
	printf("\nNajlepsi gracze:\n");
	for (int i = 0; i < liczba_graczy; i++)
	{
		printf("%d. %s - %d sekund\n", i + 1, gracze[i].imie, gracze[i].czas);
	}
}
