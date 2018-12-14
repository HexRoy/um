#ifndef EXECUM_INCLUDED
#define EXECUM_INCLUDED
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bitpack.h"
#include "instruction.h"

//typedef struct T* T;
T newProg();
void runProg(T UM, const char* input);
void openFile(T UM,  const char* input);
void opcode_instructions(T UM, uint32_t instruct);
void freeUM(T* UM);

#endif



