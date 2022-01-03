CC=gcc
CFLAGS=-Wall -g -Werror

test: Affiche_entete_elf.o entete_elf.o
	$(CC) -o $@ $^ test.c

Affiche_entete_elf.o: Affiche_entete_elf.c Affiche_entete_elf.h
	$(CC) $(CFLAGS) -c $<

entete_elf.o : entete_elf.c entete_elf.h
	$(CC) $(CFLAGS) -c $<