#ifndef BITPACK_INCLUDED
#define BITPACK_INCLUDED
#include <stdbool.h>
#include <stdint.h>
#include <math.h>
#include "except.h"
#include "assert.h"

uint64_t shl(uint64_t word, unsigned bits);
uint64_t shr(uint64_t word, unsigned bits);
uint64_t shr(uint64_t word, unsigned bits);
bool Bitpack_fitsu(uint64_t n, unsigned width);
bool Bitpack_fitss( int64_t n, unsigned width);
uint64_t Bitpack_getu(uint64_t word, unsigned width, unsigned lsb);
int64_t Bitpack_gets(uint64_t word, unsigned width, unsigned lsb);
uint64_t Bitpack_newu(uint64_t word, unsigned width, unsigned lsb, uint64_t value);
uint64_t Bitpack_news(uint64_t word, unsigned width, unsigned lsb, int64_t value);
extern Except_T Bitpack_Overflow;
#endif
