#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "table_section_elf.h"
#include "Affiche_section_elf.h"
#include "converter.h"

Elf32_Shdr* section_elf(FILE * f, Elf32_Ehdr *ehdr){

    //size_t tot = ehdr->e_shnum * ehdr->e_shentsize;
    /*
    Elf32_Shdr * shdr = malloc(sizeof(Elf32_Shdr*));

    fseek(f, ehdr->e_shoff, SEEK_SET);

    size_t s = fread(shdr, 1, tot, f);*/
    Elf32_Shdr * shdr = malloc(sizeof(Elf32_Shdr));
    char * section=NULL; 
    fread(ehdr, 1, sizeof(*ehdr), f);
    fseek(f,ehdr->e_shoff + ehdr->e_shstrndx * ehdr->e_shentsize, SEEK_SET);
    fread(shdr,1,sizeof(*shdr),f);
    section = malloc(shdr->sh_size);
    fseek(f,shdr->sh_offset,SEEK_SET);
    fread(section,1,shdr->sh_size,f);
    printf("Il y a %d sections headers, commençant à l'offset 0x%x:\n\n",ehdr->e_shnum,ehdr->e_shoff);
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
    return shdr;

}
