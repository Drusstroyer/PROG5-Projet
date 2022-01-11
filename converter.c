#include "converter.h"

Elf32_Ehdr * convertpointhdr(Elf32_Ehdr *ehdr){
    ehdr->e_ehsize = convert16(ehdr->e_ehsize);
    ehdr->e_entry = convert32(ehdr->e_entry);
    ehdr->e_flags = convert32(ehdr->e_flags);
    ehdr->e_machine = convert16(ehdr->e_machine);
    ehdr->e_phentsize = convert16(ehdr->e_phentsize);
    ehdr->e_phnum = convert16(ehdr->e_phnum);
    ehdr->e_phoff = convert32(ehdr->e_phoff);
    ehdr->e_shentsize = convert16(ehdr->e_shentsize);
    ehdr->e_shnum = convert16(ehdr->e_shnum);
    ehdr->e_shoff = convert32(ehdr->e_shoff);
    ehdr->e_shstrndx = convert16(ehdr->e_shstrndx);
    return ehdr;
}

Elf32_Ehdr converthdr(Elf32_Ehdr ehdr){
    ehdr.e_ehsize = convert16(ehdr.e_ehsize);
    ehdr.e_entry = convert32(ehdr.e_entry);
    ehdr.e_flags = convert32(ehdr.e_flags);
    ehdr.e_machine = convert16(ehdr.e_machine);
    ehdr.e_phentsize = convert16(ehdr.e_phentsize);
    ehdr.e_phnum = convert16(ehdr.e_phnum);
    ehdr.e_phoff = convert32(ehdr.e_phoff);
    ehdr.e_shentsize = convert16(ehdr.e_shentsize);
    ehdr.e_shnum = convert16(ehdr.e_shnum);
    ehdr.e_shoff = convert32(ehdr.e_shoff);
    ehdr.e_shstrndx = convert16(ehdr.e_shstrndx);
    return ehdr;
}

Elf32_Shdr convertshdr(Elf32_Shdr shdr){
    shdr.sh_addr = convert32(shdr.sh_addr);
    shdr.sh_addralign = convert32(shdr.sh_addralign);
    shdr.sh_entsize = convert32(shdr.sh_entsize);
    shdr.sh_flags = convert32(shdr.sh_flags);
    shdr.sh_info = convert32(shdr.sh_info);
    shdr.sh_link = convert32(shdr.sh_link);
    shdr.sh_name = convert32(shdr.sh_name);
    shdr.sh_offset = convert32(shdr.sh_offset);
    shdr.sh_size = convert32(shdr.sh_size);
    shdr.sh_type = convert32(shdr.sh_type);
    return shdr;
}

Elf32_Sym convertsym(Elf32_Sym sym){
    sym.st_name = convert32(sym.st_name);
    sym.st_shndx = convert16(sym.st_shndx);
    sym.st_size = convert32(sym.st_size);
    sym.st_value = convert32(sym.st_value);
    return sym;
}

Elf32_Rel convertrel(Elf32_Rel rel){
    rel.r_info = convert32(rel.r_info);
    rel.r_offset = convert32(rel.r_offset);
    return rel;
}

uint32_t convert32(uint32_t val){
    uint32_t converted = 0;
    converted |= ((0x000000ff & val) << 24);
    converted |= ((0x0000ff00 & val) << 8);
    converted |= ((0x00ff0000 & val) >> 8);
    converted |= ((0xff000000 & val) >> 24);
    return converted;
}

uint16_t convert16(uint16_t val){
    uint16_t converted = 0;
    converted = ((((val) >> 8) & 0xff) | (((val) & 0xff) << 8));
    return converted;
}

int isNumber(char number[])
{
    int i = 0;

    //checking for negative numbers
    if (number[0] == '-')
        i = 1;
    for (; number[i] != 0; i++)
    {
        //if (number[i] > '9' || number[i] < '0')
        if (!isdigit(number[i]))
            return 1;
    }
    return 0;
}