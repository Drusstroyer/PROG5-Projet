#include "Affiche_entete_elf.h"
#include "converter.h"

void elf_print_HDR(Elf32_Ehdr *ehdr){
	ehdr = convertpointhdr(ehdr);
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
		case 0x28E: printf("Machine: ARM\n");break;
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
	printf("Début des en-tetes de section: %0d (octets dans le fichier)\n", ehdr->e_shoff);
	printf("Taille des en-tetes de section: %0d (octets)\n", ehdr->e_shentsize);
	printf("Nombre d'en-tetes de section: %0d\n", ehdr->e_shnum);
	printf("Table d'index des chaines d'en-tete de section: %d\n",ehdr->e_shstrndx);
	printf("Taille de cet en-tete: %d (bytes)\n\n",ehdr->e_ehsize);

	switch(ehdr->e_ident[EI_DATA]){
		case ELFDATANONE: printf("Data: Invalid data encoding\n");break;
		case ELFDATA2LSB: printf("Data: LSB Encoding (little endian)\n");break;
		case ELFDATA2MSB: printf("Data: MSB Encoding (big endian)\n");break;
    }

	printf("Version: %0X\n", EV_CURRENT);
	printf("Adresse du point d'entree: 0x%0X\n", ehdr->e_entry);
	printf("Debuts des en-tetes de programme: %d (octets dans le fichier)\n",ehdr->e_phoff);
	printf("Flags: 0x%0X\n", ehdr->e_flags);
	printf("Taille de l'en-tete du programme: %d (octets)\n",ehdr->e_phentsize);
	printf("Nombre d'en-tete du programme: %d\n\n",ehdr->e_phnum);

	
}