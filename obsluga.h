#ifndef _OBSLUGA_H_IS_INCLUDED_
#define _OBSLUGA_H_IS_INCLUDED_
#include "saper.h"

typedef enum
{
        UNKNOWN_LEVEL,
        EASY_LEVEL,
        MEDIUM_LEVEL,
        HARD_LEVEL,
        CUSTOM_LEVEL
} Level;

void zapisz_wyniki_do_pliku(const char* nazwa_pliku, Gracz* gracze, int liczba_graczy);
int porownaj_graczy(const void* a, const void* b);
void wyswietl_najlepszych_graczy(const char* nazwa_pliku);
Level wybor_poziomu(char* poziom);


#endif
