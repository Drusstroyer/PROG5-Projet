#include "Affiche_entete_elf.h"

void elf_print_HDR(const Elf32_Ehdr *ehdr){

    printf("ELF Header:\n"
        "  Machine:                           0x%X\n"
        "  Class:                             0x%X\n"
        "  Type:                              0x%X\n"
        "  Start of section headers:          0x%X\n"
        "  Size of section headers:           0x%X (bytes)\n"
		"  Number of section headers:         0x%X\n"
		"  Section header string table index: 0x%X\n\n"
        "  Size of this header:               0x%X (bytes)\n"
		
        
		/*"  Data:                              0x%X\n"
		"  Version:                           0x%X\n"
		"  OS/ABI:                            0x%X\n"
		"  ABI Version:                       0x%X\n"
		
		
		"  Version:                           0x%X\n"
		"  Entry point address:               0x%X\n"
		"  Start of program headers:          0x%X\n"
		
		"  Flags:                             0x%X\n"
		
		"  Size of program headers:           0x%X (bytes)\n"
		"  Number of program headers:         0x%X\n"*/
		,
	ehdr->e_machine, ehdr->e_ident[EI_CLASS],
    ehdr->e_type, ehdr->e_shoff,
    ehdr->e_shentsize, ehdr->e_shnum, ehdr->e_shstrndx,
    
    /*ehdr->e_ident[EI_DATA],
	ehdr->e_ident[EI_VERSION], ehdr->e_ident[EI_OSABI],
	ehdr->e_ident[EI_ABIVERSION], 
	ehdr->e_version, ehdr->e_entry,
	ehdr->e_phoff,  ehdr->e_flags,
	ehdr->e_ehsize, ehdr->e_phentsize, ehdr->e_phnum*/);
}