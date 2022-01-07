#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "read_section_elf.h"
#include "converter.h"

//penser a faire de la robustesse
void read_section(FILE * f, Elf32_Ehdr *ehdr, Elf32_Word n){
    Elf32_Shdr shdr;
    

    fseek(f, convert32(ehdr->e_shoff) + convert16(ehdr->e_shstrndx) * convert16(ehdr->e_shentsize), SEEK_SET);
    fread(&shdr, 1, sizeof(shdr), f);
    
    fseek(f,convert32(ehdr->e_shoff) + n * sizeof(shdr), SEEK_SET);
    fread(&shdr, 1, sizeof(shdr), f);

    Elf32_Shdr *w = malloc(convert32(shdr.sh_size));

    printf("0x%X\n", convert32(shdr.sh_offset));
    printf("0x%X\n", convert32(shdr.sh_size));

    fseek(f, convert32(shdr.sh_offset), SEEK_SET);
    fread(w, 1, sizeof(convert32(shdr.sh_size)), f);

    printf("0x%X\n", *w);



}