#ifndef _READ_SECTION_ELF_READ_
#define _READ_SECTION_ELF_READ_
#include <stdint.h>
#include <stdio.h>
#include <elf.h>


void read_section(FILE * f, Elf32_Ehdr *ehdr, char* m); 


#endif