#include "Affiche_symbole.h"

void affiche_symbole(Elf32_Sym* symbole){
    //char* tab = malloc(sizeof(char)*20);
    printf("Name: %d\n", symbole->st_name);
    //sprintf(tab,"%x",symbole->st_name);
    //printf("Name: %s\n", tab);
}