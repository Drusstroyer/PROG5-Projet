#ifndef _SECTION_ELF_WRITE_
#define _SECTION_ELF_WRITE_
#include <stdint.h>
#include <stdio.h>
#include <elf.h>

void elf_print_section(const Elf32_Shdr *shdr, Elf32_Ehdr *ehdr);

#endif