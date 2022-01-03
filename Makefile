CC=gcc
CFLAGS=-Wall -Werror

test: Affiche_entete_elf.o entete_elf.o
	$(CC) -o $@ $^ 

Affiche_entete_elf.o: Affiche_entete_elf.c Affiche_entete_elf.h
	$(CC) -c $(CFLAGS) $<

entete_elf.o : entete_elf.c entete_elf.h
	$(CC) -c $(CFLAGS) $<

