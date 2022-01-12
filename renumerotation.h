#include <stdio.h>
#include <assert.h>
#include <elf.h>

#ifndef _RENUMEROTATION_SECTION_
#define _RENUMEROTATION_SECTION_

void copieelf(char* fin, char* fout);
void supprsection(FILE *f);

#endif