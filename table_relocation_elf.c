#include "table_relocation_elf.h"
#include <stdlib.h>
#include <elf.h>
#include "converter.h"

void table_relocation(FILE *f){
    Elf64_Ehdr ehdr;
    Elf64_Shdr shdr;
    Elf64_Rel relocation;
    //char * section=NULL; 
    rewind(f);
    fread(&ehdr, 1, sizeof(ehdr), f);
    //fseek(f, convert32(ehdr.e_shoff) + convert16(ehdr.e_shstrndx) * convert16(ehdr.e_shentsize), SEEK_SET);
    fseek(f, ehdr.e_shoff + ehdr.e_shstrndx * ehdr.e_shentsize, SEEK_SET);
    fread(&shdr,1,sizeof(shdr),f);
    //char *SectNames = malloc(shdr.sh_size);
    //fseek(f,shdr.sh_offset,SEEK_SET);
    //fread(SectNames,1,sizeof(SectNames),f);
    //section = malloc(convert32(shdr.sh_size));
    //fseek(f,convert32(shdr.sh_offset),SEEK_SET);
    //fread(section,1,convert32(shdr.sh_size),f);
    for(int i=0;i<=ehdr.e_shnum;i++){
        //fseek(f,convert32(ehdr.e_shoff) + i * sizeof(shdr), SEEK_SET);
        fseek(f,ehdr.e_shoff + i * sizeof(shdr), SEEK_SET);
        fread(&shdr,1,sizeof(shdr),f);
        if(shdr.sh_type == (Elf32_Word) SHT_RELA){
            fread(&relocation,1,sizeof(relocation),f);
            switch(ELF32_R_TYPE(relocation.r_info)){ //On regarde si il y a des relocations
                case R_X86_64_NONE: printf("There are no relocations in this file\n");return; // Il n'y en a pas on stop le programme sur ce return. 
                default:break;
            }
            printf("\nOFFSET : 0x%lx\n",shdr.sh_offset);
            printf("  Décalage        Info           Type\n");
            for(int j=0;j<shdr.sh_size/shdr.sh_entsize;j++){
                //char * name= "";
                fseek(f,shdr.sh_offset + j * shdr.sh_entsize,SEEK_SET);
                fread(&relocation,1,sizeof(relocation),f);
                //name = SectNames + shdr.
                printf("%012lx ",relocation.r_offset);// le decalage
                printf(" %012lx ",relocation.r_info); //il faudrait pouvoir afficher des 0000 comme pour readelf ce serait propre..  (le R_INFO)
                /*switch(ELF64_R_TYPE(relocation.r_info)){ //le type
                
                    case R_ARM_NONE: printf("R_ARM_NONE\n");break;
                    case R_ARM_PC24: printf("R_ARM_PC24\n");break;
                    case R_ARM_ABS32:printf("R_ARM_ABS32\n");break;
                    case R_ARM_REL32:printf("R_ARM_REL32\n");break;
                    case R_ARM_PC13:printf("R_ARM_PC13\n");break;
                    case R_ARM_ABS16:printf("R_ARM_ABS16\n");break;
                    case R_ARM_ABS12:printf("R_ARM_ABS12\n");break;
                    case R_ARM_THM_ABS5:printf("R_ARM_THM_ABS5\n");break;
                    case R_ARM_ABS8:printf("R_ARM_ABS8\n");break;
                    case R_ARM_SBREL32:printf("R_ARM_SBREL32\n");break;
                    case R_ARM_THM_PC22:printf("R_ARM_THM_PC22\n");break;
                    case R_ARM_THM_PC8:printf("R_ARM_THM_PC8\n");break;
                    case R_ARM_AMP_VCALL9:printf("R_ARM_AMP_VCALL9\n");break;
                    case R_ARM_SWI24:printf("R_ARM_SWI24\n");break;
                    case R_ARM_THM_SWI8:printf("R_ARM_THM_SWI8\n");break;
                    case R_ARM_XPC25:printf("R_ARM_XPC25\n");break;
                    case R_ARM_THM_XPC22:printf("R_ARM_THM_XPC22\n");break;
                    case R_ARM_TLS_DTPMOD32:printf("R_ARM_TLS_DTPMOD32\n");break;
                    case R_ARM_TLS_DTPOFF32:printf("R_ARM_TLS_DTPOFF32\n");break;
                    case R_ARM_TLS_TPOFF32:printf("R_ARM_TLS_TPOFF32\n");break;
                    case R_ARM_COPY:printf("R_ARM_COPY\n");break;
                    case R_ARM_GLOB_DAT:printf("R_ARM_GLOB_DAT\n");break;
                    case R_ARM_JUMP_SLOT:printf("R_ARM_JUMP_SLOT\n");break;
                    case R_ARM_RELATIVE:printf("R_ARM_RELATIVE\n");break;
                    case R_ARM_GOTOFF:printf("R_ARM_GOTOFF\n");break;
                    case R_ARM_GOTPC:printf("R_ARM_GOTPC\n");break;
                    case R_ARM_GOT32:printf("R_ARM_GOT32\n");break;
                    case R_ARM_PLT32:printf("R_ARM_PLT32\n");break;
                    case R_ARM_CALL:printf("R_ARM_CALL\n");break;
                    case R_ARM_JUMP24:printf("R_ARM_JUMP24\n");break;
                }*/
                switch(ELF64_R_TYPE(relocation.r_info)){ //JUSTE POUR L'AFFICHAGE QUE TU TESTE QUE CA RENDENT BIEN
                    case R_X86_64_NONE:printf("R_X86_64_NONE ");break;
                    case R_X86_64_64:printf("R_X86_64_64 ");break;
                    case R_X86_64_PC32:printf("R_X86_64_PC32 ");break;
                    case R_X86_64_GOT32:printf("R_X86_64_GOT32 ");break;
                    case R_X86_64_PLT32:printf("R_X86_64_PLT32 ");break;
                    case R_X86_64_COPY:printf("R_X86_64_COPY ");break;
                    case R_X86_64_GLOB_DAT:printf("R_X86_64_GLOB_DAT ");break;
                    case R_X86_64_JUMP_SLOT:printf("R_X86_64_JUMP_SLOT ");break;
                    case R_X86_64_RELATIVE:printf("R_X86_64_RELATIVE ");break;
                    case R_X86_64_GOTPCREL:printf("R_X86_64_GOTPCREL ");break;
                    case R_X86_64_32:printf("R_X86_64_32 ");break;
                    case R_X86_64_32S:printf("R_X86_64_32S ");break;
                    case R_X86_64_16:printf("R_X86_64_16 ");break;
                    case R_X86_64_PC16:printf("R_X86_64_PC16 ");break;
                    case R_X86_64_8:printf("R_X86_64_8 ");break;
                    case R_X86_64_PC8:printf("R_X86_64_PC8 ");break;
                    case R_X86_64_DTPMOD64:printf("R_X86_64_DTPMOD64 ");break;
                    case R_X86_64_DTPOFF64:printf("R_X86_64_DTPOFF64 ");break;
                    case R_X86_64_TPOFF64:printf("R_X86_64_TPOFF64 ");break;
                    case R_X86_64_TLSGD:printf("R_X86_64_TLSGD ");break;
                    case R_X86_64_TLSLD:printf("R_X86_64_TLSLD ");break;
                    case R_X86_64_DTPOFF32:printf("R_X86_64_DTPOFF32 ");break;
                    case R_X86_64_GOTTPOFF:printf("R_X86_64_GOTTPOFF ");break;
                    case R_X86_64_TPOFF32:printf("R_X86_64_TPOFF32 ");break;
                    case R_X86_64_PC64:printf("R_X86_64_PC64 ");break;
                    case R_X86_64_GOTOFF64:printf("R_X86_64_GOTOFF64 ");break;
                    case R_X86_64_GOTPC32:printf("R_X86_64_GOTPC32 ");break;
                    case R_X86_64_GOT64:printf("R_X86_64_GOT64 ");break;
                    case R_X86_64_GOTPCREL64:printf("R_X86_64_GOTPCREL64 ");break;
                    case R_X86_64_GOTPC64:printf("R_X86_64_GOTPC64 ");break;
                    case R_X86_64_GOTPLT64:printf("R_X86_64_GOTPLT64 ");break;
                    case R_X86_64_PLTOFF64:printf("R_X86_64_PLTOFF64 ");break;
                    case R_X86_64_SIZE32:printf("R_X86_64_SIZE32 ");break;
                    case R_X86_64_SIZE64:printf("R_X86_64_SIZE64 ");break;
                    case R_X86_64_GOTPC32_TLSDESC:printf("R_X86_64_GOTPC32_TLSDESC ");break;
                    case R_X86_64_TLSDESC_CALL:printf("R_X86_64_TLSDESC_CALL ");break;
                    case R_X86_64_TLSDESC:printf("R_X86_64_TLSDESC ");break;
                    case R_X86_64_IRELATIVE:printf("R_X86_64_IRELATIVE ");break;
                    case R_X86_64_RELATIVE64:printf("R_X86_64_RELATIVE64 ");break;
                    case R_X86_64_GOTPCRELX:printf("R_X86_64_GOTPCRELX ");break;
                    case R_X86_64_REX_GOTPCRELX:printf("R_X86_64_REX_GOTPCRELX ");break;
                    case R_X86_64_NUM:printf("R_X86_64_NUM ");break;
                    default:break;
                }
                    printf("\n");
                    //printf("le r_info : %0lx\n",relocation.r_info); //il faudrait pouvoir afficher des 0000 comme pour readelf ce serait propre.. 

            } 
        }
    }
}