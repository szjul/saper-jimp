#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "obsluga.h"
#include "saper.h"

#define MAX_HIGHSCORE_ENTRIES 100

Level wybor_poziomu(char* bufor)
{
	if(strcmp(bufor,"latwy") == 0 )
	{
		return EASY_LEVEL;
        } else if(strcmp(bufor,"sredni") == 0)
        {
        	return MEDIUM_LEVEL;
       	} else if(strcmp(bufor, "trudny") == 0)
        {
		return HARD_LEVEL;
        } else if(strcmp(bufor, "custom") == 0)
        {
		return CUSTOM_LEVEL;
	}
	return UNKNOWN_LEVEL;
}

void zapisz_wyniki_do_pliku(const char* nazwa_pliku, Gracz* gracze, int liczba_graczy) 
{
	FILE *plik = fopen(nazwa_pliku, "a");
	if (plik == NULL)
	{
		printf("Nie mozna otworzyc pliku do zapisu.\n");
		return;
	}
	for (int i = 0; i < liczba_graczy; i++)
	{
		fprintf(plik, "%s %d\n", gracze[i].imie, gracze[i].wynik);
	}
	fclose(plik);
};

int porownaj_graczy(const void* a, const void* b)
{
	return ((Gracz*)b)->wynik - ((Gracz*)a)->wynik;
}

void wyswietl_najlepszych_graczy(const char* nazwa_pliku)
{
	FILE *plik = fopen(nazwa_pliku, "r");
	if (plik == NULL)
	{
		printf("Nie mozna otworzyc pliku do odczytu.\n");
		return;
	}

	Gracz gracze[MAX_HIGHSCORE_ENTRIES];
	int liczba_graczy = 0;

	while (fscanf(plik, "%s %d", gracze[liczba_graczy].imie, &gracze[liczba_graczy].wynik) != EOF)
	{
		liczba_graczy++;
		if (liczba_graczy>=MAX_HIGHSCORE_ENTRIES)
		{
			printf("Lista graczy pelna!\n:");
			break;
		}
	}

	fclose(plik);

	qsort(gracze, liczba_graczy, sizeof(Gracz), porownaj_graczy);
	printf("5 najlepszych graczy:\n");
	for (int i = 0; i < 5 && i < liczba_graczy; i++)
	{
		printf("%d. %s - %d\n", i + 1, gracze[i].imie, gracze[i].wynik);
	}
}
