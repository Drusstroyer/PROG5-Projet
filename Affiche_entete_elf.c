#include "Affiche_entete_elf.h"

void elf_print_HDR(const Elf32_Ehdr *ehdr){

    /*printf(
		"ELF Header:\n"
        "  Machine:                           0x%X\n"
        "  Class:                             0x%X\n"
        "  Type:                              0x%X\n"
        "  Start of section headers:          0x%X\n"
        "  Size of section headers:           0x%X (bytes)\n"
		"  Number of section headers:         0x%X\n"
		"  Section header string table index: 0x%X\n\n"
        "  Size of this header:               0x%X (bytes)\n",
		
        
		"  Data:                              0x%X\n"
		"  Version:                           0x%X\n"
		"  OS/ABI:                            0x%X\n"
		"  ABI Version:                       0x%X\n"
		
		
		"  Version:                           0x%X\n"
		"  Entry point address:               0x%X\n"
		"  Start of program headers:          0x%X\n"
		
		"  Flags:                             0x%X\n"
		
		"  Size of program headers:           0x%X (bytes)\n"
		"  Number of program headers:         0x%X\n"
		
	ehdr->e_machine, ehdr->e_ident[EI_CLASS],
    ehdr->e_type, ehdr->e_shoff,
    ehdr->e_shentsize, ehdr->e_shnum, ehdr->e_shstrndx,
	ehdr->e_ehsize
    
    ehdr->e_ident[EI_DATA],
	ehdr->e_ident[EI_VERSION], ehdr->e_ident[EI_OSABI],
	ehdr->e_ident[EI_ABIVERSION], 
	ehdr->e_version, ehdr->e_entry,
	ehdr->e_phoff,  ehdr->e_flags,
	ehdr->e_ehsize, ehdr->e_phentsize, ehdr->e_phnum);*/
	printf("ELF HEADER:\n");
	switch(ehdr->e_machine){
		case 0x0E: printf("Machine: No Machine\n");break;
		case 0x1E: printf("Machine: AT&T WE 32100\n");break;
		case 0x2E: printf("Machine: SPARC\n");break;
		case 0x3E: printf("Machine: Intel Architecture\n");break;
		case 0x4E: printf("Machine: Motorola 68000\n");break;
		case 0x5E: printf("Machine: Motorola 88000\n");break;
		case 0x7E: printf("Machine: Intel 80860\n");break; 
		case 0x8E: printf("Machine: MIPS RS3000 Big-Endian\n");break;
		case 0x10E: printf("Machine: MIPS RS4000 Big-Endian\n");break;
		default: printf("Machine: Reserved for future use\n");break;
	}
	switch(ehdr->e_ident[EI_CLASS]){
		case ELFCLASSNONE: printf("Class: Invalid class\n");break;
		case ELFCLASS32: printf("Class: 32-bit objects\n");break;
		case ELFCLASS64: printf("Class: 64-bit objects\n");break;
    }
	switch(ehdr->e_type){
        case ET_NONE: printf("Type: No file type\n");break;
        case ET_REL: printf("Type: Relocatable file\n");break;
		case ET_EXEC: printf("Type: Executable file\n");break;
		case ET_DYN: printf("Type: Shared object file\n");break;
		case ET_CORE: printf("Type: Core file\n");break;
		case ET_LOPROC: printf("Type: Processor-specific LO\n");break;
		case ET_HIPROC: printf("Type: Processor-specific HI\n");break;
    }
	printf("Start of section headers: %0X\n", __builtin_bswap32(ehdr->e_shoff));
	printf("Size of section headers: %0X\n", ehdr->e_shentsize);
	printf("Number of section headers: %0X\n", ehdr->e_shnum);
	printf("Section header string table index: %0X\n",ehdr->e_shstrndx);
	printf("Size of this header: %0X (bytes)\n\n",ehdr->e_ehsize);

	switch(ehdr->e_ident[EI_DATA]){
		case ELFDATANONE: printf("Data: Invalid data encoding\n");break;
		case ELFDATA2LSB: printf("Data: LSB Encoding\n");break;
		case ELFDATA2MSB: printf("Data: MSB Encoding\n");break;
    }

	printf("Version: %0X\n", EV_CURRENT);
	printf("Entry point address: %0X\n", ehdr->e_entry);
	printf("Start of program headers: %0X\n",ehdr->e_phoff);
	printf("Flags: %0X\n", ehdr->e_flags);
	printf("Size of program headers: %0X (bytes)\n",ehdr->e_phentsize);
	printf("Number of program headers: %0x\n",ehdr->e_phnum);

	
}