#include "table_relocation_elf.h"
#include <stdlib.h>
#include <elf.h>
#include "converter.h"

void table_relocation(FILE *f){
    Elf32_Ehdr ehdr;
    Elf32_Shdr shdr;
    Elf32_Rel relocation;
    //char * section=NULL; 
    fread(&ehdr, 1, sizeof(ehdr), f);
    fseek(f, convert32(ehdr.e_shoff) + convert16(ehdr.e_shstrndx) * convert16(ehdr.e_shentsize), SEEK_SET);
    fread(&shdr,1,sizeof(shdr),f);
    //section = malloc(convert32(shdr.sh_size));
    //fseek(f,convert32(shdr.sh_offset),SEEK_SET);
    //fread(section,1,convert32(shdr.sh_size),f);
    for(int i=0;i<=convert16(ehdr.e_shnum);i++){
        fseek(f,convert32(ehdr.e_shoff) + i * sizeof(shdr), SEEK_SET);
        fread(&shdr,1,sizeof(shdr),f);
        if(convert32(shdr.sh_type) == (Elf32_Word) SHT_REL){
            fread(&relocation,1,sizeof(relocation),f);
            switch(ELF32_R_TYPE(convert32(relocation.r_info))){ //On regarde si il y a des relocations
                case R_X86_64_NONE: printf("There are no relocations in this file\n");return; // Il n'y en a pas on stop le programme sur ce return. 
                default:break;
            }
            printf("coucouuu bb\n");
            printf("OFFSET : 0x%x\n",convert32(shdr.sh_offset));
            /*for(int j=0;j<convert32(shdr.sh_size)/convert32(shdr.sh_entsize);j++){

            }
            */
        }    
    }
}