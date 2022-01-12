#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>


#include "entete_elf.h"
#include "Affiche_entete_elf.h"
#include "table_section_elf.h"
#include "read_section_elf.h"
#include "table_symbole.h"
#include "table_relocation_elf.h"
#include "converter.h"

Elf32_Ehdr* entete_elf(FILE * f){

    Elf32_Ehdr *ehdr = malloc(sizeof(Elf32_Ehdr));

    fseek(f,0,SEEK_SET);
    size_t n = fread(ehdr, 1, sizeof(Elf32_Ehdr), f);

    if (n != sizeof(Elf32_Ehdr)) {
		fprintf(stderr, "Impossible de lire le fichier\n");
		return NULL;
	}

    if (ehdr->e_ident[EI_MAG0] != ELFMAG0 ||
        ehdr->e_ident[EI_MAG1] != ELFMAG1 ||
        ehdr->e_ident[EI_MAG2] != ELFMAG2 ||
        ehdr->e_ident[EI_MAG3] != ELFMAG3
    ) {
        fprintf(stderr, "Mauvais format de fichier\n");
        return NULL;
    }

   if (ehdr->e_ident[EI_CLASS] != ELFCLASS32) {
		fprintf(stderr, "Pas en 32 bit ELF\n");
		return NULL;
	}
    /*
    if (ehdr->e_type != ET_NONE) {
		fprintf(stderr, "Pas de type de fichier défini\n");
		return NULL;
	}
    */
    return ehdr;

}




// option à passer en argument : -S affiche la table des sections
//                               -h affiche l'entete
//                               -x affiche le contenu de la section passé en argument après
// exemple d'utilisation : ./read_elf -S elf_linker-1.0/Examples_loader/example1.o
//                         ./read_elf -x 14 elf_linker-1.0/Examples_loader/example3.o
int main(int argc, char *argv[]){

    FILE *f;

    if (argc > 1){

        if(argv[argc-1] != NULL){
            
            f = fopen(argv[argc-1],"rb");

        }
    }
    else {
        printf("Veuillez passer un fichier existant en argument du programme.\n");
        return 0;
    }
    
    if(argc == 2){
        printf("Usage: ./read-elf <option> fichier ELF\n");
        printf(" Afficher les informations à propos du contenu du format des fichiers ELF\n Les options sont :\n");
        printf("    -h: Afficher l'en-tête du fichier elf\n");
        printf("    -S: Afficher l'en-tête des sections\n");
        printf("    -x <string>: Afficher le contenu de la section avec le nom <string> en hexadécimal.\n");
        printf("    -r: Afficher les réadressages (si présents)\n");
        printf("    -s: Afficher la table des symboles\n");
    }
    
    assert(f != NULL);
    char buf[1048576];
    fread(buf,sizeof buf,1,f);
    
    Elf32_Ehdr* header = entete_elf(f);

    assert(header != NULL);

    int was_a_sec = 0;

    for(int i = 1; i < argc - 1; i++){

        if(strcmp(argv[i],"-h")==0){

            elf_print_HDR(header);

        }
        else if(strcmp(argv[i],"-S")==0){

            section_elf(f, header);

        }
        else if(strcmp(argv[i],"-x")==0){
            
            char* sec_name = "";

            sec_name = argv[i + 1];

            if (strcmp(sec_name, "") != 0){
                read_section(f, header, sec_name);
            }
            else {
                printf("L'argument %s passé pour la section n'est pas valide\n", argv[i + 1]);
                return 0;
            }
            
            was_a_sec = 1;
        }else if(strcmp(argv[i],"-r")==0){

                table_relocation(f);

        }else if(strcmp(argv[i],"-s")==0){

                image_load(buf,sizeof(buf));
                //table_symbole(f);//AVANT

        }
        else 
        {
            if (was_a_sec == 0){

                printf("L'option %s n'existe pas.\n",argv[i]);
                was_a_sec = 0;

            }
        }
        
    }
    fclose(f);
    return 0;

}
