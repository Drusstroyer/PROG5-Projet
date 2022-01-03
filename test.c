#include  <stdio.h>
#include <assert.h>

#include "entete_elf.h"
#include "Affiche_entete_elf.h"

int main(int argc, char *argv[]){

    FILE *f = fopen(argv[1],"rb");

    assert(f == NULL);

    Elf32_Ehdr* header = entete_elf(f);

    assert(header == NULL);

    elf_print_HDR(header);

    return 0;

}