#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "plansza.h"
#include "obsluga.h"

typedef enum
{
	UNKNOWN_LEVEL,
	EASY_LEVEL,
	MEDIUM_LEVEL,
	HARD_LEVEL,
	CUSTOM_LEVEL
} Level;

int main(int argc, char *argv[])
{
    	plansza p;   
    	int opcja;
	char *sciezka_pliku = NULL;
	FILE* fp;
	int x, y;

	char bufor[10];
	Level poziom = UNKNOWN_LEVEL;

    	int liczba_wierszy, liczba_kolumn, liczba_min;

	while ((opcja = getopt(argc, argv, "f:")) != -1)
	{
		switch (opcja)
		{
			case 'f':
				sciezka_pliku = optarg; 
			break;
			case '?':
				printf("Nieznana opcja!\n");
				exit(1);
			break;
		}
	}

	if (sciezka_pliku)
	{
		printf("wczytywanie planszy z pliku %s\n", sciezka_pliku);
		if (fp = fopen(sciezka_pliku, "r"))
		{
// wczytywanie z pliku

		} else
		{
			printf("Nie udalo sie otworzyc pliku %s!\n", sciezka_pliku); 
			exit(1);
		}
	} else
	{
		while (poziom == UNKNOWN_LEVEL)
		{
    			printf("Wybierz poziom trudnosci - latwy, sredni, trudny lub custom: ");
			scanf("%s", bufor);
    			if(strcmp(bufor,"latwy") == 0 )
			{
				poziom = EASY_LEVEL;
				printf("Wybrano poziom latwy\n");
			    	inicjalizuj_plansze(&p, 9, 9);
				liczba_min = 9;
			} else if(strcmp(bufor,"sredni") == 0)
			{
				poziom = MEDIUM_LEVEL;
				printf("Wybrano poziom sredni \n");
			    	inicjalizuj_plansze(&p, 16, 16);
				liczba_min = 30;
			} else if(strcmp(bufor, "trudny") == 0)
			{
				poziom = HARD_LEVEL;
				printf("Wybrano poziom trudny \n");
				inicjalizuj_plansze(&p, 16, 30);
				liczba_min = 99;
 			} else if(strcmp(bufor, "custom") == 0) 
			{
				poziom = CUSTOM_LEVEL;
				printf("\nPodaj liczbe wierszy planszy: ");
	    			scanf("%d",&liczba_wierszy);
				printf("\nPodaj liczbe kolumn planszy: ");
                		scanf("%d",&liczba_kolumn);
				printf("\nPodaj liczbe wierszy planszy: ");
                		scanf("%d",&liczba_min);
    				inicjalizuj_plansze(&p, liczba_wierszy, liczba_kolumn);
			} else
			{
				printf("\nPodano zly poziom trudnosci. Prosze wpisac latwy, sredni, trudny lub custom\n");
			}	
		}
	}
	printf("Podaj x i y na ktorych chcesz zaczac: ");
        scanf("%d %d",&x, &y);
	start_plansza(&p,x,y,liczba_min);
	printf("Generuje plansze na podanym poziomie trudnosci\n");	
	wyswietl_plansze(&p);
	printf("Plansza poczatkowa. Podaj co chcesz zrobic dalej: \n");
	
	//funkcja do kolejnych ruchow

	zwolnij_plansze(&p);

}
