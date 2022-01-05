#include "table_symbole.h"
#include "Affiche_symbole.h"
#include <assert.h>


void table_symbole(FILE * f){
    Elf32_Ehdr * ehdr = malloc(sizeof(Elf32_Ehdr*));
    Elf32_Sym * symbole = malloc(sizeof(Elf32_Sym*));
    fseek(f, 0, SEEK_SET);
    size_t n = fread(ehdr, 1, sizeof(*ehdr), f);
    /*for(int i=0;i<ehdr->e_shentsize;i++){
        fseek(f,ehdr->e_phoff,SEEK_CUR);
        fread(symbole,1,sizeof(*symbole),f);
        printf("\nSymbole:%0X,size:%u",symbole->st_name,symbole->st_size);
    }*/
    //size_t tot = ehdr->e_shnum * ehdr->e_shentsize;
    Elf32_Shdr * shdr = malloc(sizeof(Elf32_Shdr*));
    size_t k = fseek(f,ehdr->e_shoff + ehdr->e_shstrndx,SEEK_SET);
    fread(shdr,1,sizeof(*shdr),f);
    //shdr->
    

    //return symbole;
}

int main(int argc, char ** argv){
    FILE * f = fopen(argv[1],"rb");
    assert(f != NULL);
    table_symbole(f);
    //assert(symbole != NULL);
    //affiche_symbole(symbole);
}