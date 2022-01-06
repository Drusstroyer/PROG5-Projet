#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "table_section_elf.h"
#include "Affiche_section_elf.h"
#include "converter.h"

//Elf32_Shdr* section_elf(FILE * f, Elf32_Ehdr *ehdr){

    //size_t tot = ehdr->e_shnum * ehdr->e_shentsize;
    /*
    Elf32_Shdr * shdr = malloc(sizeof(Elf32_Shdr*));

    fseek(f, ehdr->e_shoff, SEEK_SET);

    size_t s = fread(shdr, 1, tot, f);*/
    // Elf32_Shdr * shdr = malloc(sizeof(Elf32_Shdr));
    // char * section=NULL; 
    // fread(ehdr, 1, sizeof(*ehdr), f);
    // fseek(f,ehdr->e_shoff + ehdr->e_shstrndx * ehdr->e_shentsize, SEEK_SET);
    // fread(shdr,1,sizeof(*shdr),f);
    // section = malloc(shdr->sh_size);
    // fseek(f,shdr->sh_offset,SEEK_SET);
    // fread(section,1,shdr->sh_size,f);
    // printf("Il y a %d sections headers, commençant à l'offset 0x%x:\n\n",ehdr->e_shnum,ehdr->e_shoff);
    /*for(int i=0;i<ehdr->e_shnum;i++){
        char * section_name="";
        fseek(f,ehdr->e_shoff + i * sizeof(*shdr), SEEK_SET);
        fread(shdr,1,sizeof(*shdr),f);
        //section_name = (char*)(section + shdr->sh_name);
        //memcpy(section_name, (char*)&shdr->sh_name,sizeof(Elf32_Word));//traduire le unsigned int en char* 
        printf("[%2d] %s %0x %0x\n",i,section_name,shdr->sh_addr,shdr->sh_offset);
    }*/
    /*
    if(s != tot) {
        fprintf(stderr, "Impossible Section Headers\n");
		free(shdr);
		return 0;
    }
    */
    //return shdr;

// }

void find_type(char * sh, Elf32_Word n){
    switch(n){
            case SHT_PROGBITS: strcpy(sh, "PROGBITS");break;
            case SHT_SYMTAB: strcpy(sh, "SYMTAB");break;
            case SHT_DYNSYM: strcpy(sh, "DYNSYM");break;
            case SHT_STRTAB: strcpy(sh, "STRTAB");break;
            case SHT_RELA: strcpy(sh, "RELA");break;
            case SHT_HASH: strcpy(sh, "HASH");break;
            case SHT_DYNAMIC: strcpy(sh, "DYNAMIC");break;
            case SHT_NOTE: strcpy(sh, "NOTE");break;
            case SHT_NOBITS: strcpy(sh, "NOBITS");break;
            case SHT_REL: strcpy(sh, "REL");break;
            case SHT_SHLIB: strcpy(sh, "SHLIB");break;
            case SHT_LOPROC: strcpy(sh, "LOPROC");break;
            case SHT_HIPROC: strcpy(sh, "HIPROC");break;
            case SHT_LOUSER: strcpy(sh, "LOUSER");break;
            case SHT_HIUSER: strcpy(sh, "HIUSER");break;
            default: strcpy(sh, "NULL");break;
        }
}

void section_elf(FILE * f, Elf32_Ehdr *ehdr){

    Elf32_Shdr *shdr = malloc(sizeof(Elf32_Shdr));
    char* SectNames = NULL;
    char sh_type[30] = "";
    
    fread(ehdr, 1, sizeof(ehdr), f);

    fseek(f, ehdr->e_shoff + ehdr->e_shstrndx * sizeof(shdr), SEEK_SET);
    fread(shdr, 1, sizeof(shdr), f);

    SectNames = malloc(shdr->sh_size);
    fseek(f, shdr->sh_offset, SEEK_SET);
    fread(SectNames, 1, shdr->sh_size, f);

    printf("Il y a %d section header, commençant à l'offset 0x%x:\n\n",
         convert16(ehdr->e_shnum), convert32(ehdr->e_shoff));
    printf("sectHdr Headers:\n  [Nr] Name               Type             Address "
           "          Offset              Size               EntSize          Flags  "
           "Link  Info  Align\n");


    for (int i = 0; i < convert16(ehdr->e_shnum); i++) {

        char *name = "";

        fseek(f, ehdr->e_shoff + i * sizeof(shdr), SEEK_SET);
        fread(shdr, 1, sizeof(shdr), f);

        name = SectNames + shdr->sh_name;
        find_type(sh_type, shdr[i].sh_type); 

        //Affichage des infos
        printf("  [%2d] %-18s %-17s %016x  %08x\n", i, name, sh_type,
           shdr[i].sh_addr, shdr[i].sh_offset);
 
        // printf("       %016lx   %016lx   %-5s %-5d %-5d  %ld\n", sectHdr.sh_size,
        //    sectHdr.sh_entsize, flags, sectHdr.sh_link,
        //    sectHdr.sh_info, sectHdr.sh_addralign);

        
        // printf("Section header:\n");
        // printf("Numéro de la section:                                     0x%d\n",i);
        // printf("Nom de la section:                                        0x%X\n",shdr[i].sh_name);
        // printf("Taille de la section:                                     0x%X\n",shdr[i].sh_size);
            
        // switch(shdr[i].sh_type){
        //     case SHT_PROGBITS: printf("Type: Section défini par le proramme\n");break;
        //     case SHT_SYMTAB: printf("Type: Section contient une table de symbole\n");break;
        //     case SHT_DYNSYM: printf("Type: Section contient une table de symbole\n");break;
        //     case SHT_STRTAB: printf("Type: section contient des chaîne de charactères\n");break;
        //     case SHT_RELA: printf("Type: section holds relocation entries\n");break;
        //     case SHT_HASH: printf("Type: section holds a symbol hash table\n");break;
        //     case SHT_DYNAMIC: printf("Type: section contient les informations de liaison dynamique\n");break;
        //     case SHT_NOTE: printf("Type: Section contient un marquage quelconque pour le fichier\n");break;
        //     case SHT_NOBITS: printf("Type: section défini par le programme mais n'est pas dans le fichier\n");break;
        //     case SHT_REL: printf("Type: section contient des entrées de repositionnement\n");break;
        //     case SHT_SHLIB: printf("Type: section est réservée et sa sémantique n'est pas définie.\n");break;
        //     case SHT_LOPROC: printf("Type: Section réservée jusqu'à la section SHT_HIPROC par le processeur\n");break;
        //     case SHT_HIPROC: printf("Type: Section réservée par le processeur depuis la section SHT_LOPROC\n");break;
        //     case SHT_LOUSER: printf("Cette valeur indique la borne inférieure de la plage des indices réservés aux programmes applicatifs.\n");break;
        //     case SHT_HIUSER: printf("Cette valeur indique la borne supérieure de la plage des indices réservés aux programmes applicatifs. Les types des sections entre SHT_LOUSER et SHT_HIUSER peuvent être utilisés par l'application, sans que cela entre en conflit avec les actuels ou futurs types de sections définis par le système\n");break;
        //     default: printf("Type: Section inactive\n");break;
        // }
        // switch(shdr[i].sh_flags){
        //     case 0x1: printf("Flag: SHF_WRITE,  possible d'écrire durant l'exécution du processus\n");break;
        //     case 0x2: printf("Flag: SHF_ALLOC, section est présente en mémoire durant l'exécution du processus\n");break;
        //     case 0x4: printf("Flag: SHF_EXECINSTR, Cette section contient des instructions machine exécutables\n");break;
        //     case 0xf0000000: printf("Flag: SHF_MASKPROC,     Tous les bits contenus dans ce masque sont réservés à des sémantiques spécifiques au processeur\n");break;
        // }
            
        // //printf("les informations d’allocation: JE SAIS PAS COMMENT ON AFFICHE CA");
        // printf("Position de la section par rapport au debut:              0x%X\n",shdr[i].sh_offset);
        // printf("\n");
        
            
    }   

}