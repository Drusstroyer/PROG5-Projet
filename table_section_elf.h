#ifndef _TABLE_SECTION_ELF_READ_
#define _TABLE_SECTION_ELF_READ_
#include <stdint.h>
#include <stdio.h>
#include <elf.h>

void section_elf(FILE * f, Elf32_Ehdr *ehdr);

//Fonction permettant de trouver tous les flags d'une section
void get_flags(char *flag, int val);

//Fonction permettant d'inverser une chaîne de caractère (pour afficher les flags dans l'ordre)
void reverse_str(char *str);

#endif