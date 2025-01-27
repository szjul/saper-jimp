#include <assert.h>
#include <stdio.h>
#include "saper.h"
#include "obsluga.h"

void testuj_wybor_poziomu(void);
void testuj_gra_z_pliku(void);

int main(int argc, char * argv[])
{
	printf("Testuje: wybor_poziomu.\n");
	testuj_wybor_poziomu();
	printf("Testuje: gra_z_pliku.\n");
	testuj_gra_z_pliku();

	printf("Testy wykonane poprawnie\n");
}

