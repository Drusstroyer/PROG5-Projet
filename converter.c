#include "converter.h"

//converti un entier sur 4 octets de little endian a big endian
uint32_t convert32(uint32_t val){
    uint32_t converted = 0;
    converted |= ((0x000000ff & val) << 24);
    converted |= ((0x0000ff00 & val) << 8);
    converted |= ((0x00ff0000 & val) >> 8);
    converted |= ((0xff000000 & val) >> 24);

    return converted;
}

//converti un entier sur 2 octets de little endian a big endian
uint16_t convert16(uint16_t val){

    uint16_t converted = 0;
    converted = ((((val) >> 8) & 0xff) | (((val) & 0xff) << 8));

    return converted;

}