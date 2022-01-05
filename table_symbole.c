#include "table_symbole.h"
#include "Affiche_symbole.h"
#include <assert.h>
#include <stdint.h>
#include <string.h>


void table_symbole(FILE * f){
    Elf32_Ehdr * ehdr = malloc(sizeof(Elf32_Ehdr*));
    Elf32_Shdr * shdr = malloc(sizeof(Elf32_Shdr*));
    char * section=NULL; 
    fread(ehdr, 1, sizeof(*ehdr), f);
    fseek(f,ehdr->e_shoff + ehdr->e_shstrndx * ehdr->e_shentsize, SEEK_SET);
    fread(shdr,1,sizeof(*shdr),f);
    section = malloc(shdr->sh_size);
    fseek(f,shdr->sh_offset,SEEK_SET);
    fread(section,1,shdr->sh_size,f);
    printf("Il y a %d sections headers, commençant à l'offset 0x%x:\n\n",ehdr->e_shnum,ehdr->e_shoff);
    for(int i=0;i<ehdr->e_shnum;i++){
        char * section_name="";
        fseek(f,ehdr->e_shoff + i * sizeof(*shdr), SEEK_SET);
        fread(shdr,1,sizeof(*shdr),f);
        //section_name = (char*)(section + shdr->sh_name);
        //memcpy(section_name, (char*)&shdr->sh_name,sizeof(Elf32_Word));//traduire le unsigned int en char* 
        printf("[%2d] %s %0x %0x\n",i,section_name,shdr->sh_addr,shdr->sh_offset);
    }
    //return symbole;
}

int main(int argc, char ** argv){
    FILE * f = fopen(argv[1],"rb");
    assert(f != NULL);
    table_symbole(f);
    //assert(symbole != NULL);
    //affiche_symbole(symbole);
}