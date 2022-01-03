#include "entete_elf.h"

Elf32_Ehdr* entete_elf(FILE * f){

    Elf32_Ehdr *ehdr = NULL;

    fseek(f, 0, SEEK_SET);
    size_t n = fread(ehdr, 1, sizeof(*ehdr), f);

    if (n != sizeof(*ehdr)) {
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

    if (ehdr->e_ident[EI_CLASS] != ELFCLASS32) {
		fprintf(stderr, "Pas en 32 bit ELF\n");
		return NULL;
	}

    if (ehdr->e_type != ET_NONE) {
		fprintf(stderr, "Pas de type de fichier défini\n");
		return NULL;
	}

    return ehdr;

}