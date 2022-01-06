#ifndef _TABLE_SECTION_ELF_READ_
#define _TABLE_SECTION_ELF_READ_
#include <stdint.h>
#include <stdio.h>
#include <elf.h>

void section_elf(FILE * f, Elf32_Ehdr *ehdr);
void find_type(char * sh, Elf32_Word n);

#endif