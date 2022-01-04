#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "table_section_elf.h"
#include "Affiche_section_elf.h"

Elf32_Shdr* section_elf(FILE * f, Elf32_Ehdr *ehdr){

    size_t tot = ehdr->e_shnum * ehdr->e_shentsize;

    Elf32_Shdr * shdr = malloc(tot);

    fseek(f, ehdr->e_shoff, SEEK_SET);

    size_t s = fread(shdr, 1, tot, f);

    if(s != tot) {
        fprintf(stderr, "Impossible Section Headers\n");
		free(shdr);
		return 0;
    }

    return shdr;

}
