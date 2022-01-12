#include "renumerotation.h"

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <sys/mman.h>

int main (int argc, char *argv[]) {

    FILE *fdin, *fdout;
    char *src, *dst;
    int size;

    /* Ouvrir le fichier à copier */
    fdin = fopen(argv[1], "rb");
    assert(fdin != NULL);

    /* Créer la copie */
    fdout = fopen(argv[2],"w");
    assert(fdout != NULL);

    /* Récupérer la taille du fichier à copier (pour mmap) */
    fseek(fdin, 0, SEEK_END);
    size = ftell(fdin);
    fseek(fdin,0,SEEK_END);
    printf("%d \n",size);

    /* Aller au dernier bit de la copie */
    fseek(fdout,size-1,SEEK_SET);

    /* Ecrire un bit d'initialisation */
    char* c = "";
    fwrite(c, sizeof(char*), 1, fdout);

    /* mmap du fichier à copier */
    src = mmap(0, size, PROT_READ, MAP_SHARED, 0, 0);

    /* mmap de la copie */
    dst = mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, 0, 0);

    /* copie mémoire d'un fichier vers l'autre */
    memcpy(dst, src, size);

    fclose(fdin);
    fclose(fdout);

    return 0;

}


   