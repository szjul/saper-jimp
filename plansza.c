#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "plansza.h"

//x - ilosc kolumn
//y = ilosc wierszy

void inicjalizuj_plansze(plansza *p, int wymiar_x, int wymiar_y)
{
    p->k = wymiar_x;    //to sa kolumny
    p->w = wymiar_y;    //wiersze
    p->board = (char **)malloc((p->w) * sizeof(char*));
    for(int i = 0; i < (p->w); i++)
    {
        p->board[i] = (char *)malloc((p->k) * sizeof(char));
    }
}

void zwolnij_plansze(plansza *p)
{
    for(int i = 0; i < (p->w); i++)
    {
        free(p->board[i]);
    }
    free(p->board);
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
            if(p->board[cw][ck] != 'o' && p->board[cw][ck] != 'w' && p->board[cw][ck] != 'W')
            {
               if(isdigit(p->board[cw][ck])){
                p->board[cw][ck] += 1;
                }
                else
                p->board[cw][ck] = znak;
            }
            else if(p->board[cw][ck] == 'w' && znak == '_')
            {
                    p->board[cw][ck] = znak;
            }
        }
    }
}

void start_plansza(plansza *p, int podane_start_x, int podane_start_y, int ile_min)
{
    srand(time(NULL));
    int start_w = podane_start_y - 1;
    int start_k = podane_start_x - 1;

//wypelnienie planszy znakami '_' tj pustymi
    for(int i = 0; i < (p->w); i++)
    {
        for(int j = 0; j < (p->k); j++)
        {
            p->board[i][j] = '_';
        }
    }

    p->board[start_w][start_k] = 'W';
    zamiana_kolo_pktu(p, start_w, start_k, 'w');

//rozmieszczenie min i cyfr wokol nich na planszy
    for(int n = 0; n < ile_min; n++)
    {
        int mina_k, mina_w;
        do
        {
            mina_k = rand()%(p->k);
            mina_w = rand()%(p->w);
        }while(p->board[mina_w][mina_k] == 'o' || p->board[mina_w][mina_k] == 'w' || p->board[mina_w][mina_k] == 'W');

        p->board[mina_w][mina_k] = 'o';
        zamiana_kolo_pktu(p, mina_w, mina_k, '1');
    }
    //p->board[start_w][start_k] = '_';
    //zamiana_kolo_pktu(p, start_w, start_k, '_');
}


void wyswietl_plansze(plansza *p)
{
    //wiersz z numerami linii
    for(int i = 0; i <= (p->w); i++)
    {
        if(i == 0){
            printf("   ");
        }
        else
            printf("%3d ", i);
    }
    printf("\n");
    //wiersz z obramowaniem planszy
    for(int i = 0; i <= (p->w); i++)
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
            if(p->board[i][j] == 'W' || p->board[i][j] == 'w')
            {
                //p->board[i][j] = '_';
                //zamiana_kolo_pktu(p, i, j, '_');
                printf(" %c  ", p->board[i][j]);
            }
            else
                printf(" %c  ", p->board[i][j]);
                //printf(" \u2588  ");

        }
        printf("\n\n");
    }
}
