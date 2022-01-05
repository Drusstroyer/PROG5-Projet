#ifndef AFFICHE_SYMBOLE_H
#define AFFICHE_SYMBOLE_H 
#include <elf.h>
#include <stdio.h>
#include <stdlib.h>
void affiche_symbole(Elf32_Sym* symbole);
#endif