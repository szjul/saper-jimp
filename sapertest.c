#include <assert.h>
#include <stdio.h>
#include "saper.h"
#include "obsluga.h"
void testuj_poziom()
{
assert(wybor_poziomu(NULL)==UNKNOWN_LEVEL);
assert(wybor_poziomu("latwy")==EASY_LEVEL);
assert(wybor_poziomu("sredni")==MEDIUM_LEVEL);
assert(wybor_poziomu("trudny")==HARD_LEVEL);
assert(wybor_poziomu("custom")==CUSTOM_LEVEL);
assert(wybor_poziomu("inny")==UNKNOWN_LEVEL);

}


int main(int argc, char * argv[])
{

testuj_poziom();


printf("Testy wykonane poprawnie\n");
}

