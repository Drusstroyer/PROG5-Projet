#include "bit_operations.h"

char get_bit(int32_t value, int position) {
    return (value >> position) & 1;
}

int32_t set_bit(int32_t value, int position) {
    return value | (1 << position);
}

int32_t clr_bit(int32_t value, int position) {
    return value & ~(1 << position);
}
