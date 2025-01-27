#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "plansza.h"

//x - ilosc kolumn
//y = ilosc wierszy
//stan - zakryte(0), odkryte(1)

void inicjalizuj_plansze(plansza *p, int wymiar_x, int wymiar_y)
{
    p->k = wymiar_x;    //to sa kolumny
    p->w = wymiar_y;    //wiersze
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
            if(p->board[cw][ck] == 'w')
            {
                if(isdigit(p->board[cw][ck]));
                else
                {
                    p->board[cw][ck] = znak;
                }
            }

            else if(znak == '_' && isdigit(p->board[cw][ck]));

            else if(p->board[cw][ck] != 'o')
            {
               if(isdigit(p->board[cw][ck])){
                p->board[cw][ck] += 1;
                }
                else
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
            p->stan[i][j] = 0; //zakryte
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
        }while(p->board[mina_w][mina_k] == 'o' || p->board[mina_w][mina_k] == 'w'
               || p->board[mina_w][mina_k] == 'W'|| isdigit(p->board[mina_w][mina_k]));

        p->board[mina_w][mina_k] = 'o';
        zamiana_kolo_pktu(p, mina_w, mina_k, '1');
    }
    p->board[start_w][start_k] = '_';
    zamiana_kolo_pktu(p, start_w, start_k, '_');

    stan_kolo_pktu(p, start_w, start_k);


}

int ruch(plansza *p, char co, int x, int y) //zwraca 0 jesli ok, 1 jesli ruch to nie 'r' ani 'f', 2 jesli trafi na mine
{
    //printf("ruch\n");
    x--;
    y--;
    if(co != 'r' && co != 'f')
    {
        printf("zly ruch\n");
        return 1;
    }
    else if(co == 'r')
    {
        //printf("zaczynam (r)\n");
        p->stan[y][x] = 1;
        if(p->board[y][x] == '_')
            stan_kolo_pktu(p, y, x);
        else if(p->board[y][x] =='o')
        {
            printf("trafiles na mine, przegrywasz:(\n");
            return 2;
        }
    }
    else
    {
        //printf("zaczynam (f)\n");
        if(p->stan[y][x] == 0 || p->stan[y][x] == 1) //jesli zakryte (albo odkryte daje te opcje)
            p->stan[y][x] = 2;
        else if(p->stan[y][x] == 2)
            p->board[y][x] = 1;
    }
    return 0;
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
