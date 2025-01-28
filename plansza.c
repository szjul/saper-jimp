#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "saper.h"
#include "plansza.h"
#include "obsluga.h"


//x - ilosc kolumn
//y = ilosc wierszy
//stan - zakryte(0), odkryte(1), flaga(2), startowe(3)

void inicjalizuj_plansze(plansza *p, int wymiar_x, int wymiar_y, int ile_min)
{
    p->k = wymiar_x;      // to sa kolumny
    p->w = wymiar_y;      // wiersze
    p->ile_min = ile_min; // liczba min
    p->board = (char **)malloc((p->w) * sizeof(char*));
    p->stan = malloc((p->w) * sizeof(int*));
    for(int i = 0; i < (p->w); i++)
    {
        p->board[i] = (char *)malloc((p->k) * sizeof(char));
        p->stan[i] = malloc((p->k)* sizeof(int));
    }
}

void zwolnij_plansze(plansza *p)
{
    for(int i = 0; i < (p->w); i++)
    {
        free(p->board[i]);
        free(p->stan[i]);
    }
    free(p->board);
    free(p->stan);
}

void stan_kolo_pktu(plansza *p, int w, int k)
{
    if (w < 0 || w >= p->w || k < 0 || k >= p->k)
        return;

    if (p->board[w][k] != '_' && !isdigit(p->board[w][k]))
        return;

    if (p->stan[w][k] == 1)
        return;

    if (isdigit(p->board[w][k]))
    {
        p->stan[w][k] = 1;
        return;
    }
    p->stan[w][k] = 1;


    int dw[8] = {0, 1, 1, 1, 0, -1, -1, -1};
    int dk[8] = {-1, -1, 0, 1, 1, 1, 0, -1};

    for (int i = 0; i < 8; i++)
    {
        int cw = w + dw[i];
        int ck = k + dk[i];
        stan_kolo_pktu(p, cw, ck);
    }
}

void zamiana_kolo_pktu(plansza *p, int w, int k, char znak) //(w, k) = (y, x)
{
    int dw[8] = {0, 1, 1, 1, 0, -1, -1, -1};
    int dk[8] = {-1, -1, 0, 1, 1, 1, 0, -1};

    for(int i = 0; i < 8; i++)
    {
        int cw = w + dw[i]; //cale wiersze
        int ck = k + dk[i]; //cale kolumny
        if(cw >= 0 && cw < (p->w) && ck >= 0 && ck < (p->k) )
        {
            if(p->stan[w][k] == 3)
            {
                p->stan[cw][ck] = 3;
            }

            if(p->board[cw][ck] != 'o')
            {
                if(isdigit(p->board[cw][ck])){
                    p->board[cw][ck] += 1;
                }
                else
                {
                    p->board[cw][ck] = znak;
                }
            }
        }
    }
}

void start_plansza(plansza *p, int podane_start_x, int podane_start_y)
{
    srand(time(NULL));
    int start_w = podane_start_y - 1;
    int start_k = podane_start_x - 1;

//wypelnienie planszy znakami '_' tj pustymi
    for (int i = 0; i < (p->w); i++)
    {
        for(int j = 0; j < (p->k); j++)
        {
            p->board[i][j] = '_';
            p->stan[i][j] = 0; //zakryte
        }
    }

    p->stan[start_w][start_k] = 3;
    zamiana_kolo_pktu(p, start_w, start_k, '_');

//rozmieszczenie min i cyfr wokol nich na planszy
    for (int n = 0; n < p->ile_min; n++)
    {
        int mina_k, mina_w;
        do
        {
            mina_k = rand()%(p->k);
            mina_w = rand()%(p->w);
        }while((p->board[mina_w][mina_k] == 'o' || p->stan[mina_w][mina_k] == 3));

        p->board[mina_w][mina_k] = 'o';
        zamiana_kolo_pktu(p, mina_w, mina_k, '1');
    }
    stan_kolo_pktu(p, start_w, start_k);
}

StepResult ruch(plansza *p, char co, int x, int y) //zwraca 0 jesli ok, 1 jesli ruch to nie 'r' ani 'f', 2 jesli trafi na mine
{
    x--;
    y--;
    if( x<0 || x>p->k || y<0 || y>p->w)
    {
	printf("Podane wspolrzedne sa poza granicami planszy\n");
	return STEP_INVALID_CMD;
    }

    if(co != 'r' && co != 'f')
    {
        printf("Zly ruch\n");
        return STEP_INVALID_CMD;
    }

    if(co == 'r')
    {
	    if(p->stan[y][x]== 1)
	    {
	    	printf("Podane pole jest juz odkryte\n");
	    	return STEP_ALREADY_USED;
	    }

        if(p->board[y][x] == '_')
            stan_kolo_pktu(p, y, x);
        p->stan[y][x] = 1;

        if(p->board[y][x] =='o')
        {
            printf("Trafiles na mine, przegrywasz:(\n");
            return STEP_BOMB_HIT;
        }
    }
    if(co == 'f')
    {
        if(p->stan[y][x] == 0)
            p->stan[y][x] = 2;
        else if(p->stan[y][x] == 1)
        {
            printf("Podane pole jest juz odkryte\n");
            return STEP_ALREADY_USED;
        }
        else if(p->stan[y][x] == 2)
            p->stan[y][x] = 0;
    }
    return STEP_OK;
}

void wyswietl_plansze(plansza *p)
{
    //wiersz z numerami linii
    for(int i = 0; i <= (p->k); i++)
    {
        if(i == 0){
            printf("   ");
        }
        else
            printf("%3d ", i);
    }
    printf("\n");
    //wiersz z obramowaniem planszy
    for(int i = 0; i <= (p->k); i++)
    {
        if(i == 0){
            printf("   ");
        }
        else
            printf("----");
    }
    printf("\n");

    //sam print
    for(int i = 0; i < (p->w); i++)
    {
        printf("%3d|", i+1);
        for(int j = 0; j < (p->k); j++)
        {
            if(p->stan[i][j] == 1) //odkryte
                printf(" %c  ", p->board[i][j]);
            else if(p->stan[i][j] == 2) //flaga
                printf(" X  ");
            else
                printf(" \u2588  "); //zakryte
        }
        printf("\n\n");
    }
}

StepResult gra_z_pliku(plansza *p, const char *sciezka)
{
	int x, y, wymiar_x, wymiar_y, ile_min;
	char znak;
	char bufor[10];
	StepResult krok = STEP_OK;
	int poprawne_kroki = 0, wynik = 0;
	FILE* plik;
	Level poziom = UNKNOWN_LEVEL;
	int mnoznik = 0;

	if (p!= NULL && sciezka!=NULL)
	{
		plik = fopen(sciezka, "r");
		if (plik != NULL)
		{
			fscanf(plik,"%s", bufor);
			poziom = wybor_poziomu(bufor);
			printf("poziom gry %s - %d\n", bufor, poziom);
			fscanf(plik, "%d %d %d", &wymiar_x, &wymiar_y, &ile_min);
			printf("rozmiar planszy x = %d, y = %d, liczba min = %d\n", wymiar_x ,wymiar_y, ile_min);
			switch (poziom)
        		{
        	   		case EASY_LEVEL:
        	                        mnoznik = 1;
        	                        break;
				case MEDIUM_LEVEL:
        	                        mnoznik = 2;
        	                        break;
        		                case HARD_LEVEL:
               				mnoznik = 3;
					break;
				case CUSTOM_LEVEL:
					mnoznik = 1;
					break;
				default:
				break;
			}
			inicjalizuj_plansze(p, wymiar_x,wymiar_y, ile_min);
			fscanf(plik,"%d %d", &x, &y);
			printf("Miejsce startu: x = %d,y = %d\n", x ,y);
            start_plansza(p,x,y);
			while (krok == STEP_OK || krok == STEP_ALREADY_USED)
			{
				if (fscanf(plik, " %c %d %d", &znak, &x, &y)== EOF)
				{
					printf("Koniec danych z pliku!\n");
					break;
				}
				printf("Komenda %c, x = %d, y = %d\n", znak, x ,y);
				krok = ruch(p,znak,x,y);
				switch (krok)
				{
					case STEP_OK:
						poprawne_kroki++;
						wynik+=mnoznik;
					break;
					case STEP_INVALID_CMD:
						printf("Niepoprawna opcja\n");
						fclose(plik);
						return krok;
					break;
					case STEP_BOMB_HIT:
						printf("przegrana!\n");
						fclose(plik);
						return krok;
					break;
					case STEP_ALREADY_USED:
					break;
					default:
					break;
				}
			}
			fclose(plik);

			printf("Liczba poprawnych krokow: %d\n", poprawne_kroki);
        		printf("Liczba punktow: %d\n", wynik);
			printf("Wygrana!\n");
			return krok;
		}
	}
	return STEP_INVALID_CMD;
}
