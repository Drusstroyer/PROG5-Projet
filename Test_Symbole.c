#include "table_symbole.h"
#include "Affiche_symbole.h"
#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "converter.h"
#include "table_relocation_elf.h"

int main(int argc, char ** argv){
    FILE * f = fopen(argv[1],"rb");
    assert(f != NULL);
    table_symbole(f);
    //table_relocation(f);
    //assert(symbole != NULL);
    //affiche_symbole(symbole);
}