#include "converter.h"

uint32_t convert32(uint32_t val){
    //  printf("Value Before Converting = 0x%x\n", val);
     uint32_t converted = 0;
     converted |= ((0x000000ff & val) << 24);
     converted |= ((0x0000ff00 & val) << 8);
     converted |= ((0x00ff0000 & val) >> 8);
     converted |= ((0xff000000 & val) >> 24);

    //  printf("Value After Converting = 0x%x\n", converted);
     return converted;
}

uint16_t convert16(uint16_t val){
    //  printf("Value Before Converting = 0x%x\n", val);
     uint16_t converted = 0;
     converted = ((((val) >> 8) & 0xff) | (((val) & 0xff) << 8));

    //  printf("Value After Converting = 0x%x\n", converted);
    return converted;
}