#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "plansza.h"
#include "obsluga.h"
#include "saper.h"


int main(int argc, char *argv[])
{
    	plansza p;
    	int opcja;
	char *sciezka_pliku = NULL;
	FILE* fp;
	int x, y;
	char znak;
	int wynik= 0;
	Gracz gracze[10];
	int mnoznik;
	StepResult wynik_ruchu;

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
		printf("Wczytywanie planszy z pliku %s\n", sciezka_pliku);
		if ((fp = fopen(sciezka_pliku, "r")))
		{
			gra_z_pliku(&p, sciezka_pliku);
			return 0;
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
			poziom = wybor_poziomu(bufor);

			switch(poziom)
			{
				case EASY_LEVEL:
					printf("Wybrano poziom latwy\n");
			    		inicjalizuj_plansze(&p, 9, 9, 10);
					mnoznik = 1;
				break;
				case MEDIUM_LEVEL:
					printf("Wybrano poziom sredni \n");
			    		inicjalizuj_plansze(&p, 16, 16, 30);
					mnoznik = 2;
				break;
				case HARD_LEVEL:
					printf("Wybrano poziom trudny \n");
					inicjalizuj_plansze(&p, 16, 30, 99);
					mnoznik = 3;
				break;
				case CUSTOM_LEVEL:
					printf("\nPodaj liczbe wierszy planszy: ");
	    				scanf("%d",&liczba_wierszy);
					printf("\nPodaj liczbe kolumn planszy: ");
                			scanf("%d",&liczba_kolumn);
					printf("\nPodaj liczbe min: ");
                			scanf("%d",&liczba_min);
    					inicjalizuj_plansze(&p, liczba_wierszy, liczba_kolumn, liczba_min);
					mnoznik = 1;
				break;
				default:
					printf("\nPodano zly poziom trudnosci. Prosze wpisac latwy, sredni, trudny lub custom\n");
				break;
			}
		}
	}
	do{
        printf("Podaj x pola, na ktorym chcesz zaczac, gdzie x nalezy do zakresu (1, %d): ", p.k);
        if(scanf("%d",&x)!=1)
        {
            printf("Niepoprawny parametr pola startowego\n");
            while (getchar() != '\n');
        }
        else if(x < 0 || x >= p.k)
        {
            printf("Podany parametr nie nalezy do planszy, sprobuj ponownie\n");
        }
        else
        {
            break;
        }
	}while(1);

	do{
        printf("Podaj y pola, na ktorym chcesz zaczac, gdzie y nalezy do zakresu (1, %d): ", p.w);
        if(scanf("%d",&y)!=1)
        {
            printf("Niepoprawny parametr pola startowego\n");
            while (getchar() != '\n');
        }
        else if(y < 0 || y >= p.w)
        {
            printf("Podany parametr nie nalezy do planszy, sprobuj ponownie\n");
        }
        else
        {
            break;
        }
	}while(1);


	printf("Generuje plansze na podanym poziomie trudnosci\n");
    start_plansza(&p,x,y);
	wyswietl_plansze(&p);
	printf("Plansza poczatkowa \n");

	do
	{
		printf("Podaj co chcesz zrobic f lub r i wspolrzedne x y: ");
		if(scanf(" %c%d%d",&znak, &x,&y)!=3)
		printf("Niepoprawne dane wejsciowe\n");
		wynik_ruchu = ruch(&p, znak, x, y);
		switch(wynik_ruchu)
		{
		case STEP_OK:
			wynik += mnoznik;
			wyswietl_plansze(&p);
			printf("\nTwoj wynik to %d\n", wynik);
			break;
		case STEP_INVALID_CMD:
			printf("Sprobuj ponownie\n");
			break;
		case STEP_BOMB_HIT:
			wyswietl_plansze(&p);
			printf("Koniec gry\n");
			break;
		case STEP_ALREADY_USED:
			break;
		default:
			break;
		}
	} while (wynik_ruchu != STEP_BOMB_HIT);
	zwolnij_plansze(&p);
	printf("Twoj koncowy wynik to %d\n", wynik);
	printf("Podaj swoje imie: ");
	scanf("%s",gracze[0].imie);
	gracze[0].wynik = wynik;
	zapisz_wyniki_do_pliku("wyniki.txt",gracze, 1);
	wyswietl_najlepszych_graczy("wyniki.txt");
}
