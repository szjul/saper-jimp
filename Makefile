saper: saper.c plansza.c obsluga.c
	cc -Wall -Wextra -ggdb -o saper saper.c plansza.c obsluga.c


test: sapertest.c 
	cc -Wall -Wextra -ggdb -o sapertest sapertest.c plansza.c obsluga.c

