#include <assert.h>
#include <stdio.h>
#include "saper.h"
#include "plansza.h"

void testuj_gra_z_pliku()
{
	plansza p;
	StepResult result;
	
	assert(gra_z_pliku(NULL, NULL)==STEP_INVALID_CMD);
	assert(gra_z_pliku(NULL, "zlasciezka")==STEP_INVALID_CMD);
	assert(gra_z_pliku(NULL, "rozgrywka")==STEP_INVALID_CMD);
	assert(gra_z_pliku(&p, NULL)==STEP_INVALID_CMD);
	assert(gra_z_pliku(&p, "zlasciezka")==STEP_INVALID_CMD);
	result = gra_z_pliku(&p, "rozgrywka");
	assert ((result==STEP_BOMB_HIT) || (result == STEP_OK) || (result == STEP_ALREADY_USED));
}
