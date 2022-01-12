#include "renumerotation.h"

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <elf.h>
#include <converter.h>

int main (int argc, char *argv[]) {

    //FILE *fdin, *fdout;
    char *src, *dst;
    size_t size;
    int fd,fdout;

    /* Ouvrir le fichier à copier */
    fd = open(argv[1], O_RDWR);
    //assert(fdin != NULL);

    /* Créer la copie */
    fdout = open(argv[2],O_RDWR | O_CREAT,0666);
    //assert(fdout != NULL);
    /* Récupérer la taille du fichier à copier (pour mmap) */
    size = lseek(fd, 0, SEEK_END);
    //size = ftell(fd);
    //lseek(fd,0,SEEK_END);
    printf("%ld \n",size);
    ftruncate(fdout,size);
    src = mmap(0, size, PROT_READ, MAP_SHARED, fd, 0);
    dst = mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, fdout, 0);
    memcpy(dst, src, size);
    
    Elf32_Ehdr* hdr = NULL;
    Elf32_Shdr* shdr = NULL;
    shdr = (Elf32_Shdr * ) (dst + convert32(hdr->e_shoff));
    //fseek(fdout,0,SEEK_SET);
    //fwrite(&src,1,sizeof(src),fdout);
    /* Aller au dernier bit de la copie */
    //fseek(fdout,size-1,SEEK_SET);

    /* Ecrire un bit d'initialisation */
    //char* c = "";
    //fwrite(c, sizeof(char*), 1, fdout);

    /* mmap du fichier à copier */
    //src = mmap(0, size, PROT_READ, MAP_SHARED, 0, 0);

    /* mmap de la copie */
    //dst = mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, 0, 0);

    /* copie mémoire d'un fichier vers l'autre */
    //memcpy(dst, src, size);

    /*close(fdin);
    close(fdout);
    */
    return 0;

}


   