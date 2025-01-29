saper: saper.c plansza.c obsluga.c
	cc -Wall -Wextra -o saper saper.c plansza.c obsluga.c


test: sapertest.c
	cc -Wall -Wextra -ggdb -o sapertest sapertest.c plansza_test.c obsluga_test.c plansza.c obsluga.c

