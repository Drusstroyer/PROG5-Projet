#include "table_symbole.h"
#include "Affiche_symbole.h"
#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "converter.h"
#include "table_relocation_elf.h"
 
void find_name(FILE *f, Elf32_Word index){
    char* sname="";
    Elf32_Ehdr ehdr;
    Elf32_Shdr shdr;
    Elf32_Sym symbole;
    

    fseek(f,0,SEEK_SET);
    fread(&ehdr,1,sizeof(ehdr),f);
    ehdr = converthdr(ehdr);
    fseek(f, convert32(ehdr.e_shoff) + convert16(ehdr.e_shstrndx) * convert16(ehdr.e_shentsize), SEEK_SET);
    //fseek(f, ehdr.e_shoff + ehdr.e_shstrndx * ehdr.e_shentsize, SEEK_SET);
    fread(&shdr,1,sizeof(shdr),f);
    shdr = convertshdr(shdr);
    for(int i=0;i<=ehdr.e_shnum;i++){
        fseek(f,convert32(ehdr.e_shoff) + i * sizeof(shdr), SEEK_SET);
        fread(&shdr,1,sizeof(shdr),f);
        fread(sname,1,convert32(shdr.sh_size),f);
        if(convert32(shdr.sh_type) == (Elf32_Word) SHT_STRTAB){
            sname = convert32(shdr.sh_offset) + index;
            printf("Symbole : %s",sname);
        }
    }

}


void table_symbole(FILE * f){
    Elf32_Ehdr ehdr;
    Elf32_Shdr shdr;
    Elf32_Sym symbole;

    rewind(f);
    fread(&ehdr, 1, sizeof(ehdr), f);
    ehdr = converthdr(ehdr);
    fseek(f, ehdr.e_shoff + ehdr.e_shstrndx * ehdr.e_shentsize, SEEK_SET);
    //fseek(f, convert32(ehdr.e_shoff) + convert16(ehdr.e_shstrndx) * convert16(ehdr.e_shentsize), SEEK_SET);
    fread(&shdr,1,sizeof(shdr),f);
    shdr = convertshdr(shdr);

    //char * symbolee = malloc(convert32(shdr.sh_size));
    
    
    for(int i=0;i<=ehdr.e_shnum;i++){
        fseek(f,ehdr.e_shoff + i * sizeof(shdr), SEEK_SET);
        //fseek(f,convert32(ehdr.e_shoff) + i * sizeof(shdr), SEEK_SET);
        fread(&shdr,1,sizeof(shdr),f);
        shdr = convertshdr(shdr);
        if(shdr.sh_type == (Elf32_Word) SHT_SYMTAB){
            printf("La table de symboles .symtab contient %d entrées\n",shdr.sh_size/shdr.sh_entsize);
            //fseek(f, convert32(shdr.sh_offset) + convert32(shdr.sh_entsize), SEEK_SET);
            //fread(symbolee, 1, convert32(shdr.sh_size), f);
            for(int j=0;j<shdr.sh_size/shdr.sh_entsize;j++){
                //char * symbolename ="";
                fseek(f,shdr.sh_offset + j * shdr.sh_entsize,SEEK_SET);
                //fseek(f,convert32(ehdr.e_shoff) + i * sizeof(shdr), SEEK_SET);
                fread(&symbole,1,sizeof(symbole),f);
                symbole = convertsym(symbole);
                //symbolename = convert32(symbole.st_name) + symbolee;
                printf("Num:%-4d    Valeur:%-6x     Taille:%-4d     Nom:%08x   NDX:%08d     ",j,symbole.st_value,symbole.st_size,symbole.st_name,symbole.st_shndx);//symbolename);
                switch(symbole.st_info & 0xf){
                    case STT_NOTYPE: printf("Type: NOTYPE  ");break;
                    case STT_OBJECT: printf("Type: OBJECT  ");break;
                    case STT_FUNC: printf("Type: FUNCTION");break;
                    case STT_SECTION: printf("Type: SECTION ");break;
                    case STT_FILE: printf("Type: FILE    ");break;
                    case STT_COMMON: printf("Type: COMMON  ");break;
                    case STT_TLS: printf("Type: TLS     ");break;
                    case STT_NUM: printf("Type: NUMBER  ");break;        
                    case STT_LOOS: printf("Type: LOOS    ");break;
                    case STT_HIOS: printf("Type: HIOS    ");break;
                    case STT_LOPROC: printf("Type: LOPROC  ");break;
                    case STT_HIPROC: printf("Type: HIPROC  ");break;
                }
                switch(symbole.st_other & 0x03){
                    case STV_DEFAULT: printf(" Visibility: Default   ");break;
                    case STV_INTERNAL: printf(" Visibility: Internal  ");break;
                    case STV_HIDDEN: printf(" Visibility: Hidden     ");break;
                    case STV_PROTECTED: printf(" Visibility: Protected ");break;
                }
                switch(symbole.st_info >> 4){
                    case STB_LOCAL: printf("Lien: LOCAL\n");break;
                    case STB_GLOBAL: printf("Lien: GLOBAL\n");break;
                    case STB_WEAK: printf("Lien: WEAK\n");break;
                    case STB_NUM: printf("Lien: NUM\n");break;
                    case STB_LOOS: printf("Lien: LOOS\n");break;
                    case STB_HIOS: printf("Lien: HIOS\n");break;
                    case STB_LOPROC: printf("Lien: LOPROC\n");break;
                    case STB_HIPROC: printf("Lien: HIPROC\n");break;
                }
                //find_name(f,convert32(symbole.st_name));
            }
        }
    
    }
}

