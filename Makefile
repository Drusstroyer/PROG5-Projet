CC=gcc
CFLAGS=-Wall -g
progs=read_elf renum

all: $(progs)

read_elf: Affiche_entete_elf.o entete_elf.o table_section_elf.o converter.o read_section_elf.o table_symbole.o table_relocation_elf.o 
	$(CC) -o $@ $^ 

renum : renumerotation.o
	$(CC) -o $@ $^

Affiche_entete_elf.o: Affiche_entete_elf.c Affiche_entete_elf.h
	$(CC) -c $(CFLAGS) $<

entete_elf.o : entete_elf.c entete_elf.h
	$(CC) -c $(CFLAGS) $<

table_section_elf.o: table_section_elf.c table_section_elf.h
	$(CC) -c $(CFLAGS) $<

table_symbole.o: table_symbole.c table_symbole.h
	$(CC) -c $(CFLAGS) $<

read_section_elf.o: read_section_elf.c read_section_elf.h
	$(CC) -c $(CFLAGS) $<

converter.o: converter.c converter.h
	$(CC) -c $(CFLAGS) $<
	
table_relocation_elf.o: table_relocation_elf.c table_relocation_elf.h
	$(CC) -c $(CFLAGS) $<

renumerotation.o : renumerotation.c renumerotation.h
	$(CC) -c $(CFLAGS) $<

clean: 
	rm -r -f $(progs) *.o *.txt