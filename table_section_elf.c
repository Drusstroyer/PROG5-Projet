#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "table_section_elf.h"
#include "converter.h"


void section_elf(FILE * f, Elf32_Ehdr *ehdr){

    Elf32_Shdr shdr;

    fseek(f, convert32(ehdr->e_shoff) + convert16(ehdr->e_shstrndx) * convert16(ehdr->e_shentsize), SEEK_SET);
    fread(&shdr, 1, sizeof(shdr), f);

    char *SectNames = malloc(convert32(shdr.sh_size));
    fseek(f, convert32(shdr.sh_offset), SEEK_SET);
    fread(SectNames, 1, convert32(shdr.sh_size), f);


    printf("Il y a %d section header, commençant à l'offset 0x%x:\n\n", convert16(ehdr->e_shnum), convert32(ehdr->e_shoff));
    printf("Section Headers:\n  [Nr] Name                Type             Address "
           "          Offset     Size     EntSize  Flags   "
           "Link  Info Align\n");

    for (int i = 0; i <= convert16(ehdr->e_shnum) - 1; i++) {
        char* name = "";
        char* type = "";
        char* flags = "";

        fseek(f,convert32(ehdr->e_shoff) + i * sizeof(shdr), SEEK_SET);
        fread(&shdr, 1, sizeof(shdr), f);

        name = SectNames + convert32(shdr.sh_name);
        

        switch(convert32(shdr.sh_type)){
            case SHT_PROGBITS: type = "PROGBITS";break;
            case SHT_SYMTAB: type = "SYMTAB";break;
            case SHT_DYNSYM: type = "DYNSYM";break;
            case SHT_STRTAB: type = "STRTAB";break;
            case SHT_RELA: type = "RELA";break;
            case SHT_HASH: type = "HASH";break;
            case SHT_DYNAMIC: type = "DYNAMIC";break;
            case SHT_NOTE: type = "NOTE";break;
            case SHT_NOBITS: type = "NOBITS";break;
            case SHT_REL: type = "REL";break;
            case SHT_SHLIB: type = "SHLIB";break;
            case SHT_LOPROC: type = "LOPROC";break;
            case SHT_HIPROC: type = "HIPROC";break;
            case SHT_LOUSER: type = "LOUSER";break;
            case SHT_HIUSER: type = "HIUSER";break;
            default: type = "NULL";break;
        }

        switch(convert32(shdr.sh_flags)){
            case 0x1: flags = "SHF_WRITE";break;
            case 0x2: flags = "HF_ALLOC";break;
            case 0x4: flags = "SHF_EXECINSTR";break;
            case 0xf0000000: flags = "SHF_MASKPROC";break;
        }

        printf("  [%2d] %-18s %-17s %016x  0x%08X %08x %08x %-7s %-5d %-3d  %d\n", i, name, type, convert32(shdr.sh_addr), convert32(shdr.sh_offset), convert32(shdr.sh_size), convert32(shdr.sh_entsize), flags, convert32(shdr.sh_link), convert32(shdr.sh_info), convert32(shdr.sh_addralign));
    }   
    printf("\n");

}