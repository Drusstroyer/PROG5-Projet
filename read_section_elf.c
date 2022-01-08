#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1000

#include "read_section_elf.h"
#include "converter.h"


//penser a faire de la robustesse
void read_section(FILE * f, Elf32_Ehdr *ehdr, int n){

    Elf32_Shdr shdr;

    fseek(f, convert32(ehdr->e_shoff) + convert16(ehdr->e_shstrndx) * convert16(ehdr->e_shentsize), SEEK_SET);
    fread(&shdr, 1, sizeof(shdr), f);

    fseek(f,convert32(ehdr->e_shoff) + n * sizeof(shdr), SEEK_SET);
    fread(&shdr, 1, sizeof(shdr), f);

    char *SectNames = malloc(convert32(shdr.sh_size));
    fseek(f, convert32(shdr.sh_offset), SEEK_SET);
    fread(SectNames, 1, convert32(shdr.sh_size), f);
            
    // printf("offset : %X \n", convert32(shdr.sh_offset));
    // printf("size : %X \n", convert32(shdr.sh_size));

    char* name = "";
    name = SectNames + convert32(shdr.sh_name);

    unsigned char section[MAX];

    printf("Hex dump of section '%s': \n",name);

    int cmpt = 0;
    int cmptAddr = 0;  
    printf("  0x%08d", cmptAddr);

    for(int i = convert32(shdr.sh_offset) ; i < convert32(shdr.sh_offset) + convert32(shdr.sh_size) ; i++){
        if (cmpt%16 == 0 && cmpt != 0) {                                //retour à la ligne tous les quatre blocs affichés (format du readelf)
            printf("\n");
            cmptAddr+=10;                                           
            printf("  0x%08d",cmptAddr);                                //nouvelle adresse à gauche        
        }
        if (cmpt%4 == 0) {                                              //espace tous les blocs de 4 affichés (format du readelf)
            printf(" ");
            fseek(f, i, SEEK_SET);
            fread(section, 1, convert32(shdr.sh_size), f);
            printf("%02X", *section);
        }
        else {
            fseek(f, i, SEEK_SET);
            fread(section, 1, convert32(shdr.sh_size), f);
            printf("%02X",*section);
        }
        cmpt+=1;
    }

    printf("\n");
}       
