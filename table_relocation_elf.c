#include "table_relocation_elf.h"
#include <stdlib.h>
#include <elf.h>
#include "converter.h"
#include <sys/mman.h>
#include <stdio.h>
#include <string.h>

void table_relocation32(char *elf_start, unsigned int taille){
    Elf32_Ehdr* hdr = NULL;
    Elf32_Shdr* shdr = NULL;
    Elf32_Shdr* reltab = NULL;
    Elf32_Shdr* symtab = NULL;
    Elf32_Shdr* strtab = NULL;
    Elf32_Rel *rel = NULL;
    Elf32_Rela *rela = NULL;
    char* exec = mmap(NULL, taille, PROT_READ | PROT_WRITE | PROT_EXEC,
                      MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
    //memset(exec,0x0,taille);
    hdr = (Elf32_Ehdr *) elf_start;
    //hdr = convertpointhdr(hdr);
    int ok = 0; //Booléen pour la présence de réadressages.
    shdr = (Elf32_Shdr *) (elf_start + convert32(hdr->e_shoff));
    char *str = (char *) (elf_start + convert32(shdr[convert16(hdr->e_shstrndx)].sh_offset));
    for(int i=0;i< convert16(hdr->e_shnum);i++){
        if (strcmp(&str[convert32(shdr[i].sh_name)], ".symtab") == 0){
         	symtab = (Elf32_Shdr *) &shdr[i]; 
        }
        if (strcmp(&str[convert32(shdr[i].sh_name)], ".dynstr") == 0){
         	strtab = (Elf32_Shdr *) &shdr[i]; 
        }
        if (convert32(shdr[i].sh_type) == (Elf32_Word) SHT_RELA){
            ok=1;
        }
        if (convert32(shdr[i].sh_type) == (Elf32_Word) SHT_REL){
            ok=1;
        }     
    }
    if (ok == 0){
        printf("Il n'y a pas de réadressages dans ce fichier.\n");
        return;
    }
    for(int i=0;i< convert32(hdr->e_shnum);i++){
        if (convert32(shdr[i].sh_type) == (Elf32_Word) SHT_RELA){
            reltab = (Elf32_Shdr *) &shdr[i];
            rela = (Elf32_Rela *) (elf_start + convert32(reltab->sh_offset));
            for(int j=0;j<convert32(reltab->sh_size) / convert32(reltab->sh_entsize);j++){
                printf("%012x ",convert32(rela[j].r_offset));// le decalage
                printf(" %012x ",convert32(rela[j].r_info)); 
                    switch(ELF32_R_TYPE(convert32(rela[j].r_info))){ //le type
                    
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
                    }
                    switch(ELF32_R_TYPE(convert32(rela[j].r_info))){ 
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
                    }printf("\n");
            }printf("\n");
        } 
    }

}


void table_relocation64(char *elf_start, unsigned int taille){
    Elf64_Ehdr* hdr = NULL;
    Elf64_Shdr* shdr = NULL;
    Elf64_Shdr* reltab = NULL;
    Elf64_Shdr* symtab = NULL;
    Elf64_Shdr* strtab = NULL;
    Elf64_Rel *rel = NULL;
    Elf64_Rela *rela = NULL;
    char* exec = mmap(NULL, taille, PROT_READ | PROT_WRITE | PROT_EXEC,
                      MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
    //memset(exec,0x0,taille);
    hdr = (Elf64_Ehdr *) elf_start;
    //hdr = convertpointhdr(hdr);

    shdr = (Elf64_Shdr *) (elf_start + hdr->e_shoff);
    char *str = (char *) (elf_start + shdr[hdr->e_shstrndx].sh_offset);
    for(int i=0;i< hdr->e_shnum;i++){
        if (strcmp(&str[shdr[i].sh_name], ".symtab") == 0){
         	symtab = (Elf64_Shdr *) &shdr[i]; 
        }
        if (strcmp(&str[shdr[i].sh_name], ".dynstr") == 0){
         	strtab = (Elf64_Shdr *) &shdr[i]; 
        }      
    }

    for(int i=0;i< hdr->e_shnum;i++){
        if (shdr[i].sh_type == (Elf64_Word) SHT_RELA){
            reltab = (Elf64_Shdr *) &shdr[i];
            rela = (Elf64_Rela *) (elf_start + reltab->sh_offset);
            for(int j=0;j<reltab->sh_size / reltab->sh_entsize;j++){
                printf("%012lx ",rela[j].r_offset);// le decalage
                printf(" %012lx ",rela[j].r_info); 
                    switch(ELF64_R_TYPE(rela[j].r_info)){ //le type
                    
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
                    }
                    switch(ELF64_R_TYPE(rela[j].r_info)){ 
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
                    }printf("\n");
            }printf("\n");
        } 
    }

}