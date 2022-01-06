#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "entete_elf.h"
#include "Affiche_entete_elf.h"
#include "Affiche_section_elf.h"
#include "table_section_elf.h"
#include "converter.h"

Elf32_Ehdr* entete_elf(FILE * f){

    Elf32_Ehdr *ehdr = malloc(sizeof(Elf32_Ehdr));

    
    size_t n = fread(ehdr, 1, sizeof(Elf32_Ehdr), f);

    if (n != sizeof(Elf32_Ehdr)) {
		fprintf(stderr, "Impossible de lire le fichier\n");
		return NULL;
	}

    if (ehdr->e_ident[EI_MAG0] != ELFMAG0 ||
        ehdr->e_ident[EI_MAG1] != ELFMAG1 ||
        ehdr->e_ident[EI_MAG2] != ELFMAG2 ||
        ehdr->e_ident[EI_MAG3] != ELFMAG3
    ) {
        fprintf(stderr, "Mauvais format de fichier\n");
        return NULL;
    }

   /*if (ehdr->e_ident[EI_CLASS] != ELFCLASS32) {
		fprintf(stderr, "Pas en 32 bit ELF\n");
		return NULL;
	}

    if (ehdr->e_type != ET_NONE) {
		fprintf(stderr, "Pas de type de fichier défini\n");
		return NULL;
	}
    */
    return ehdr;

}



int main(int argc, char *argv[]){

    FILE *f = fopen(argv[1],"rb");

    assert(f != NULL);
    
    Elf32_Ehdr* header = entete_elf(f);

    assert(header != NULL);

    //Elf32_Shdr* sections = section_elf(f, header);

    //section_elf(f, header);
    //assert(sections != NULL);

    elf_print_HDR(header);

    //elf_print_section(sections, header);

    return 0;

}
