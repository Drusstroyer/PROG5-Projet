#include "Affiche_section_elf.h"
#include <endian.h>
#include "converter.h"

void elf_print_section(const Elf32_Shdr *shdr, Elf32_Ehdr *ehdr){
    // for (int i=0; i < val; i++){
    //     printf("Section header:\n");
    //     printf("Numéro de la section:                                     %d\n",i);
    //     printf("Nom de la section:                                        0x%X\n",shdr[i].sh_name);
    //     printf("Taille de la section:                                     0x%X\n",shdr[i].sh_size);
            
    //     switch(shdr[i].sh_type){
    //         case SHT_PROGBITS: printf("Type: Section défini par le proramme\n");break;
    //         case SHT_SYMTAB: printf("Type: Section contient une table de symbole\n");break;
    //         case SHT_DYNSYM: printf("Type: Section contient une table de symbole\n");break;
    //         case SHT_STRTAB: printf("Type: section contient des chaîne de charactères\n");break;
    //         case SHT_RELA: printf("Type: section holds relocation entries\n");break;
    //         case SHT_HASH: printf("Type: section holds a symbol hash table\n");break;
    //         case SHT_DYNAMIC: printf("Type: section contient les informations de liaison dynamique\n");break;
    //         case SHT_NOTE: printf("Type: Section contient un marquage quelconque pour le fichier\n");break;
    //         case SHT_NOBITS: printf("Type: section défini par le programme mais n'est pas dans le fichier\n");break;
    //         case SHT_REL: printf("Type: section contient des entrées de repositionnement\n");break;
    //         case SHT_SHLIB: printf("Type: section est réservée et sa sémantique n'est pas définie.\n");break;
    //         case SHT_LOPROC: printf("Type: Section réservée jusqu'à la section SHT_HIPROC par le processeur\n");break;
    //         case SHT_HIPROC: printf("Type: Section réservée par le processeur depuis la section SHT_LOPROC\n");break;
    //         case SHT_LOUSER: printf("Cette valeur indique la borne inférieure de la plage des indices réservés aux programmes applicatifs.\n");break;
    //         case SHT_HIUSER: printf("Cette valeur indique la borne supérieure de la plage des indices réservés aux programmes applicatifs. Les types des sections entre SHT_LOUSER et SHT_HIUSER peuvent être utilisés par l'application, sans que cela entre en conflit avec les actuels ou futurs types de sections définis par le système\n");break;
    //         default: printf("Type: Section inactive\n");break;
    //     }

    //     printf("Attributs de la section : \n");
    //     switch(shdr[i].sh_flags){
    //         case 0x1: printf("Flag : SHF_WRITE, la section contient des données modifiables lors de l’exécution du programme\n");
    //             break;
    //         case 0x2: printf("Flag : SHF_ALLOC, la section fait partie de l’image mémoire du programme à exécuter\n");
    //             break;
    //         case 0x4: printf("Flag : SHF_EXECINSTR, la section contient du code exécutable \n");
    //             break;
    //         case 0xf0000000: printf("Flag: SHF_MASKPROC, Tous les bits contenus dans ce masque sont réservés à des sémantiques spécifiques au processeur\n");
    //             break;
    //     }
    
    //     printf("Position de la section par rapport au debut:              0x%X\n",shdr[i].sh_offset);

    // }
}