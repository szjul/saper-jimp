#include <assert.h>
#include <stdio.h>
#include "saper.h"
#include "obsluga.h"

void testuj_wybor_poziomu(void);
void testuj_gra_z_pliku(void);
void testuj_zapisz_wyniki_do_pliku();
void testuj_wyswietl_najlepszych_graczy();

int main(int argc, char * argv[])
{
	printf("Testuje: wybor_poziomu.\n");
	testuj_wybor_poziomu();
	printf("Testuje: gra_z_pliku.\n");
	testuj_gra_z_pliku();
	printf("Testuje: zapisz_wyniki_do_pliku.\n");
	testuj_zapisz_wyniki_do_pliku();
	printf("Testuje: wyswietl_najlepszych_graczy.\n");
	testuj_wyswietl_najlepszych_graczy();

	printf("Testy wykonane poprawnie\n");
}

