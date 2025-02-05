#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "saper.h"
#include "obsluga.h"

void testuj_wybor_poziomu()
{
	assert(wybor_poziomu(NULL)==UNKNOWN_LEVEL);
	assert(wybor_poziomu("latwy")==EASY_LEVEL);
	assert(wybor_poziomu("sredni")==MEDIUM_LEVEL);
	assert(wybor_poziomu("trudny")==HARD_LEVEL);
	assert(wybor_poziomu("custom")==CUSTOM_LEVEL);
	assert(wybor_poziomu("inny")==UNKNOWN_LEVEL);
}


void testuj_zapisz_wyniki_do_pliku()
{
	Gracz gracze[] = { {"Ola", 15}, {"Kasia", 9}, {"Kuba", 2} };
	int liczba_graczy = 3;
	Gracz gracze_odcz[liczba_graczy];
	int nr_gracza = 0;
	const char* testowy_plik = "testowe_wyniki.txt";

	assert(zapisz_wyniki_do_pliku(NULL, gracze, liczba_graczy) == RESULT_ERROR);
	assert(zapisz_wyniki_do_pliku(NULL, NULL, liczba_graczy) == RESULT_ERROR);
	assert(zapisz_wyniki_do_pliku(testowy_plik, NULL, liczba_graczy) == RESULT_ERROR);
	assert(zapisz_wyniki_do_pliku(testowy_plik, gracze, liczba_graczy) == RESULT_OK);

	FILE * plik =fopen(testowy_plik, "r");
	assert(plik!=NULL);
	while (fscanf(plik, "%s %d", gracze_odcz[nr_gracza].imie, &gracze_odcz[nr_gracza].wynik) != EOF)
        {
                nr_gracza++;
		if (nr_gracza>=liczba_graczy)
			break;
        }
        fclose(plik);
	assert(liczba_graczy == nr_gracza);

	for(int i =0; i<liczba_graczy;i++)
	{
		assert(strcmp(gracze_odcz[i].imie,gracze[i].imie)==0);
		assert(gracze_odcz[i].wynik ==gracze[i].wynik);
	}

	zapisz_wyniki_do_pliku(testowy_plik, gracze, 0);
}

void testuj_wyswietl_najlepszych_graczy()
{
	Gracz gracze[] = { {"Ola", 6}, {"Kasia", 9}, {"Kuba", 7} };
        int liczba_graczy = 3;
        Gracz gracze_odcz[liczba_graczy];
        int nr_gracza = 0;
        const char* testowy_plik = "testowe_wyniki2.txt";
        const char* nieistniejacy_plik = "nieistniejace_wyniki2.txt";

        zapisz_wyniki_do_pliku(testowy_plik, gracze, liczba_graczy);

	assert(wyswietl_najlepszych_graczy(NULL)== RESULT_ERROR);
	assert(wyswietl_najlepszych_graczy(nieistniejacy_plik)== RESULT_ERROR);
	assert(wyswietl_najlepszych_graczy(testowy_plik)== RESULT_OK);
}
