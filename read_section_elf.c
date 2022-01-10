#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1000

#include "read_section_elf.h"
#include "converter.h"


//PB AU NIVEAU DE L'AFFICHAGE DU NOM DE LA SECTION EXAMINEE
void read_section(FILE * f, Elf32_Ehdr *ehdr, char* m){

    Elf32_Shdr shdr;
    int n = 0;

    if(isNumber(m) == 0){
        n = atoi(m);
    }

    fseek(f, convert32(ehdr->e_shoff) + convert16(ehdr->e_shstrndx) * convert16(ehdr->e_shentsize), SEEK_SET);
    fread(&shdr, 1, sizeof(shdr), f);

    //si on passe le nom et pas le numéro
    if( n == 0) {
        
        char *SectionNames = malloc(convert32(shdr.sh_size));
        fseek(f, convert32(shdr.sh_offset), SEEK_SET);
        fread(SectionNames, 1, convert32(shdr.sh_size), f);

        char* tabSection[convert16(ehdr->e_shnum) - 1];

        for(int i = 0; i <= convert16(ehdr->e_shnum) - 1; i++){
            char* name = "";
            fseek(f,convert32(ehdr->e_shoff) + i * sizeof(shdr), SEEK_SET);
            fread(&shdr, 1, sizeof(shdr), f);

            name = SectionNames + convert32(shdr.sh_name);

            tabSection[i] = name;
        }

        char * dot = ".";
        char* sect = malloc(strlen(dot) + strlen(m) + 1);
            
        strcpy(sect, dot);
        strcat(sect, m);

        for(int j = 0; j <= convert16(ehdr->e_shnum) - 1; j++){
            if (strcmp(tabSection[j], sect) == 0) {
                n = j;
            }
        }
    }    

    fseek(f,convert32(ehdr->e_shoff) + n * sizeof(shdr), SEEK_SET);
    fread(&shdr, 1, sizeof(shdr), f);

    char *SectNames = malloc(convert32(shdr.sh_size));
    fseek(f, convert32(shdr.sh_offset), SEEK_SET);
    fread(SectNames, 1, convert32(shdr.sh_size), f);

    char* name = "";
    name = SectNames + convert32(shdr.sh_name);

    char section[MAX];
    char tradASCII[MAX] = "";
    char temp[10];
    
    printf("Hex dump of section '%s': \n",name);

    int cmpt = 0;
    int cmptAddr = 0;  
    printf("  0x%08d", cmptAddr);

    for(int i = convert32(shdr.sh_offset) ; i < convert32(shdr.sh_offset) + convert32(shdr.sh_size) ; i++){
        if (cmpt%16 == 0 && cmpt != 0) {                                //retour à la ligne tous les quatre blocs affichés (format du readelf)
        
            printf("  %s", tradASCII);
            strcpy(tradASCII, "");
            printf("\n");
            cmptAddr+=10;                                           
            printf("  0x%08d",cmptAddr);                                //nouvelle adresse à gauche        
        }
        if (cmpt%4 == 0) {                                              //espace tous les blocs de 4 affichés (format du readelf)
            printf(" ");
            fseek(f, i, SEEK_SET);
            fread(section, 1, convert32(shdr.sh_size), f);
            if (*section == 0) {
                strcat(tradASCII, ".");
            }
            else {
                snprintf(temp, sizeof(section), "%c", *section);   
                strcat(tradASCII, temp);  
            }
            printf("%02X", *section);
        }
        else {
            fseek(f, i, SEEK_SET);
            fread(section, 1, convert32(shdr.sh_size), f);
            if ((int) *section < 33 || (int) *section > 126) {
                strcat(tradASCII, ".");
            }
            else {
                snprintf(temp, sizeof(section), "%c", *section);
                strcat(tradASCII, temp);
            }     
            printf("%02X",*section);
        }
        cmpt+=1;
    }
    printf("  %s", tradASCII);
    printf("\n");
}       
