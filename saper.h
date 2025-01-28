#ifndef SAPER_H
#define SAPER_H

typedef struct
{
        char imie[50];
        int wynik;
} Gracz;

typedef enum Result
{
	RESULT_OK,
	RESULT_ERROR
} Result;

#endif

