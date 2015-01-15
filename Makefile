# Makefile
#

SH = bash
CFLAGS = -g
LDFLAGS = -lm

all: main

main: chessgui.o chessmove.o chess_1player.o
	gcc $(LDFLAGS) $^ -o $@ `pkg-config --libs --cflags gtk+-2.0`

chess_1player.o: chess_1player.c chessmove.h
	gcc -c $(CFLAGS) $< -o $@

chessgui.o: chessgui.c chessmove.h
	gcc -c $(CFLAGS) $< -o $@ `pkg-config --libs --cflags gtk+-2.0`

chessmove.o: chessmove.c chessmove.h
	gcc -c $(CFLAGS) $< -o $@


.PHONY: clean lint test

clean:
	rm -rf *.o
	rm -rf main
