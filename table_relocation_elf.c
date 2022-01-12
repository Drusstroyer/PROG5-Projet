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
        if (strcmp(&str[convert32(shdr[i].sh_name)], ".strtab") == 0){
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
    Elf32_Sym *sym = (Elf32_Sym*) (elf_start + convert32(symtab->sh_offset));
    str = (char*) (elf_start + convert32(strtab->sh_offset));
    for(int i=0;i< convert16(hdr->e_shnum);i++){
        if (convert32(shdr[i].sh_type) == (Elf32_Word) SHT_REL){
            reltab = (Elf32_Shdr *) &shdr[i];
            rel = (Elf32_Rel *) (elf_start + convert32(reltab->sh_offset));
            for(int j=0;j<convert32(reltab->sh_size) / convert32(reltab->sh_entsize);j++){
                printf("%012x ",convert32(rel[j].r_offset));// le decalage
                printf(" %012x ",convert32(rel[j].r_info)); 
                    switch(ELF32_R_TYPE(convert32(rel[j].r_info))){ //le type
                    
                        case R_ARM_NONE: printf("R_ARM_NONE");break;
                        case R_ARM_PC24: printf("R_ARM_PC24");break;
                        case R_ARM_ABS32:printf("R_ARM_ABS32");break;
                        case R_ARM_REL32:printf("R_ARM_REL32");break;
                        case R_ARM_PC13:printf("R_ARM_PC13");break;
                        case R_ARM_ABS16:printf("R_ARM_ABS16");break;
                        case R_ARM_ABS12:printf("R_ARM_ABS12");break;
                        case R_ARM_THM_ABS5:printf("R_ARM_THM_ABS5");break;
                        case R_ARM_ABS8:printf("R_ARM_ABS8");break;
                        case R_ARM_SBREL32:printf("R_ARM_SBREL32");break;
                        case R_ARM_THM_PC22:printf("R_ARM_THM_PC22");break;
                        case R_ARM_THM_PC8:printf("R_ARM_THM_PC8");break;
                        case R_ARM_AMP_VCALL9:printf("R_ARM_AMP_VCALL9");break;
                        case R_ARM_SWI24:printf("R_ARM_SWI24");break;
                        case R_ARM_THM_SWI8:printf("R_ARM_THM_SWI8");break;
                        case R_ARM_XPC25:printf("R_ARM_XPC25");break;
                        case R_ARM_THM_XPC22:printf("R_ARM_THM_XPC22");break;
                        case R_ARM_TLS_DTPMOD32:printf("R_ARM_TLS_DTPMOD32");break;
                        case R_ARM_TLS_DTPOFF32:printf("R_ARM_TLS_DTPOFF32");break;
                        case R_ARM_TLS_TPOFF32:printf("R_ARM_TLS_TPOFF32");break;
                        case R_ARM_COPY:printf("R_ARM_COPY");break;
                        case R_ARM_GLOB_DAT:printf("R_ARM_GLOB_DAT");break;
                        case R_ARM_JUMP_SLOT:printf("R_ARM_JUMP_SLOT");break;
                        case R_ARM_RELATIVE:printf("R_ARM_RELATIVE");break;
                        case R_ARM_GOTOFF:printf("R_ARM_GOTOFF");break;
                        case R_ARM_GOTPC:printf("R_ARM_GOTPC");break;
                        case R_ARM_GOT32:printf("R_ARM_GOT32");break;
                        case R_ARM_PLT32:printf("R_ARM_PLT32");break;
                        case R_ARM_CALL:printf("R_ARM_CALL");break;
                        case R_ARM_JUMP24:printf("R_ARM_JUMP24");break;
                    } printf("    Nom:%8s\n", str + convert32(sym[i].st_name)); //ELF32_R_SYM(convert32(rel[i].r_info)));
                    printf("\n");
            }printf("\n");
        } 
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
                    printf("\n");
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
    int ok = 0;
    shdr = (Elf64_Shdr *) (elf_start + hdr->e_shoff);
    char *str = (char *) (elf_start + shdr[hdr->e_shstrndx].sh_offset);
    for(int i=0;i< hdr->e_shnum;i++){
        if (strcmp(&str[shdr[i].sh_name], ".symtab") == 0){
         	symtab = (Elf64_Shdr *) &shdr[i]; 
        }
        if (strcmp(&str[shdr[i].sh_name], ".dynstr") == 0){
         	strtab = (Elf64_Shdr *) &shdr[i]; 
        }      
        if (shdr[i].sh_type == (Elf32_Word) SHT_RELA){
            ok=1;
        }
        if (shdr[i].sh_type == (Elf32_Word) SHT_REL){
            ok=1;
        }   
    }
    if (ok == 0){
        printf("Il n'y a pas de réadressages dans ce fichier.\n");
        return;
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
                    printf("\n");
            }printf("\n");
        } 
    }

}