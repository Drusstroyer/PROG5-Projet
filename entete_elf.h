#ifndef _ENTETE_ELF_READ_
#define _ENTETE_ELF_READ_
#include <stdint.h>
#include <stdio.h>
#include <elf.h>

Elf32_Ehdr* entete_elf(FILE * f);

#endif