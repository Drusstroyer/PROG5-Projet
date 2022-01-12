#ifndef TABLE_RELOCATION_ELF_H
#define TABLE_RELOCATION_ELF_H
#include <stdio.h>
void table_relocation32(char *elf_start, unsigned int taille);
void table_relocation64(char *elf_start, unsigned int taille);
#endif