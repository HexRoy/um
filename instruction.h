#ifndef INSTRUCTION_INCLUDED
#define INSTRUCTION_INCLUDED
#include <math.h>
#include <stdio.h>
#include "segment.h"
//#include "execUM.h"
//OPCODE 0
void conmove(uint32_t a, uint32_t b, uint32_t c, uint32_t *r);

//OPCODE 1
void segload(uint32_t a, uint32_t b, uint32_t c, uint32_t *r, T segment_memory);

//OPCODE 2
void segstore(uint32_t a, uint32_t b, uint32_t c, uint32_t *r, T segment_memory);

//OPCODE 3
void add(uint32_t a, uint32_t b, uint32_t c, uint32_t *r);

//OPCODE 4
void multiply(uint32_t a, uint32_t b, uint32_t c, uint32_t *r);

//OPCODE 5
void divide(uint32_t a, uint32_t b, uint32_t c, uint32_t *r);

//OPCODE 6
void nand(uint32_t a, uint32_t b, uint32_t c, uint32_t *r);

//OPCODE 7
void halt();

//OPCODE 8
void mapseg(uint32_t b, uint32_t c, uint32_t *r , T segment_memory);

//OPCODE 9
void unmapseg(uint32_t c, uint32_t *r, T segment_memory);

//OPCODE 10
void output(uint32_t c, uint32_t *r);

//OPCODE 11
void input(uint32_t c, uint32_t *r);

//OPCODE 12
void load(uint32_t b, uint32_t c, uint32_t *r, T segment_memory);

//OPCODE 13
void loadval(uint32_t a, uint32_t val, uint32_t *r);

#endif
