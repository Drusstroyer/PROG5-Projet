CC=gcc
CFLAGS=-Wall -Werror

test: Affiche_entete_elf.o entete_elf.o Affiche_section_elf.o table_section_elf.o
	$(CC) -o $@ $^ 

Affiche_entete_elf.o: Affiche_entete_elf.c Affiche_entete_elf.h
	$(CC) -c $(CFLAGS) $<

entete_elf.o : entete_elf.c entete_elf.h
	$(CC) -c $(CFLAGS) $<

Affiche_section_elf.o: Affiche_section_elf.c Affiche_section_elf.h
	$(CC) -c $(CFLAGS) $<

table_section_elf.o: table_section_elf.c table_section_elf.h
	$(CC) -c $(CFLAGS) $<

