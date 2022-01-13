#include "renumerotation.h"
#include "converter.h"

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

void copieelf(char* fin, char* fout) {
    int fd, fdout;
    char *src, *dst;
    size_t size;

    /* Ouvrir le fichier à copier */
    fd = open(fin, O_RDWR, 0666);
    if (fd < 0) {
        printf("Impossible d'ouvrir %s \n", fin);
        exit(EXIT_FAILURE);
    }

    /* Créer la copie */
    fdout = open(fout, O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (fdout < 0) {
        printf("Impossible d'ouvrir %s \n", fout);
        exit(EXIT_FAILURE);
    }

    /* Récupérer la taille du fichier à copier (pour mmap) */
    size = lseek(fd, 0, SEEK_END);
    //printf("size : %ld \n", size);
    ftruncate(fdout,size);

    lseek(fdout,size-1,SEEK_SET);
    write (fdout, "", 1);

    /* mmap du fichier à copier */
    if ((src = mmap(0, size, PROT_READ, MAP_SHARED, fd, 0)) == (caddr_t) -1) {
        printf ("Erreur de mapping pour %s\n", fin);
        exit(EXIT_FAILURE);
    }

    /* mmap de la copie */
    if ((dst = mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, fdout, 0)) == (caddr_t) -1) {
        printf("Code erreur : %d \n", errno);
        printf ("Erreur de mapping pour %s\n", fout);
        exit(EXIT_FAILURE);
    }

    /* copie mémoire d'un fichier vers l'autre */
    memcpy(dst,src,size);
    printf("Fichier bien copié \n");

    msync(src, size, MS_SYNC);
    msync(dst,size,MS_SYNC);
    munmap(src,size);
    munmap(dst,size);

    close(fd);
    close(fdout);
}

void supprsection(FILE* f){

     Elf32_Ehdr *ehdr = malloc(sizeof(Elf32_Ehdr));

     fseek(f,0,SEEK_SET);
     size_t n = fread(ehdr, 1, sizeof(Elf32_Ehdr), f);

     Elf32_Shdr shdr;

     ehdr = convertpointhdr(ehdr);
     fseek(f, ehdr->e_shoff + ehdr->e_shstrndx * ehdr->e_shentsize, SEEK_SET);
     fread(&shdr, 1, sizeof(shdr), f);
     shdr = convertshdr(shdr);

     char* type = "";

     for (int i = 0; i <= ehdr->e_shnum - 1; i++) {

         fseek(f,ehdr->e_shoff + i * sizeof(shdr), SEEK_SET);
         fread(&shdr, 1, sizeof(shdr), f);
         shdr = convertshdr(shdr);
         
         switch(shdr.sh_type){
            case SHT_REL: 
                type = "REL";
                char *mem;
                if ((mem = mmap(0, shdr.sh_size, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_SHARED, 0, 0)) == (caddr_t) -1) {
                    printf("Code erreur : %d \n", errno);
                    printf ("Erreur de mapping\n");
                    exit(EXIT_FAILURE);
                }
                memset(mem, 0, shdr.sh_size);
                msync(mem, shdr.sh_size, MS_SYNC);
                munmap(mem, shdr.sh_size);
            default: 
                type = "BALLEC";
                break;
         }
         
         printf("[Nr] : %d, type : %s \n", i, type);
     }
 }

int main (int argc, char *argv[]) {

    copieelf(argv[1],argv[2]);

    FILE *fp = fopen(argv[2],"rb");

    supprsection(fp);

    return 0;

}


   