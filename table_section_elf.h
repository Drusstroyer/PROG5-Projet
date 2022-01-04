#ifndef _TABLE_SECTION_ELF_READ_
#define _TABLE_SECTION_ELF_READ_
#include <stdint.h>
#include <stdio.h>
#include <elf.h>

Elf32_Shdr* section_elf(FILE * f,  Elf32_Ehdr *ehdr);

#endif