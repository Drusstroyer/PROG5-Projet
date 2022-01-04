#include "Affiche_section_elf.h"

void elf_print_section(const Elf32_Shdr *shdr, Elf32_Ehdr *ehdr){
    for (int i=0; i < ehdr->e_shnum; i++){
        printf(
            "Section header:\n"
            "Numéro de la section:                                     0x%X\n"
            "Nom de la section:                                        0x%X\n"
            "Taille de la section:                                     0x%X\n"
            "Type de la section:                                       0x%X\n"
            "les informations d’allocation: JE SAIS PAS COMMENT ON AFFICHE CA"
            "Permissions:                                              0x%X\n"
            "Position de la section par rapport au debut:              0x%X\n",
            i, 
            shdr[i].sh_name, 
            shdr[i].sh_size,
            shdr[i].sh_type,
            shdr[i].sh_flags,
            shdr[i].sh_offset

        );
    }
}