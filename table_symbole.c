#include "table_symbole.h"
#include "Affiche_symbole.h"
#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "converter.h"
#include "table_relocation_elf.h"

void table_symbole(FILE * f){
    Elf32_Ehdr ehdr;
    Elf32_Shdr shdr;
    Elf32_Sym symbole;
    char * section=NULL; 
    rewind(f);
    fread(&ehdr, 1, sizeof(ehdr), f);
    fseek(f, convert32(ehdr.e_shoff) + convert16(ehdr.e_shstrndx) * convert16(ehdr.e_shentsize), SEEK_SET);
    fread(&shdr,1,sizeof(shdr),f);
    section = malloc(convert32(shdr.sh_size));
    fseek(f,convert32(shdr.sh_offset),SEEK_SET);
    fread(section,1,convert32(shdr.sh_size),f);

    //char * symbolee = malloc(convert32(shdr.sh_size));
    
    
    for(int i=0;i<=convert16(ehdr.e_shnum);i++){
        fseek(f,convert32(ehdr.e_shoff) + i * sizeof(shdr), SEEK_SET);
        fread(&shdr,1,sizeof(shdr),f);
        if(convert32(shdr.sh_type) == (Elf32_Word) SHT_SYMTAB){
            printf("La table de symboles .symtab contient %d entrées\n",convert32(shdr.sh_size)/convert32(shdr.sh_entsize));
            //fseek(f, convert32(shdr.sh_offset) + convert32(shdr.sh_entsize), SEEK_SET);
            //fread(symbolee, 1, convert32(shdr.sh_size), f);
            for(int j=0;j<convert32(shdr.sh_size)/convert32(shdr.sh_entsize) ;j++){
                //char * symbolename ="";
                fseek(f,convert32(shdr.sh_offset) + j * convert32(shdr.sh_entsize),SEEK_SET);
                //fseek(f,convert32(ehdr.e_shoff) + i * sizeof(shdr), SEEK_SET);
                fread(&symbole,1,sizeof(symbole),f);
                //symbolename = convert32(symbole.st_name) + symbolee;
                printf("Num:%d    Valeur:%x     Taille:%d     Nom:%0x   NDX:%0d     ",j,convert32(symbole.st_value),convert32(symbole.st_size),convert32(symbole.st_name),convert16(symbole.st_shndx));//symbolename);
                switch(symbole.st_info & 0xf){
                    case STT_NOTYPE: printf("Type: NOTYPE");break;
                    case STT_OBJECT: printf("Type: OBJECT");break;
                    case STT_FUNC: printf("Type: FUNCTION");break;
                    case STT_SECTION: printf("Type: SECTION");break;
                    case STT_FILE: printf("Type: FILE");break;
                    case STT_COMMON: printf("Type: COMMON");break;
                    case STT_TLS: printf("Type: TLS");break;
                    case STT_NUM: printf("Type: NUMBER");break;        
                    case STT_LOOS: printf("Type: LOOS");break;
                    case STT_HIOS: printf("Type: HIOS");break;
                    case STT_LOPROC: printf("Type: LOPROC");break;
                    case STT_HIPROC: printf("Type: HIPROC");break;
                }
                switch(symbole.st_other & 0x03){
                    case STV_DEFAULT: printf("  Visibility: Default");break;
                    case STV_INTERNAL: printf(" Visibility: Internal");break;
                    case STV_HIDDEN: printf("   Visibility: Hidden");break;
                    case STV_PROTECTED: printf("    Visibility: Protected");break;
                }
                switch(symbole.st_info >> 4){
                    case STB_LOCAL: printf("    Lien: LOCAL\n");break;
                    case STB_GLOBAL: printf("   Lien: GLOBAL\n");break;
                    case STB_WEAK: printf("     Lien: WEAK\n");break;
                    case STB_NUM: printf("      Lien: NUM\n");break;
                    case STB_LOOS: printf("     Lien: LOOS\n");break;
                    case STB_HIOS: printf("     Lien: HIOS\n");break;
                    case STB_LOPROC: printf("   Lien: LOPROC\n");break;
                    case STB_HIPROC: printf("   Lien: HIPROC\n");break;
                }
            }
        }
    
    }
    //return symbole;*/
}

