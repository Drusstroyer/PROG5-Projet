#ifndef _CONVERTER_
#define _CONVERTER_
#include <stdint.h>
#include <stdio.h>
#include <elf.h>

//converti un entier sur 4 octets de little endian a big endian
uint32_t convert32(uint32_t val);

//converti un entier sur 2 octets de little endian a big endian
uint16_t convert16(uint16_t val);

int isNumber(char number[]);

#endif