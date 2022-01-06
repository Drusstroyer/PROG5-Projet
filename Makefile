CC=gcc
CFLAGS=-Wall -g
progs=test test_symbole

all: $(progs)

test: Affiche_entete_elf.o entete_elf.o Affiche_section_elf.o table_section_elf.o converter.o
	$(CC) -o $@ $^ 

test_symbole: table_symbole.o Affiche_symbole.o
	$(CC) -o $@ $^

Affiche_entete_elf.o: Affiche_entete_elf.c Affiche_entete_elf.h
	$(CC) -c $(CFLAGS) $<

entete_elf.o : entete_elf.c entete_elf.h
	$(CC) -c $(CFLAGS) $<

Affiche_section_elf.o: Affiche_section_elf.c Affiche_section_elf.h
	$(CC) -c $(CFLAGS) $<

table_section_elf.o: table_section_elf.c table_section_elf.h
	$(CC) -c $(CFLAGS) $<

Affiche_symbole.o: Affiche_symbole.c Affiche_symbole.h
	$(CC) -c $(CFLAGS) $<

table_symbole.o: table_symbole.c table_symbole.h Affiche_symbole.h
	$(CC) -c $(CFLAGS) $<

converter.o: converter.c converter.h
	$(CC) -c $(CFLAGS) $<

clean: 
	rm -r $(progs) *.o *.txt