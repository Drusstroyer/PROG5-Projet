#include "converter.h"

uint32_t convert32(uint32_t val){
    uint32_t converted = 0;
    converted |= ((0x000000ff & val) << 24);
    converted |= ((0x0000ff00 & val) << 8);
    converted |= ((0x00ff0000 & val) >> 8);
    converted |= ((0xff000000 & val) >> 24);
    return converted;
}

uint16_t convert16(uint16_t val){
    uint16_t converted = 0;
    converted = ((((val) >> 8) & 0xff) | (((val) & 0xff) << 8));
    return converted;
}

int isNumber(char number[])
{
    int i = 0;

    //checking for negative numbers
    if (number[0] == '-')
        i = 1;
    for (; number[i] != 0; i++)
    {
        //if (number[i] > '9' || number[i] < '0')
        if (!isdigit(number[i]))
            return 1;
    }
    return 0;
}