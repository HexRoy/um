#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Initialized registers
static uint32_t r[8] = {0,0,0,0,0,0,0,0};

//initialize program counter
static int prgcntr = 0;
