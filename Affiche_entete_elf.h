#ifndef _ENTETE_ELF_WRITE_
#define _ENTETE_ELF_WRITE_
#include <stdint.h>
#include <stdio.h>
#include <elf.h>

void elf_print_HDR(Elf32_Ehdr *ehdr);

#endif