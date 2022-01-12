#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "table_section_elf.h"
#include "converter.h"


void get_flags(char *flag, int val) {

  int i, j = 0;
  strcpy(flag, "");

  char flagChar[11] = {'T', 'G', 'O', 'L', 'I', 'S', 'M', 'X', 'A', 'W', ' '}; 
  int flagVal[11] = {0x400, 0x200, 0x100, 0x80, 0x40, 0x20, 0x10, 0x4, 0x2, 0x1, 0x0}; 

  for (i = 0; val > 0x0; i++) {
    if (val >= flagVal[i])
    {
      flag[j] = flagChar[i];
      val = val - flagVal[i];
      j++;
    }
  }
  flag[j] = '\0';
}


void reverse_str(char *str) {
  int n = strlen(str);

  for (int i = 0; i < n / 2; i++)
  {
    char ch = str[i];
    str[i] = str[n - i - 1];
    str[n - i - 1] = ch;
  }
}


void section_elf(FILE * f, Elf32_Ehdr *ehdr, int rel){

    Elf32_Shdr shdr;
    char flags[7] = "";

    ehdr = convertpointhdr(ehdr);
    fseek(f, ehdr->e_shoff + ehdr->e_shstrndx * ehdr->e_shentsize, SEEK_SET);
    fread(&shdr, 1, sizeof(shdr), f);
    shdr = convertshdr(shdr);

    //permet de récupérer le nom de la section
    char *SectNames = malloc(shdr.sh_size);
    fseek(f, shdr.sh_offset, SEEK_SET);
    fread(SectNames, 1, shdr.sh_size, f);

    if (rel == 0) {
      printf("Il y a %d section headers, commençant à l'offset 0x%x:\n\n", ehdr->e_shnum, ehdr->e_shoff);
    }
    else {
      printf("Affichage des section headers, commençant à l'offset 0x%x:\n\n", ehdr->e_shoff);
    }

    printf("Section Headers:\n  [Nr] Name                Type             Address "
           "          Offset     Size     EntSize  Flags   "
           "Link  Info Align\n");

    int cmpt = 0;

    for (int i = 0; i <= ehdr->e_shnum - 1; i++) {  

      char* name = "";
      char* type = "";

      fseek(f,ehdr->e_shoff + i * sizeof(shdr), SEEK_SET);
      fread(&shdr, 1, sizeof(shdr), f);
      shdr = convertshdr(shdr);

      //nom de la section i
      name = SectNames + shdr.sh_name;

      //flags de la section i
      get_flags(flags, shdr.sh_flags);
      reverse_str(flags);

      if (rel != 0) {
        if (shdr.sh_type == SHT_RELA || shdr.sh_type == SHT_REL) {
          cmpt+=1;
          continue;
        }
      }
        
      //type de la section i
      switch(shdr.sh_type){
          case SHT_PROGBITS: type = "PROGBITS";
            break;
          case SHT_SYMTAB: type = "SYMTAB";
            break;
          case SHT_DYNSYM: type = "DYNSYM";
            break;
          case SHT_STRTAB: type = "STRTAB";
            break;
          case SHT_RELA: type = "RELA";
            break;
          case SHT_HASH: type = "HASH";
            break;
          case SHT_DYNAMIC: type = "DYNAMIC";
            break;
          case SHT_NOTE: type = "NOTE";
            break;
          case SHT_NOBITS: type = "NOBITS";
            break;
          case SHT_REL: type = "REL";
            break;
          case SHT_SHLIB: type = "SHLIB";
            break;
          case SHT_LOPROC: type = "LOPROC";
            break;
          case SHT_HIPROC: type = "HIPROC";
            break;
          case SHT_LOUSER: type = "LOUSER";
            break;
          case SHT_HIUSER: type = "HIUSER";
            break;
          default: type = "NULL";
            break;
        }

        //affichage des sections
        printf("  [%2d] %-18s %-17s %016x  0x%08X %08x %08x %-7s %-5d %-3d  %d\n", i-cmpt, name, type, convert32(shdr.sh_addr), 
                shdr.sh_offset, shdr.sh_size, shdr.sh_entsize, 
                flags, shdr.sh_link, shdr.sh_info, shdr.sh_addralign);
      }   

    printf("\n");
    printf("Flags: W (write), A (alloc), X (execute), M (merge), S (strings), I (info), \n L (link order), O (extra OS processing required), G (group), T (TLS), \n C (compressed), x (unknown), o (OS specific), E (exclude),\n (purecode), p (processor specific) \n");

}